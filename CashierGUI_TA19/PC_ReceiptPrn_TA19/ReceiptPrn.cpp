// ReceiptPrn.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "math.h"
#include "ReceiptPrn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _CHINESE_RECEIPT_
#define _TRADITIONAL_CHINESE_
static AFX_EXTENSION_MODULE ReceiptPrnDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("RECEIPTPRN.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ReceiptPrnDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(ReceiptPrnDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("RECEIPTPRN.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ReceiptPrnDLL);
	}
	return 1;   // ok
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CompareDbl(double value1, double value2)
{
	if (fabs(value1 - value2) < 0.00001) return 0;
	if (value1 > value2) return 1;
	else return -1;
}

#define PAPER_WIDTH 40
CReceiptPrn::CReceiptPrn(CString PortName, CString Starter[], CString Ending[], int leftspc, int linespc, int cutline,
				CString TaxName, CString TaxNo, int TaxPerc, int StationID, long DevID)
{
	HANDLE tmphdl;
	pfile = NULL;
	m_dwErrCode = 0;
	m_isDeviceOK = FALSE;
	m_RPrn = NULL;
	if ((tmphdl = OpenRPrn(PortName)) != NULL ) m_RPrn = tmphdl;
	else return;
	m_nStationID = StationID;
	m_lpStarter[0] = Starter[0]; 
	m_lpStarter[1] = Starter[1]; 
	m_lpStarter[2] = Starter[2];
	m_lpEnding[0] = Ending[0]; 
	m_lpEnding[1] = Ending[1];
	m_nLeftSpc = leftspc; 
	m_nLineSpc = linespc; 
	m_nCutLine = cutline;
	m_lpTaxName = TaxName; 
	m_lpTaxNo = TaxNo; 
	m_nTaxPerc = TaxPerc;
	m_isDeviceOK = TRUE;
	m_DevID = DevID;
	pfile = new CFile;
	bChineseAvailable = FALSE;
#ifdef _CHINESE_RECEIPT_	
#ifdef _TRADITIONAL_CHINESE_
	if (!pfile->Open("c:\\hzk16f", CFile::modeRead, 0))
#else
	if (!pfile->Open("c:\\hzk24k", CFile::modeRead, 0))
#endif
	{
		::AfxMessageBox("Cannot load Chinese font library!");
		bChineseAvailable = FALSE;
		pfile = NULL;
		m_isDeviceOK = FALSE;
	}
	else bChineseAvailable = TRUE;
#endif

	AuxReset();
	SendtoPrn("\033%%\01", 3);
	SetLineSpace(12); 
	//SetCharSpace(3);
	CharsReverse(FALSE);
	SetCharSpace(0);

	
}



CReceiptPrn::~CReceiptPrn() {
	CloseRPrn();
	if (pfile) delete pfile;
}


//print account information
BOOL CReceiptPrn::PrintShiftCloseReceipt(CString Operator, LONG ReceiptNo, COleDateTime DutyStart, int PayNum, double CashAmt, double CCAmt, double SVAmt, double ShiftCashMaintain)
{
	if ((m_RPrn == NULL) || (!m_isDeviceOK)) return 1;
	char abuf[80];
	::ZeroMemory(abuf, 80);
	//Title
	PurgeComm(m_RPrn, PURGE_TXCLEAR|PURGE_RXCLEAR);
/////////////////////////////////////////////////////////////heading
/*	SendtoPrn("       ",6);      
	if (!CharsReverse(TRUE)) return 3; 
    if (!CharSize(1, 1)) return 2;
    PrintChineseChar(-1410);    // " " 
	PrintChineseChar(150*17+12);//佴   斯
	PrintChineseChar(103*17+14);//鎖   瑪
	PrintChineseChar(99*17+9);//癒     隆
	PrintChineseChar(172*17+10);//炵   系
	PrintChineseChar(161*17+7);//苀    統
	if (!PrintLine(" ", 0)) return 8;
/////////////////////////////////////////////////////////[JC] 20060303
*/	if (!CharsReverse(FALSE)) return 5;
	if (!CharSize(0, 0)) return 2;

	if (!PrintHeader()) return 7; // print "----------"

	PrintLSpc();
	PrintChineseChar(160*17+8);//        停		
	PrintChineseChar(17 * 17+ 13);//     車
	PrintChineseChar(1692-1410);//       場
	PrintChineseChar(2470-1410);
	PrintChineseChar(1473-1410);
	PrintChineseChar(2696-1410);
	PrintChineseChar(4930-1410);
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據

	if (!PrintLine(" ", 0)) return 8;
	if (!PrintLine("  CASHIER SHIFT CLOSE ACCOUNT RECEIPT", 0)) return 8;
	
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;
	
	
	///////Body-Status///////////////////////

	PrintLSpc();
    PrintChineseChar(123);       //桴   本
	PrintChineseChar(206*17 + 5);//桴   站
	PrintChineseChar(57 *17 + 7);//瘍   號
	PrintChineseChar(103 *17 + 15);//鎢 碼

	sprintf(abuf, " Station No.   : %02d\0", m_nStationID); 

	if (!PrintLine(abuf, 0)) return 8;

//Device ID
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(66 *17 + 1);//      機
	PrintChineseChar(57 *17 + 7);//瘍    號
//	sprintf(abuf, " Device No.  : %d\0", m_DevID);
	sprintf(abuf, " Device No.  : %x\0", m_DevID);//new TA
	if (!PrintLine(abuf, 0)) return 10;


	PrintLSpc();
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼

	sprintf(abuf, " Receipt No.   : %08d\0", ReceiptNo); 
	if (!PrintLine(abuf, 0)) return 9;

	PrintLSpc();
	PrintChineseChar(2259-1410);
	PrintChineseChar(5162-1410);
	PrintChineseChar(3708-1410);
	PrintChineseChar(4810-1410);
	sprintf(abuf, " Operator      : %s\0", Operator); 
	if (!PrintLine(abuf, 0)) return 9;
/*	
	PrintLSpc();
	PrintChineseChar(2829-1410);
	PrintChineseChar(4930-1410);
	PrintChineseChar(144*17 +12);//奀  時
	PrintChineseChar(70 *17 + 5);//潔  間
	sprintf(abuf, " : %02d-%02d-%04d %02d:%02d \0", DutyStart.GetDay(), DutyStart.GetMonth(), DutyStart.GetYear(), DutyStart.GetHour(), DutyStart.GetMinute());
	if (!PrintLine(abuf, 0)) return 13;
*/
	PrintLSpc();
	PrintChineseChar(2696-1410);
	PrintChineseChar(4930-1410);
	PrintChineseChar(144*17 +12);//奀  時
	PrintChineseChar(70 *17 + 5);//潔  間
	COleDateTime x = COleDateTime::GetCurrentTime();
	sprintf(abuf, " S.Close Time  : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());
	if (!PrintLine(abuf, 0)) return 13;

	PrintLSpc();
	PrintChineseChar(2183-1410);
	PrintChineseChar(2116-1410);
	PrintChineseChar(1831-1410);//
	PrintChineseChar(3946-1410);//
	sprintf(abuf, " Payment Times : %d\0", PayNum);
	if (!PrintLine(abuf, 0)) return 13;

	//Account info
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;
	PrintLSpc();
	PrintChineseChar(4377-1410);//葆     現    
	PrintChineseChar(76 *17 +9);//       金
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(137*17 + 1);//��    入

	sprintf(abuf, " Cash Income   : $%12.2f", CashAmt);
	if (!PrintLine(abuf, 0)) return 9;
	
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(137*17 + 1);//��    入
	sprintf(abuf, " Octopus Income: $%12.2f", CCAmt);
	if (!PrintLine(abuf, 0)) return 9;
	PrintLSpc();
	PrintChineseChar(22 *17 + 3);//揣 儲
	PrintChineseChar(211*17 + 5);//硉 值
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(137*17 + 1);//��    入
	sprintf(abuf, " S. V. Income  : $%12.2f", SVAmt);
	if (!PrintLine(abuf, 0)) return 9;
	
//	if (!PrintLine(" ", 0)) return 8;

	CharsBold(TRUE); 
	PrintLSpc();
	/*
	PrintChineseChar(2696-1410);
	PrintChineseChar(4763-1410);
	PrintChineseChar(2396-1410);
	PrintChineseChar(2575-1410);
    */
	PrintChineseChar(1828-1410); // 此
	PrintChineseChar(2253-1410); // 更
	PrintChineseChar(146*17 +14);// 彶   收
	PrintChineseChar(137*17 + 1);//��    入

	sprintf(abuf, " Shift Amount  : $%12.2f", CashAmt + CCAmt + SVAmt);
	if (!PrintLine(abuf, 0)) return 9;
	CharsBold(FALSE);


	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;	
	CharsBold(TRUE); 
	PrintLSpc();
	
	PrintChineseChar(4106-1410); // 提
	PrintChineseChar(3666-1410); // 取
	PrintChineseChar(4377-1410); // 葆    現    
	PrintChineseChar(76 *17 +9); //       金

	sprintf(abuf, " Cash Maintain : $%12.2f", ShiftCashMaintain);
	if (!PrintLine(abuf, 0)) return 9;

//	PrintLine(abuf, FALSE);
	CharsBold(FALSE);
	
	///////Tailer///////////////////////////
	//Tax info
	if (!PrintEnding()) return 23; //print "-----------"
	//cut paper
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	if (!AuxFullCut()) return 25;
	return 0;
}

//after manually open barrier by pressing the barrier button
BOOL CReceiptPrn::PrintBarrierReceipt(CString Operator, CTime Time, CString Reason)
{
	if (!m_isDeviceOK || !m_RPrn) return 1;
	PurgeComm(m_RPrn,  PURGE_TXCLEAR|PURGE_RXCLEAR);
	if (!PrintFeedBack(80)) return 2;
	if (!CharsReverse(TRUE)) return 3;
	if (!PrintLine(_T("Barrier Action"), FALSE)) return 4;
	if (!CharsReverse(FALSE)) return 5;
	CString abuf;
	//station id
	abuf.Format(_T("Station : %02d"), m_nStationID); 
	if (!PrintLine(abuf, FALSE)) return 6;
	//operator
	if (!Operator.IsEmpty())	{
		abuf.Format(_T("Operator: %s"), Operator); 
		if (!PrintLine(abuf, FALSE)) return 7;
	}
	//Time
	abuf.Format(_T("Time    : %02d:%02d %02d/%02d"), Time.GetHour(), Time.GetMinute(), Time.GetDay(), Time.GetMonth());
	if (!PrintLine(abuf, FALSE)) return 8;
	if (!PrintLine(_T("-----Reason------"), TRUE)) return 9;
	if (!PrintLine(_T("Press barrier button"), TRUE)) return 10;
	if (!PrintFeed(150)) return 11;
	if (!AuxFullCut()) return 12;
	return 0;
}



//print parking reciept   // damage payment check point 009 (receipt)
BOOL CReceiptPrn::PrintParkingReceipt(LONG ReceiptNo, 
									  LPSTR CAN, 
									  LPSTR PaymentCAN, 
									  BOOL IsReply,
									  LPSTR Cate, 
									  double EnterTime,
									  double LastPayTime,
									  double PayTime,
									  LPSTR DiscountStr,
									  double fFareCardAmt, 
									  double fFareCardBal,
									  double fStoreValueAmt, 
									  double fStoreValueBal,
									  double ReceiptCash, 
									  double ReceiptChange,
									  short  VehicleType,
									  CString R)//For TA18- AddValue info "2017-03-13x"
{
	if ((m_RPrn == NULL) || (!m_isDeviceOK)) return 1;
//	MessageBox(NULL,R,"",0);
	char abuf[80];
	::ZeroMemory(abuf, 80);
	//Title
	PurgeComm(m_RPrn, PURGE_TXCLEAR|PURGE_RXCLEAR);
	//if (!PrintFeedBack(80)) return 2;
	
	OpenDrawer();	
	
//#ifdef _CHINESE_RECEIPT_	
//	PrintLSpc();

//////////////////////////////////////////////////////////heading
/*	SendtoPrn("         ",8);      

	if (!CharsReverse(TRUE)) return 3; 
    if (!CharSize(1, 1)) return 2;
    PrintChineseChar(-1410);    // " " 
	PrintChineseChar(150*17+12);//佴   斯
	PrintChineseChar(103*17+14);//鎖   瑪
	PrintChineseChar(99*17+9);//癒     隆
	PrintChineseChar(172*17+10);//炵   系
	PrintChineseChar(161*17+7);//苀    統
	if (!PrintLine(" ", 0)) return 8;
////////////////////////////////////////////////////////////[JC] 20060303
*/	if (!CharsReverse(FALSE)) return 5;
	if (!CharSize(0, 0)) return 2;

	//SendtoPrn("  ",2);    
	//PrintLine(" ", 0);
//#else
//	if (!CharSize(1, 1)) return 2;
//	if (!CharsReverse(TRUE)) return 3; 
//	if (!PrintLine(_T("SMARON System"), 1)) return 4; 
//	if (!CharsReverse(FALSE)) return 5;
//	if (!CharSize(0, 0)) return 2;
//#endif
	
	//if (!PrintLine(" ", 1)) return 6;
/*Station No.
Receipt No
Mag-Tkt No.
Octopus No
Pay Method
Park Type
Entry Time
Last Paymt
Paymt Time
Park Fee  
Discount 
Amount Due
Paid
Change
Remain Val
Octopus Paid*/

	if (!PrintHeader()) return 7; // print "----------"


	PrintLSpc();
	PrintChineseChar(160*17+8);//        停		
	PrintChineseChar(17 *17 + 13);//     車
	PrintChineseChar(1692-1410);//       場
	PrintChineseChar(146*17+14);//	     收	 
	PrintChineseChar( 41*17+ 9);//       費
	PrintChineseChar(1791-1410);//       處
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	if (!PrintLine(" ", 0)) return 8;
	if (!PrintLine("  CARPARK CASHIER RECEIPT", 0)) return 8;
	
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
    PrintChineseChar(123);       //桴    本
	PrintChineseChar(206*17 + 5);//桴    站
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Station No.   : %02d\0", m_nStationID); 
	if (!PrintLine(abuf, 0)) return 8;

//Device ID

	if (!((fFareCardAmt-ReceiptCash+ReceiptChange) == 0)) //pay by cash only
	{
		PrintLSpc();
		PrintChineseChar(2 *17 + 8);//縐     八		
		PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(66 *17 + 1);//      機
		PrintChineseChar(57 *17 + 7);//瘍    號

//		sprintf(abuf, " Device No.  : %d\0", m_DevID);
		sprintf(abuf, " Device No.  : %x\0", m_DevID); //new TA
		if (!PrintLine(abuf, 0)) return 10;
	}

//receipt no
	PrintLSpc();
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Receipt No.   : %08d\0", ReceiptNo); 
	if (!PrintLine(abuf, 0)) return 9;
//#endif

//card no
if (CAN[0] == 'O')
{
//	#ifndef _CHINESE_RECEIPT_
//		sprintf(abuf, "Card NO: %s\0", CAN); 
//		if (!PrintLine(abuf, FALSE)) return 10;
//	#else
//		if (!PrintLine("  Octopus Card No.", 0)) return 8;

		PrintLSpc();
		PrintChineseChar(2 *17 + 8);//縐     八		
		PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(83 *17 + 6);//縐    卡
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Octopus Card No.: %s\0", CAN+1);
		if (!PrintLine(abuf, 0)) return 10;
//	#endif
}
else if (CAN[0] == 'P')
{
//	#ifndef _CHINESE_RECEIPT_
//		sprintf(abuf, "Card NO: %s\0", CAN); 
//		if (!PrintLine(abuf, FALSE)) return 10;
//	#else
//		if (!PrintLine("  Paper Ticket No.", 0)) return 8;

		PrintLSpc();
		PrintChineseChar(412);//縐           磁
		PrintChineseChar(122 *17 + 10);//縐  票  
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Ticket No.    : %s\0", CAN);
		if (!PrintLine(abuf, 0)) return 10;
//	#endif
}
else if (CAN[0] == 'B')
{
	//	#ifndef _CHINESE_RECEIPT_
	//		sprintf(abuf, "Card NO: %s\0", CAN); 
	//		if (!PrintLine(abuf, FALSE)) return 10;
	//	#else
	//		if (!PrintLine("  Paper Ticket No.", 0)) return 8;
	
	PrintLSpc();
//	PrintChineseChar(412);//縐           磁
	PrintChineseChar(122 *17 + 10);//縐  票  
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Ticket No.    : %s\0", CAN);
	if (!PrintLine(abuf, 0)) return 10;
	//	#endif
}
else if (CAN[0] == 'D') // Damage Ticket
{
        PrintLSpc();
//		PrintChineseChar(412);//縐           磁
		PrintChineseChar(122 *17 + 10);//縐  票  
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Ticket No.    : %s", CAN);
		if (!PrintLine(abuf, 0)) return 10;
}
else if (CAN[0] == 'L') // Lost Ticket
{
        PrintLSpc();
//		PrintChineseChar(412);//縐           磁
		PrintChineseChar(122 *17 + 10);//縐  票  
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Ticket No.    : %s", CAN);
		if (!PrintLine(abuf, 0)) return 10;
}


    if (fFareCardAmt > 0)//has a payment card
	{
//		if (!PrintLine("  Payment Method", 0)) return 8;

		PrintLSpc();
		PrintChineseChar(45*17 + 8);//葆     付
		PrintChineseChar( 87*17 + 8);//遴    款
		PrintChineseChar(2096-1410);//       方
		PrintChineseChar(3882-1410);//       式
		SendtoPrn(" Payment Method: ",17);

		if ((ReceiptCash > 0) && (fFareCardAmt-ReceiptCash+ReceiptChange > 0))
		{	
//         	if (!PrintLine(_T("               "), 0)) return 8;
//			PrintLSpc();
	    	PrintChineseChar(4377-1410);//葆     現    
		    PrintChineseChar(76 *17 +9);//       金
		    PrintChineseChar(2553-1410);//       及
			PrintChineseChar(2 *17 + 8);//縐     八		
			PrintChineseChar(26 *17 + 12);//縐   達
			PrintChineseChar(160 *17 + 13);//    通
			if (!PrintLine(" ", 0)) return 11;


			sprintf(abuf, "           Cash and Octopus Card %s\0", PaymentCAN+1); //paymentCAN undefine
			if (!PrintLine(abuf, 0)) return 11;
//			if (!PrintLine("Cash and Octopus", 0)) return 8;

		}
		else if ((fFareCardAmt-ReceiptCash+ReceiptChange) == 0)
		{
//			if (!PrintLine(_T("  "), 1)) return FALSE;
			PrintChineseChar(4377-1410);//葆     現    
			PrintChineseChar(76 *17 +9);//       金
			if (!PrintLine(" Cash", 0)) return 11;
		}
		else if ((fFareCardAmt-ReceiptCash+ReceiptChange) == fFareCardAmt)
		{
//			if (!PrintLine(_T("  "), 1)) return FALSE;
//         	if (!PrintLine(_T("               "), 0)) return 8;
//			PrintLSpc();
			PrintChineseChar(2 *17 + 8);//縐     八		
			PrintChineseChar(26 *17 + 12);//縐   達
			PrintChineseChar(160 *17 + 13);//    通
			if (!PrintLine(" ", 0)) return 11;
			
			sprintf(abuf, "            Octopus Card  : %s\0", PaymentCAN+1); //paymentCAN undefine
			if (!PrintLine(abuf, 0)) return 11;
		}
		else
		{
			if (!PrintLine("Others", 0)) return 11;
		}
	}				
		

//#endif
		
//	}

//card category
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, "Type: %s\0", Cate); 
//	if (!PrintLine(abuf, FALSE)) return 12;
//#else
	// Chinese receipt
	
//	if (!PrintLine("  Parking Type", 0)) return 8;

	PrintLSpc();
	PrintChineseChar(160 *17 + 8);//縐  停
	PrintChineseChar(17*17 + 13);//笱   車
	PrintChineseChar(92 *17 + 3);//濬   類
	PrintChineseChar(179 *17 + 9);//濬  型
	sprintf(abuf, " Parking Type  : %s\0", Cate); 
	if (!PrintLine(abuf, 0)) return 12;

	PrintLSpc();

	PrintChineseChar(17*17 + 13);//笱   車
	PrintChineseChar(3037-1410);//      輛
	PrintChineseChar(92 *17 + 3);//濬   類
	PrintChineseChar(179 *17 + 9);//濬  型
	SendtoPrn(" Vehicle Type  : ",17);
/*
	if (VehicleType == 1)
	{
		PrintChineseChar(4347-1410);//葆    細    
		PrintChineseChar(17*17 + 13);//笱   車
		if (!PrintLine(" (TYPE 1)", 0)) return 11;
	}
	else if (VehicleType == 2)
	{
		PrintChineseChar(1868-1410);//葆    大    
		PrintChineseChar(17*17 + 13);//笱   車
		if (!PrintLine(" (TYPE 2)", 0)) return 11;
	}	
	else
*/	{
		sprintf(abuf, "Type  : %d\0", VehicleType); 
		if (!PrintLine(abuf, 0)) return 12;
	}
//#endif
	
	
	//Enter time
	COleDateTime x;
	if (EnterTime > 100) {
		//x = COleDateTime(EnterTime);
		if (IsReply)
		{
//#ifndef _CHINESE_RECEIPT_
//			sprintf(abuf, "Enter Time : %02d:%02d %02d/%02d\0", x.GetHour(), x.GetMinute(), x.GetDay(), x.GetMonth());
//			if (!PrintLine(abuf, FALSE)) return 13;

//#else
			x = COleDateTime(EnterTime);
//			if (!PrintLine("  Entry Time", 0)) return 8;

			PrintLSpc();
			PrintChineseChar(77 *17 + 0);//輛  進
			PrintChineseChar(137*17 + 1);//��  入
			PrintChineseChar(144*17 +12);//奀  時
			PrintChineseChar(70 *17 + 5);//潔  間
		    sprintf(abuf, " Entry Time    : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());

			//sprintf(abuf, ": %02d:%02d %02d/%02d\0", x.GetHour(), x.GetMinute(), x.GetDay(), x.GetMonth());
			if (!PrintLine(abuf, 0)) return 13;

//#endif
		}
		else 
		{
//#ifndef _CHINESE_RECEIPT_
//			sprintf(abuf, "Last Paid: %02d:%02d %02d/%02d\0", x.GetHour(), x.GetMinute(), x.GetDay(), x.GetMonth());
//			if (!PrintLine(abuf, FALSE)) return 13;
//#else
			x = COleDateTime(LastPayTime);
//			if (!PrintLine("  Last Payment Time", 0)) return 8;

			PrintLSpc();
			PrintChineseChar(140*17 +16);//奻  上
			PrintChineseChar(24*17 +13);//棒   次
			PrintChineseChar(45*17 + 8);//葆   付
			PrintChineseChar( 87*17 + 8);//遴  款
		    sprintf(abuf, " Last Paid Time: %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());			
			if (!PrintLine(abuf, 0)) return 13;

//#endif
		}
	}
	else if (!PrintLine("** Per-Entry Charge **", TRUE)) return 14;
	
	//x = COleDateTime::GetCurrentTime();
	x = COleDateTime(PayTime);
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, "Paid Time : %02d:%02d %02d/%02d\0", x.GetHour(), x.GetMinute(), x.GetDay(), x.GetMonth());
//	if (!PrintLine(abuf, FALSE)) return 15;
//#else
//	if (!PrintLine("  Payment Time", 0)) return 8;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar( 87*17 + 8);//遴   款
	PrintChineseChar(144*17 +12);//奀   時
	PrintChineseChar(70 *17 + 5);//潔   間
	sprintf(abuf, " Payment Time  : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());				
	if (!PrintLine(abuf, 0)) return 15;
//#endif
	

		
//	if (!CharsBold(TRUE)) return 17;
//Amount Due
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, "Park Fee: $%.2f\0", fFareCardAmt + fStoreValueAmt); 
//#else
//	if (!PrintLine("  Parking Fee", 0)) return 8;
/*
	PrintLSpc();
	PrintChineseChar(3295);//          應   
	PrintChineseChar(45*17 + 8);//葆   付
	PrintChineseChar(76 *17 +9);//     金
	PrintChineseChar(37 *17 + 12);//   額  
	sprintf(abuf, " Parking Fee   : $%.2f\0", fFareCardAmt + fStoreValueAmt); 
	if (!PrintLine(abuf, 0)) return 18;
*/
//#endif

// Discount
//	if (strlen(DiscountStr) > 0)
//	{
//#ifndef _CHINESE_RECEIPT_
//		sprintf(abuf, "Discount : %s\0", DiscountStr);
//		if (!PrintLine(abuf, FALSE)) return 16;
//#else
//		if (!PrintLine("  Discount Mode", 0)) return 8;

/* After FAT testing
		PrintLSpc();
		PrintChineseChar(208*17 +0);//殏    折
		PrintChineseChar(86 *17 + 6);//諶   扣
		PrintChineseChar(92 *17 + 3);//濬   類
		PrintChineseChar(179 *17 + 9);//濬  型
		sprintf(abuf, " Discount Mode : %s\0", DiscountStr);
		if (!PrintLine(abuf, 0)) return 16;
*/
//#endif
//	}

if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

//paid
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, "Paid    : $%9.2f\0", fFareCardAmt + fStoreValueAmt); 
//#else

	PrintLSpc();
	if (!CharsBold(TRUE)) return FALSE;
	PrintChineseChar(144*17 +16);//妗   實
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(76 *17 +9);//      金
	PrintChineseChar(37 *17 + 12);//    額  
	sprintf(abuf, "   Total Amount   : $%10.2f\0", fFareCardAmt + fStoreValueAmt); 
	if (!PrintLine(abuf, 0)) return 18;
	if (!CharsBold(FALSE)) return FALSE;
//#endif

//Cash
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, " Paid   : $%.2f\0", fFareCardAmt + fStoreValueAmt); 
//#else
	if (ReceiptCash > 0) 
	{
		PrintLSpc();
		PrintChineseChar(3244);     //妗    已
		PrintChineseChar(45*17 + 8);//葆    付
		PrintChineseChar(4377-1410);//葆    現    
		PrintChineseChar(76 *17 +9);//      金
		sprintf(abuf, "   Cash Paid      : $%10.2f\0", ReceiptCash); 
		if (!PrintLine(abuf, 0)) return 18;
//#endif

//changes

//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, "Changes : $%9.2f\0", fFareCardAmt + fStoreValueAmt); 
//#else
		PrintLSpc();
		PrintChineseChar(207*17 + 8);//梑    找
		PrintChineseChar(2517);//錨          贖
		PrintChineseChar(76 *17 +9);//       金
		PrintChineseChar(37 *17 + 12);//     額  
		sprintf(abuf, "   Changes        : $%10.2f\0", ReceiptChange); 
		if (!PrintLine(abuf, 0)) return 18;
	}
//#endif

	
//Cash
//#ifndef _CHINESE_RECEIPT_
//	sprintf(abuf, " Paid   : $%.2f\0", fFareCardAmt + fStoreValueAmt); 
//#else

	if (fFareCardAmt-ReceiptCash+ReceiptChange > 0)
	{
		PrintLSpc();
//		PrintChineseChar(3244);     //妗    已
		PrintChineseChar(2 *17 + 8);//縐     八		
	    PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(45*17 + 8);//葆    付
		PrintChineseChar(87*17 + 8);//葆    款
//		PrintChineseChar(83 *17 + 6);//縐   卡
//		PrintChineseChar(211*17 + 5);//硉   值
		sprintf(abuf, " Octopus Payment: $%10.2f\0", fFareCardAmt-ReceiptCash+ReceiptChange); 
		if (!PrintLine(abuf, 0)) return 18;
	
//#endif

// Octopus Balance	
	//if (CompareDbl(fFareCardAmt, 0) > 0)
	//{ 

//#ifndef _CHINESE_RECEIPT_
//		sprintf(abuf, "Remain Bal. : $%10.2f\0", fFareCardBal); 
//		if (!PrintLine(abuf, FALSE)) return 19;
//#else
		PrintLSpc();
//		PrintChineseChar(83 *17 + 6);//縐  卡
//		PrintChineseChar(113*17 +16);//囀  內
		PrintChineseChar(2 *17 + 8);//縐     八		
		PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(197*17 + 4);//豻  餘
		PrintChineseChar(37 *17 +12);//塗  額
		sprintf(abuf, " Remaining Value: $%10.2f\0", fFareCardBal); 
		if (!PrintLine(abuf, 0)) return 19;
//#endif
	}

// Store Value	
	
	if (CompareDbl(fStoreValueAmt, 0)>0)
	{ 
//#ifndef _CHINESE_RECEIPT_
//		sprintf(abuf, "Store Value : $%10.2f\0", fStoreValueBal); 
//		if (!PrintLine(abuf, FALSE)) return 20;
//#else
		PrintLSpc();
		PrintChineseChar(172*17+10);//炵  系
		PrintChineseChar(161*17+7);//苀   統
		PrintChineseChar(22 *17 + 3);//揣 儲
		PrintChineseChar(211*17 + 5);//硉 值
		sprintf(abuf, " Store Value Remain : $%8.2f\0", fStoreValueBal); 
		if (!PrintLine(abuf, 0)) return 20;
//#endif
	}
	if (!CharsBold(FALSE)) return 21;
	//Tax info

	if(R.GetLength()>10)//TA19-
	{
		PrintLSpc();
		if(R[11]=='1')//1-CASH, 4-AAVS 2- ONLINE
			sprintf(abuf, "Last add value by Cash On %s", R.Left(10)); 
		else if(R[11]=='4')
			sprintf(abuf, "Last add value by AAVS On %s", R.Left(10)); 
		else if(R[11]=='2')
			sprintf(abuf, "Last add value by Online On %s", R.Left(10)); 
		else 		
			sprintf(abuf, "   "); 

		if (!PrintLine(abuf, 0)) return 10;

	}
	
//	if (!PrintTax()) return 22;
	if (!PrintEnding()) return 23; //print "-----------"
	//cut paper
	//if (!PrintFeed(150)) return 24;
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	if (!AuxFullCut()) return 25;
	return 0;
}

BOOL CReceiptPrn::PrintTax()
{
	CString abuf;
#ifndef _CHINESE_RECEIPT_
	abuf.Format(_T("%d%% %s is included"), m_nTaxPerc, m_lpTaxName);
	if (!PrintLine(abuf, FALSE)) return FALSE;
#else
	PrintLSpc();
	PrintChineseChar(5*17+6);//婦
	PrintChineseChar(55*17+16);//漪
	PrintChineseChar(176*17+12);//秏
	PrintChineseChar(41*17+9);//煤
	PrintChineseChar(150*17+3);//阭
	abuf.Format(_T("%d%%"), m_nTaxPerc, m_lpTaxName);
	if (!PrintLine(abuf, 1)) return FALSE;
#endif
	
#ifndef _CHINESE_RECEIPT_
	abuf.Format(_T("%s No.: %s"), m_lpTaxName, m_lpTaxNo);
	if (!PrintLine(abuf, FALSE)) return FALSE;
#else
	PrintLSpc();
	PrintChineseChar(150*17+3);//阭
	PrintChineseChar(57 *17 + 7);//瘍
	abuf.Format(_T(": %s"), m_lpTaxNo);
	if (!PrintLine(abuf, 1)) return FALSE;
#endif
	return TRUE;
}

BOOL CReceiptPrn::PrintHeader()
{
	//Header
	//if (!SetLineSpace(9)) return FALSE;
	if (!CharsBold(TRUE)) return FALSE;
    
//    sprintf(receipt_abuf, ": %s\0",m_lpStarter[0] );
//	if (!PrintLine(receipt_abuf, 1)) return FALSE;

	if (!PrintLine(m_lpStarter[0], 1)) return FALSE;
	if (!PrintLine(m_lpStarter[1], 1)) return FALSE;   
	if (!PrintLine(m_lpStarter[2], 1)) return FALSE;
	if (!CharsBold(FALSE)) return FALSE;
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;
	//if (!SetLineSpace(12)) return FALSE;
	return TRUE;
}

BOOL CReceiptPrn::PrintEnding()
{
	//char abuf[80];
	//if (!SetLineSpace(9)) return FALSE;
	//PrintLine(" ",0);
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;
	if (!CharsBold(TRUE)) return FALSE;
	//SendtoPrn("      ",6);     
	if (!PrintLine(m_lpEnding[0], 1)) return FALSE;
	//SendtoPrn("      ",6);     
	if (!PrintLine(m_lpEnding[1], 1)) return FALSE;
	if (!CharsBold(FALSE)) return FALSE;
	//if (!SetLineSpace(12)) return FALSE; 
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//  Private Rountine
//print a line
BOOL CReceiptPrn::PrintLine(LPSTR datamsg, BOOL NoSpacing)
{
	int len = strlen(datamsg);
	if (len < 1) return TRUE;
	if (len > PAPER_WIDTH) len = PAPER_WIDTH -1;
	char spcbuf[PAPER_WIDTH];
	memset(spcbuf, ' ', PAPER_WIDTH);
	int spclen;
	if (!NoSpacing) {//no left alignment  (NoSpacing = 0)
		spclen = 0;
		//spclen = (PAPER_WIDTH - strlen(datamsg)) / 2;
	}else{//left alignment
		//spclen = 0;  // orginal
		//spclen = m_nLeftSpc;
		spclen = ((PAPER_WIDTH - strlen(datamsg)) / 2)+2;
	}
	char buf[100];
	memcpy(buf, spcbuf, spclen);
	memcpy(buf+spclen, datamsg, len);
	buf[spclen + len] = 10;
	buf[spclen + len + 1] = 0;
	if (!SendtoPrn(buf, spclen + len + 1)) return FALSE;
	return TRUE;
}

BOOL CReceiptPrn::PrintLSpc()
{
	char spcbuf[PAPER_WIDTH];
	memset(spcbuf, ' ', PAPER_WIDTH);
	int spclen = m_nLeftSpc;
	if (!SendtoPrn(spcbuf, spclen)) return FALSE;
	return TRUE;
}
BOOL CReceiptPrn::PrintLine(CString datamsg, BOOL isCentre)
{
	if (datamsg.IsEmpty()) return TRUE;
	datamsg = datamsg.Left(PAPER_WIDTH);
	datamsg.TrimRight();
	datamsg.TrimLeft();
	char abuf[50];
	int len = datamsg.GetLength();
	if (len > PAPER_WIDTH) return FALSE;
	//if (wcstombs(abuf, (LPCTSTR)datamsg, len+1) < 0) return FALSE;
	strcpy(abuf, datamsg.GetBuffer(0));
	//abuf[len] = 0;
	return PrintLine(abuf, isCentre);
}

HANDLE CReceiptPrn::OpenRPrn(LPCTSTR PortName)
{
	HANDLE prnID = CreateFile(
						PortName, 
						GENERIC_READ|GENERIC_WRITE, 
						FILE_SHARE_READ, 
						NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL, 
						0);
    if (prnID == INVALID_HANDLE_VALUE) return NULL;
	ClearCommBreak(prnID);
	EscapeCommFunction(prnID, SETDTR||SETRTS);
  
    SetupComm(prnID, 256, 256);
    PurgeComm(prnID, PURGE_TXCLEAR|PURGE_RXCLEAR);
    return prnID;
}

BOOL CReceiptPrn::SendtoPrn(LPCVOID pbuf, DWORD MsgLen)
{
	if (!m_isDeviceOK) return FALSE;
	DWORD flag, ActualLen = 0;
	BOOL WriteOK;
	COMSTAT	ComStat;
	int count = 0;
	for (DWORD dw = 0; dw < MsgLen; dw ++)
	{
		ClearCommError(m_RPrn, &flag, &ComStat);
		//Sleep(1);
		WriteOK = WriteFile(m_RPrn, ((LPSTR)pbuf)+dw, 1, &ActualLen, NULL);
		if ((!WriteOK) || (ActualLen != 1)) 
		{
			if (!WriteOK) m_dwErrCode = 5;
			if (ActualLen != 1) m_dwErrCode = 6;
			EscapeCommFunction(m_RPrn, SETDTR|SETRTS);
			m_isDeviceOK = FALSE;
//			::AfxMessageBox("與收據打印機通訊失敗, 請檢查收據打印機是否開啟或電源是否連上!", MB_ICONSTOP);
			::AfxMessageBox("收據打印機故障，修復故障後，必須關閉及重新啟動本軟件，方能恢復列印.", MB_ICONSTOP); //for ymd 20091224
			return FALSE;
		}
	}
	FlushFileBuffers(m_RPrn);
	return TRUE;
}

DWORD CReceiptPrn::GetErrCode(){return m_dwErrCode;}
BOOL CReceiptPrn::LineFeed(){ char abuf[] = {13}; return SendtoPrn(abuf, 1); }
BOOL CReceiptPrn::PrintFeed(BYTE dotLine){ if (dotLine > 255) return FALSE; char abuf[] = {27, 74, dotLine}; return SendtoPrn(abuf, 3); }
BOOL CReceiptPrn::PrintFeedBack(BYTE dotLine){  if (dotLine > 255) return FALSE; char abuf[] = {27, 106, dotLine}; return SendtoPrn(abuf, 3);}
//default is 16 dots
BOOL CReceiptPrn::SetLineSpace(BYTE dotNo){ if (dotNo > 255) return FALSE; char abuf[] = {27, 65, dotNo}; return SendtoPrn(abuf, 3); }
//default is 4 dots
BOOL CReceiptPrn::SetCharSpace(BYTE dotNo){ if (dotNo > 127) return FALSE; char abuf[] = {27, 32, dotNo}; return SendtoPrn(abuf, 3); }
//turn on/off(default) inverse print by line
BOOL CReceiptPrn::LineInverse(BOOL isActive){ char abuf[] = {27, 85, (isActive ? 1 : 0)}; return SendtoPrn(abuf, 3); }
//rotate the char; 0: Non-rotate; 1: 90' right; 2; 90'left; 3: ignoral
BOOL CReceiptPrn::CharRotate(BYTE Rotate){ if (Rotate > 3) return FALSE; char abuf[] = {18, 89, Rotate}; return SendtoPrn(abuf, 3);}
//Character Shape modification
BOOL CReceiptPrn::CharsUnderLine(BYTE LineWidth){ if (LineWidth > 7)	return FALSE; char abuf[] = {27, 45, LineWidth}; return SendtoPrn(abuf, 3); }
BOOL CReceiptPrn::CharsDblWidth(BOOL isActive){ char abuf[] = {27, 87, (isActive ? 1 : 0)}; return SendtoPrn(abuf, 3); }
BOOL CReceiptPrn::CharsDblHeight(BOOL isActive){ char abuf[] = {27, 119, (isActive ? 1 : 0)}; return SendtoPrn(abuf, 3); }
BOOL CReceiptPrn::CharsReverse(BOOL isActive)
{ 
	char abuf[] = {29, 66, (isActive ? 1 : 0)}; 
	return SendtoPrn(abuf, 3); 
}
//composed by 2 cmds(Esc+E; Esc+F);
BOOL CReceiptPrn::CharsBold(BOOL isActive)
{  
	char abuf[] = {27, 69, (isActive ? 1 : 0)}; return SendtoPrn(abuf, 3); 
}
BOOL CReceiptPrn::CharSize(int H, int W){ 
	char a; 
	a = H*16 + W;
	char abuf[] = {29, 33, a}; return SendtoPrn(abuf, 3); 
}

//BarCode
BOOL CReceiptPrn::BCodeSelect(BYTE Mode, CString Data)//mode =4 barcode 39.
{
	if (Mode > 8) return FALSE; 
	char abuf[50]; abuf[0] = 29; abuf[1] = 107; abuf[2] = Mode; 
	strcpy(abuf + 3, Data.GetBuffer(0));
	//wcstombs(abuf+3, (LPCTSTR)Data, Data.GetLength());
	int i = Data.GetLength() + 3; 
	return SendtoPrn(abuf, i);
}
BOOL CReceiptPrn::BCodeWidth(BYTE NWidth, BYTE WWidth)//narrow width= 1(3 dots); wide 2(9 dots)
{
	if (NWidth > 2) return FALSE; if (WWidth > 3) return FALSE;
	char abuf[] = {29, 119, NWidth, WWidth}; return SendtoPrn(abuf, 4);
}
//pos = 0-left; 1-centre; 2-right;
BOOL CReceiptPrn::BCodePos(BYTE Pos){ if (Pos > 2) return FALSE; char abuf[] = {29, 80, Pos}; return SendtoPrn(abuf, 3);}
BOOL CReceiptPrn::BCodeHeight(BYTE Height){ if (Height > 255) return FALSE; char abuf[] = {29, 104, Height}; return SendtoPrn(abuf, 3);}
//pos= 0-No print; 1-top; 2-bottom; 3-top and bottom.
BOOL CReceiptPrn::BCodeCharPos(BYTE Pos){ if (Pos > 3) return FALSE; char abuf[] = {29, 72, Pos}; return SendtoPrn(abuf, 3); }
//size = 0-24*12; 1-16*8
BOOL CReceiptPrn::BCodeCharSize(BYTE Size) { if (Size > 1) return FALSE; char abuf[] = {29, 102, Size}; return SendtoPrn(abuf, 3); }

//Auxiliary functions
BOOL CReceiptPrn::AuxMarkDetect(BYTE DetectCon, int DotsLen){
	BYTE bh = BYTE((DotsLen / 255) % 255); 	BYTE bl = BYTE(DotsLen % 255);
	char abuf[] = {18, 109, DetectCon, bl, bh}; return SendtoPrn(abuf, 5);
}
BOOL CReceiptPrn::AuxNoPaperAct(BOOL act) { char abuf[] = {18, 112, (act ? 1 : 0)}; return SendtoPrn(abuf, 3); }
BOOL CReceiptPrn::AuxCancel(){ char abuf[] = {24}; return SendtoPrn(abuf, 1); }
BOOL CReceiptPrn::AuxReset(){ char abuf[] = {27, 64}; return SendtoPrn(abuf, 2); }
BOOL CReceiptPrn::AuxFullCut() {	char abuf[] = {27, 105}; return SendtoPrn(abuf, 2); }
BOOL CReceiptPrn::AuxPartialCut() { char abuf[] = {27, 109}; return SendtoPrn(abuf, 2); }
void CReceiptPrn::CloseRPrn(){ if (m_RPrn) CloseHandle(m_RPrn); }
BOOL CReceiptPrn::SetOutOfPaperInstruction(BOOL bEnabled) { char abuf[] = {27, 'p', 0}; if (bEnabled) abuf[2] = 1; return SendtoPrn(abuf, 3); }
 
void CReceiptPrn::LoadChineseFontLib()
{
	PrintChineseChar(150*17+12);//佴
	PrintChineseChar(103*17+14);//鎖
	PrintChineseChar(99*17+9);//癒
	PrintChineseChar(172*17+10);//炵
	PrintChineseChar(161*17+8);//苀
	
	PrintChineseChar(2  *17 + 8);//匐
	PrintChineseChar(26 *17 +12);//湛
	PrintChineseChar(160*17 + 13);//籵
	PrintChineseChar(179*17 + 9);//倰
	PrintChineseChar(22 *17 + 3);//揣
	PrintChineseChar(211*17 + 5);//硉
	PrintChineseChar(83 *17 + 6);//縐
	PrintChineseChar(158*17 + 1);//杻
	PrintChineseChar(147*17 +10);//忷
	PrintChineseChar(77 *17 + 0);//輛
	PrintChineseChar(137*17 + 1);//��
	PrintChineseChar(144*17 +12);//奀
	PrintChineseChar(70 *17 + 5);//潔
	PrintChineseChar(160*17 + 8);//礿
	PrintChineseChar(17 *17 +13);//陬
	PrintChineseChar(41 *17 + 9);//煤
	PrintChineseChar(144*17 +16);//妗
	PrintChineseChar(146*17 +14);//彶
	PrintChineseChar(208*17 +0);//殏
	PrintChineseChar(86 *17 + 6);//諶
	PrintChineseChar(76 *17 +9);//踢
	PrintChineseChar(37 *17 +12);//塗
	SendtoPrn("thesecondsentence", 17);
	PrintChineseChar(207*17 + 8);//梑
	PrintChineseChar(197*17 + 4);//豻
	PrintChineseChar( 87*17 + 8);//遴
	PrintChineseChar(53 *17 +10);//嫖
	PrintChineseChar(68 *17 +9);//數
	PrintChineseChar(122*17 +10);//き
	PrintChineseChar(213*17 + 4);//笱
	PrintChineseChar(110*17 + 6);//靡
	SendtoPrn("nonsense", 8);
	PrintChineseChar(97 *17 +15);//錨
	PrintChineseChar(57 *17 + 7);//瘍
	PrintChineseChar(66 *17 + 1);//儂
	PrintChineseChar(206*17 + 5);//桴
	PrintChineseChar(113*17 +16);//囀
	PrintChineseChar(135*17 + 3);//��
	PrintChineseChar(92 *17 + 3);//濬
	PrintChineseChar(178*17 + 8);//郅
	PrintChineseChar(80*17 + 16);//擂
	PrintChineseChar(45*17 + 8);//葆
	PrintChineseChar(97 *17 + 5);//還
	SendtoPrn("\012\012", 2);

}
BOOL CReceiptPrn::GetFontMatrix(int ID, BYTE * Buf)
{
#ifdef _TRADITIONAL_CHINESE_ //16x16
	memset(Buf, 0, 72);
	pfile->Seek(ID * 32, CFile::begin);
	if (pfile->Read(Buf, 32) != 32) return FALSE;
	ConvertDotMatrix(Buf);
	return TRUE;
#else
	pfile->Seek(ID * 72, CFile::begin);
	if (pfile->Read(Buf, 72) != 72) return FALSE;
	return TRUE;
#endif
}	
BOOL CReceiptPrn::PrintChineseChar(int ID)
{
#ifdef _TRADITIONAL_CHINESE_
	ID += 1410;
#endif
	if (!bChineseAvailable) return FALSE;
	SetCharSpace(0);
	BYTE cfont[72];
	SendtoPrn("\033&\03^_", 5);
	if (!GetFontMatrix(ID, cfont)) return FALSE;
	SendtoPrn("\014", 1);
	SendtoPrn(cfont, 36);
	SendtoPrn("\014", 1);
	SendtoPrn(cfont+36, 36);
	SendtoPrn("^_", 2);
//	SetCharSpace(3);
	return TRUE;
}

void CReceiptPrn::ConvertDotMatrix(BYTE * ByteBuf)
{
	bool ab[24][24];
	memset(ab, 0, 24*24);
	int tmpx, tmpy;
	for (int i=0;i<32;i++)
	{
		tmpx = i/2; tmpy = i%2;
		for (int j=0;j<8;j++)
		{
			ab[4+tmpy*8+j][4+tmpx]=ByteBuf[i] & (1<<(7-j));
		}
	}
	memset(ByteBuf, 0, 72);
	for (tmpx=0;tmpx<24;tmpx++)
		for (tmpy=0;tmpy<3;tmpy++)
			for (int j=0;j<8;j++)
			{
				ByteBuf[tmpx*3+tmpy]+= (1<<(7-j)) * ab[tmpx][(tmpy)*8+j];
			}
}


// Print Add Value receipt
BOOL CReceiptPrn::PrintAddValueReceipt(
			LONG         av_ReceiptNo, 
			CString      av_ReceiptOtpNo,
			COleDateTime av_ReceiptPayTime,
			double       av_ReceiptAmt,            // Add Value amount
		    double       av_ReceiptOtpOldBal, 
			double       av_ReceiptOtpNewBal,      
            double       av_ReceiptCash,           // cash paid
			double       av_ReceiptChange
			)
{
	if ((m_RPrn == NULL) || (!m_isDeviceOK)) return 1;
	
	COleDateTime x;

	char abuf[80];
	::ZeroMemory(abuf, 80);
	//Title
	PurgeComm(m_RPrn, PURGE_TXCLEAR|PURGE_RXCLEAR);
	//if (!PrintFeedBack(80)) return 2;

////////////////////////////////////////////////////////////heading
/*	SendtoPrn("         ",8);      

	if (!CharsReverse(TRUE)) return 3; 
    if (!CharSize(1, 1)) return 2;
    PrintChineseChar(-1410);    // " " 
	PrintChineseChar(150*17+12);//佴   斯
	PrintChineseChar(103*17+14);//鎖   瑪
	PrintChineseChar(99*17+9);//癒     隆
	PrintChineseChar(172*17+10);//炵   系
	PrintChineseChar(161*17+7);//苀    統
	if (!PrintLine(" ", 0)) return 8;
/////////////////////////////////////////////////////////////[JC] 20060303
*/	if (!CharsReverse(FALSE)) return 5;
	if (!CharSize(0, 0)) return 2;

	if (!PrintHeader()) return 7; // print "----------"

	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(4879-1410);//		 增
	PrintChineseChar(211*17 + 5);//硉    值
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據

	if (!PrintLine(" ", 0)) return 8;
	if (!PrintLine("  OCTOPUS ADD VALUE RECEIPT", 0)) return 8;
	
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
    PrintChineseChar(123);       //桴   本
	PrintChineseChar(206*17 + 5);//桴   站
	PrintChineseChar(57 *17 + 7);//瘍   號
	PrintChineseChar(103 *17 + 15);//鎢 碼

	sprintf(abuf, " Station No.   : %02d\0", m_nStationID); 
	if (!PrintLine(abuf, 0)) return 8;

//Device ID
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(66 *17 + 1);//      機
	PrintChineseChar(57 *17 + 7);//瘍    號

//	sprintf(abuf, " Device No.  : %d\0", m_DevID);
	sprintf(abuf, " Device No.  : %x\0", m_DevID);//new TA
	if (!PrintLine(abuf, 0)) return 10;

	PrintLSpc();
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Receipt No.   : %08d\0", av_ReceiptNo); 
	if (!PrintLine(abuf, 0)) return 9;

//card no

	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(83 *17 + 6);//縐    卡
//	PrintChineseChar(57 *17 + 7);//瘍    號
//	PrintChineseChar(103 *17 + 15);//鎢  碼
//	sprintf(abuf, " Octopus Card No.: %s\0", av_ReceiptOtpNo.Mid(1,8));
	sprintf(abuf, " Octopus Card No.: %s\0", av_ReceiptOtpNo.Mid(1,10));
	if (!PrintLine(abuf, 0)) return 10;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆      付
	PrintChineseChar( 87*17 + 8);//遴     款
	PrintChineseChar(2096-1410);//        方
	PrintChineseChar(3882-1410);//        式
	SendtoPrn(" Payment Method: ",17);

	PrintChineseChar(4377-1410);//葆     現    
	PrintChineseChar(76 *17 +9);//       金
	if (!PrintLine(" Cash", 0)) return 11;

	x = av_ReceiptPayTime;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar( 87*17 + 8);//遴   款
	PrintChineseChar(144*17 +12);//奀   時
	PrintChineseChar(70 *17 + 5);//潔   間
	sprintf(abuf, " Payment Time  : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());				
	if (!PrintLine(abuf, 0)) return 15;
/*
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(4879-1410);//		 增
	PrintChineseChar(211*17 + 5);//硉    值
	PrintChineseChar(3587-1410);//       前 
	PrintChineseChar(197*17 + 4);//豻    餘
	PrintChineseChar(37 *17 +12);//塗    額
	if (!PrintLine(_T(" "), 0)) return 11;
	PrintLSpc();
	sprintf(abuf, "Balance Before Add Value: $%12.2f\0", av_ReceiptOtpOldBal); 
	if (!PrintLine(abuf, 0)) return 19;
*/
if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
	if (!CharsBold(TRUE)) return FALSE;
	PrintChineseChar(4879-1410);//		 增
	PrintChineseChar(211*17 + 5);//硉    值
	PrintChineseChar(76 *17 +9);//       金
	PrintChineseChar(37 *17 +12);//塗    額
	sprintf(abuf, "   Add Value      : $%10.2f\0", av_ReceiptAmt); 
	if (!PrintLine(abuf, 0)) return 19;
	if (!CharsBold(FALSE)) return FALSE;

	PrintLSpc();
	PrintChineseChar(3244);     //妗   已
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(4377-1410);//葆    現    
	PrintChineseChar(76 *17 +9);//      金
	sprintf(abuf, "   Cash Paid      : $%10.2f\0", av_ReceiptCash); 
	if (!PrintLine(abuf, 0)) return 18;

	PrintLSpc();
	PrintChineseChar(207*17 + 8);//梑    找
	PrintChineseChar(2517);//錨          贖
	PrintChineseChar(76 *17 +9);//       金
	PrintChineseChar(37 *17 + 12);//     額  
	sprintf(abuf, "   Changes        : $%10.2f\0", av_ReceiptChange); 
	if (!PrintLine(abuf, 0)) return 18;

	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
    PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(197*17 + 4);//豻  餘
	PrintChineseChar(37 *17 + 12);//   額  
	sprintf(abuf, " Remaining Value: $%10.2f\0", av_ReceiptOtpNewBal); 
	if (!PrintLine(abuf, 0)) return 18;

	if (!CharsBold(FALSE)) return 21;
	if (!PrintEnding()) return 23; //print "-----------"
	//cut paper

	PrintLSpc();
//TA19- add last addvalue info 
	COleDateTime t=COleDateTime::GetCurrentTime();
	sprintf(abuf, "Last add value by Cash %04d-%02d-%02d", t.GetYear(),t.GetMonth(),t.GetDay()); 
	if (!PrintLine(abuf, 0)) return 10;

	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	if (!AuxFullCut()) return 25;
	return 0;
}	


// Print Create Season Card receipt
BOOL CReceiptPrn::PrintSeasonCreate(
			LONG         sc_ReceiptNo, 
			CString      sc_ReceiptCardNo, 
			COleDateTime sc_ReceiptPayTime,
			COleDateTime sc_ReceiptValidFrom,
			COleDateTime sc_ReceiptValidTo,
			double       sc_ReceiptAmt, 
			double       sc_ReceiptCash,
			double       sc_ReceiptChange
			)
{
	if ((m_RPrn == NULL) || (!m_isDeviceOK)) return 1;
	
	COleDateTime x;

	char abuf[80];
	::ZeroMemory(abuf, 80);
	//Title
	PurgeComm(m_RPrn, PURGE_TXCLEAR|PURGE_RXCLEAR);
	//if (!PrintFeedBack(80)) return 2;

//////////////////////////////////////////////////////////////heading
/*	SendtoPrn("         ",8);      

	if (!CharsReverse(TRUE)) return 3; 
    if (!CharSize(1, 1)) return 2;
    PrintChineseChar(-1410);    // " " 
	PrintChineseChar(150*17+12);//佴   斯
	PrintChineseChar(103*17+14);//鎖   瑪
	PrintChineseChar(99*17+9);//癒     隆
	PrintChineseChar(172*17+10);//炵   系
	PrintChineseChar(161*17+7);//苀    統
	if (!PrintLine(" ", 0)) return 8;
//////////////////////////////////////////////////////////////////[JC] 20060303
*/	if (!CharsReverse(FALSE)) return 5;
	if (!CharSize(0, 0)) return 2;

	if (!PrintHeader()) return 7; // print "----------"

	PrintLSpc();
	PrintChineseChar(160*17+8);//        停		
	PrintChineseChar(17 *17 + 13);//     車
	PrintChineseChar(1692-1410);//       場
	PrintChineseChar(4451-1410);//                新
	PrintChineseChar(4879-1410);//		 增
	PrintChineseChar(2567-1410);//	             季
	PrintChineseChar(3494-1410);//                票
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據

	if (!PrintLine(" ", 0)) return 8;
	if (!PrintLine("  CARPARK SEASON CARD CREATE RECEIPT", 0)) return 8;
	
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
    PrintChineseChar(123);       //桴   本
	PrintChineseChar(206*17 + 5);//桴   站
	PrintChineseChar(57 *17 + 7);//瘍   號
	PrintChineseChar(103 *17 + 15);//鎢 碼

	sprintf(abuf, " Station No.   : %02d\0", m_nStationID); 
	if (!PrintLine(abuf, 0)) return 8;
/*
//Device ID
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(66 *17 + 1);//      機
	PrintChineseChar(57 *17 + 7);//瘍    號

	sprintf(abuf, " Device No.  : %d\0", m_DevID);
	if (!PrintLine(abuf, 0)) return 10;
*/
	PrintLSpc();
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Receipt No.   : %08d\0", sc_ReceiptNo); 
	if (!PrintLine(abuf, 0)) return 9;

	PrintLSpc();
	PrintChineseChar(4451-1410);//       新
	PrintChineseChar(4879-1410);//		 增
	PrintChineseChar(2567-1410);//	 季
	PrintChineseChar(3494-1410);//    票
	sprintf(abuf, " Season Card Created : "); 
	if (!PrintLine(abuf, 0)) return 9;


//card no
if (sc_ReceiptCardNo[0] == 'O')
{
		PrintLSpc();
		PrintChineseChar(2 *17 + 8);//縐     八		
		PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(83 *17 + 6);//縐    卡
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Octopus Card No. %s\0", sc_ReceiptCardNo.Mid(1,8));
		if (!PrintLine(abuf, 0)) return 10;
}else if (sc_ReceiptCardNo[0] == 'P')
{
		PrintLSpc();
		PrintChineseChar(412);//縐           磁
		PrintChineseChar(122 *17 + 10);//縐  票  
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Ticket No. %s \0", sc_ReceiptCardNo.Mid(1,8));
		if (!PrintLine(abuf, 0)) return 10;
}
	
	PrintLSpc();
	PrintChineseChar(4747-1410);//   有
	PrintChineseChar(4424-1410);//   效
	PrintChineseChar(3718-1410);//   日
	PrintChineseChar(3535-1410);//   期
	sprintf(abuf, " Valid Period  : ");				
	if (!PrintLine(abuf, 0)) return 15;
	sprintf(abuf, "           %02d-%02d-%02d to %02d-%02d-%02d \0", sc_ReceiptValidFrom.GetDay(), sc_ReceiptValidFrom.GetMonth(), sc_ReceiptValidFrom.GetYear()%100, 
		sc_ReceiptValidTo.GetDay(), sc_ReceiptValidTo.GetMonth(), sc_ReceiptValidTo.GetYear()%100);				
	if (!PrintLine(abuf, 0)) return 15;


	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆      付
	PrintChineseChar( 87*17 + 8);//遴     款
	PrintChineseChar(2096-1410);//        方
	PrintChineseChar(3882-1410);//        式
	SendtoPrn(" Payment Method: ",17);

	PrintChineseChar(4377-1410);//葆     現    
	PrintChineseChar(76 *17 +9);//       金
	if (!PrintLine(" Cash", 0)) return 11;

	x = sc_ReceiptPayTime;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar( 87*17 + 8);//遴   款
	PrintChineseChar(144*17 +12);//奀   時
	PrintChineseChar(70 *17 + 5);//潔   間
	sprintf(abuf, " Payment Time  : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());				
	if (!PrintLine(abuf, 0)) return 15;

if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
	if (!CharsBold(TRUE)) return FALSE;
	PrintChineseChar(144*17 +16);//妗   實
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(76 *17 +9);//      金
	PrintChineseChar(37 *17 + 12);//    額  
	sprintf(abuf, "   Total Amount   : $%10.2f\0", sc_ReceiptAmt); 
	if (!PrintLine(abuf, 0)) return 18;
	if (!CharsBold(FALSE)) return FALSE;

	PrintLSpc();
	PrintChineseChar(3244);     //妗    已
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(4377-1410);//葆    現    
	PrintChineseChar(76 *17 +9);//      金
	sprintf(abuf, "   Cash Paid      : $%10.2f\0", sc_ReceiptCash); 
	if (!PrintLine(abuf, 0)) return 18;

	PrintLSpc();
	PrintChineseChar(207*17 + 8);//梑    找
	PrintChineseChar(2517);//錨          贖
	PrintChineseChar(76 *17 +9);//       金
	PrintChineseChar(37 *17 + 12);//     額  
	sprintf(abuf, "   Changes        : $%10.2f\0", sc_ReceiptChange); 
	if (!PrintLine(abuf, 0)) return 18;
/*
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
    PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(197*17 + 4);//豻  餘
	PrintChineseChar(37 *17 + 12);//   額  
	sprintf(abuf, " Remaining Value: $%10.2f\0", av_ReceiptOtpNewBal); 
	if (!PrintLine(abuf, 0)) return 18;
*/
	if (!CharsBold(FALSE)) return 21;
	if (!PrintEnding()) return 23; //print "-----------"
	//cut paper
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	if (!AuxFullCut()) return 25;
	return 0;
}	


// Print Extend Season Card receipt
BOOL CReceiptPrn::PrintSeasonExtend(
			LONG         se_ReceiptNo, 
			CString      se_ReceiptCardNo, 
			COleDateTime se_ReceiptPayTime,
			COleDateTime se_ReceiptExtendFrom,
			COleDateTime se_ReceiptExtendTo,
			double       se_ReceiptAmt, 
			double       se_ReceiptCash,
			double       se_ReceiptChange
			)
{
	if ((m_RPrn == NULL) || (!m_isDeviceOK)) return 1;
	
	COleDateTime x;

	char abuf[80];
	::ZeroMemory(abuf, 80);
	//Title
	PurgeComm(m_RPrn, PURGE_TXCLEAR|PURGE_RXCLEAR);
	//if (!PrintFeedBack(80)) return 2;

/////////////////////////////////////////////////////////////heading
/*	SendtoPrn("         ",8);      

	if (!CharsReverse(TRUE)) return 3; 
    if (!CharSize(1, 1)) return 2;
    PrintChineseChar(-1410);    // " " 
	PrintChineseChar(150*17+12);//佴   斯
	PrintChineseChar(103*17+14);//鎖   瑪
	PrintChineseChar(99*17+9);//癒     隆
	PrintChineseChar(172*17+10);//炵   系
	PrintChineseChar(161*17+7);//苀    統
	if (!PrintLine(" ", 0)) return 8;
///////////////////////////////////////////////////////////////[JC] 20060303
*/	if (!CharsReverse(FALSE)) return 5;
	if (!CharSize(0, 0)) return 2;

	if (!PrintHeader()) return 7; // print "----------"

	PrintLSpc();
	PrintChineseChar(160*17+8);//        停		
	PrintChineseChar(17 *17 + 13);//     車
	PrintChineseChar(1692-1410);//       場
	PrintChineseChar(2567-1410);//	     季
	PrintChineseChar(3494-1410);//       票
	PrintChineseChar(4505-1410);//       續
	PrintChineseChar(3535-1410);//		 期
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據

	if (!PrintLine(" ", 0)) return 8;
	if (!PrintLine("  CARPARK SEASON CARD EXTEND RECEIPT", 0)) return 8;
	
	if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
    PrintChineseChar(123);       //桴   本
	PrintChineseChar(206*17 + 5);//桴   站
	PrintChineseChar(57 *17 + 7);//瘍   號
	PrintChineseChar(103 *17 + 15);//鎢 碼

	sprintf(abuf, " Station No.   : %02d\0", m_nStationID); 
	if (!PrintLine(abuf, 0)) return 8;
/*
//Device ID
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
	PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(66 *17 + 1);//      機
	PrintChineseChar(57 *17 + 7);//瘍    號

	sprintf(abuf, " Device No.  : %d\0", m_DevID);
	if (!PrintLine(abuf, 0)) return 10;
*/
	PrintLSpc();
	PrintChineseChar(146*17 +14);//彶    收
	PrintChineseChar(80*17 + 16);//擂    據
	PrintChineseChar(57 *17 + 7);//瘍    號
	PrintChineseChar(103 *17 + 15);//鎢  碼
	sprintf(abuf, " Receipt No.   : %08d\0", se_ReceiptNo); 
	if (!PrintLine(abuf, 0)) return 9;

	PrintLSpc();
	PrintChineseChar(2567-1410);//	     季
	PrintChineseChar(3494-1410);//       票
	PrintChineseChar(4505-1410);//       續
	PrintChineseChar(3535-1410);//		 期
	sprintf(abuf, " Season Card Create: "); 
	if (!PrintLine(abuf, 0)) return 9;


//card no
if (se_ReceiptCardNo[0] == 'O')
{
		PrintLSpc();
		PrintChineseChar(2 *17 + 8);//縐     八		
		PrintChineseChar(26 *17 + 12);//縐   達
		PrintChineseChar(160 *17 + 13);//    通
		PrintChineseChar(83 *17 + 6);//縐    卡
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Octopus Card No. %s\0", se_ReceiptCardNo.Mid(1,8));
		if (!PrintLine(abuf, 0)) return 10;
}else if (se_ReceiptCardNo[0] == 'P')
{
		PrintLSpc();
		PrintChineseChar(412);//縐           磁
		PrintChineseChar(122 *17 + 10);//縐  票  
		PrintChineseChar(57 *17 + 7);//瘍    號
		PrintChineseChar(103 *17 + 15);//鎢  碼
		sprintf(abuf, " Ticket No. %s\0", se_ReceiptCardNo.Mid(1,8));
		if (!PrintLine(abuf, 0)) return 10;
}
	
	PrintLSpc();

	PrintChineseChar(2253-1410);//   更
	PrintChineseChar(4451-1410);//   新
	PrintChineseChar(2432-1410);//   後
	PrintChineseChar(4747-1410);//   有
	PrintChineseChar(4424-1410);//   效
	PrintChineseChar(3718-1410);//   日
	PrintChineseChar(3535-1410);//   期
	sprintf(abuf, " New Valid Period : ");				
	if (!PrintLine(abuf, 0)) return 15;
	sprintf(abuf, "           %02d-%02d-%02d to %02d-%02d-%02d \0", se_ReceiptExtendFrom.GetDay(), se_ReceiptExtendFrom.GetMonth(), se_ReceiptExtendFrom.GetYear()%100, 
		se_ReceiptExtendTo.GetDay(), se_ReceiptExtendTo.GetMonth(), se_ReceiptExtendTo.GetYear()%100);				
	if (!PrintLine(abuf, 0)) return 15;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆      付
	PrintChineseChar( 87*17 + 8);//遴     款
	PrintChineseChar(2096-1410);//        方
	PrintChineseChar(3882-1410);//        式
	SendtoPrn(" Payment Method: ",17);

	PrintChineseChar(4377-1410);//葆     現    
	PrintChineseChar(76 *17 +9);//       金
	if (!PrintLine(" Cash", 0)) return 11;

	x = se_ReceiptPayTime;

	PrintLSpc();
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar( 87*17 + 8);//遴   款
	PrintChineseChar(144*17 +12);//奀   時
	PrintChineseChar(70 *17 + 5);//潔   間
	sprintf(abuf, " Payment Time  : %02d-%02d-%02d %02d:%02d \0", x.GetDay(), x.GetMonth(), x.GetYear()%100, x.GetHour(), x.GetMinute());				
	if (!PrintLine(abuf, 0)) return 15;

if (!PrintLine(_T("---------------------------------------"), 1)) return FALSE;

	PrintLSpc();
	if (!CharsBold(TRUE)) return FALSE;
	PrintChineseChar(144*17 +16);//妗   實
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(76 *17 +9);//      金
	PrintChineseChar(37 *17 + 12);//    額  
	sprintf(abuf, "   Total Amount   : $%10.2f\0", se_ReceiptAmt); 
	if (!PrintLine(abuf, 0)) return 18;
	if (!CharsBold(FALSE)) return FALSE;

	PrintLSpc();
	PrintChineseChar(3244);     //妗   已
	PrintChineseChar(45*17 + 8);//葆    付
	PrintChineseChar(4377-1410);//葆    現    
	PrintChineseChar(76 *17 +9);//      金
	sprintf(abuf, "   Cash Paid      : $%10.2f\0", se_ReceiptCash); 
	if (!PrintLine(abuf, 0)) return 18;

	PrintLSpc();
	PrintChineseChar(207*17 + 8);//梑    找
	PrintChineseChar(2517);//錨          贖
	PrintChineseChar(76 *17 +9);//       金
	PrintChineseChar(37 *17 + 12);//     額  
	sprintf(abuf, "   Changes        : $%10.2f\0", se_ReceiptChange); 
	if (!PrintLine(abuf, 0)) return 18;
/*
	PrintLSpc();
	PrintChineseChar(2 *17 + 8);//縐     八		
    PrintChineseChar(26 *17 + 12);//縐   達
	PrintChineseChar(160 *17 + 13);//    通
	PrintChineseChar(197*17 + 4);//豻  餘
	PrintChineseChar(37 *17 + 12);//   額  
	sprintf(abuf, " Remaining Value: $%10.2f\0", av_ReceiptOtpNewBal); 
	if (!PrintLine(abuf, 0)) return 18;
*/
	if (!CharsBold(FALSE)) return 21;
	if (!PrintEnding()) return 23; //print "-----------"
	//cut paper
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	PrintLine(" ", 1);
	if (!AuxFullCut()) return 25;
	return 0;
}	



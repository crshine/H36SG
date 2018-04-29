// CMDOTP.cpp: implementation of the CCmdOtp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Setting.h"
#include "Customer.h"
#include "CmdOtp.h"
#include "cmdlcd.h"
#include "Msgboxwait.h"

CString AddValueInfo;//TA19-
CString NewCardPollEx;//TA19- 
CString OldCardPollEx;//TA19- 

extern int 	_TicketProcessCate;
 
extern _System g_System;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define OCTOPUS_LOG			".\\Octopus.log"

#define MIN_ERROR_CODE		10000
#define ERR_NOERR			0	//No error 
#define ERR_COM_ERR			1	//Communication error, R/W not connected
#define ERR_FILE_OPEN		2	//File open error 
#define ERR_INVPARAM		3	//Invalid parameter 
#define ERR_FILE_READ		4	//File read error 
#define ERR_COM_INVRESP		5	//Invalid response from R/W 
#define ERR_FILE_CHECKSUM	10	//File Checksum error 
#define ERR_CSCREAD			16	//Card read error 
#define ERR_CSCWRITE		17	//Card write error 
#define ERR_CSCBLOCK		19	//Card blocked 
#define ERR_NOCSC			20	//No Card found(deduct/add) 
#define ERR_INCOMP			22	//Incomplete transaction 
#define ERR_TLOGFULL		23	//TLOG full 
#define ERR_CSCBLOCKED		24	//CSC blocked by this call 
#define ERR_POLLTIME		32	//Time out polling Card/No card found 
#define ERR_POLLAUTH		34	//Card authentication error 
#define ERR_POLLRECOVER		35	//Card recovery error 
#define ERR_NOFUND			48	//Insufficient fund 
#define ERR_EXCLMT			49	//Remaining value exceed limit 
#define ERR_AVEXPIRE		50	//AV quota exceeded 
#define ERR_CTRLID			51	//Invalid Controller ID 
#define ERR_WRITEID			54	//Write ID failure 
#define ERR_DEFER_NOMORE	55	//Purse go negative 
#define ERR_DEFER_STATE		56	//Invalid defer deduct sequence 
#define ERR_USAGEEXCEED		57	//Retail usage exceeded 
#define ERR_FIRM_NONE		98	//No new firmware found 
#define ERR_FIRM_DONE		99	//Firmware upgraded done by Houskeeping 
#define ERR_OPEN_AR			101 //Open local AR error 
#define ERR_OPEN_UD			102 //Open local UD error
#define ERR_CCHS_1005		1005//CCHS/Firmware Upgrade Errors
#define ERR_CCHS_1006		1006//CCHS/Firmware Upgrade Errors
#define ERR_CCHS_1007		1007//CCHS/Firmware Upgrade Errors
#define ERR_CCHS_1008		1008//CCHS/Firmware Upgrade Errors
#define ERR_CCHS_1009		1009//CCHS/Firmware Upgrade Errors
//not define by Octopus
#define ERR_DIFFER_CARD		2000//Use different card error

extern _System g_System;
extern CLog *		g_pLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCmdOtp::DeviceStatus CCmdOtp::_DeviceStatus		= DS_Stop;
CCmdOtp* CCmdOtp::_instance				= NULL;
CWinThread* CCmdOtp::CW_Async_Poll		= NULL;
CWinThread* CCmdOtp::CW_Start_Reader	= NULL;
CWinThread* CCmdOtp::CW_Main_Poll		= NULL;
BYTE CCmdOtp::m_nLastMsgDate;
CFile CCmdOtp::m_fOtpLog;
bool CCmdOtp::Run_Start_Reader	= false;		//	堍俴梓暮 湖羲黍縐ん盄最
bool CCmdOtp::Run_Main_Poll		= false;		//	堍俴梓暮 毀葩潰聆黍縐盄最
bool CCmdOtp::Run_Async_Poll	= false;		//	堍俴梓暮 祑祭黍縐盄最
long CCmdOtp::_LastError = 0; 

bool CCmdOtp::StopRead_Status	= false;		//	礿砦黍縐梓祩,婓ShiftAcc奀妏蚚



CCmdOtp* CCmdOtp::Instance(int SpID)
{
    if (NULL == _instance) {
        _instance = new CCmdOtp(SpID);
    }
    return _instance;
}

CCmdOtp::CCmdOtp(int SpID)
:Display_Blank(-3000.0), Diaplay_Dashes(-3000.1)
{
	if (GetWindowsDirectory(_RWL_FilePath.GetBuffer(_MAX_PATH), _MAX_PATH) != 0)
	{
		_RWL_FilePath.ReleaseBuffer();
		_RWL_FilePath += "\\RWL.INI";
	}
	else
		_RWL_FilePath = _T("C:\\Windows\\Rwl.ini");

	m_nLastMsgDate = 0xFF;
	m_fOtpLog.m_hFile = CFile::hFileNull;
	_Display_Delay_Times = 0;
	_Service_Provider_ID = SpID;
	SetPollDetectCallBack(PollDetect);
}

CCmdOtp::~CCmdOtp()
{
	Stop();
}

bool CCmdOtp::IsConnection()
{
	if ( (DS_Normal==_DeviceStatus) || (DS_Busy==_DeviceStatus) || (DS_Error==_DeviceStatus))
		return true;
	else
	{
		CCmdOtp::Instance()->_LastError = 9999;//ERR_COM_ERR;
		return false;
	}
}
//湖羲黍縐ん盄最
UINT CCmdOtp::THR_Start_Reader(LPVOID)
{
	if (IsConnection()) return 0;
	TRACE(_T("Thread Start Octopus Reader: Begin \n"));
	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;
	int ret = InitComm( Peripheral.OtpPort(), Peripheral.OtpBaudRate() );
//	long ret = InitComm(4,115200);
	AddOtpLog("InitComm", ret, "");
	if (ret > MIN_ERROR_CODE) 
	{
		CString log;
		log.Format( "Start reader error: \'%s\' ", CCmdOtp::Instance()->Translate());
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), log );
		log.Format("八達通讀卡器無法回應 : [%s] !", Translate());
		::AfxMessageBox(log, MB_ICONSTOP|MB_SYSTEMMODAL);
		_DeviceStatus = DS_Stop;
	}
	else
	{
		SYSINFO Ver1;
		ret=GetSysInfo((unsigned char*)&Ver1);//TA19- checking blacklist file date
		CString tmp;
		tmp.Format("%d,%d",Ver1.BlkUpToDate,Ver1.ActionListVer);
		AddOtpLog("GetSysInfo", ret, tmp);

		if(Ver1.BlkUpToDate==0)
			MessageBox(NULL,"Blacklist outdated.Please\ncontact technical support.","",0);

		_DeviceStatus = DS_Normal;
	}

	TRACE(_T("Thread Start Octopus Reader: Exit \n"));
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//	ゐ雄迵OTP籵捅.
bool CCmdOtp::Start()
{
	Run_Start_Reader = false;
	Run_Main_Poll = false;

	if (NULL != CW_Start_Reader)
		WaitForSingleObject(CW_Start_Reader->m_hThread,1000);//脹渾盄最賦旰
	if (NULL != CW_Main_Poll)
		WaitForSingleObject(CW_Main_Poll->m_hThread,1000);//脹渾盄最賦旰
	_DeviceStatus = DS_Stop;
	THR_Start_Reader(0);	//湖羲黍縐ん盄最

	if (_DeviceStatus == DS_Stop) return false;
    CW_Main_Poll = AfxBeginThread( &THR_Main_Poll, 0 );		//毀葩潰聆黍縐盄最
	ASSERT(NULL != CW_Main_Poll );
	if (_DeviceStatus == DS_Normal)
		::SendMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)525);//礿砦
	else
		::SendMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)515);//礿砦
	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//	礿砦迵OTP籵捅.
void CCmdOtp::Stop()
{
	Run_Start_Reader = false;
	Run_Main_Poll = false;

	if (NULL != CW_Start_Reader)
		WaitForSingleObject(CW_Start_Reader->m_hThread,1000);//脹渾盄最賦旰
	if (NULL != CW_Main_Poll)
		WaitForSingleObject(CW_Main_Poll->m_hThread,1000);//脹渾盄最賦旰

	OTP_DisplayNoInService();
	_DeviceStatus = DS_Stop;
	::SendMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)515);//礿砦
}
///////////////////////////////////////////////////////////////////////////////
////////////                                                       ////////////
////////////                        祑祭黍縐                       ////////////
////////////                                                       ////////////
///////////////////////////////////////////////////////////////////////////////
//	祑祭黍縐
void CCmdOtp::Async_Poll(POLL_DETECT_CALLBACK PollDetectCallBack)
{
	Kill_Async_Poll();
	CW_Async_Poll = AfxBeginThread( &THR_Async_Poll , (void *)PollDetectCallBack);
}
void CCmdOtp::Kill_Async_Poll()
{
	AfxGetApp()->BeginWaitCursor();
	Run_Async_Poll = false;
	if (NULL != CW_Async_Poll)
		WaitForSingleObject(CW_Async_Poll->m_hThread,INFINITE);//脹渾盄最賦旰
	AfxGetApp()->EndWaitCursor();
}
//	祑祭黍縐盄最
UINT CCmdOtp::THR_Async_Poll(LPVOID lpParam/* POLL_DETECT_CALLBACK */)
{
	Run_Async_Poll = true;
	TRACE(_T("Thread Async Poll Octopus: Begin \n"));
	const short Poll_Time_Out = 15; //0.1鏃峈等弇
	const short Thread_Time_Out = 150; //0.1鏃峈等弇
	USHORT TryTimes = Thread_Time_Out / Poll_Time_Out;

	CCmdOtp * pCmd = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	POLL_DETECT_CALLBACK PollDetectCallBack = (POLL_DETECT_CALLBACK)lpParam;
	pCmd->OTP_DisplayBeforePoll();
	while( TryTimes-- )
	{
		if (!Run_Async_Poll) return 1;			//	潰聆堍俴梓暮
		//絞ヶ盄最祥蚚蕉藉肮祭恀枙
		//Sleep( Peripheral.OtpThreadStep() );	
		Sleep( 10 );	
		if ( pCmd->OTP_Poll(CardInfo, Poll_Time_Out) )
		{
			pCmd->OTP_DisplayAfterPoll(CardInfo._Remain);
			PollDetectCallBack(CardInfo);
			break;
		}
	}

	TRACE(_T("Thread Async Poll Octopus: End \n"));
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
//	OTP籵捅盄最.
UINT CCmdOtp::THR_Main_Poll(LPVOID)  // OTP Payment Check Point 001
{
	Run_Main_Poll = true;
	Sleep(10);//Give time to initcomm
	TRACE(_T("Thread Poll Octopus: Begin \n"));
	CString dsp;
	//彸芞湖羲揹諳甜迵"OTP"(匐湛籵)黍縐ん籵捅.
	CCmdOtp * pCmd = CCmdOtp::Instance();
	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;
	//PATRON_LOG CardLogInfo;//斐膘黍縐遣湔.
	PATRON CardInfo;
	char	PollBuf[512];
	bool PollRet;
	UINT nCheckCount = 0;
	while ( Run_Main_Poll )
	{
		Sleep( Peripheral.OtpThreadStep() );
		//植OTP黍縐ん黍杅擂
		if (!Run_Main_Poll) return 1;			//	潰聆堍俴梓暮
		if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 0)) 
		{ Sleep(300); continue;}	//	紱釬埜疆 //UCH 3- faster
//		{ Sleep(1000); continue;}	//	紱釬埜疆
		//int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	紱釬埜玿
		//ASSERT (TRUE == b);
		if(StopRead_Status) PollRet=0;
		else
		PollRet = pCmd->OTP_Poll(CardInfo, 1);
		if (PollRet)
		{
			nCheckCount = 0;
//			[BW]: 22Jun05 Cancel Display MOP Balance
			//pCmd->OTP_DisplayAfterPoll(CardInfo._Remain);
			pCmd->_PollDetectCallBack(CardInfo);//眒冪黍善杅擂賸
			
			showTip("請把八達通卡拿走...", true, false);
			
//	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	紱釬埜疆
			while (1) 
			{
				if (Poll(0, 1, PollBuf) == 100032) break;
//				if (PollEx(0, 1, PollBuf) == 100032) break;
				Sleep(1000);
			}
//			ReleaseMutex(g_System.m_OprBusyMutex);	
			::Sleep(2000);	//絞珨跺衄虴腔蝠眢徹最俇傖綴腔ㄛ脹渾3鏃綴輛俴狟棒肮欴腔蝠眢  
			//[JC]20060308  increase from 2000 to 500 解決閃電手問題
//			showTip("請拍八達通卡或插入磁卡...", true, false);
			showTip("請拍八達通或掃瞄條碼票...", true, false); //UCH 3-barcode message tips
		}
		else{
			
			if (_LastError == 32) {pCmd->OTP_DisplayBeforePoll();nCheckCount = 0;}
//	TA11A 2009 ITEM4
			//			else if (_LastError == 1)
			else if (_LastError == 1 || _LastError==5)
			{
				nCheckCount ++;
				if (nCheckCount > 0) 
				{
					ReleaseMutex(g_System.m_OprBusyMutex);			//	紱釬埜玿
					break;
				}
				dsp.Format("發現錯誤 : [%s] ", Translate());
				showTip(dsp, true);
			}else if ((_LastError == 9999) || (_LastError == 5)|| (_LastError==16) || (_LastError==17) || (_LastError==19)|| (_LastError==34)){
				dsp.Format("發現錯誤 : [%s] ", Translate());
				showTip(dsp, true);
			}else {
				nCheckCount = 0;
				dsp.Format("發現錯誤 : [%s] \n 請把八達通卡拿走, 然後按確定", Translate());
//				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);//(dsp, MB_ICONWARNING);
//TA11A ken20090817
				if(_LastError!=22 && _LastError!=21 && _LastError!=48)
					::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);//(dsp, MB_ICONWARNING);
//				OtpErrProcess();
			}
		}
		int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	紱釬埜玿
		ASSERT (TRUE == b);
	} // while
	DWORD reta = PortClose();
	AddOtpLog("PortClose", reta, "");
	_DeviceStatus = DS_Stop;
//	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)515);//礿砦
//	showTip("八達通讀卡器已經停止工作!");

//TA11A 2009 item4
	if(_LastError==1 || _LastError==5)
	{
		::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)545);//disconnected
//		showTip("八達通讀卡器已經停止工作!");
		showTip(Translate(0,_LastError));
	}

	TRACE(_T("Thread Poll Octopus: Exit \n"));
	return 0;
}


////////////////////////////////////////////////////////////////////////
void CCmdOtp::SetPollDetectCallBack(POLL_DETECT_CALLBACK func/* = NULL*/)
{
	if (func != NULL)
		_PollDetectCallBack = func;
	else
		_PollDetectCallBack = PollDetect;
}

void CALLBACK CCmdOtp::PollDetect(const PATRON &CardInfo)
{
	_TicketProcessCate=1;
	//潰聆善縐, 蘇�玴肩羶妊鶶﹋翹�楷汜.
	CCustomer::COtpUserExitCarPark Exit;
	Exit.TradeCommon(CardInfo);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool CCmdOtp::OTP_InitComm()
{
	if ( !IsConnection() ) return false;
	CSetting::CPeripheral &Peripheral = CSetting::Instance()->m_Peripheral;
	long ret = InitComm(Peripheral.OtpPort(), Peripheral.OtpBaudRate());
	AddOtpLog("InitComm", ret, "");
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	else
	{
		OTP_Display(Diaplay_Dashes, Diaplay_Dashes, Red, Successful);
		Sleep(100);
		OTP_Display(Diaplay_Dashes, Diaplay_Dashes, Red, Fail);
		Sleep(100);
		OTP_Display(Display_Blank , Display_Blank , Green, Successful);
		
		return true;
	}
}
//壽敕扢掘
void CCmdOtp::OTP_PortClose()
{
	DWORD ret = PortClose();
	AddOtpLog("PortClose", ret, "");
} 
//�篲�笭离
void CCmdOtp::OTP_Reset()
{
	if ( !IsConnection()) return;
	DWORD ret = Reset();
	AddOtpLog("Reset", ret, "");
}
//揭燴蝠遙恅璃
bool CCmdOtp::OTP_HouseKeeping()
{
	if ( !IsConnection() ) return false;
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE); 
	OTP_PortClose();
	Sleep(100);
	OTP_InitComm();
	Sleep(100);
	int ret = HouseKeeping();
	ReleaseMutex(g_System.m_OprBusyMutex);
	AddOtpLog("HouseKeep", ret, "");
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	return true;
}
void CCmdOtp::Set_Display_Delay()
{
	COleDateTimeSpan ts;
	ts.SetDateTimeSpan(0, 0, 0, 10);

	_Display_Delay_Times = 10;	//10棒拸Ч轄猁⑴腔珆尨飲祥昹珆尨.
	_Display_Delay_Time = COleDateTime::GetCurrentTime();
	_Display_Delay_Time += ts;
}

bool CCmdOtp::In_Display_Delay()
{
	if (0 == _Display_Delay_Times) return false;
	_Display_Delay_Times--;
	if (COleDateTime::GetCurrentTime() > _Display_Delay_Time) return false;
	return true;
}

//raw 珆尨滲杅
void  CCmdOtp::OTP_Display(double Amount, double Remain, Color c, Sound s)
{
	if ( !IsConnection() ) return ;
	long LineAmount = (long)(Amount * 10);
	long LineRemain = (long)(Remain * 10);
	int ret = TxnAmt(LineAmount, LineRemain, (BYTE)c, (BYTE)s);
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
	}
}
//諾玿珆尨
void CCmdOtp::OTP_DisplayIdle()
{
	OTP_Display(0.0, Display_Blank, None, NoSound);
}
//祥督昢珆尨
void CCmdOtp::OTP_DisplayNoInService()
{
	OTP_Display(Diaplay_Dashes, Diaplay_Dashes, None, NoSound);
}
void CCmdOtp::OTP_DisplayBeforeDeduct(const double Amount)
{
	ASSERT( 0 <= Amount);
	OTP_Display(Amount, Display_Blank, None, NoSound);
}
void CCmdOtp::OTP_DisplayBeforeAddValue(const double Amount)
{
	ASSERT( 0 <= Amount);
	OTP_Display(Amount, Display_Blank, None, NoSound);
}
//彸芞黍縐ヶ腔珆尨.
void CCmdOtp::OTP_DisplayBeforePoll()
{
	if ( In_Display_Delay() ) return;
	OTP_Display(Display_Blank, Display_Blank, None, NoSound);
}
//彸芞黍縐綴腔珆尨.
void CCmdOtp::OTP_DisplayAfterPoll(const double Remain)
{
	OTP_Display(Display_Blank, Remain, None, NoSound);
}
//Enquiry display. TA11A 2009 item5
void CCmdOtp::OTP_DisplayEnquiry(const double Remain)
{
	OTP_Display(Display_Blank, Remain, None, NoSound);
}
//彸芞黍縐ヶ腔珆尨.
void CCmdOtp::OTP_DisplayAfterEnquiry()
{
//	if ( In_Display_Delay() ) return;
	OTP_Display(Display_Blank, Display_Blank, None, NoSound);
}

//掛華晤瘍
bool CCmdOtp::OTP_WriteID(const short ID)
{
	if ( !IsConnection() ) return false;
	ASSERT( (0<=ID) && (9999>=ID) );
	int ret = WriteID(ID);
	CString spid;
	spid.Format("SPID=%d", ID);
	AddOtpLog(L"WriteID", ret, spid);

	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	return true;}

long CCmdOtp::OTP_GetDevID()
{
	VER_TIME a;
	if (OTP_TimeVer(a)) return a._DevID;
	else return 0;
}

//扢离奀潔,殿隙唳掛瘍.
bool CCmdOtp::OTP_TimeVer(VER_TIME &VerTime)
{
	if ( !IsConnection() ) return false;
	int ret = TimeVer((BYTE *)&VerTime);
	CString ver;
	ver.Format("DID:%d,OID:%d,Time:%d,CID:%d,KV:%d,EV:%d,BLV:%d,FV:%d,CV:%d,CSN:%d", 
				VerTime._DevID, 	/* Device ID */
				VerTime._OperID,	/* Operator ID */
				VerTime._DevTime,	/* Device Time */
				VerTime._CompID,	/* Company ID */
				VerTime._KeyVer,	/* Key Version */
				VerTime._EODVer,	/* EOD Version */
				VerTime._BLVer,		/* Blacklist Version */
				VerTime._FIRMVer,	/* Firmware Version */
				VerTime._CCHSVer,	/* CCHS MSG ID */
				VerTime._CSSer);	/* CS Serial #, Loc ID */
	AddOtpLog(L"TimeVer", ret, ver);

	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	if (VerTime._CSSer != CSetting::Instance()->m_BaseSystemSetting.SystemID())
		OTP_WriteID(CSetting::Instance()->m_BaseSystemSetting.SystemID());
	return true;
}

void CCmdOtp::WaitForOtpRemove(bool bNeedInitCheck)
{
	if ( !IsConnection() ) return;
	PATRON CardInfo;
	char	PollBuf[512];
	if (bNeedInitCheck)
	{
		if (Poll(0, 1, PollBuf) != 100032) showTip("請手動取出八達通卡...", true, false);
		else return;
	}else showTip("請取出八達通卡...", true, false);
	while (1) 
	{
		if (_DeviceStatus == DS_Stop) return;
		if (Poll(0, 1, PollBuf) == 100032) break;
		if (Poll(0, 1, PollBuf) == 100001) break;
		Sleep(1000);
		
	}
}

//TA11A 2009 item2
void CCmdOtp::WaitOtpRemove()
{
	if ( !IsConnection() ) return;
	PATRON CardInfo;
	char	PollBuf[512];
	while (1) 
	{
		if (_DeviceStatus == DS_Stop) return;
		if (Poll(0, 1, PollBuf) == 100032) break;
		if (Poll(0, 1, PollBuf) == 100001) break;
		if (Poll(0, 1, PollBuf) == 100005) break;
		Sleep(1000);
		
	}
}



//TA11A 2009 item2 潰聆匐湛籵縐
bool CCmdOtp::OTP_Poll()
{
#ifdef _DEBUG
//	_LastError = 19;
//	return false;
#endif
	if ( !IsConnection() ) return false;
	const short WITH_PATRON = 0;
	char	PollBuf[512];
//	int ret = Poll(0, 1, PollBuf);
	int ret = PollEx(0, 1, PollBuf); //TA19- for addvalue, Using PollEx, not Poll for it can't work on new card,
	CString remark;
	remark.Format("Subcom:%d, PollBuf:%s", WITH_PATRON, (LPSTR)PollBuf);

	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
//TA11A 2009 item3
		if(_LastError==1 || _LastError==5)
		::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)545);//disconnected
//		showTip(Translate(0,_LastError));
		return false;
	}
	else
		return true;
}

//潰聆匐湛籵縐,諦誧陓洘
bool CCmdOtp::OTP_Poll(PATRON &Patron, short TimeOut/* =1*/)
{
	if ( !IsConnection() ) return false;
	ASSERT( (0<TimeOut) && (300>TimeOut) );
	const short WITH_PATRON = 0;
//	char	PollBuf[512];
	char	PollBuf[1024];//TA18-

//	MessageBox(NULL,"",tmp,0);
//	return FALSE;

//	int ret = Poll(WITH_PATRON, TimeOut, PollBuf);
	int ret = PollEx(WITH_PATRON, TimeOut, PollBuf);//TA18-

	CString remark;
	remark.Format("Subcom:%d, PollBuf:%s", WITH_PATRON, (LPSTR)PollBuf);
	if (ret != 100032)
	{
		if (ret <= 100000) 
		{
			AddOtpLog("Pollx", ret, remark);
			
			unsigned char r[1024];
			int test= GetExtraInfo(0, 1, r);//TA18-test
			
			AddValueInfo.Format("%s",r);


			CString tmp;
			tmp.Format("%d,%s",test,r);
			
			tmp.Format("%d,%d,%s",ret,test,r);
//			MessageBox(NULL,tmp,"test",0);
		}
		else AddOtpLog("Poll", ret, "");


	}
	
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		/*
		if (ERR_POLLTIME == _LastError)
		{
			::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)525);//諾玿
		}
		else
			::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)545);//渣昫
		*/
		return false;
		
	}
//	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)535);//衄縐

	char seps[]   = ",-";
	char *token;

	Patron._Remain		= 0.1 * static_cast<double>(ret);
	token = strtok( PollBuf, seps );
//	OldCard		= 'O' + static_cast<CString>(token);
	Patron._CardNo	= 'O' + static_cast<CString>(token);

//	Patron._CardNo.Format("%s00",Patron._CardNo); // TA19- test 10 byte card number.
//	MessageBox(NULL,Patron._CardNo,"test",0);

	token = strtok( NULL, seps );
	OldCardPollEx	= 'O' + static_cast<CString>(token);
//	MessageBox(NULL,Patron._CardNo,"test2",0);

// 	Patron._CardNo=Patron._CardNo+"00";// TA19- test 10 byte card number.
// 	OldCardPollEx=OldCardPollEx+"00";//TA19- test

	if(Patron._CardNo[1]=='0' && Patron._CardNo[2]=='0')
		Patron._CardNo=OldCardPollEx;

//	OldCardPollEx=OldCardPollEx+"00";//TA19- test
//	else		OldCardPollEx=Patron._CardNo;

	CString tmp;
	tmp=OldCardPollEx;
	OldCardPollEx=Patron._CardNo;
	Patron._CardNo=tmp;

	NewCardPollEx=Patron._CardNo;

//	MessageBox(NULL,Patron._CardNo,OldCardPollEx,0);


	token = strtok( NULL, seps );
	Patron._AddValueDetail
						= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron._LastAddValueDevice
						= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron._Class		= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron._Language	= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron._AvailableAmount
						= 50 * _ttol(static_cast<CString>(token));


	return true;
}


//潰聆匐湛籵縐,諦誧陓洘  - TA19- for PollEx()
bool CCmdOtp::OTP_PollEx(PATRON &Patron, short TimeOut/* =1*/)
{
	if ( !IsConnection() ) return false;
	ASSERT( (0<TimeOut) && (300>TimeOut) );
	const short WITH_PATRON = 0;
//	char	PollBuf[512];
	char	PollBuf[1024];//TA18-

//	MessageBox(NULL,"",tmp,0);
//	return FALSE;

//	int ret = Poll(WITH_PATRON, TimeOut, PollBuf);
	int ret = PollEx(WITH_PATRON, TimeOut, PollBuf);//TA18- OTP company test0104

	CString remark;
	remark.Format("Subcom:%d, PollBuf:%s", WITH_PATRON, (LPSTR)PollBuf);
	if (ret != 100032)
	{
		if (ret <= 100000) 
		{
			AddOtpLog("Pollx", ret, remark);
			
			unsigned char r[1024];
			int test= GetExtraInfo(0, 1, r);//TA18-test
			
			AddValueInfo.Format("%s",r);


			CString tmp;
			tmp.Format("%d,%s",test,r);
			
			tmp.Format("%d,%d,%s",ret,test,r);
//			MessageBox(NULL,tmp,"test",0);
		}
		else AddOtpLog("Pollx", ret, "");


	}
	
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		/*
		if (ERR_POLLTIME == _LastError)
		{
			::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)525);//諾玿
		}
		else
			::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)545);//渣昫
		*/
		return false;
		
	}
//	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)535);//衄縐

	char seps[]   = ",-";
	char *token;

	Patron._Remain		= 0.1 * static_cast<double>(ret);
	token = strtok( PollBuf, seps );
//	OldCard		= 'O' + static_cast<CString>(token);
	Patron._CardNo	= 'O' + static_cast<CString>(token);
//	MessageBox(NULL,Patron._CardNo,"test",0);

	token = strtok( NULL, seps );
	OldCardPollEx	= 'O' + static_cast<CString>(token);
//	MessageBox(NULL,Patron._CardNo,"test2",0);

	if(Patron._CardNo[1]=='0' && Patron._CardNo[2]=='0')
		Patron._CardNo=OldCardPollEx;

//	else		OldCardPollEx=Patron._CardNo;


	token = strtok( NULL, seps );
	Patron._AddValueDetail
						= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron._LastAddValueDevice
						= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron._Class		= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron._Language	= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron._AvailableAmount
						= 50 * _ttol(static_cast<CString>(token));


	return true;
}

//潰聆匐湛籵縐,諦誧陓洘 + 堤釦晤瘍 + 盪妢暮翹
bool CCmdOtp::OTP_Poll(PATRON_LOG &Patron_Log, short TimeOut/* =1*/)
{
	if ( !IsConnection() ) return false;
	_MarkTime = 0;
	char _PollBuf[512];
	ASSERT( (0<TimeOut) && (300>TimeOut) );
	const short WITH_PATRON_LOG = 3;
	int ret = Poll(WITH_PATRON_LOG, TimeOut, _PollBuf);
	CString remark;
	remark.Format("Subcom:3, PollBuf:%s", (LPSTR)_PollBuf);
	if (ret != 100032)
	{
		if (ret <= 100000) AddOtpLog("Poll", ret, remark);
		else AddOtpLog("Poll", ret, "");
	}

	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}

	char seps[]   = ",-";
	char *token;

	Patron_Log._Remain		= 0.1 * static_cast<double>(ret);
	token = strtok( _PollBuf, seps );
	Patron_Log._CardNo		= 'O' +static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._AddValueDetail
							= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._LastAddValueDevice
							= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._Class		= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._Language	= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._AvailableAmount
						= 50 * _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._ManufactureID
						= static_cast<CString>(token);
			
	/*const*/ COleDateTime TimeBase;
	TimeBase.SetDateTime(2000, 1, 1, 0, 0, 0); //"1 January 2000"
	COleDateTimeSpan Hour8(0,8,0,0);
	COleDateTimeSpan ts;

	CString Wanted;
	Wanted.Format("ABCD%02X", _Service_Provider_ID);

	for(int i = 0; i < 10; i++)
	{
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._SP_ID			= static_cast<CString>(token);
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._TransactionAmt	= 0.1 * static_cast<double>(_ttol(static_cast<CString>(token)));
		token = strtok( NULL, seps );
		ts.SetDateTimeSpan( 0, 0, 0, _ttol(static_cast<CString>(token)) );
		Patron_Log._Log[i]._TransactionTime = TimeBase + ts + Hour8;
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._MachineID		= static_cast<CString>(token);
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._ServiceInfo		= static_cast<CString>(token);
		if (Patron_Log._Log[i]._ServiceInfo.Find(Wanted) >=0)
		{
			_MarkTime = Patron_Log._Log[i]._TransactionTime;
			break;
		}
	}
	return true;
}

//潰聆匐湛籵縐, 盪妢暮翹
bool CCmdOtp::OTP_Poll_2(PATRON_LOG &Patron_Log, short TimeOut/* =1*/)
{
	if ( !IsConnection() ) return false;
	_MarkTime = 0;
	char _PollBuf[512];
	ASSERT( (0<TimeOut) && (300>TimeOut) );
	const short WITH_PATRON_LOG = 2;
	int ret = Poll(WITH_PATRON_LOG, TimeOut, _PollBuf);
	CString remark;
	remark.Format("Subcom:2, PollBuf:%s", (LPSTR)_PollBuf);

//	MessageBox(NULL,remark,"",0);
#ifdef _DEBUG
//	ret = 100019;
#endif

	if (ret != 100032)
	{
		if (ret <= 100000) AddOtpLog("Poll", ret, remark);
		else AddOtpLog("Poll", ret, "");
	}

	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}

	char seps[]   = ",-";
	char cs_seps[]   = ",";
	char *token;

	Patron_Log._Remain		= 0.1 * static_cast<double>(ret);
	token = strtok( _PollBuf, seps );
	Patron_Log._CardNo		= 'O' +static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._AddValueDetail
							= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._LastAddValueDevice
							= static_cast<CString>(token);
	token = strtok( NULL, seps );
	Patron_Log._Class		= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._Language	= _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._AvailableAmount
						= 50 * _ttol(static_cast<CString>(token));
	token = strtok( NULL, seps );
	Patron_Log._ManufactureID
						= static_cast<CString>(token);
			
	/*const*/ COleDateTime TimeBase;
	TimeBase.SetDateTime(2000, 1, 1, 0, 0, 0); //"1 January 2000"
	COleDateTimeSpan Hour8(0,8,0,0);
	COleDateTimeSpan ts;

	CString Wanted;
	Wanted.Format("ABCD%02X", _Service_Provider_ID);

	for(int i = 0; i < 10; i++)
	{
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._SP_ID			= static_cast<CString>(token);
//		token = strtok( NULL, seps );
		token = strtok( NULL, cs_seps );//TA17- use cs seps without "-"
		Patron_Log._Log[i]._TransactionAmt	= 0.1 * static_cast<double>(_ttol(static_cast<CString>(token)));
		token = strtok( NULL, seps );
		ts.SetDateTimeSpan( 0, 0, 0, _ttol(static_cast<CString>(token)) );
		Patron_Log._Log[i]._TransactionTime = TimeBase + ts + Hour8;
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._MachineID		= static_cast<CString>(token);
		token = strtok( NULL, seps );
		Patron_Log._Log[i]._ServiceInfo		= static_cast<CString>(token);
		if (Patron_Log._Log[i]._ServiceInfo.Find(Wanted) >=0)
		{
			_MarkTime = Patron_Log._Log[i]._TransactionTime;
			break;
		}
	}
	return true;
}
//淩淏妏蚚腔諶煤滲杅, 婦蚾賸珨跺潰聆肮珨桲縐腔滲杅.
bool CCmdOtp::OTP_Deduct(const CString CardNo, const double Amount)//諶煤
{
	if ( !IsConnection()) return false;
	const short Poll_Time_Out = 15; //0.1鏃峈等弇
	const short Thread_Time_Out = 50; //5鏃囀斛剕俇傖.
	USHORT TryTimes = Thread_Time_Out / Poll_Time_Out;

	PATRON CardInfo;
//	OTP_DisplayBeforeDeduct(Amount);
	while( TryTimes-- )
	{
		Sleep( 1 );	//絞ヶ盄最祥蚚蕉藉肮祭恀枙
		if (!OTP_Poll(CardInfo, Poll_Time_Out) )
			continue;
		if (CardNo == CardInfo._CardNo)
			break;
		else
		{
			_LastError = ERR_DIFFER_CARD;
			return false;
		}
	}

	return OTP_Deduct(Amount);
}
//諶煤
bool CCmdOtp::OTP_Deduct(const double Amount)
{
	if ( !IsConnection() ) return false;
	double TmpAmt = Amount;
	long Amt10Cents = (TmpAmt * 10);
	BYTE AIInfo[65];
	AIInfo[0] = 7;
	AIInfo[1] = 7;
	AIInfo[2] = 0xAB;
	AIInfo[3] = 0xCD;
	AIInfo[4] = _Service_Provider_ID;

	//	ASSERT((long)(Amount * 100) == Amt10Cents * 10);//Amount's value at 100cents must zero.
	int ret = Deduct(Amt10Cents, (LPBYTE)AIInfo);
	CString remark;
	remark.Format("Amt:%d, AI:%s", Amt10Cents, (LPSTR)AIInfo);
	if (ret <= 100000) AddOtpLog("Deduct", ret, remark);
	else AddOtpLog("Deduct", ret, "");
	
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;	
		return false;
	}

	Set_Display_Delay();
	return true;
}

//諶煤,甜鳳�±銃�
bool CCmdOtp::OTP_Deduct(const double Amount, double &Remain, long ReceiptNo, int TransType, CString CardNo)
{
	if ( !IsConnection() ) return false;
	BYTE AIInfo[65];
	long l = (long)ReceiptNo % 10000;
	AIInfo[0] = ReceiptNo / 256; //receipt byte 0
	AIInfo[1] = ReceiptNo  % 256; //receipt byte 1
	AIInfo[2] = 0; //rfu
	AIInfo[3] = 0; //rfu
	AIInfo[4] = 0; //rfu
	switch (TransType)
	{
	case 0: AIInfo[5] = 1; AIInfo[6] = 1; break;
	case 1: AIInfo[5] = 2; AIInfo[6] = 1; break;
	case 2: AIInfo[5] = 2; AIInfo[6] = 2; break;
	case 3: AIInfo[5] = 2; AIInfo[6] = 3; break;
	case 4: AIInfo[5] = 2; AIInfo[6] = 4; break;
	case 5: AIInfo[5] = 2; AIInfo[6] = 5; break;
	case 6: AIInfo[5] = 2; AIInfo[6] = 6; break;
	default: AIInfo[5] = 1; AIInfo[6] = 1; break;
	}
	CString AI;
	AI.Format("[%03d][%03d][%03d][%03d][%03d][%03d][%03d]=2B(Receipt)+3B(RFU)+2B(T.Type)", 
		      AIInfo[0], AIInfo[1], AIInfo[2], AIInfo[3], AIInfo[4], AIInfo[5], AIInfo[6]);
	
	long Amt10Cents = static_cast<long>(Amount * 10);
	ASSERT(static_cast<long>(Amount * 100) == Amt10Cents * 10);//Amount's value at 100cents must zero.
	CString remark;
	remark.Format("Deduct Amt/10c:%d, AI:%s", Amt10Cents, AI);
	int ret;
	int ret_Extra;
	PATRON CardInfo;
	LONG DeductTime;

	CTime t1,t2;

	while (1)
	{
		ret = Deduct(Amt10Cents, (LPBYTE)AIInfo);
		t1=CTime::GetCurrentTime();
		if (ret <= 100000) 
		{
			AddOtpLog("Deduct", ret, remark);

			unsigned char ExtraInf[1024];
			ret_Extra= GetExtraInfo(0, 1, ExtraInf);//TA19- GetExtraInfo, refresh addvalue info after deduct
			AddValueInfo.Format("%s",ExtraInf);
			AddOtpLog("GetExtra", ret_Extra, ExtraInf);

			break;
		}
		else 
		{
			AddOtpLog("Deduct", ret, remark);
			if (!CardNo.IsEmpty() && ret == 100022)
			{
				CCmdLcd::Instance()->LCD_Display("OCTOPUS DEDUCT ERROR","Try the SAME card!",CCmdLcd::DA_Center);
				showTip("交易未完成!請重試",true);
//TA11A 2009 item3 new messagebox for waiting 20s
//				MsgBoxWait dlg;
//					if(!dlg.DoModal())
				if (::AfxMessageBox("交易未完成!請重試", MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL) == IDCANCEL) // [PY]: 07 Jun 2005 - added msg box
//				if (::AfxMessageBox("交易未完成!請重試", MB_ICONWARNING | MB_OKCANCEL|MB_SYSTEMMODAL) == IDCANCEL) // [PY]: 07 Jun 2005 - added msg box
				{
					_LastError = 22;
					return false;
				}
				CString str;
				BOOL ret1;
				do 
				{
					//CString a;
					ret1 = OTP_Poll(CardInfo, 20);
					if (ret1 && (CardInfo._CardNo == CardNo)) break;
//					if (!ret1 && (_LastError == 32)) {Sleep(1000); continue;}
					if ((_LastError != 22) && (_LastError != 32))
					{
//TA11A 20090824 
						OTP_DisplayBeforeDeduct(Amount);
						str.Format("發現錯誤 : [%s] ", Translate());
						showTip(str, true);
						if (_LastError != 19&&_LastError != 24&&_LastError != 16 && _LastError != 34)
						::AfxMessageBox(str, MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL);
						_LastError = 22;
					}
					if (!ret1 && (_LastError == 32)) 
					{
						str.Format("錯卡: 請重試(八達通卡編號 %s)", CardNo.Mid(1,8));
						if(CardNo.GetLength()>10)
							str.Format("錯卡: 請重試(八達通卡編號 %s)", CardNo.Mid(1,10));
						t2=CTime::GetCurrentTime();
						if(t2-t1>=20)
							if (::AfxMessageBox(str, MB_ICONWARNING | MB_OKCANCEL|MB_SYSTEMMODAL) == IDCANCEL)
							{
								_LastError = 22; return FALSE;
							}
							//						Sleep(1000);
							continue;
					}
	
					CString a;
					a.Format("Octopus No: %08s", CardNo.Mid(1, 8));
// 					if(CardNo.GetLength()>10)
// 						a.Format("Octopus No: %10s", CardNo.Mid(1, 10));//TA19- 10 byte card number
					CCmdLcd::Instance()->LCD_Display("NOT SAME CARD!",a,CCmdLcd::DA_Center);
					//CCmdLcd::Instance()->LCD_Display("NOT SAME CARD!"," ",CCmdLcd::DA_Center);
					::AfxMessageBox(CardNo, MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL);
//ta11a ken20090817
					str.Format("錯卡: 請重試(八達通卡編號 %s)", CardNo.Mid(1,8));
					if(CardNo.GetLength()>10)
						str.Format("錯卡: 請重試(八達通卡編號 %s)", CardNo.Mid(1,10));
					showTip(str,true);
					t2=CTime::GetCurrentTime();
					//TA11A 2009 item3  for waiting 20s
					if(t2-t1<20)
						::AfxMessageBox(str, MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL);
					else
					if (::AfxMessageBox(str, MB_ICONWARNING | MB_OKCANCEL|MB_SYSTEMMODAL) == IDCANCEL)
					{
						_LastError = 22; return FALSE;
					}
				}while (1);
			}else
				break;
		}
	}
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	Remain = 0.1 * static_cast<double>(ret);
	Set_Display_Delay();
	return true;
}
//淩淏妏蚚腔喃硉滲杅, 婦蚾賸珨跺潰聆肮珨桲縐腔滲杅.
bool CCmdOtp::OTP_AddValue(double Amount, double & Remain, CString CardNo)//喃硉
{
	if ( !IsConnection() ) return false;
	PATRON CardInfo;
	OTP_DisplayBeforeAddValue(Amount);
	
	long Amt10Cents = static_cast<long>(Amount * 10);
	ASSERT(static_cast<long>(Amount * 100) == Amt10Cents * 10);//Amount's value at 100cents must zero.
	
	char AIInfo[65];
	memset(AIInfo, 0, 10);
	
	long ReceiptNo = CSetting::Instance()->m_Account.GetReceiptNo();
	long l = (long)ReceiptNo % 10000;
	AIInfo[0] = ReceiptNo / 256; //receipt byte 0
	AIInfo[1] = ReceiptNo  % 256; //receipt byte 1
	AIInfo[2] = 0; //rfu
	AIInfo[3] = 0; //rfu
	AIInfo[4] = 0; //rfu
	AIInfo[5] = 0;
	AIInfo[6] = 0;
	CString AI;
	AI.Format("[%03d][%03d][%03d][%03d][%03d][%03d][%03d]=2B(Receipt)+3B(RFU)+2B(T.Type)", 
		      AIInfo[0], AIInfo[1], AIInfo[2], AIInfo[3], AIInfo[4], AIInfo[5], AIInfo[6]);

	CString remark;
	remark.Format("Amt:%d, AvType=7, AI:%s", Amt10Cents, AI);
	
	int ret;
	bool is22err = false;
	CTime t1,t2;
	while (1)
	{
		ret = AddValue(Amt10Cents, 7, (LPBYTE)AIInfo);
//TA11A 2009 item3 for waiting 20s
#ifdef _DEBUG
		ret=100022;
#endif
		t1=CTime::GetCurrentTime();
		if (ret <= 100000) 
		{
			AddOtpLog("AddValue", ret, remark);
			
			break;
		}
		else 
		{
			AddOtpLog("AddValue", ret, remark);
			if (!CardNo.IsEmpty() && ret == 100022)
			{
//TA11A 2009 item 3 , program will exit once running these codes.
//				CCmdLcd::Instance()->LCD_Display("OCTOPUS ADD-VALUE ERROR","Try the SAME card!",CCmdLcd::DA_Center);
				showTip("交易未完成!請重試",true);
				::AfxMessageBox("交易未完成!請重試", MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL);
				CString str;
				
				BOOL ret1;
				do 
				{
					Sleep(1000);
					ret1 = OTP_Poll(CardInfo);
//TA11A 2009
					OTP_DisplayBeforeAddValue(Amount);
					if (ret1 && (CardInfo._CardNo == CardNo)) break;
//					if (!ret1 && (_LastError == 32)) {Sleep(1000);continue;}

//					str.Format("錯卡: 請重試八達通卡編號[%s]", CardNo);
					str.Format("錯卡: 請重試(八達通卡編號[%s])", CardNo);

//TA11A 20090920 item3 for waiting 20s 
					if (!ret1 && (_LastError == 32)) 
					{
						t2=CTime::GetCurrentTime();
						if(t2-t1>=20)
							if (::AfxMessageBox(str, MB_ICONWARNING | MB_OKCANCEL|MB_SYSTEMMODAL) == IDCANCEL)
							{
								_LastError = 22; return FALSE;
							}
							//						Sleep(1000);
							continue;
					}

					CString a;
					a.Format("Octopus No: %08d", CardNo.Mid(1, 8));
					CCmdLcd::Instance()->LCD_Display("NOT SAME CARD!",a,CCmdLcd::DA_Center);
//TA11A 2009 item3 for waiting 20s
					t2=CTime::GetCurrentTime();
					if(t2-t1<20)
						::AfxMessageBox(str, MB_ICONWARNING | MB_OK|MB_SYSTEMMODAL);
					else
				  	  if (::AfxMessageBox(str, MB_ICONWARNING | MB_OKCANCEL|MB_SYSTEMMODAL) == IDCANCEL)
					  {
						_LastError = 22; return FALSE;
					  }
				}while (1);
			}else break;
		}
	}
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	
	Remain = 0.1 * static_cast<double>(ret);
	OTP_Display(Amount, Remain, Green, NoSound);
	Set_Display_Delay();

	
	unsigned char ExtraInf[1024];
	ret= GetExtraInfo(0, 1, ExtraInf);//TA19- GetExtraInfo,  after addvalue
	AddValueInfo.Format("%s",ExtraInf);
	AddOtpLog("GetExtra", ret, ExtraInf);

	return true;
}

//汜傖蝠遙恅璃,甜鳳�■遙銜躁�靡備
bool CCmdOtp::OTP_XFile(CString &XFileName)
{
	if ( !IsConnection() ) return false;
	char Buf[_MAX_PATH];
	OTP_StopRead(true);  //modified  060817 [cc]
	Sleep(1000);
	int ret = XFile(Buf);
	OTP_StopRead(false);
	AddOtpLog("XFile", ret, "");
	if (ret > MIN_ERROR_CODE) 
	{
		_LastError = ret - 100000;
		return false;
	}
	XFileName = Buf;
	return true;
}

//get last error code
int CCmdOtp::GetLastError(){return _LastError;}

//鳳�●簊鯗欐�
CString CCmdOtp::Translate(int Language/*=0*/, int ErrCode/* = -1*/) //language = 0;(chinese) = 1(english); =2;(both). 
//if the both language is returned, the 2 sentences are joined by a "\n"
{
	CString English, Chinese;
	if (ErrCode == -1) ErrCode = _LastError;
	switch (ErrCode)
	{
	case 00:
		English = "";
		Chinese = "";
		break;
	case 01: 
		English = "Octopus Error : Communication error, R/W not connected";
		Chinese = "八達通錯誤: 未能接駁八達通收費器";
	break;
	case 02: 
		English = "Octopus Error : File open error";
		Chinese = "八達通錯誤: 文件打開錯誤";
	break;
	case 03: 
		English = "Octopus Error : Invalid parameter";
		Chinese = "八達通錯誤: 發現錯誤的參數";
	break;
	case 04: 
		English = "Octopus Error : File read error";
		Chinese = "八達通錯誤: 文件讀取錯誤";
	break;
	case 05: 
		English = "Octopus Error : Invalid response from R/W";
		Chinese = "八達通錯誤: 未能接駁八達通收費器";
	break;
	case 10: 
		English = "Octopus Error : File Checksum error";
		Chinese = "八達通錯誤: 文件校驗碼發現錯誤";
		break;
	case 16: 
		English = "Octopus Error : Card read error";
		Chinese = "八達通錯誤: 讀卡錯誤, 請重試";
		break;
	case 17: 
		English = "Octopus Error : Card write error";
		Chinese = "八達通錯誤: 讀卡錯誤, 請重試";
		break;
	case 19: 
		English = "Octopus Error : Card blocked";
		Chinese = "八達通錯誤: 此卡失效";
		break;
	case 20: 
		English = "Octopus Error : No Card found (deduct / add)";
		Chinese = "八達通錯誤: 請再拍卡";
		break;
//	case 21: 
//		English = "Invalid Octopus,Please Contact MTR!)";
//		Chinese = "八達通錯誤: ";
//		break;
	case 22: 
		English = "Octopus Error : Incomplete transaction";
		Chinese = "八達通錯誤: 交易未完成";
		break;
	case 23: 
		English = "Octopus Error : TLOG full";
		Chinese = "八達通錯誤: TLOG已滿";
		break;
	case 24: 
		English = "Octopus Error : CSC blocked by this call";
		Chinese = "八達通錯誤: 此卡失效";
		break;
	case 32: 
		English = "Octopus Error : Time out polling Card/No card found";
		Chinese = "八達通錯誤: 請再拍卡";
		break;
	case 34: 
		English = "Octopus Error : Card authentication error";
		Chinese = "八達通錯誤: 卡驗證錯誤, 請重試";
		break;
	case 35: 
		English = "Octopus Error : Card recovery error";
		Chinese = "八達通錯誤: 卡恢復發現錯誤";
		break;
	case 48: 
		English = "Octopus Error : Insufficient fund";
		Chinese = "八達通錯誤: 餘額不足";
		break;
	case 49: 
		English = "Octopus Error : Remaining value exceed limit";
		Chinese = "八達通錯誤: 儲值額超出上限";
		break;
	case 50: 
		English = "Octopus Error : AV quota exceeded";
		Chinese = "八達通錯誤: 增值配額已滿";
		break;
	case 54:
		English = "Octopus Error : Write ID failure";
		Chinese = "八達通錯誤: Write ID失敗";
		break;
	case 55: 
		English = "Octopus Error : Purse go negative";
		Chinese = "八達通錯誤: Purse go negative";
		break;
	case 56: 
		English = "Octopus Error : Invalid defer deduct sequence";
		Chinese = "八達通錯誤: 錯誤的'defer deduct'排序";
		break;
	case 98: 
		English = "Octopus Error : No new firmware found";
		Chinese = "八達通錯誤: 找不到更新程式";
		break;
	case 99: 
		English = "Octopus Error : Firmware upgraded done by Houskeeping";
		Chinese = "八達通錯誤: Firmware upgraded done by Houssekeeping";
		break;
	case 101: 
		English = "Octopus Error : Open local AR error";
		Chinese = "八達通錯誤: 打開本地的AR錯誤";
		break;
	case 102: 
		English = "Octopus Error : Open local UD error";
		Chinese = "八達通錯誤: 打開本地的UD錯誤";
		break;
	case 1005: 
		English = "Octopus Error : CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤: CCHS/Firmware 更新錯誤";
		break;
	case 1006: 
		English = "Octopus Error : CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤: CCHS/Firmware 更新錯誤";
		break;
	case 1007: 
		English = "Octopus Error : CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤: CCHS/Firmware 更新錯誤";
		break;
	case 1008: 
		English = "Octopus Error : CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤: CCHS/Firmware 更新錯誤";
		break;
	case 1009: 
		English = "Octopus Error : CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤: CCHS/Firmware 更新錯誤";
		break;
	case 9999:
		English = "MOP is manually disabled!";
		Chinese = "八達通讀卡器已經停止工作!";
		break;
	default: 
		English.Format("Other Octopus Error (%d)", ErrCode);
		Chinese.Format("發生錯誤 (%d)", ErrCode);
		break;
	}
	if (Language == 0) return Chinese;
	if (Language == 1) return English;
	return Chinese + "\n" + English;
}
//CString CCmdOtp::Translate(int Language/*=0*/, int ErrCode/* = -1*/) //language = 0;(chinese) = 1(english); =2;(both). 
//if the both language is returned, the 2 sentences are joined by a "\n"
/*
{
	CString English, Chinese;
	if (ErrCode == -1) ErrCode = _LastError;
	switch (ErrCode)
	{
	case 00:
		English = "";
		Chinese = "";
		break;
	case 01: 
		English = "Octopus Error (001): Communication error, R/W not connected";
		Chinese = "八達通錯誤(001): 未能接駁八達通收費器";
	break;
	case 02: 
		English = "Octopus Error (002): File open error";
		Chinese = "八達通錯誤(002): 文件打開錯誤";
	break;
	case 03: 
		English = "Octopus Error (003): Invalid parameter";
		Chinese = "八達通錯誤(003): 發現錯誤的參數";
	break;
	case 04: 
		English = "Octopus Error (004): File read error";
		Chinese = "八達通錯誤(004): 文件讀取錯誤";
	break;
	case 05: 
		English = "Octopus Error (005): Invalid response from R/W";
		Chinese = "八達通錯誤(005): 未能接駁八達通收費器";
	break;
	case 10: 
		English = "Octopus Error (010): File Checksum error";
		Chinese = "八達通錯誤(010): 文件校驗碼發現錯誤";
		break;
	case 16: 
		English = "Octopus Error (016): Card read error";
		Chinese = "八達通錯誤(016): 讀卡錯誤, 請重試";
		break;
	case 17: 
		English = "Octopus Error (017): Card write error";
		Chinese = "八達通錯誤(017): 讀卡錯誤, 請重試";
		break;
	case 19: 
		English = "Octopus Error (019): Card blocked";
		Chinese = "八達通錯誤(019): 此卡失效";
		break;
	case 20: 
		English = "Octopus Error (020): No Card found (deduct / add)";
		Chinese = "八達通錯誤(020): 請再拍卡";
		break;
	case 22: 
		English = "Octopus Error (022): Incomplete transaction";
		Chinese = "八達通錯誤(022): 交易未完成";
		break;
	case 23: 
		English = "Octopus Error (023): TLOG full";
		Chinese = "八達通錯誤(023): TLOG已滿";
		break;
	case 24: 
		English = "Octopus Error (024): CSC blocked by this call";
		Chinese = "八達通錯誤(024): 此卡失效";
		break;
	case 32: 
		English = "Octopus Error (032): Time out polling Card/No card found";
		Chinese = "八達通錯誤(032): 請再拍卡";
		break;
	case 34: 
		English = "Octopus Error (034): Card authentication error";
		Chinese = "八達通錯誤(034): 卡驗證錯誤, 請重試";
		break;
	case 35: 
		English = "Octopus Error (035): Card recovery error";
		Chinese = "八達通錯誤(035): 卡恢復發現錯誤";
		break;
	case 48: 
		English = "Octopus Error (048): Insufficient fund";
		Chinese = "八達通錯誤(048): 餘額不足";
		break;
	case 49: 
		English = "Octopus Error (049): Remaining value exceed limit";
		Chinese = "八達通錯誤(049): 儲值額超出上限";
		break;
	case 50: 
		English = "Octopus Error (050): AV quota exceeded";
		Chinese = "八達通錯誤(050): 增值配額已滿";
		break;
	case 54:
		English = "Octopus Error (054): Write ID failure";
		Chinese = "八達通錯誤(054): Write ID失敗";
		break;
	case 55: 
		English = "Octopus Error (055): Purse go negative";
		Chinese = "八達通錯誤(055): Purse go negative";
		break;
	case 56: 
		English = "Octopus Error (056): Invalid defer deduct sequence";
		Chinese = "八達通錯誤(056): 錯誤的'defer deduct'排序";
		break;
	case 98: 
		English = "Octopus Error (098): No new firmware found";
		Chinese = "八達通錯誤(098): 找不到更新程式";
		break;
	case 99: 
		English = "Octopus Error (099): Firmware upgraded done by Houskeeping";
		Chinese = "八達通錯誤(099): Firmware upgraded done by Houssekeeping";
		break;
	case 101: 
		English = "Octopus Error (101): Open local AR error";
		Chinese = "八達通錯誤(101): 打開本地的AR錯誤";
		break;
	case 102: 
		English = "Octopus Error (102): Open local UD error";
		Chinese = "八達通錯誤(102): 打開本地的UD錯誤";
		break;
	case 1005: 
		English = "Octopus Error (1005): CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤(1005): CCHS/Firmware 更新錯誤";
		break;
	case 1006: 
		English = "Octopus Error (1006): CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤(1006): CCHS/Firmware 更新錯誤";
		break;
	case 1007: 
		English = "Octopus Error (1007): CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤(1007): CCHS/Firmware 更新錯誤";
		break;
	case 1008: 
		English = "Octopus Error (1008): CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤(1008): CCHS/Firmware 更新錯誤";
		break;
	case 1009: 
		English = "Octopus Error (1009): CCHS/Firmware Upgrade Errors";
		Chinese = "八達通錯誤(1009): CCHS/Firmware 更新錯誤";
		break;
	case 9999:
		English = "MOP is manually disabled!";
		Chinese = "八達通讀卡器已經停止工作!";
		break;
	default: 
		English.Format("Other Octopus Error (%d)", ErrCode);
		Chinese.Format("發生錯誤 (%d)", ErrCode);
		break;
	}
	if (Language == 0) return Chinese;
	if (Language == 1) return English;
	return Chinese + "\n" + English;
}
*/
void CCmdOtp::OTP_Folders_Read(RWL_SETTINGS &RWL_Settings)
{
	
	CString RWLDefaultUploadPath = "C:\\RWL\\UPLOAD";

	GetPrivateProfileString( _T("EXCHANGE"),	_T("FILEDIR"),	RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._Exchange.GetBuffer(_MAX_PATH),	_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("BLACKLIST"),	_T("FILEDIR"),	RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._Blacklist.GetBuffer(_MAX_PATH),_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("FIRMWARE"),	_T("FILEDIR"),	RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._Firmware.GetBuffer(_MAX_PATH),	_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("EOD"),			_T("FILEDIR"),	RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._EOD.GetBuffer(_MAX_PATH),		_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("CCHS"),		_T("FILEDIR"),	RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._CCHS.GetBuffer(_MAX_PATH),		_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("AR"),			_T("DIR1"),		RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._AR1.GetBuffer(_MAX_PATH),		_MAX_PATH, (LPCTSTR)_RWL_FilePath);
	GetPrivateProfileString( _T("AR"),			_T("DIR2"),		RWLDefaultUploadPath ,(LPTSTR)RWL_Settings._AR2.GetBuffer(_MAX_PATH),		_MAX_PATH, (LPCTSTR)_RWL_FilePath);

	RWL_Settings._Exchange.ReleaseBuffer();
	RWL_Settings._Blacklist.ReleaseBuffer();
	RWL_Settings._Firmware.ReleaseBuffer();
	RWL_Settings._EOD.ReleaseBuffer();
	RWL_Settings._CCHS.ReleaseBuffer();
	RWL_Settings._AR1.ReleaseBuffer();
	RWL_Settings._AR2.ReleaseBuffer();
}

void CCmdOtp::OTP_Folders_Write(RWL_SETTINGS &RWL_Settings)
{
	CString RWLDefaultUploadPath = "C:\\RWL\\UPLOAD";

	WritePrivateProfileString(_T("EXCHANGE"),	_T("FILEDIR"),	(LPCTSTR)RWL_Settings._Exchange,	(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("BLACKLIST"),	_T("FILEDIR"),	(LPCTSTR)RWL_Settings._Blacklist,	(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("FIRMWARE"),	_T("FILEDIR"),	(LPCTSTR)RWL_Settings._Firmware,	(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("EOD"),		_T("FILEDIR"),	(LPCTSTR)RWL_Settings._EOD,			(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("CCHS"),		_T("FILEDIR"),	(LPCTSTR)RWL_Settings._CCHS,		(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("AR"),			_T("DIR1"),		(LPCTSTR)RWL_Settings._AR1,			(LPCTSTR)_RWL_FilePath);
	WritePrivateProfileString(_T("AR"),			_T("DIR2"),		(LPCTSTR)RWL_Settings._AR2,			(LPCTSTR)_RWL_FilePath);
}

void CCmdOtp::ForceMarkTime(){}//{double x; OTP_Deduct(0, x);}
double CCmdOtp::GetMarkTime(){return 0.0;}//_MarkTime;}
                            // 0.0 -- disable mark time     _MArkTime -- enable mark time 


//+------------+---------------------+-------+---------------------------------------------------------------------------------------------------+       
//| OTP CMD    | ACTION TIME         | RET   | RESULT                                                                                            |
//+------------+---------------------+-------+---------------------------------------------------------------------------------------------------+       
//| OTP CMD    | HH:MM:SS DD/MM/YYYY | 10000 | CMD REMARK                               
extern CSetting * g_Setting;
void CCmdOtp::AddOtpLog(CString Cmd, int Value, CString Remark)
{ 

	BYTE CurLastMsgDate = (BYTE)CTime::GetCurrentTime().GetDayOfWeek();
	if (m_nLastMsgDate == 0xFF) m_nLastMsgDate = CurLastMsgDate;
	if (CurLastMsgDate != m_nLastMsgDate)//not the same day, use the new file
	{
		m_fOtpLog.Close();//close the old file
		CString filename; //get the old file name
		filename.Format("LOG%s.OTP.%s", g_Setting->m_Communicate.StationID(), CTime::GetCurrentTime().Format("%y%m%d%H%M%S"));
		CString path = g_System.RunTime.sAppPath + "\\octopus.log";
		path = path.Left(path.ReverseFind('\\') + 1) + filename;
		CopyFile(g_System.RunTime.sAppPath + "\\octopus.log", path, FALSE);//copy the old file to the new named file
		DeleteFile(g_System.RunTime.sAppPath + "\\octopus.log");//delete the old file
		if (CCmdMntSend::Instance()->SendFile(path) == 1)//transfer the old file to management station
			DeleteFile(path);
		m_fOtpLog.m_hFile = CFile::hFileNull;//prepare to open the new file

	}

	CString rec;
	rec.Format("| %10s | %19s | %06d | %-100s |", Cmd, CTime::GetCurrentTime().Format("%H:%M:%S %d/%m/%Y"), Value, Remark.Left(100));
	if (m_fOtpLog.m_hFile == CFile::hFileNull) //open file
	{

		m_fOtpLog.Open(g_System.RunTime.sAppPath + "\\octopus.log", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::shareDenyNone);
		m_fOtpLog.SeekToEnd();
		CString Title1 = "+------------+---------------------+--------+------------------------------------------------------------------------------------------------------+";
		CString Title2 = "| OTP CMD    | ACTION TIME         | RET    | RESULT                                                                                               |";
		CString tmp;
		tmp.Format("%s\r\n\0", Title1);
		m_fOtpLog.Write(tmp, tmp.GetLength());
		tmp.Format("%s\r\n\0", Title2);
		m_fOtpLog.Write(tmp, tmp.GetLength());
		tmp.Format("%s\r\n\0", Title1);
		m_fOtpLog.Write(tmp, tmp.GetLength());
	}
//TA11A 2009 for item1
	if (Value>100000) Value=Value-100000;
	else Value=0;
	switch(Value)
	{
	case 1:
	case 5:
//		MessageBox(NULL,"MOP connection failure","Octopus Error",0);
		break;
	case 19:
	case 24:
			MessageBox(NULL,"Invalid card!","Octopus Error",0);
		break;
	case 21:
			MessageBox(NULL,"Invalid Octopus,please contact MTR!","Octopus Error",0);
		break;
	case 22:
		//		MessageBox(NULL,"Incomplete transaction,retry please!","Octopus Error",0);
		break;
	case 16:
	case 17:
	case 34:
			MessageBox(NULL,"Read card error,retry please!","Octopus Error",0);
		break;
	case 35:
			MessageBox(NULL,"Card recover error!","Octopus Error",0);
		break;
	case 48:
			MessageBox(NULL,"Insufficient value!","Octopus Error",0);
		break;
	case 50:
		//		MessageBox(NULL,"100022","Octopus Error",0);
		break;
	}

//END of TA11A	
	m_fOtpLog.Write(rec+"\r\n", rec.GetLength() + 2);
	m_fOtpLog.Flush();
	m_nLastMsgDate = CurLastMsgDate;
}

void CCmdOtp::OTP_StopRead(bool flag)
{

	StopRead_Status=flag;
}

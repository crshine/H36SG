// CmdPrint.cpp: implementation of the CCmdPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cashiergui.h"
#include "Setting.h"
#include "dlg\DlgProgress.h"
#include "CmdPrint.h"
#include "cmdotp.h"
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
	#define new DEBUG_NEW
#else
	#define MOUNT_PRINTER	//是否加载打印机?
#endif

extern	CString AddValueInfo;
extern CString NewCardPollEx;//TA18- 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCmdPrint* CCmdPrint::_instance = 0;

CCmdPrint* CCmdPrint::Instance()
{
    if (_instance == 0) {
        _instance = new CCmdPrint;
    }
    return _instance;
}

CCmdPrint::CCmdPrint()
{
	_pPrinter = NULL;
#ifdef MOUNT_PRINTER
	ResetPrinter();
#endif
}

CCmdPrint::~CCmdPrint()
{
	if (_pPrinter != NULL)
		delete _pPrinter;
}
//////////////////////////////////////////////////////////////////////
//初始化或重置打印机
void CCmdPrint::ResetPrinter()
{	
	CSetting * pSetting = CSetting::Instance();
	CString Starter[3];
	CString Ending[2];

	Starter[0]	= pSetting->m_Receipt.Title1();
	Starter[1]	= pSetting->m_Receipt.Title2();
	Starter[2]	= pSetting->m_Receipt.Title3();
	Ending[0]	= pSetting->m_Receipt.Ending1();
	Ending[1]	= pSetting->m_Receipt.Ending2();
	int leftspc = pSetting->m_Receipt.LeftBlackSpaces();
	int linespc = pSetting->m_Receipt.LineSpaces();
	int cutline = pSetting->m_Receipt.FeedLines();
	CString TaxName = pSetting->m_Receipt.TaxName();
	CString TaxNo   = pSetting->m_Receipt.TaxRegNo();
	int TaxPerc     = static_cast<int>(pSetting->m_Receipt.TaxPercentageRate()*100);
	int StationID	= _ttol(pSetting->m_Communicate.StationID());
	short Port, ThreadStep;
	long BaudRate;
	pSetting->m_Peripheral.GetPrinterParameter(Port, ThreadStep, BaudRate);
	//初始化打印机.
	_pPrinter  = new CReceiptPrn("LPT"+show(Port)+":", Starter, Ending, 
		leftspc, linespc, cutline, TaxName, TaxNo, TaxPerc, StationID, CCmdOtp::Instance()->OTP_GetDevID());
}
//票据头
bool CCmdPrint::PrintHeader()
{
	if (NULL == _pPrinter) return false;
	if (TRUE == _pPrinter->PrintHeader())
		return true;
	else
		return false; 
}
//票据尾
bool CCmdPrint::PrintEnding()
{
	if (NULL == _pPrinter) return false;
	if (TRUE == _pPrinter->PrintEnding())
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////
//打印换班票据
bool CCmdPrint::PrintShiftAccount(CString Operator, CString ReceiptNo, COleDateTime DutyStart, int PayNum, double Cash, double Octopus, double StoreValue, double ShiftCashMaintain)
{
	if (NULL == _pPrinter) return false;
	
	if (!_pPrinter->PrintShiftCloseReceipt(Operator, Str2Long(ReceiptNo, 0), DutyStart, PayNum, Cash, Octopus, StoreValue, ShiftCashMaintain)) return false;
	return true;
//	thrPrintShiftAccount(0);
//	CWinThread* cw = AfxBeginThread( &thrPrintShiftAccount , 0);
//	CDlgProgress * Dlg = new CDlgProgress(15, "Print shift account receipt!");
//	Dlg->DoModal();
	return true;
}

UINT CCmdPrint::thrPrintShiftAccount(LPVOID)
{
	CCmdPrint* pCmdPrint = CCmdPrint::Instance();
	if (NULL == pCmdPrint->_pPrinter) return false;
	if (!pCmdPrint->PrintHeader()) return 1;
	if (!pCmdPrint->PrintEnding()) return 2;
	return 0;
}
//打印停车收费票据
bool CCmdPrint::PrintParkingFee(
			const CString		CardNo,
			const short		SpecialCardTypeId,
			const COleDateTime	TimeEntry,
			const COleDateTime  TimeLastPay,
			const COleDateTime	TimePay,
			const CDiscount	Discount,
			const CString		ReceiptNo,
			const CString		Octopus_CardNo,		//实际付费使用的八达通卡号
			const CString		StoreValue_CardNo,	//实际付费使用的储值卡号
			const short			PaymentTimes,
			const double		OctopusRemain,		//八达通余额
			const double		StoreValueRemain,	//储值余额
			const double		Amount,				//总额
			const double		Cash,				//现金
			const double		Change,				//找零
			const double		Octopus,			//八达通
			const double		StoreValue,         //储值
			const short         VehicleType
			)
{
	if (NULL == _pPrinter) return false;
	PARKINGFEEPARA ParkingFeePara;
	{
		ParkingFeePara._ReceiptNo	= ReceiptNo;
		ParkingFeePara._CardNo		= CardNo;
		ParkingFeePara._PayCardNo	= Octopus_CardNo + StoreValue_CardNo;
		ParkingFeePara._PayCardNo	= NewCardPollEx;//TA18- 
		ParkingFeePara._IsRepay		= (0 == PaymentTimes ? true : false);
		ParkingFeePara._CardType	= showSpecialCardTypeName(SpecialCardTypeId);
		ParkingFeePara._EntryTime	= TimeEntry;
		ParkingFeePara._LastPayTime = TimeLastPay;
		ParkingFeePara._PayTime     = TimePay;
		ParkingFeePara._Discount	= show(Discount);
		ParkingFeePara._CardAmt		= Amount;
		ParkingFeePara._CardBal		= OctopusRemain;
		ParkingFeePara._StoreValueAmt	= StoreValue;
		ParkingFeePara._StoreValueBal	= StoreValueRemain;
		ParkingFeePara._Cash            = Cash;
		ParkingFeePara._Change          = Change;
		ParkingFeePara._VehicleType     = VehicleType;
	}

// disable receipt printing check point 
// [BW] 20060301 - clear the following prog.///////////////////////////////////
	thrPrintParkingFee(&ParkingFeePara);
///////////////////////////////////////////////////////////////////////////////

//	CWinThread* cw = AfxBeginThread( &thrPrintParkingFee, &ParkingFeePara);
//	CDlgProgress * Dlg = new CDlgProgress(49, "Print parking fee receipt!");
//	Dlg->DoModal();
	return true;
}
UINT CCmdPrint::thrPrintParkingFee(LPVOID pParam/* HPARKINGFEEPARA*/)
{
	CCmdPrint* pCmdPrint = CCmdPrint::Instance();
	if (NULL == pCmdPrint->_pPrinter) return false;
	HPARKINGFEEPARA hParkingFeePara = (HPARKINGFEEPARA)pParam;

	char CardNo[50];
	char PayCardNo[50];
	char CardType[50];
	char Discount[50];
	memset(CardNo, 0, sizeof(CardNo));
	memset(PayCardNo, 0, sizeof(PayCardNo));
	memset(CardType, 0, sizeof(CardType));
	memset(Discount, 0, sizeof(Discount));

	memcpy(CardNo, hParkingFeePara->_CardNo, hParkingFeePara->_CardNo.GetLength());
	memcpy(PayCardNo, hParkingFeePara->_PayCardNo, hParkingFeePara->_PayCardNo.GetLength());
	memcpy(CardType, hParkingFeePara->_CardType, hParkingFeePara->_CardType.GetLength());
	memcpy(Discount, hParkingFeePara->_Discount, hParkingFeePara->_Discount.GetLength());


	if (!pCmdPrint->_pPrinter->PrintParkingReceipt(
				_ttol(hParkingFeePara->_ReceiptNo),
				CardNo,
				PayCardNo,
				hParkingFeePara->_IsRepay,
				CardType,
				hParkingFeePara->_EntryTime,
				hParkingFeePara->_LastPayTime,
				hParkingFeePara->_PayTime,
				Discount,
				hParkingFeePara->_CardAmt,
				hParkingFeePara->_CardBal,
				hParkingFeePara->_StoreValueAmt,
				hParkingFeePara->_StoreValueBal,
				hParkingFeePara->_Cash,
				hParkingFeePara->_Change,
				hParkingFeePara->_VehicleType,
				AddValueInfo)) return 1;//TA18- 
	return 0;
}

bool CCmdPrint::PrintAddValue(
			CString        av_No, 
			CString        av_OtpNo,
			COleDateTime av_PayTime,
			double       av_Amt, 
		    double       av_OtpOldBal, 
			double       av_OtpNewBal,
            double       av_Cash, 
			double       av_Change
			)
{

	CCmdPrint* pCmdPrint = CCmdPrint::Instance();

	if (!pCmdPrint->_pPrinter->PrintAddValueReceipt(
				_ttol(av_No),
				av_OtpNo,
				av_PayTime,
				av_Amt,
				av_OtpOldBal,
				av_OtpNewBal,
				av_Cash,
				av_Change))return 1;
	return 0;
	return true;
}

bool CCmdPrint::PrintSeasonCreate(
			CString      sc_No, 
			CString      sc_CardNo, 
			COleDateTime sc_PayTime,
			COleDateTime sc_ValidFrom,
			COleDateTime sc_ValidTo,
			double       sc_Amt, 
			double       sc_Cash,
			double       sc_Change
			)
{
	CCmdPrint* pCmdPrint = CCmdPrint::Instance();

	if (!pCmdPrint->_pPrinter->PrintSeasonCreate(
		        _ttol(sc_No), 
		    	sc_CardNo, 
			    sc_PayTime,
		    	sc_ValidFrom,
		    	sc_ValidTo,
			    sc_Amt, 
			    sc_Cash,
			    sc_Change))return 1;
	return 0;
	return true;
}


bool CCmdPrint::PrintSeasonExtend(
			CString      se_No, 
			CString      se_CardNo, 
			COleDateTime se_PayTime,
			COleDateTime se_ValidFrom,
			COleDateTime se_ValidTo,
			double       se_Amt, 
			double       se_Cash,
			double       se_Change
			)
{
	CCmdPrint* pCmdPrint = CCmdPrint::Instance();

	if (!pCmdPrint->_pPrinter->PrintSeasonExtend(
		        _ttol(se_No), 
		    	se_CardNo, 
			    se_PayTime,
		    	se_ValidFrom,
		    	se_ValidTo,
			    se_Amt, 
			    se_Cash,
			    se_Change))return 1;
	return 0;
	return true;
}			
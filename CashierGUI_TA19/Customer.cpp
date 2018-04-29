// Customer.cpp: implementation of the CCustomer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Setting.h"
//#include "CmdKde.h"
#include "CmdJmdm.h"		
#include "CmdOtp.h"
#include "PayMode.h"
#include "dlg\DlgPaymentParkFee11.h"		//	
#include "dlg\DlgPaymentOperate.h" //	
#include "CmdLcd.h"
#include "dlgcheckcard.h"
#include "CmdMntSend.h"
#include "FeeCalculate.h"
#include "cmdprint.h"
#include "dlgcardrenew.H"
#include "dlg\DlgPayment.h"
#include "dlg\DlgPaymentReceipt.h"
#include "dlg\DlgPaymentKDE.h"
#include "dlg\DlgPaymentKDETicketNo.h"
#include "dlg\DlgPaymentOtpTicketNo.h"
#include "dlg\DlgPaymentOTPEntry.h"
#include "dlg\DlgPaymentSelectDiscount.h"

#include "dlg\DlgPaymentOTPPreAddvalue.h"
#include "dlg\DlgPaymentOTPSubAddvalue.h"

#include "dlg\DlgPaymentShiftAccount.h"
#include "dlg\DlgPaymentReceiptShiftAccount.h"
#include "dlg\DlgPaymentReceiptCloseAccount.h"
#include "dlg\DlgPaymentParkFee.h"		//	停车收费     Parking Payment
#include "dlg\DlgCreateCard.h"			//	创建卡向导   Create Card

#include "dlg\DlgReceiptParkingFee.h"	//	票据打印     Receipt Printing

#include "Customer.h"

#include "Eltra.h"
#include "Jmdm.h"

extern CString NewCardPollEx;//TA18- 
extern CString OldCardPollEx;//TA18- 

COleDateTime t_AV[6];//TA19- TEST

//CEltra *pRMPM=new CEltra(4);
extern CJmdm *pRMPM;

extern UINT g_nCurrentStatus;
extern int g_nTransDiscountID;
extern _System		g_System;
extern CLog *		g_pLog;
extern CSetting * g_Setting;

int _TicketProcessCate=0;//UCH OTP/barcode - 1/2 ; other-0 ;
int _TicketPro_Vehicle; //record current vehicleType 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomer::CCustomer()
{

}

CCustomer::~CCustomer()
{

}
///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    Base Trade Operate                     ////////
////////                                                           ////////
///////////////////////////////////////////////////////////////////////////
bool CCustomer::CBase::_PrintReceipt = true;

CCustomer::CBase::CBase()
{
	_ActionTime = COleDateTime::GetCurrentTime();
	_hGUI = g_System.RunTime.hOtpPaymentDlg;		//图形界面句柄
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	操作员忙
	#ifdef _DEBUG
	//检测相应的值是否在使用前初始化过.
	//-0.0005671 仅仅是一个我认不可能出现的数.
		_Amount = -0.0005671;
		_Cash = -0.0005671;
		_Octopus = -0.0005671;
		_StoreValue = -0.0005671;
		_OctopusRemain = -0.0005671;
		_StoreValueRemain = -0.0005671;
		_Octopus_CardNo = "-0.0005671";
		_StoreValue_CardNo = "-0.0005671";

	#endif

}

CCustomer::CBase::~CBase()
{
	int b = ReleaseMutex(g_System.m_OprBusyMutex);					//	操作员闲
	ASSERT (TRUE == b);
}



//交易

SYSRESULT CCustomer::CBase::Trade()  // (add value check point 003)
									 // payment check point (Trade)
									 // shift close account check point (Trade)
{
	_DisableOTPPay = false;
	_ForbiddenOtp = false;
	ClearGUI();
	Init();
	if (ERROR_STANDARD > Pre_Trade()) { g_nCurrentStatus = 0; /*showTip("礚",true, true);*/g_nTransDiscountID = -1; return ERROR_CANCEL;}
	if (ERROR_STANDARD > Payment()) { g_nCurrentStatus = 0; /*showTip("礚",true, true);*/g_nTransDiscountID = -1; return ERROR_CANCEL;}
	if (ERROR_STANDARD > Sub_Trade()) { g_nCurrentStatus = 0; /*showTip("礚",true, true);*/g_nTransDiscountID = -1; return ERROR_CANCEL;}
//  disable receipt print check point 
#ifndef _DEBUG
	if(FALSE)//HA-
	if(	_TicketProcessCate>=1)
	{
		pRMPM->OpenDev();
		pRMPM->Send_RMPM_Cmd(1,TRUE);
		Sleep(1000);
		pRMPM->Send_RMPM_Cmd(1,FALSE);
		pRMPM->CloseDev();
	}
#endif
//TA11A 2009 addvalue workflow, program exit if no printer setup
//#ifndef _DEBUG	
	if (ERROR_STANDARD > PrintReceipt()) { g_nCurrentStatus = 0; /*showTip("礚",true, true);*/g_nTransDiscountID = -1; return ERROR_CANCEL;}
//#endif
	 
	LogTransaction();  //Send 戈man
	Account();
	g_nTransDiscountID = -1;
//	showTip("礚",true, true);
	g_nTransDiscountID = -1; g_nCurrentStatus = 0; 

	_TicketProcessCate=0;
	
	return SUCCESS;
}
//清除GUI显示.
void CCustomer::CBase::ClearGUI()
{
	SetDlgItemText(_hGUI, IDC_TICKET_NO, "");
	SetDlgItemText(_hGUI, IDC_ENTRY_DATE, "");
	SetDlgItemText(_hGUI, IDC_ENTRY_TIME, "");
	SetDlgItemText(_hGUI, IDC_PAY_DATE, "");
	SetDlgItemText(_hGUI, IDC_PAY_TIME, "");
	SetDlgItemText(_hGUI, IDC_DURATION, "");
	SetDlgItemText(_hGUI, IDC_PARKING_FEE, "");
	SetDlgItemText(_hGUI, IDC_DISCOUNT, "");
	SetDlgItemText(_hGUI, IDC_AMOUNT, "");
	SetDlgItemText(_hGUI, IDC_RECEIVE, "");
	SetDlgItemText(_hGUI, IDC_CHANGE, "");
}
//具体付款的操作.
SYSRESULT CCustomer::CBase::Payment()   // (add value check point 005)
										// (payment check point 005)
										// (damage payment check point)
{                                        
	#ifdef _DEBUG

		ASSERT( _Amount != -0.0005671 );
		ASSERT( _OctopusRemain != -0.0005671 );
		ASSERT( _StoreValueRemain != -0.0005671 );
		ASSERT( _Octopus_CardNo != "-0.0005671" );
		ASSERT( _StoreValue_CardNo != "-0.0005671" );
	#endif
	bool bPaybyCash = TRUE;
/* HA-delete the following for auto calculating
//UCH payment dialog
	if(_TicketProcessCate==1 )
	{
		DlgPaymentOperate dlg;
		dlg.m_TicketNo = _Octopus_CardNo;
		if (IDOK == dlg.DoModal())  
		{
			_DisableOTPPay = _DisableOTPPay;

			_Amount=dlg._Amount; //get new fee calculated in manual Dialog

			if(dlg.PaywithOTP)  // UCH if need otp payment
			{
				CCmdOtp * pCmdOtp = CCmdOtp::Instance();
				long ReceiptNo = CSetting::Instance()->m_Account.GetReceiptNo();;
				if (_Amount > 0.009) {			
					_OTPZeroDeductType = 0;
				}			
				pCmdOtp->OTP_DisplayBeforeDeduct(_Amount);
	//			showTip("[琌(Y)] -- ミ笷硄蹿    [(N)] -- 瞷蹿    [] -- 蹿", true, false);
	//			int zzz = ::AfxMessageBox("琌絋﹚ミ笷硄蹿?" , MB_YESNOCANCEL|MB_ICONQUESTION|MB_SYSTEMMODAL );
#ifdef _DEBUG				
				_Amount=0.1;
#endif
				if (!pCmdOtp->OTP_Deduct(_Amount, _OctopusRemain, ReceiptNo, _OTPZeroDeductType, _Octopus_CardNo)) 
				{	//扣费失败 //successfully deducted
					CString dsp;
					dsp.Format("祇瞷岿粇 : [%s]", pCmdOtp->Translate());
					//				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
					//TA11A ken20090817
					if(pCmdOtp->GetLastError()!=48 &&pCmdOtp->GetLastError()!=22 )
						::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
					return ERROR_CANCEL;
				}else{
					bPaybyCash = FALSE;
					_Cash				= 0;
					_Change				= 0;
					_StoreValue			= 0;
					_Octopus			= _Amount;
					_PrintReceipt		= true; 
				}
			}
			else
			{//UCH cash payment
				bPaybyCash = TRUE;
				_Octopus_CardNo		= dlg.m_TicketNo;
//				_StoreValue_CardNo	= dlg._StoreValue_CardNo;
//				_OctopusRemain		= dlg._OctopusRemain;
				_Cash				= dlg._Amount;
				_Change				= 0;
				_StoreValue			= 0;
				_Octopus			= 0;
				_PrintReceipt		= true; 
				
				ASSERT(0.1 > (_Amount + _Change - _Cash - _Octopus - _StoreValue) );
			}
		}
		else 
			return ERROR_CANCEL;
		
		return SUCCESS; //?
	}
	if(_TicketProcessCate==2 )
	{
		DlgPaymentOperate dlg;
		dlg.m_TicketNo = _Barcode_CardNo;
		if (IDOK == dlg.DoModal())  
		{
//			_DisableOTPPay = TRUE;
			
			_Amount=dlg._Amount; //get new fee calculated in manual Dialog
			
			if(dlg.PaywithOTP)  // UCH if need otp payment
			{
				CCmdOtp * pCmdOtp = CCmdOtp::Instance();
				long ReceiptNo = CSetting::Instance()->m_Account.GetReceiptNo();;
				if (_Amount > 0.009) {			
					_OTPZeroDeductType = 0;
				}			
				pCmdOtp->OTP_DisplayBeforeDeduct(_Amount);
				//			showTip("[琌(Y)] -- ミ笷硄蹿    [(N)] -- 瞷蹿    [] -- 蹿", true, false);
				//			int zzz = ::AfxMessageBox("琌絋﹚ミ笷硄蹿?" , MB_YESNOCANCEL|MB_ICONQUESTION|MB_SYSTEMMODAL );
#ifdef _DEBUG				
				_Amount=0.1;
#endif
//				CCmdOtp::PATRON CardInfo;
				
//				if (pCmdOtp->OTP_Poll(CardInfo))

				_Octopus_CardNo = dlg._Octopus_CardNo; //UCH 3-
				if (!pCmdOtp->OTP_Deduct(_Amount, _OctopusRemain, ReceiptNo, _OTPZeroDeductType, _Octopus_CardNo)) 
				{	//扣费失败 //successfully deducted
					CString dsp;
					dsp.Format("祇瞷岿粇 : [%s]", pCmdOtp->Translate());
					//				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
					//TA11A ken20090817
					if(pCmdOtp->GetLastError()!=48 &&pCmdOtp->GetLastError()!=22 )
						::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
					return ERROR_CANCEL;
				}else{//
					bPaybyCash = FALSE;
					_Cash				= 0;
					_Change				= 0;
					_StoreValue			= 0;
					_Octopus			= _Amount;
					_PrintReceipt		= true; 
				}
			}
			else
			{//UCH cash payment
				bPaybyCash = TRUE;
				_Octopus_CardNo		= "";
				//				_StoreValue_CardNo	= dlg._StoreValue_CardNo;
				//				_OctopusRemain		= dlg._OctopusRemain;
				_Cash				= dlg._Amount;
				_Change				= 0;
				_StoreValue			= 0;
				_Octopus			= 0;
				_PrintReceipt		= true; 
				
				ASSERT(0.1 > (_Amount + _Change - _Cash - _Octopus - _StoreValue) );
			}
		}
		else 
			return ERROR_CANCEL;
		
		return SUCCESS; //?
	}
/*/
    //  OTP Direct Payment is enabled 
	if (!_DisableOTPPay)
	{//direct payment by OTP
		CCmdOtp * pCmdOtp = CCmdOtp::Instance();
		long ReceiptNo = CSetting::Instance()->m_Account.GetReceiptNo();;
		if (_Amount > 0.009) {			
			_OTPZeroDeductType = 0;
		}

		t_AV[1]=COleDateTime::GetCurrentTime();//TA19-test
		
		// [PY]: 06 Jun 2005 - to include a dialog box to confirm deduction
		// [BW]: 22Jun05 pCmdOtp->OTP_Display(_Amount, _OctopusRemain, CCmdOtp::None, CCmdOtp::NoSound); // display amount on MOP reader
		pCmdOtp->OTP_DisplayBeforeDeduct(_Amount);
		showTip("[琌(Y)] -- ミ笷硄蹿    [(N)] -- 瞷蹿    [] -- 蹿", true, false);
		int zzz = ::AfxMessageBox("琌絋﹚ミ笷硄蹿?" , MB_YESNOCANCEL|MB_ICONQUESTION|MB_SYSTEMMODAL );
		if (zzz == IDYES)
		{

			if (!pCmdOtp->OTP_Deduct(_Amount, _OctopusRemain, ReceiptNo, _OTPZeroDeductType, _Octopus_CardNo)) 
			{	//扣费失败 //successfully deducted
				CString dsp;
				dsp.Format("祇瞷岿粇 : [%s]", pCmdOtp->Translate());
//				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
//TA11A ken20090817
				if(pCmdOtp->GetLastError()!=48 &&pCmdOtp->GetLastError()!=22 )
				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
				return ERROR_CANCEL;
			}else{
				bPaybyCash = FALSE;
				_Cash				= 0;
				_Change				= 0;
				_StoreValue			= 0;
				_Octopus			= _Amount;
				_PrintReceipt		= true; 

				_ActionTime = COleDateTime::GetCurrentTime();//TA19- solve the deducting time different between card records and managemnt

				t_AV[2]=COleDateTime::GetCurrentTime();//TA19-test
			}

		}
		else if (zzz == IDNO) // IDNO, Payment by Cash
		{// [PY]: 06 Jun 2005

			_ForbiddenOtp = true;
			//[BW]: 22Jun05 Reset Display Balance in MOP 
			pCmdOtp->OTP_DisplayBeforeDeduct(0);
			if (bPaybyCash)
			{
				CDlgPaymentParkFee dlg;
				dlg._Amount = _Amount;
				dlg._bForbiddenOtp = _ForbiddenOtp;
				dlg._PrintReceipt = _PrintReceipt;
		
				if (IDOK != dlg.DoModal()) return ERROR_CANCEL;

				_Octopus_CardNo		= dlg._Octopus_CardNo;
				_StoreValue_CardNo	= dlg._StoreValue_CardNo;
				_OctopusRemain		= dlg._OctopusRemain;
				_Cash				= dlg._Cash;
				_Change				= dlg._Change;
				_StoreValue			= dlg._StoreValue;
				_Octopus			= dlg._Octopus;
				_PrintReceipt		= dlg._PrintReceipt;

				ASSERT(0.1 > (_Amount + _Change - _Cash - _Octopus - _StoreValue) );
			}
		}
		// while IDCANCEL
		else return ERROR_CANCEL;
	}
	else // NOT OTP direct payment, Display payment dialog
	{
		CDlgPaymentParkFee dlg;
		dlg._Amount = _Amount;
		dlg._OctopusRemain = _OctopusRemain;
		dlg._StoreValueRemain = _StoreValueRemain;
		dlg._Octopus_CardNo = _Octopus_CardNo;
		dlg._StoreValue_CardNo = _StoreValue_CardNo;
		dlg._PrintReceipt = _PrintReceipt;
		dlg._bForbiddenOtp = _ForbiddenOtp;  // False = enable OTP Payment
		dlg._PrintReceipt = _PrintReceipt;
		if (IDOK != dlg.DoModal()) return ERROR_CANCEL;

		_Octopus_CardNo		= dlg._Octopus_CardNo;
		_StoreValue_CardNo	= dlg._StoreValue_CardNo;
		_OctopusRemain		= dlg._OctopusRemain;
		_Cash				= dlg._Cash;
		_Change				= dlg._Change;
		_StoreValue			= dlg._StoreValue;
		_Octopus			= dlg._Octopus;
		_PrintReceipt		= dlg._PrintReceipt;

		ASSERT(0.1 > (_Amount + _Change - _Cash - _Octopus - _StoreValue) );
	}
	return SUCCESS;
}

SYSRESULT CCustomer::CBase::PrintReceipt()
{
	ASSERT(1!=1);	//Receipt must different by difference func;
	return SUCCESS;
}

void CCustomer::CBase::Account()
{
	#ifdef _DEBUG
	//检测相应的值是否在使用前初始化过.
	//-0.0005671 仅仅是一个我认不可能出现的数.
		ASSERT( _Amount != -0.0005671 );
		ASSERT( _Cash != -0.0005671 );
		ASSERT( _Octopus != -0.0005671 );
		ASSERT( _StoreValue != -0.0005671 );
	#endif
//	CSetting *pSetting = CSetting::Instance();
//	pSetting->m_Account.LogPayAmount(_Amount, _Cash, _Octopus, _StoreValue);
}

///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                      Exit Car Park                        ////////
////////                             public 'CBase'                ////////
///////////////////////////////////////////////////////////////////////////
bool CCustomer::CExitCarPark::_PrintReceipt = true;

CCustomer::CExitCarPark::CExitCarPark()
{
	_hGUI		= g_System.RunTime.hOtpPaymentDlg;	//图形界面句柄
	_OctopusRemain = 0.0;
	_SpecialCardTypeId = 0;
	_StoreValueRemain = 0.0;
	_Discount.Clear();
	_PaymentTimes = 0;
	_CardNo = "";
}

void CCustomer::CExitCarPark::RefreshDsp(CWnd * pWnd) // damage payment check point 002 (RefreshDsp)
{
	if (pWnd)
	{
		if (!((CDlgPaymentKDETicketNo *)pWnd)->m_bFindInfoFromNet) // The Information Not find in MAN
		{
			_EntryTime = ((CDlgPaymentKDETicketNo *)pWnd)->m_cEntryTime;
			_ExitTime = ((CDlgPaymentKDETicketNo *)pWnd)->m_cExitTime;
			_EntryStationID = ((CDlgPaymentKDETicketNo *)pWnd)->m_cEntryStationID+1;
			_GroupId = g_Setting->m_StationInformation.GroupID(_EntryStationID);
			_VehicleId = ((CDlgPaymentKDETicketNo *)pWnd)->m_cVehicleType+1;
			//_Discount = "$0000000";
			//_Discount = 0;
			_PaymentTimes = 0;
			_LastPayTime = COleDateTime(0.0);
		}
		if (((CDlgPaymentKDETicketNo *)pWnd)->m_Type == 0) // Damage Ticket
		{
			_VehicleId = ((CDlgPaymentKDETicketNo *)pWnd)->m_cVehicleType+1;//UCH 3-for new car type
			_SpecialCardTypeId = 7; //+ ((CDlgPaymentKDETicketNo *)pWnd)->m_Type;
		}
		if (((CDlgPaymentKDETicketNo *)pWnd)->m_Type == 1) // Lost Ticket
			_SpecialCardTypeId = 8;
		if (((CDlgPaymentKDETicketNo *)pWnd)->m_Type == 3) // Change VehType
		{
			_SpecialCardTypeId = 0;
			_VehicleId = ((CDlgPaymentKDETicketNo *)pWnd)->m_cVehicleType+1;
		}
	}
	SetDlgItemText(_hGUI, IDC_ENTRY_DATE, _EntryTime.Format((CString)(LPCTSTR)SYS_SHOW_DATE));
	SetDlgItemText(_hGUI, IDC_ENTRY_TIME, _EntryTime.Format((CString)(LPCTSTR)SYS_SHOW_HHMMSS));
	SetDlgItemText(_hGUI, IDC_PAY_DATE, _ExitTime.Format((CString)(LPCTSTR)SYS_SHOW_DATE));
	SetDlgItemText(_hGUI, IDC_PAY_TIME, _ExitTime.Format((CString)(LPCTSTR)SYS_SHOW_HHMMSS));
	SetDlgItemText(_hGUI, IDC_DURATION, (_ExitTime - _EntryTime).Format((CString)(LPCTSTR)SYS_SHOW_TIMESPAN));
	SetDlgItemText(_hGUI, IDC_TICKET_NO, _CardNo);

	switch (_SpecialCardTypeId)
	{
	case 0: SetDlgItemText(_hGUI, IDC_PAY_RULE, "布");break;
	case 6: SetDlgItemText(_hGUI, IDC_PAY_RULE, "VIP布");break;
	case 7: SetDlgItemText(_hGUI, IDC_PAY_RULE, "穕胊布");break;
	case 8: SetDlgItemText(_hGUI, IDC_PAY_RULE, "框ア布");break;
	default: SetDlgItemText(_hGUI, IDC_PAY_RULE, g_Setting->m_CardType.Name(_SpecialCardTypeId));
	}
	
//	SetDlgItemText(_hGUI, IDC_DISCOUNT_RULE, "╬產ó");
	SetDlgItemText(_hGUI, IDC_DISCOUNT_RULE, " ");
//	SetDlgItemText(_hGUI, IDC_DISCOUNT, show(_Discount));
	SetDlgItemText(_hGUI, IDC_DISCOUNT, ""); // UCH - disable discount display

	if (pWnd)
	{
	    //         _||_
		//         \  /
		//          \/
		if (ERROR_STANDARD > Calculate()) return;	//计算费用
		CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, _EntryTime);		
	}
}

void CCustomer::CExitCarPark::ReCalculate(CWnd * pWnd) 
{
	if (pWnd)
	{
//		if (!((DlgPaymentOperate *)pWnd)->m_bFindInfoFromNet) // The Information Not find in MAN
		{
			_EntryTime = ((DlgPaymentOperate *)pWnd)->m_cEntryTime;
			_Amount = ((DlgPaymentOperate *)pWnd)->_Amount;
		}
	}
	//_Amount=20;
	//_EntryTime=COleDateTime::GetCurrentTime();
	CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, _EntryTime);		
}


SYSRESULT CCustomer::CExitCarPark::QueryServer(CWnd * pManualWnd)
{
	bool QueryServerSuccess = false;
//	short DiscountPlanId;			//普通卡享受的折扣的编号	//炊硄ㄉчΙ絪腹
	CSetting * pSetting = CSetting::Instance();
	CCmdMntSend* pCmdSend = CCmdMntSend::Instance();
	
	// Query Card Information
	//查询卡信息
	if (pManualWnd)
	{
		if(_TicketProcessCate>=1 && FALSE)//HA-
//			if(_TicketProcessCate>=1)
			_CardNo = ((DlgPaymentOperate *)pManualWnd)->m_TicketNo;
		else
			_CardNo = ((CDlgPaymentKDETicketNo *)pManualWnd)->m_TicketNo;
		_StoreValue = 0.0;
		_StoreValueRemain = 0.0;
		_Octopus = 0.0;
		_OctopusRemain = 0.0;
		_Octopus_CardNo = "";
		_StoreValue_CardNo = "";
	}

	//                   refer to "CCmdMntSend::QueryCardStatus(const CString &CardID, HCARDSTATUS &CardStatus)"
	//		             _||_
	//                   \  /
	//                    \/
Retry://TA18- for PollEx function
//	MessageBox(NULL,_CardNo,"query",0);//ta19- test
	bool sendresult = pCmdSend->QueryCardStatus(_CardNo, _CardStatus);
	/*if ( !sendresult)
	{
		if (!bManual) showTip( (LPCTSTR)Err_Read_Entry_Msg );
		//	查询失败, 手动输入.
		/*CDlgPaymentOTPEntry Dlg;
		if (IDOK != Dlg.DoModal()) return ERROR_CANCEL;
		_EntryTime = CDlgPaymentOTPEntry::EntryTime();
		_ExitTime = CDlgPaymentOTPEntry::ExitTime();
		EntryStationId = CDlgPaymentOTPEntry::EntryStation();
		_GroupId = pSetting->m_StationInformation.GroupID(EntryStationId);
		_VehicleId = CDlgPaymentOTPEntry::VehicleId();
		_SpecialCardTypeId = 0;	//普通卡
		_Discount = "$0000000"; //无折扣
		//有关储值卡信息可以初步确定
		_StoreValueRemain = 0;
		_StoreValue_CardNo = "";
		//上次付款信息
		_PaymentTimes = 0;
		_LastPayTime.SetStatus(COleDateTime::null);
	}
	else*/
	
	if (pManualWnd && !sendresult) return ERROR_CANCEL;
		
		//特殊卡信息
		// Special Card Information
	if ( !sendresult || !_CardStatus._IsSpecialCard || (!_CardStatus._SpecialCardInfo._Status/*状态为有效	set status valid*/) )
	{
		// NOT SPECIAL CARD
		_SpecialCardTypeId = _CardStatus._SpecialCardInfo._CardType;
		
		//有关储值卡信息可以初步确定
		//Τ闽纗戈癟˙絋﹚
		_StoreValueRemain = 0;
		_StoreValue_CardNo = "";
	}
	else
	{
		// SPECIAL CARD
		_SpecialCardTypeId = _CardStatus._SpecialCardInfo._CardType;
		_Discount = pSetting->m_CardType.Discount(_SpecialCardTypeId);
		//有关储值卡信息可以初步确定
		//Τ闽纗戈癟˙絋﹚
		_StoreValueRemain = _CardStatus._SpecialCardInfo._StoreValue;
		_StoreValue_CardNo = _CardNo;
	}

		//入场信息
		//  Entry Information
	if (!sendresult || !_CardStatus._HaveTransaction || !_CardStatus._TransactionInfo._TransState)
	{
		if(OldCardPollEx!=_CardNo)//TA18-
		{
			_CardNo=OldCardPollEx;
			goto Retry;
		}

		// NOT NORMAL / DAMAGE / LOST TICKET
		if (pManualWnd) return ERROR_CANCEL;
		if (_CardNo[0] == 'O')//Octopus and auto mode
		{
			CCmdOtp * pCmd = CCmdOtp::Instance();
			double xtime = pCmd->GetMarkTime();
			if (xtime > 100)
			{
				COleDateTime xxtime(xtime);
				CString dsp;
				dsp.Format("猔種 : \nтぃ獃ó魁!");
				::AfxMessageBox(dsp,MB_SYSTEMMODAL);
/*
				{//use mark time
		
					_EntryTime = xxtime;
					_ExitTime = _ActionTime;
					_EntryStationID = 1;
					_GroupId = pSetting->m_StationInformation.GroupID(_EntryStationID);
					_VehicleId = 0;
					_Discount = "$0000000";
					_PaymentTimes = 0;
					_LastPayTime = COleDateTime(0.0);
					RefreshDsp();
				}
				else*/
				{//do not use, cancel
					showTip( (LPCTSTR)Err_No_Entry_Info );
//					showTip("叫笷硄!", true, false);
					return ERROR_CANCEL;
				}
			}else return ERROR_CANCEL;

		}else
		{
			return ERROR_CANCEL;
		}
		
	}
	else
	{
		// NORMAL / DAMAGE / LOST Ticket
		_EntryTime = _CardStatus._TransactionInfo._EntryTime;
		_ExitTime = _ActionTime;
		_EntryStationID = _CardStatus._TransactionInfo._EntryStation;
		if (_EntryStationID > 0.0)  // Assume _Entry station ID is valid
			_GroupId = pSetting->m_StationInformation.GroupID(_EntryStationID);

		_VehicleId = _CardStatus._TransactionInfo._CarType;
		_VehicleType = _CardStatus._TransactionInfo._CarType; 
		
		_PaymentTimes      = _CardStatus._TransactionInfo._PaymentNum;
		_LastPayTime       = _CardStatus._TransactionInfo._PayTime;
		_PayStationID      = _CardStatus._TransactionInfo._PayStation;

		if (pManualWnd) 
		{
			if(_TicketProcessCate>=1 && FALSE)//HA-
			{
				((DlgPaymentOperate *)pManualWnd)->m_cEntryStationID = _EntryStationID;
				((DlgPaymentOperate *)pManualWnd)->m_cEntryTime = _EntryTime;
				if(_LastPayTime>1 && _PayStationID>0)
					((DlgPaymentOperate *)pManualWnd)->m_cEntryTime = _LastPayTime;
				((DlgPaymentOperate *)pManualWnd)->m_cExitTime = _ExitTime;
				((DlgPaymentOperate *)pManualWnd)->m_cVehicleType = _VehicleType;
			}
			else
			{	
				((CDlgPaymentKDETicketNo *)pManualWnd)->m_cEntryStationID = _EntryStationID;
				((CDlgPaymentKDETicketNo *)pManualWnd)->m_cEntryTime = _EntryTime;
				((CDlgPaymentKDETicketNo *)pManualWnd)->m_cExitTime = _ExitTime;
				((CDlgPaymentKDETicketNo *)pManualWnd)->m_cVehicleType = _VehicleType;
			}		
		}
		_PaidAmtBefore     = _CardStatus._TransactionInfo._PaidAmount;
		_Remarks           = _CardStatus._TransactionInfo._Remark; 	
		_SpecialCardTypeId = _CardStatus._TransactionInfo._CardCate;
	
		if ((_SpecialCardTypeId == 0) || (_SpecialCardTypeId == 1))
			_TransactionNo = _EntryTime.Format((CString)(LPCTSTR)SYS_STORE_DATETIME) + showStationID(_EntryStationID);
		else if ((_SpecialCardTypeId == 7) || (_SpecialCardTypeId == 8))
			_TransactionNo = " ";
	}

	return SUCCESS;
}

SYSRESULT CCustomer::CExitCarPark::Calculate() // OTP Payment Check Point 003
                                               // damage payment check point 003
{
	if (ERROR_STANDARD > SelectDiscount()) return ERROR_CANCEL;//为非特殊卡选择一个折扣类型
	const bool PayAgain = true;
	int Result;
	CFeeCalculate FeeCalculate;
	int nCardType = _SpecialCardTypeId;
	if (_SpecialCardTypeId > 5) _SpecialCardTypeId= 0;
	if (nCardType == 8)//lost ticket
	{
		if (!g_Setting->m_ParkingFee.HandleLostTicket())
		{//no parking fee, only for penalty
			_Amount = g_Setting->m_ParkingFee.LostAmount();
			Result = Calculate_Success;
			SetDlgItemText(_hGUI, IDC_PARKING_FEE, show(_Amount));
			SetDlgItemText(_hGUI, IDC_AMOUNT, show(_Amount));
			return SUCCESS;
		}
	}
	if ((nCardType > 0)&&(nCardType <= 5))
	{}
	//preset the UD type
	_OTPZeroDeductType = 0;
	if (0 < _PaymentTimes)
	{//PayAgain
				    //           _||_
					//           \  /
					//            \/                                                 VehicleId = Vehicle type
		Result = FeeCalculate.Calculate(_Amount, _Discount, _LastPayTime, _ExitTime, _VehicleId, _GroupId, PayAgain, _OTPZeroDeductType, ShowDetail);
	}
	else
	{//first Payment
				    //           _||_
					//           \  /
					//            \/                                               VehicleId = Vehicle type
		Result = FeeCalculate.Calculate(_Amount, _Discount, _EntryTime, _ExitTime, _VehicleId, _GroupId, !PayAgain, _OTPZeroDeductType, ShowDetail);
	}
	if (!Calculate_Success == Result)
	{//计算失败
//		AfxMessageBox(FeeCalculate.GetErrorMessage(Result));	//显示错误或免费信息
		return ERROR_CANCEL;
	}
	
	if ((_Amount > -0.009) && (_Amount < 0.009) && (_OTPZeroDeductType == 0)) //free parking and haven't get the zero deduct type
	{
		if ((_SpecialCardTypeId >= 1) && (_SpecialCardTypeId <= 5)) _OTPZeroDeductType = 4;//if a special card, possible type 4;
		else if (g_nTransDiscountID >= 0) _OTPZeroDeductType = 2; //if has discount, possible type 2
		else _OTPZeroDeductType = 3; //else possible 3, grace time.
	}
	if (nCardType == 8 && g_Setting->m_ParkingFee.HandleLostTicket())//lost ticket
	{//parking fee = penalty + parking fee
		_Amount += g_Setting->m_ParkingFee.LostAmount();
	}
	//更新GUI
	SetDlgItemText(_hGUI, IDC_PARKING_FEE, show(_Amount));
	SetDlgItemText(_hGUI, IDC_AMOUNT, show(_Amount));
	_SpecialCardTypeId = nCardType;
	return SUCCESS;
}

CString CCustomer::CExitCarPark::LoadManualCardNo(bool isLost) // Genergate the manual card no. check point
{
	struct ManualTicketNo{
		int DamageCardNo;
		int LostCardNo;
	} mtn;
	CFile f;
	if (!f.Open("\\ManCAN.dat", CFile::modeReadWrite))  // 20051003 [BW] ManCan.dat modify anything will reset the manual no.
	{
		mtn.DamageCardNo = 0;
		mtn.LostCardNo = 0;
		if (isLost) mtn.LostCardNo ++;
		else mtn.DamageCardNo ++;
		f.Open("\\ManCAN.dat", CFile::modeWrite | CFile::modeCreate);
		f.Write(&mtn, sizeof(mtn));
		f.Flush();
		f.Close();
	}else{
		f.Read(&mtn, sizeof(mtn));
		if (isLost) mtn.LostCardNo ++;
		else mtn.DamageCardNo ++;
		if (mtn.LostCardNo > 999999) mtn.LostCardNo = 0;   // [BW] 20051003
		if (mtn.DamageCardNo > 999999) mtn.DamageCardNo = 0;
		f.SeekToBegin();
		f.Write(&mtn, sizeof(mtn));
		f.Flush();
		f.Close();
	}
	int c = (isLost ? 8 : 7);
	long x = (isLost ? mtn.LostCardNo : mtn.DamageCardNo);
	char a = (isLost ? 'L' : 'D');
	CString y;
	y.Format("%c%02d%06d", a, Str2Int(g_Setting->m_Communicate.StationID(), 3), x);
	return y;	
}


//打印发票
SYSRESULT CCustomer::CExitCarPark::PrintReceipt() // damage payment check point 008 (print receipt)
{
	if (!_PrintReceipt) return SUCCESS;

	CSetting *pSetting = CSetting::Instance();
	_ReceiptNo = pSetting->m_Account.ReceiptNo();

	CCmdPrint * pCmdPrint = CCmdPrint::Instance(); 
	pCmdPrint->PrintParkingFee(
				_CardNo,
				_SpecialCardTypeId,
				_EntryTime,
				_LastPayTime,
				_ActionTime,
				_Discount,
				_ReceiptNo,
				_Octopus_CardNo,
				_StoreValue_CardNo,
				_PaymentTimes,
				_OctopusRemain,
				_StoreValueRemain,
				_Amount,
				_Cash,
				_Change,
				_Octopus,
				_StoreValue,
				_VehicleId);

	return SUCCESS;
}
//  记录这次收费事件
//  Record the transaction details

void CCustomer::CExitCarPark::LogTransaction()  // damage payment check point 010 (Log Transaction)
{
	CSetting * pSetting = CSetting::Instance();
	pSetting->m_Account.LogPayAmount(_Amount, _Cash-_Change, _Octopus, _StoreValue, _SpecialCardTypeId);

	CCmdMntSend* pCMDMNT = CCmdMntSend::Instance();		//MNT通讯操作指针  // MNT communication operation pointer
	CCmdMntSend::HPAYMENT Payment;
	//发送到管理站
	// Send to Management Station
	
	_Remarks=NewCardPollEx; //TA19- remark the pay card number
	pCMDMNT->Payment(	_CardNo, _SpecialCardTypeId, _VehicleId, _ActionTime, _ReceiptNo, 
						_Amount, _Cash, _Octopus, _StoreValue, _TransactionNo, _Remarks);
	                                                           // if it is damage ticket or lost ticket
	                                                           // _TransactionNo is use to store a Manual Entry Time and Manual Entry st. no temperory
	t_AV[3]=_ActionTime;//TA19-test
	t_AV[4]=COleDateTime::GetCurrentTime();//TA19-test
CString tmp;
tmp.Format("%d:%02d,%d:%02d,%d:%02d,%d:%02d,%d:%02d",t_AV[0].GetMinute(),t_AV[0].GetSecond,
		  t_AV[1].GetMinute(),t_AV[1].GetSecond, t_AV[2].GetMinute(),t_AV[2].GetSecond,
		  t_AV[3].GetMinute(),t_AV[3].GetSecond, t_AV[4].GetMinute(),t_AV[4].GetSecond);															   // After the cmd to management, the management will arrange a new transaction no to this record

//MessageBox(NULL,t_AV[0].Format("%H:%S - ")+t_AV[1].Format("%H:%S - ")+t_AV[2].Format("%H:%S - ")+t_AV[3].Format("%H:%S - ")+t_AV[4].Format("%H:%S"),"",0);
/*	CDlgPayment::AddPaymentLog(_CardNo,showSpecialCardTypeName(_SpecialCardTypeId),
								showVehicleTypeName(_VehicleId-1),
								pSetting->m_Communicate.StationID(),
								_ActionTime.Format((CString)(LPCTSTR)SYS_SHOW_DATETIME),
								_ReceiptNo,show(_Amount),"",show(_Cash),"",show(_Octopus),
								"",show(_StoreValue),_TransactionNo);
*/
	CDlgPayment::AddPaymentLog(_CardNo,showSpecialCardTypeName(_SpecialCardTypeId),
								showVehicleTypeName(_VehicleId-1).Mid(12,5),
								pSetting->m_Communicate.StationID(),
								_ActionTime.Format((CString)(LPCTSTR)SYS_SHOW_DATETIME),
								_ReceiptNo,show(_Amount),show(_Cash),show(_Octopus),
								show(_StoreValue),_TransactionNo);
	CDlgPayment::AddAccountLog();
	
}
//.为非特殊卡选择一个折扣类型
SYSRESULT CCustomer::CExitCarPark::SelectDiscount()
{
	if (g_nTransDiscountID >= 0)
	{//has set the discount before
		if ((0 == _SpecialCardTypeId) || (7 == _SpecialCardTypeId)) //普通卡 //[BW] 20050930 
		{//discount only for hourly ticket or Damage Ticket
			_Discount = CSetting::Instance()->m_DiscountPlan.Discount(g_nTransDiscountID);
		}else{//no discount for special card
//			::AfxMessageBox("Only Hourly Ticket/Card can be entitled discount!", MB_ICONWARNING);
			::AfxMessageBox("纔磃続ノ布!", MB_ICONWARNING|MB_SYSTEMMODAL);
			_Discount = "0000";
		}
	}
	//_Discount = "0000006";
	return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    KDE Exit Car Park                      ////////
////////                             public 'ExitCarkPark'         ////////
///////////////////////////////////////////////////////////////////////////
CCustomer::CKdeUserExitCarPark::CKdeUserExitCarPark()
{
}
CCustomer::CKdeUserExitCarPark::~CKdeUserExitCarPark()
{
	CCmdJmdm* pCMDKDE = CCmdJmdm::Instance();		//KDE读卡器操作指针
//	CCmdKde* pCMDKDE = CCmdKde::Instance();		//KDE读卡器操作指针
	pCMDKDE->KDE_EjectCard();//最后无论如何都要吐票
}
void CCustomer::CKdeUserExitCarPark::Init()
{
}

SYSRESULT CCustomer::CKdeUserExitCarPark::Pre_Trade()
{
//	CCmdKde* pCMDKDE = CCmdKde::Instance();		//KDE读卡器操作指针
//	CCmdKde::PATRON CardInfo;
	CCmdJmdm* pCMDKDE = CCmdJmdm::Instance();		//KDE读卡器操作指针
	CCmdJmdm::PATRON CardInfo;
	CCmdMntSend* pCmdSend = CCmdMntSend::Instance();
	short result = ERROR_STANDARD + 1;
	if ( pCMDKDE->KDE_ReadTicket(CardInfo) )
	{//读卡成功  // Read Card Success
		// Get Card No for QueryServer
		_CardNo = CardInfo._CardNo;
		_Barcode_CardNo = CardInfo._CardNo;
		
        // Communication Normal
		if ( pCmdSend->IsNormal())
		{	
			result = QueryServer();          

			// Check the information from Database is Valid
			// Check have the entry information?
			if (_EntryStationID < 0.009)
			{
				// no entry information from database
				_EntryTime      = CardInfo._EntryTime;
				_EntryStationID = CardInfo._EntryId;	
				_GroupId        = CSetting::Instance()->m_StationInformation.GroupID(_EntryStationID);
				_VehicleId      = CardInfo._VehicleId;
				_VehicleType    = CardInfo._VehicleId;
				_Discount       = CSetting::Instance()->m_DiscountPlan.Discount(CardInfo._DiscountId);
				if (( _SpecialCardTypeId == 0) || ( _SpecialCardTypeId == 1)) //??? temp for Hourly tk
					_TransactionNo = _EntryTime.Format((CString)(LPCTSTR)SYS_STORE_DATETIME) + showStationID(_EntryStationID);					
				else if (( _SpecialCardTypeId == 7) || ( _SpecialCardTypeId == 8))
					_TransactionNo = " ";											
			}
			// check have payment information
			if (_PayStationID < 0.009)
			{
				//no payment information
				//check cardinfo
				if (CardInfo._PayId > 0.009)
				{
					// card have payment info.
					_LastPayTime   = CardInfo._PayTime;
					_PaidAmtBefore = CardInfo._PayAmount / 10;   
					_PaymentTimes  = CardInfo._PaymentTimes;
					_PayStationID  = CardInfo._PayId;
				}
			}
			// check the information in card is update than database
			else if (_PaymentTimes < CardInfo._PaymentTimes)
			{
				_LastPayTime   = CardInfo._PayTime;
				_PaidAmtBefore = CardInfo._PayAmount / 10;
				_PaymentTimes  = CardInfo._PaymentTimes;
				_PayStationID  = CardInfo._PayId;
			}
		}

		// Communication Down
		// can not get info from internet
		if (!pCmdSend->IsNormal() || result < ERROR_STANDARD )
		{
			//UCH 3-return error directly for UCH barcode ticket without entry record 20100813
			::AfxMessageBox(Err_No_Entry_Info, MB_ICONSTOP|MB_SYSTEMMODAL);
			return ERROR_CANCEL;


			if (/*( CardInfo._TicketTypeId == 1) ||*/ ( CardInfo._TicketTypeId == 2) || //??? temp for Hourly tk
                ( CardInfo._TicketTypeId == 3) || ( CardInfo._TicketTypeId == 4))
			{//if it is a speical card, and cannot retrieve info from management, abort.
				::AfxMessageBox(Err_No_Entry_Info, MB_ICONSTOP|MB_SYSTEMMODAL);
				return ERROR_CANCEL;
			}
			_EntryTime = CardInfo._EntryTime;			
			_EntryStationID = CardInfo._EntryId;
			_SpecialCardTypeId = CardInfo._TicketTypeId;

			if (( _SpecialCardTypeId == 0) || ( _SpecialCardTypeId == 1)) //??? temp for Hourly tk
				_TransactionNo = " ";					
			else if (( _SpecialCardTypeId == 7) || ( _SpecialCardTypeId == 8))
				_TransactionNo = " ";	

			_GroupId   = CSetting::Instance()->m_StationInformation.GroupID(_EntryStationID);
			_VehicleId = CardInfo._VehicleId;
			_VehicleType = CardInfo._VehicleId;		
			
			if (_SpecialCardTypeId == 1) //??? temp for hourly tk
			{
				_SpecialCardTypeId = 0;
			}
			_Discount = CSetting::Instance()->m_DiscountPlan.Discount(CardInfo._DiscountId);
			_ExitTime = _ActionTime;
			// Primary confirm the storevalue card information
			_StoreValueRemain = 0;
			_StoreValue_CardNo = "";
			// Last Payment information
			_PaymentTimes = CardInfo._PaymentTimes;
			_LastPayTime = CardInfo._PayTime;
			_PayStationID = CardInfo._PayId;
//			_PaidAmtBefore = CardInfo._PayAmount / 10;
			_PaidAmtBefore = CardInfo._PayAmount * 10; // [JC] 20060301

		}
	}
	else
	{//读卡失败
	 // Read Card Fail
		pCMDKDE->KDE_EjectCard();//吐卡
								 // Card Eject
		if (g_nCurrentStatus == 0)
		{
			::AfxMessageBox("牡 : \n布穕胊!\n叫ㄏノ'穕胊布も笆蹿'膥尿", MB_ICONSTOP|MB_SYSTEMMODAL);
			//waiting for remove the octopus card
			showTip("叫合兵布!", true, false);
			return ERROR_CANCEL;
		}
		else
		{
			SYSRESULT Result = InputTicketNo();
			if (ERROR_STANDARD > Result) 
			{
				g_nCurrentStatus = 0;
				return Result;
			}
			if (ERROR_STANDARD > QueryServer()) 
			{
				//showTip("CANNOT retrieve any info from the card! Abort...");
				showTip("礚猭т獃ó魁!");
				g_nCurrentStatus = 0;
				return ERROR_CANCEL;//查询信息
									// Check Information
			}
		}
	}
	//有关八达通卡信息可以初步确定
	// Octopus card information primary confirm
	_OctopusRemain = 0;
	_Octopus_CardNo = "";

	ASSERT(_CardNo.GetLength() > 1);
	if (g_nCurrentStatus == 0)
		if (ERROR_STANDARD > Calculate()) return ERROR_CANCEL;	//计算费用
																// Parking fee calculation

	//更新GUI 
	// 穝 GUI
	
	if (g_nCurrentStatus == 1) //Check Ticket Check Point (KDE Pre Trade)
	{
		CDlgCheckCard dlg;
		dlg.m_nKind = 0;//kde
		dlg.m_fCredit = 0.0;
		dlg.m_lpCAN = _CardNo;
		dlg.m_nCate = CardInfo._TicketTypeId;
		dlg.m_tEntTime = _EntryTime;
		dlg.m_nEntStn = _EntryStationID;
		dlg.m_tPayTime = _LastPayTime;
		dlg.m_nPayStn = _PayStationID;
		dlg.m_nPayNum = _PaymentTimes;
		dlg.m_dPayAmt = _PaidAmtBefore;
		dlg.m_VehType = _VehicleType;
		dlg.m_Remarks = _Remarks;

		if (result < ERROR_STANDARD)//successfully retrieve info from managment.
		{
			if (_CardStatus._HaveHolder)	
				dlg.m_lpHolder =_CardStatus._HolderInfo._HolderName; 
			else dlg.m_lpHolder = "";
			if (_CardStatus._IsSpecialCard) 
				dlg.m_tRegTime =_CardStatus._SpecialCardInfo._RegTime; 
			else dlg.m_tRegTime	= COleDateTime(0.0);
			if (_CardStatus._IsSpecialCard) 
				dlg.m_dSVAmt =_CardStatus._SpecialCardInfo._StoreValue; 
			else dlg.m_dSVAmt		= 0.0;
			if (_CardStatus._IsSpecialCard) 
				dlg.m_tValidFrom =_CardStatus._SpecialCardInfo._ValidForm; 
			else dlg.m_tValidFrom	= COleDateTime(0.0);
			if (_CardStatus._IsSpecialCard) 
				dlg.m_tValidTo =_CardStatus._SpecialCardInfo._ValidTo; 
			else dlg.m_tValidTo	= COleDateTime(0.0);
			if (_CardStatus._IsSpecialCard) 
				dlg.m_nValidTimes =_CardStatus._SpecialCardInfo._ValidTimes; 
			else dlg.m_nValidTimes= 0;
			if (_CardStatus._HaveHolder)	
				dlg.m_lpVehNo =_CardStatus._HolderInfo._VehiclePlateNo; 
			else dlg.m_lpVehNo	= "";
		}else{
			dlg.m_lpHolder = "";
			dlg.m_tRegTime = COleDateTime(0.0);
			dlg.m_dSVAmt = 0.0;
			dlg.m_tValidFrom = COleDateTime(0.0);
			dlg.m_tValidTo = COleDateTime(0.0);
			dlg.m_nValidTimes = 0;
			dlg.m_lpVehNo = ""; 
		}
//		CCmdKde * pCMDKDE = CCmdKde::Instance();
//		pCMDKDE->KDE_EjectCard();
		dlg.DoModal();
		g_nCurrentStatus = 0;
//		showTip("秈タ盽Μ禣家Α", true, true);
		return ERROR_CANCEL;
	}else CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, _EntryTime);
	RefreshDsp();
	
	if ((_Amount > -0.009) && (_Amount < 0.009))
	{
		if (_CardStatus._IsSpecialCard) return ERROR_CANCEL;
		if ((_PaymentTimes > 0.009) && (((double)_ActionTime - (double)_LastPayTime) <= CSetting::Instance()->m_ParkingFee.PaidGrace())) 
			return ERROR_CANCEL;//parking fee = 0, and do payment defore. donot proceed the payment again
	}
	_DisableOTPPay = TRUE;
	return SUCCESS;
}

//手动输入
SYSRESULT CCustomer::CKdeUserExitCarPark::InputTicketNo()
{
	CDlgPaymentOTPTicketNo Dlg;
	if (IDOK != Dlg.DoModal()) return ERROR_CANCEL;
	_CardNo = Dlg.CardNo();
	return SUCCESS;
}

SYSRESULT CCustomer::CKdeUserExitCarPark::Sub_Trade()
{
	CCmdJmdm * pCMDKDE = CCmdJmdm::Instance();
//	CCmdKde * pCMDKDE = CCmdKde::Instance();
//ha-	if(_TicketProcessCate>=1)//UCH 3 -for vehtype change of barcode ticket 
//		_VehicleId = _TicketPro_Vehicle;
	if ( pCMDKDE->KDE_IssueHourlyCard(_CardNo, _ActionTime, _Amount) )
	{//写卡成功
		if (_Octopus_CardNo.IsEmpty())
			CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);
		else
			CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _OctopusRemain, true);
		return SUCCESS;
	}
	else
	{//写卡失败
		return ERROR_CANCEL;
	}
}


SYSRESULT CCustomer::CKdeUserExitCarPark::ManualTrade(int _ProcessType, int _VehType, CString _ManTicketNo, COleDateTime _ManEntryTime, short _ManEntryStationID) 
// damage payment check point 007 (Manual Trade)
{
	CString tmp;
	_TicketProcessCate=0; //UCH manual 
	_DisableOTPPay = true; // false = direct pay by OTP
	_ForbiddenOtp = false; // false = enable OTP payment in cash payment dialog
    //                     _||_
	//                     \  /
	//                      \/
	if (ERROR_STANDARD > Payment()) return ERROR_CANCEL;
	if (!_Octopus_CardNo.IsEmpty()) CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _OctopusRemain, true);
	else CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);

//	CCmdKde * pCMDKDE = CCmdKde::Instance();
    //                     _||_
	//                     \  /
	//                      \/
	_DamageLostCardNo = _CardNo;
/*
	_CardNo = (isLost ? LoadManualCardNo(1) : LoadManualCardNo(0));
	_Remarks = _ManTicketNo;
    _TransactionNo = _ManEntryTime.Format((CString)(LPCTSTR)SYS_STORE_DATETIME) + showStationID(_ManEntryStationID);

*/
	if (_ProcessType == 0) //Damage Ticket
	{
		_CardNo = LoadManualCardNo(0);
		_Remarks = _ManTicketNo;
        _TransactionNo = _ManEntryTime.Format((CString)(LPCTSTR)SYS_STORE_DATETIME) + showStationID(_ManEntryStationID);
	}
	else if (_ProcessType == 1) // Lost Ticket
	{
		_CardNo = LoadManualCardNo(1);
		_Remarks = _ManTicketNo;
        _TransactionNo = _ManEntryTime.Format((CString)(LPCTSTR)SYS_STORE_DATETIME) + showStationID(_ManEntryStationID);
	}
	else if (_ProcessType == 3) // Change VehType
	{
		tmp.Format("TP%d", _VehType+1);
		_Remarks = tmp;
		_TransactionNo = "";
	}
	if (!((_ProcessType == 3) && (_CardNo.Mid(0,1) == "O")))
	{
// UCH disable issue magnet ticket
//		if (!pCMDKDE->IssueManualTicket(_CardNo, _VehType+1, _ProcessType, _EntryStationID, _EntryTime, _ActionTime, _Amount))
//			return ERROR_CANCEL;
	}
	
	// Print damage / lost ticket receipt

	//return ERROR_CANCEL; // just for test [CS]20051021

	if (ERROR_STANDARD > PrintReceipt()) return ERROR_CANCEL;
//UCH 3- open barrier after damage/lost ticket paid
	pRMPM->OpenDev();
	pRMPM->Send_RMPM_Cmd(1,TRUE);
	Sleep(1000);
	pRMPM->Send_RMPM_Cmd(1,FALSE);
	pRMPM->CloseDev();
	
	LogTransaction();
	Account();
	_DamageLostCardNo.Empty();
	g_nTransDiscountID = -1;
//	showTip("礚",true, true);
	g_nTransDiscountID = -1; g_nCurrentStatus = 0; 
	return SUCCESS;
}

///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    OTP Exit Car Park                      ////////
////////                             public 'ExitCarkPark'         ////////
///////////////////////////////////////////////////////////////////////////
CCustomer::COtpUserExitCarPark::COtpUserExitCarPark()
{
}

SYSRESULT CCustomer::COtpUserExitCarPark::TradeCommon(const CCmdOtp::PATRON& CardInfo)
{
	_CardNo = CardInfo._CardNo;

	_OctopusRemain = CardInfo._Remain;
	
	_Octopus_CardNo = _CardNo;

	//更新GUI
	SetDlgItemText(_hGUI, IDC_TICKET_NO, _CardNo);
	if (ERROR_STANDARD > CBase::Trade()) return ERROR_CANCEL;//查询信息
	return SUCCESS;
}

SYSRESULT CCustomer::COtpUserExitCarPark::TradeError()
{
	if ("" == _CardNo)
	{//获得卡号
		SYSRESULT Result = InputTicketNo();
		if (ERROR_STANDARD > Result) return Result;
	}
	//有关八达通卡信息可以初步确定
	_Octopus_CardNo = "";
	_OctopusRemain	= 0;
	//更新GUI
	SetDlgItemText(_hGUI, IDC_TICKET_NO, _CardNo);
	if (ERROR_STANDARD > CBase::Trade()) return ERROR_CANCEL;//查询信息
	return SUCCESS;
}

void CCustomer::COtpUserExitCarPark::Init()
{

}

SYSRESULT CCustomer::COtpUserExitCarPark::Pre_Trade()  // (OTP payment check point 004)
{
	
//	MessageBox(NULL,_CardNo,"exit",0);//TA19- test
	CCmdOtp * pCmd = CCmdOtp::Instance();
	if (_CardNo.GetLength() != 9 && _CardNo.GetLength() != 11)
	{
		if (g_nCurrentStatus == 0)
		{
			if (::AfxMessageBox("牡 : \n笷硄穕胊!\n叫ㄏノ'穕胊布も笆蹿'膥尿" , MB_YESNO|MB_ICONSTOP|MB_SYSTEMMODAL) == IDYES)
			{//enter the damage ticket operation
				//showTip("Octopus Card CANNOT be read!");
				showTip("礚猭т獃ó魁!");
				return ERROR_CANCEL;
			}else
			{//waiting for remove the octopus card
//				showTip("叫笷硄!", true, false);
				return ERROR_CANCEL;
			}
		}
		else
		{
			SYSRESULT Result = InputTicketNo();
			if (ERROR_STANDARD > Result) 
			{
				g_nCurrentStatus = 0;
				return Result;
			}
			if (ERROR_STANDARD > QueryServer()) 
			{
				
				return ERROR_CANCEL;//查询信息
			}
		}
	}
	short result = QueryServer();
	if (ERROR_STANDARD > result)
	{
		if (g_nCurrentStatus == 1)
		{
			::AfxMessageBox("猔種 : \nтぃ獃ó魁! \n礚猭琩布", MB_ICONWARNING|MB_SYSTEMMODAL);
			showTip("猔種 : тぃ獃ó魁!",true);
			g_nCurrentStatus = 0;
//			showTip("秈タ盽Μ禣家Α", true, true);
		}
		else
		{
			::AfxMessageBox("猔種 : \nтぃ獃ó魁! \n叫絋粄琌ノ秈初 \n絋粄'穕胊布も笆蹿'膥尿", MB_ICONWARNING|MB_SYSTEMMODAL);
			showTip("猔種 : тぃ獃ó魁!",true);
			//			showTip("叫笷硄!", true, false);
		}
		return ERROR_CANCEL;
	}
	else //UCH 4-preset card function: dont pay at cashier for pre-set card 
		if(_CardStatus._IsSpecialCard) 
			if(_CardStatus._SpecialCardInfo._CardType == 5) return ERROR_CANCEL;
	//if (ERROR_STANDARD > QueryServer()) return ERROR_CANCEL;//查询信息

	if (g_nCurrentStatus == 1) //check ticket check point (OTP Pre Trade)
	{
		CDlgCheckCard dlg;
		dlg.m_lpCAN = _CardNo;
		dlg.m_Kind = 1;
		dlg.m_fCredit = _OctopusRemain;
		dlg.m_nCate = _CardStatus._TransactionInfo._CardCate;
		dlg.m_tEntTime = _EntryTime;
		dlg.m_nEntStn = _EntryStationID;
		dlg.m_tPayTime = _LastPayTime;
		dlg.m_nPayStn = _PayStationID;
		dlg.m_nPayNum = _PaymentTimes;
		dlg.m_dPayAmt = _PaidAmtBefore;
		dlg.m_VehType = _VehicleType;
		dlg.m_Remarks = _Remarks;

		if (_CardStatus._HaveHolder) dlg.m_lpHolder =_CardStatus._HolderInfo._HolderName; 
		else dlg.m_lpHolder = "";
		if (_CardStatus._IsSpecialCard) dlg.m_tRegTime =_CardStatus._SpecialCardInfo._RegTime; 
		else dlg.m_tRegTime	= COleDateTime(0.0);
		if (_CardStatus._IsSpecialCard) dlg.m_dSVAmt =_CardStatus._SpecialCardInfo._StoreValue; 
		else dlg.m_dSVAmt		= 0.0;
		if (_CardStatus._IsSpecialCard) dlg.m_tValidFrom =_CardStatus._SpecialCardInfo._ValidForm; 
		else dlg.m_tValidFrom	= COleDateTime(0.0);
		if (_CardStatus._IsSpecialCard) dlg.m_tValidTo =_CardStatus._SpecialCardInfo._ValidTo; 
		else dlg.m_tValidTo	= COleDateTime(0.0);
		if (_CardStatus._IsSpecialCard) dlg.m_nValidTimes =_CardStatus._SpecialCardInfo._ValidTimes; 
		else dlg.m_nValidTimes= 0;
		if (_CardStatus._HaveHolder)	dlg.m_lpVehNo =_CardStatus._HolderInfo._VehiclePlateNo; 
		else dlg.m_lpVehNo	= "";
		dlg.DoModal();
		g_nCurrentStatus = 0;
//		showTip("秈タ盽Μ禣家Α", true, true);
		return ERROR_CANCEL;
	}
	RefreshDsp();
	if (ERROR_STANDARD > Calculate()) return ERROR_CANCEL;	//计算费用

	CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, _EntryTime);

	if ((_Amount > -0.009) && (_Amount < 0.009))
	{
		if (_CardStatus._IsSpecialCard) return ERROR_CANCEL;
		if ((_PaymentTimes > 0) && ((int)(((double)_ActionTime - (double)_LastPayTime)*1440) <= CSetting::Instance()->m_ParkingFee.PaidGrace())) 
			return ERROR_CANCEL;//parking fee = 0, and do payment defore. donot proceed the payment again
	}
	return SUCCESS;
}
//手动输入
SYSRESULT CCustomer::COtpUserExitCarPark::InputTicketNo()
{
	CDlgPaymentOTPTicketNo Dlg;
	if (IDOK != Dlg.DoModal()) return ERROR_CANCEL;
	_CardNo = Dlg.CardNo();
	return SUCCESS;
}

SYSRESULT CCustomer::COtpUserExitCarPark::Sub_Trade()
{
	if (!_Octopus_CardNo.IsEmpty()) CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _OctopusRemain, true);
	else CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);
//UCH modify vehicle type in private channel
//ha-	if(_TicketProcessCate>=1)
//		_VehicleId = _TicketPro_Vehicle;

	return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    Shift Account                          ////////
////////                             public 'CBase'                ////////
///////////////////////////////////////////////////////////////////////////
bool CCustomer::CShiftAccount::_PrintReceipt = true;		//是否打印发票

CCustomer::CShiftAccount::CShiftAccount()
{
}

SYSRESULT	CCustomer::CShiftAccount::Pre_Trade() // shift close account check point (Pre Trade)
{
	CSetting *pSetting = CSetting::Instance();
	pSetting->m_Account.GetCurrentAccount(_AmountRemain, _CashRemain, _OctopusRemain, _StoreValueRemain, _DutyStart, _PayNum, _CashMaintainRemain);
	return SUCCESS;
}

SYSRESULT CCustomer::CShiftAccount::Sub_Trade() // Shift Close Account check point (Sub_Trade)
{
	//	3输入参数
	CDlgPaymentShiftAccount::SetCashRemain(_CashRemain);
	CDlgPaymentShiftAccount::SetOctopusRemain(_OctopusRemain);
	CDlgPaymentShiftAccount::SetStoreValueRemain(_StoreValueRemain);
	CDlgPaymentShiftAccount::SetOperator(g_System.Operator.CurUserName);
	CDlgPaymentShiftAccount::SetDutyTime(_DutyStart);
	CDlgPaymentShiftAccount::SetPayNum(_PayNum);
	CDlgPaymentShiftAccount::SetCashKeepRemain(_CashRemain - _CashMaintainRemain);

	//  4个返回的值
	_Cash			= _CashRemain;
	_StoreValue		= _StoreValueRemain;
	_Octopus		= _OctopusRemain;
	_PrintReceipt	= TRUE;
	_Amount			= _Cash + _StoreValue + _Octopus;
	_ShiftCashMaintain = _CashRemain - _CashMaintainRemain;

	if(_AutoShift==false)
	{
		CDlgPaymentShiftAccount Dlg;
		if (IDOK != Dlg.DoModal()) return ERROR_CANCEL;
	}
	else
	if(_Cash==0 && _StoreValue==0 &&  _Octopus==0 &&  _Amount==0 &&  _ShiftCashMaintain==0)
		return ERROR_CANCEL;
	
	CCmdMntSend* pCMDMNT = CCmdMntSend::Instance();
	CSetting *pSetting = CSetting::Instance();
	_ReceiptNo = pSetting->m_Account.ReceiptNo();
	pCMDMNT->FinancialMaintain(_DutyStart, _ReceiptNo, _PayNum, _Cash, _Octopus, _StoreValue, _ShiftCashMaintain);
	//pSetting->m_Account.Demolish(); // funcation replaced by AfterShiftCloseAccount()
	pSetting->m_Account.AfterShiftCloseAccount(_ShiftCashMaintain);
	CDlgPayment::AddAccountLog();
	return SUCCESS;
}

SYSRESULT CCustomer::CShiftAccount::PrintReceipt()
{
	if (!_PrintReceipt) return SUCCESS;
	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
	pCmdPrint->PrintShiftAccount(g_System.Operator.CurUserName, _ReceiptNo,  _DutyStart, _PayNum, _Cash, _Octopus, _StoreValue, _ShiftCashMaintain);
	return SUCCESS;
}
//.记录这次交易.(log this transaction);
void CCustomer::CShiftAccount::LogTransaction()
{
	CDlgPayment::AddAccountLog();
}
///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    Close Account                          ////////
////////                             public 'ShiftAccount'         ////////
///////////////////////////////////////////////////////////////////////////
CCustomer::CCloseAccount::CCloseAccount()
{
}

void CCustomer::CCloseAccount::LogTransaction()
{
//	CSetting * pSetting = CSetting::Instance();
//	pSetting->m_Account.LogPayAmount(-_Amount, -_Cash, -_Octopus, -_StoreValue);
	CDlgPayment::AddAccountLog();
}

///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    Create Special Card                    ////////
////////                             public 'CBase'                ////////
///////////////////////////////////////////////////////////////////////////

CCustomer::CCreateSpecialCard::CCreateSpecialCard(bool IsRenewOp)
{
	/*
	 * 将使用上次的选择
	 */
	_IsRenewOp = IsRenewOp;
	_CardTypeId = 1;			//CardType from 1 ~ 4;
	_Holder_Opr_Type = Opr_New;	//默任新建用户信息
	_CardNo = "";				//让'_CardNo'始终保持卡种类信息
}


void CCustomer::CCreateSpecialCard::Init()
{
	_ActionTime = COleDateTime::GetCurrentTime();	//当前时间
	_CardNo = _CardNo.Left(1);	//紧清除卡号部分
	_CardTypeId = 1;//CardType from 1 ~ 4;	
	_StoreValueFee = 0;
	_ValidFrom = _ActionTime;
	_ValidTo = _ActionTime;
	_ValidTranTimes = 0;

	_Octopus_CardNo = "";
	_StoreValue_CardNo = "";
	_OctopusRemain = 0;		//八达通余额
	_StoreValueRemain = 0;	//储值余额

}

SYSRESULT CCustomer::CCreateSpecialCard::Calculate()
{//.跟据用户的输入,计算相应的费用
	CSetting * pSetting = CSetting::Instance();
	
	_PeriodFee		= pSetting->m_CardType.PeriodFee(_CardTypeId, _ValidFrom, _ValidTo);
	_TransactionFee	= pSetting->m_CardType.TimesFee(_CardTypeId, _ValidTranTimes);
	_JoiningFee		= pSetting->m_CardType.JoiningFee(_CardTypeId);
	_CardFee		= pSetting->m_CardType.CardFee(_CardTypeId); 
	
	_Amount = _PeriodFee + _TransactionFee + _JoiningFee + _CardFee + _StoreValueFee;
	return SUCCESS;
}

SYSRESULT CCustomer::CCreateSpecialCard::Pre_Trade()
{//	具体操作
	if (!_IsRenewOp)
	{
		CDlgCreateCard dlg;
		dlg._CardNo=			_CardNo;				
		dlg._CardTypeId=		_CardTypeId;		
														
		dlg._ValidFrom=			_ValidFrom;		
		dlg._ValidTo=			_ValidTo;				
		dlg._ValidTranTimes=	_ValidTranTimes;		
		dlg._StoreValueFee=		_StoreValueFee;			
														
		dlg._PeriodFee=			_PeriodFee;						
		dlg._TransactionFee=	_TransactionFee;		
		dlg._JoiningFee=		_JoiningFee;			
		dlg._CardFee=			_CardFee;				
		if (IDOK != dlg.DoModal()) return ERROR_CANCEL;
		_CardNo=			dlg._CardNo;				
		_CardTypeId=		dlg._CardTypeId;		
														
		_ValidFrom=							dlg._ValidFrom;			
		_ValidTo=							dlg._ValidTo;					
		_RegTime=							COleDateTime::GetCurrentTime();
		_ValidTranTimes=					dlg._ValidTranTimes;			
		_StoreValueFee=						0;
		_Status =							1;
		_HolderID =							0;
		_PeriodFee=							dlg._PeriodFee;							
		_TransactionFee=					dlg._TransactionFee;			
		_JoiningFee=						dlg._JoiningFee;				
		_CardFee=							dlg._CardFee;				
		Calculate();
		CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, "CREATE SEASON CARD");
	}else{
		CDlgCardRenew dlg;
		dlg._CardNo=			_CardNo;				
		dlg._CardTypeId=		_CardTypeId;		
		dlg._Status = 1;
		dlg._ValidFrom=			_ValidFrom;		
		dlg._ValidTo=			_ValidTo;				
		dlg._ValidTranTimes=	_ValidTranTimes;		
		dlg._StoreValueFee=		0.0;
		if (IDOK != dlg.DoModal()) return ERROR_CANCEL;

		_CardNo=		dlg._CardNo;
		_RegTime=		dlg._RegTime;
		_HolderID=		dlg._HolderID;
		_CardTypeId=	dlg._CardTypeId;		
		_Status =		dlg._Status;
		_ValidFrom=		dlg._ValidFrom;			
		_ValidTo=		dlg._ValidTo;					
		_ValidTranTimes=dlg._ValidTranTimes;			
		_StoreValueFee=	0;
		_Amount =		dlg._Amount;
		CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, "EXTEND SEASON CARD");
	}
	_DisableOTPPay = true;
	_ForbiddenOtp = true;
	return SUCCESS;
}

SYSRESULT CCustomer::CCreateSpecialCard::Sub_Trade()
{//	发布一个特殊特殊卡
	if (_IsRenewOp) 
	{//remove the card
		//UCH 3 -remove kde
//		CCmdKde * pkde = CCmdKde::Instance();
		if (_CardNo.Left(1) == "P")
		{
			showTip("叫合兵布!", true);
//			pkde->KDE_EjectCard();
			DWORD x = GetTickCount();
//			while(pkde->KDE_NeedRead()) 
			{
				Sleep(500);	//等待操作员取卡.
//				if (GetTickCount() - x > 5000) {pkde->KDE_EjectCard(); x = GetTickCount();}
			}
		}else{
			CCmdOtp::Instance()->WaitForOtpRemove(true);
		}
		CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);
		return SUCCESS;
	}
	if (_CardNo.Left(1) == "P")
	{
		CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);
		const CString IssueError = "Issue Ticket Error:\n\n    1. Retry .\n\n    2. Change another ticket retry. \n\n    3. Cancel.";
/*		CCmdKde * pkde = CCmdKde::Instance();
		while( true )
		{
			showTip("叫础合兵...", true, false);
			while(!pkde->KDE_NeedRead())
			{
				Sleep(500);	//等待操作员取卡.
			}
			if (pkde->KDE_IssueSpecialCard(_CardNo, ""))
			{
				showTip("叫合兵布!", true);
				pkde->KDE_EjectCard();
				while(CCmdKde::Instance()->KDE_NeedRead())
				{
					Sleep(500);	//等待操作员取卡.
				}
				return SUCCESS;
			}
			else
			{
				if (IDRETRY == MessageBox(_hGUI,
						(CString)(LPCTSTR)IssueError,
						(CString)(LPCTSTR)"Issue Ticket Error", 
						MB_RETRYCANCEL| MB_ICONQUESTION ) )
				{
					showTip("叫合兵布!", true);
					pkde->KDE_EjectCard();
					while(CCmdKde::Instance()->KDE_NeedRead()) Sleep(500);	//等待操作员取卡.
					continue;
				}
				else
				{
					showTip("叫合兵布!", true);
					pkde->KDE_EjectCard();
					while(CCmdKde::Instance()->KDE_NeedRead()) Sleep(500);	//等待操作员取卡.
					break;
				}
			}
		}
		*/
	}else 
	{
		CCmdOtp::Instance()->WaitForOtpRemove(true);
		return SUCCESS;
	}
	return ERROR_CANCEL;
}

SYSRESULT CCustomer::CCreateSpecialCard::PrintReceipt()
{//	打印发票
	if (!_PrintReceipt) return SUCCESS;

	CSetting *pSetting = CSetting::Instance();
	_ReceiptNo = pSetting->m_Account.ReceiptNo();
	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
	
	if (!_IsRenewOp)//is create receipt
	{
		pCmdPrint->PrintSeasonCreate(
					_ReceiptNo,// -> CString         sc_No, 
		    		_CardNo,   // -> CString      sc_CardNo, 
					_ActionTime,// -> COleDateTime sc_PayTime,
					_ValidFrom,// -> COleDateTime sc_ValidFrom,
					_ValidTo,// -> COleDateTime sc_ValidTo,
					_PeriodFee+_TransactionFee+_JoiningFee+_CardFee,	// -> double       sc_Amt, 
					_Cash,// -> double       sc_Cash,
					_Change// -> double       sc_Change
				);
	}else{//is extend receipt
		pCmdPrint->PrintSeasonExtend(
					_ReceiptNo,// -> CString         sc_No, 
		    		_CardNo,   // -> CString      sc_CardNo, 
					_ActionTime,// -> COleDateTime sc_PayTime,
					_ValidFrom,// -> COleDateTime sc_ValidFrom,
					_ValidTo,// -> COleDateTime sc_ValidTo,
					_Amount,	// -> double       sc_Amt, 
					_Cash,// -> double       sc_Cash,
					_Change// -> double       sc_Change
				);
	}
	return SUCCESS;
}

void CCustomer::CCreateSpecialCard::LogTransaction()
{//  记录这次事件
	CSetting * pSetting = CSetting::Instance();
	pSetting->m_Account.LogPayAmount(_Amount, _Cash-_Change, _Octopus, _StoreValue, 10);
	CDlgPayment::AddAccountLog();
	//send communication message to manganement to registe a special card.
	CCmdMntSend * pCmd = CCmdMntSend::Instance();
	pCmd->CreateSpecCard(_CardNo, _HolderID, _RegTime, _CardTypeId, _Status, _ValidFrom, _ValidTo, _ValidTranTimes, _StoreValueFee, "");

	CString remark, tmpstr, tmpstr1;
	if (!_IsRenewOp)//create
	{
		if (pSetting->m_CardType.WorkMode(_CardTypeId) == 0) tmpstr.Format("Validity:%s-%s", _ValidFrom.Format("%d/%m/%y"), _ValidTo.Format("%d/%m/%y"));
		else tmpstr.Format("Num of Free Uses: %d", _ValidTranTimes);
		remark.Format("2Add %s: %s", pSetting->m_CardType.Name(_CardTypeId).Left(17), tmpstr);
		pCmd->AddValue(_CardNo, g_System.Operator.CurUserName.Left(20), _ActionTime, _ReceiptNo, 
						  _Amount,  remark);
	}else{//renew
		if (pSetting->m_CardType.WorkMode(_CardTypeId) == 0) 
		{
			tmpstr.Format("%s-%s", _ValidFrom.Format("%d/%m/%y"), _ValidTo.Format("%d/%m/%y"));
		}
		else 
		{
			tmpstr.Format("%d Trans", _ValidTranTimes);
		}
		remark.Format("3Extend %s to %s", pSetting->m_CardType.Name(_CardTypeId).Left(17), tmpstr);
		pCmd->AddValue(_CardNo, g_System.Operator.CurUserName.Left(20), _ActionTime, _ReceiptNo, 
						  _Amount,  remark);
	}
}

///////////////////////////////////////////////////////////////////////////
////////                                                           ////////
////////                    Otp User Add Value                     ////////
////////                             public 'CBase'                ////////
///////////////////////////////////////////////////////////////////////////
bool CCustomer::COtpUserAddValue::_PrintReceipt = true;

CCustomer::COtpUserAddValue::COtpUserAddValue()
{
}

void CCustomer::COtpUserAddValue::Init()
{
	_StoreValue = 0.0;
	_StoreValueRemain = 0.0;
	_Octopus = 0.0;
	_OctopusRemain = 0.0;
	_Octopus_CardNo = "";
	_StoreValue_CardNo = "";
}

SYSRESULT CCustomer::COtpUserAddValue::Pre_Trade()  // (add value check point 004)
{//确定将要冲值的金额
//	MessageBox(NULL,"try add","",0);//TA19- test
	CDlgPaymentOTPPreAddvalue Dlg;
	if (IDOK != Dlg.DoModal()) 
		return ERROR_CANCEL;

	t_AV[0]=COleDateTime::GetCurrentTime();//TA19-test

	_ValueBeforeAdd = CDlgPaymentOTPPreAddvalue::OctopusRemain();
	_Amount			= CDlgPaymentOTPPreAddvalue::Amount();
	_CardNo			= CDlgPaymentOTPPreAddvalue::OctopusCardNo();
	_DisableOTPPay  = true;
	_ForbiddenOtp   = true;
	_CardNo = "O" + _CardNo;
	
	CCmdLcd::Instance()->LCD_DisplayBeforePay(_Amount, "OCTOPUS ADD-VALUE");
	return SUCCESS;
}

SYSRESULT CCustomer::COtpUserAddValue::Sub_Trade()
{//冲值
	
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	if (!pCmdOtp->OTP_AddValue(_Amount, _OctopusRemain, _CardNo)) 
	{//充值失败
		CString x = pCmdOtp->Translate();
//TA11A 2009
	if(pCmdOtp->GetLastError()!=22)
		::AfxMessageBox(x, MB_ICONSTOP|MB_SYSTEMMODAL);
		return ERROR_CANCEL;
	}
	CCmdLcd::Instance()->LCD_DisplayAfterPay(_Amount, _Change);	
	return SUCCESS;
}

//	打印发票
SYSRESULT CCustomer::COtpUserAddValue::PrintReceipt()
{
	//return SUCCESS;
	if (!_PrintReceipt) return SUCCESS;

	CSetting *pSetting = CSetting::Instance();
	_ReceiptNo = pSetting->m_Account.ReceiptNo();


	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
	pCmdPrint->PrintAddValue(
				_ReceiptNo,
				_CardNo,
				_ActionTime,
				_Amount,
				_ValueBeforeAdd,
				_ValueBeforeAdd+_Amount,
				_Cash,
				_Change);

	return SUCCESS;
}

void CCustomer::COtpUserAddValue::LogTransaction()
{//  记录这次收费事件


	CSetting * pSetting = CSetting::Instance();
	pSetting->m_Account.LogPayAmount(_Amount, _Cash-_Change, _Octopus, _StoreValue, 9/*add value*/);

	CCmdMntSend* pCMDMNT = CCmdMntSend::Instance();		//MNT通讯操作指针
	CString remark;
	remark.Format("1Add Value: $%6.2f->%6.2f", _ValueBeforeAdd, _ValueBeforeAdd+_Amount);
	//发送到管理站
	pCMDMNT->AddValue(_CardNo, g_System.Operator.CurUserName.Left(20), _ActionTime, _ReceiptNo, 
					  _Amount,  remark);


	CDlgPayment::AddAccountLog();
}







void CCustomer::CBase::OTPstop()
{
	_DisableOTPPay = false;
	_ForbiddenOtp = false;
}

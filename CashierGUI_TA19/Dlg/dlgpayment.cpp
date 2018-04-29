// dlgpayment.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdMntSend.h"
#include "..\Customer.h"
#include "..\setting.h"
#include "DlgLogin.h"
#include "dlgInput.h"
#include "dlgpayment.h"
#include "dlgpaymentkdeticketno.h"
#include "DlgPaymentSelectDiscount.h"
#include "..\dlgcheckcard.h"
#include "..\dlgexitconfirm.h"
#include "..\dlgentcreate.h"
#include "DlgOTP4Record.h"

//#include "..\Eltra.h"
#include "..\Jmdm.h"

//CEltra *pRMPM=new CEltra(4);
CJmdm *pRMPM=new CJmdm(4);

extern _System		g_System;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int _TicketProcessCate;//UCH OTP/barcode - 1/2 ; other-0 ;

UINT g_nCurrentStatus;
int  g_nTransDiscountID;
/////////////////////////////////////////////////////////////////////////////
// CDlgPayment dialog
CDlgPayment* CDlgPayment::m_pThis=NULL;


CDlgPayment::CDlgPayment(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPayment::IDD, pParent)
{
	m_pThis=this;
	//{{AFX_DATA_INIT(CDlgPayment)
	m_fCashAmt = 0.0;
	m_CurOptr = _T("");
	m_DutyStart = _T("");
	m_fOTPAmt = 0.0;
	m_nPayNum = 0;
	m_fSVAmt = 0.0;
	m_fTotAmt = 0.0;
	m_strWMode = _T("");
	m_fShiftCashAmt = 0.0;
	m_fShiftOTPAmt = 0.0;
	m_fShiftSVAmt = 0.0;
	m_fShiftTotalAmt = 0.0;
	m_fCashKeep = 0.0;
	m_fCashMaintain = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgPayment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPayment)
	DDX_Control(pDX, IDC_MSG_LIST2, m_TipCtrl2);
	DDX_Control(pDX, IDC_MSG_LIST, m_TipCtrl);
	DDX_Control(pDX, PAYMENT_LIST, m_Payment_List);
	DDX_Control(pDX, IDC_ERROR_OTP_CARD, m_Error_OTP_Card);
	DDX_Control(pDX, IDC_ERROR_KDE_CARD, m_Error_KDE_Card);
	DDX_Control(pDX, IDC_OTP_CARD_ADD_VALUE, m_Otp_Card_Add_Value);
	DDX_Text(pDX, IDC_EDIT_CASHAMT, m_fCashAmt);
	DDX_Text(pDX, IDC_EDIT_CUROPTR, m_CurOptr);
	DDX_Text(pDX, IDC_EDIT_DUTYSTART, m_DutyStart);
	DDX_Text(pDX, IDC_EDIT_OTPAMT, m_fOTPAmt);
	DDX_Text(pDX, IDC_EDIT_PAYNUM, m_nPayNum);
	DDX_Text(pDX, IDC_EDIT_SVAMT, m_fSVAmt);
	DDX_Text(pDX, IDC_EDIT_TOTALAMT, m_fTotAmt);
	DDX_Text(pDX, IDC_STATIC_WMODE, m_strWMode);
	DDX_Text(pDX, IDC_EDIT_SHIFT_CASHAMT, m_fShiftCashAmt);
	DDX_Text(pDX, IDC_EDIT_SHIFT_OTPAMT, m_fShiftOTPAmt);
	DDX_Text(pDX, IDC_EDIT_SHIFT_SVAMT, m_fShiftSVAmt);
	DDX_Text(pDX, IDC_EDIT_SHIFT_TOTALAMT, m_fShiftTotalAmt);
	DDX_Text(pDX, IDC_EDIT_CASHKEEP, m_fCashKeep);
	DDX_Text(pDX, IDC_EDIT_CASHMAINTAIN, m_fCashMaintain);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CDlgPayment, CDialog)
	//{{AFX_MSG_MAP(CDlgPayment)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OTP_CARD_ADD_VALUE, OnOtpCardAddValue)
	ON_BN_CLICKED(IDC_ERROR_KDE_CARD, OnErrorKdeCard)
	ON_BN_CLICKED(IDC_TIMESYNCHRONIZE, OnTimesynchronize)
	ON_BN_CLICKED(IDC_ERROR_OTP_CARD, OnErrorOtpCard)
	ON_BN_CLICKED(IDC_SHIFT_ACCOUNT, OnShiftAccount)
	ON_BN_CLICKED(IDC_CLOSEACCOUNT, OnCloseaccount)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEL_DISCOUNT, OnSelDiscount)
	ON_BN_CLICKED(IDC_LAST4RECORD, OnLast4record)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_TIP, OnTip)
	ON_MESSAGE(IDC_CLOSEACCOUNT1, OnCloseaccount1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPayment message handlers

void CDlgPayment::InitControl()
{
	g_nCurrentStatus = 0;
	g_nTransDiscountID = -1;
	//操作提示
	CSetting * pSetting = CSetting::Instance();
	//改变文字大小
	//GetDlgItem(IDC_MSG_LIST)->SetFont(&pSetting->FontBig()); // [PY]: 06 Jun 2005 - changed upper msg
	GetDlgItem(IDC_MSG_LIST)->SetFont(&pSetting->FontMid());   // listbox to a smaller font size

	//付款列表
	m_Payment_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
//	m_Payment_List.InsertColumn(0, LoadS(IDS_STRING_CARDNO), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(0, LoadS(IDS_STRING_CARDNO), LVCFMT_LEFT, 100);//TA19-
	m_Payment_List.InsertColumn(1, LoadS(IDS_STRING_CATEGORY), LVCFMT_LEFT, 60);
	m_Payment_List.InsertColumn(2, LoadS(IDS_STRING_VEHTYPE), LVCFMT_RIGHT, 60);
	m_Payment_List.InsertColumn(3, LoadS(IDS_STRING_STNID), LVCFMT_LEFT, 50);
	m_Payment_List.InsertColumn(4, LoadS(IDS_STRING_PAYTIME), LVCFMT_LEFT, 160);
	m_Payment_List.InsertColumn(5, LoadS(IDS_STRING_RECEIPTNO), LVCFMT_LEFT, 80);
/*
	m_Payment_List.InsertColumn(6, LoadS(IDS_STRING_AMOUNT), LVCFMT_LEFT, 80);
	
	m_Payment_List.InsertColumn(7, LoadS(IDS_STRING_PAYMODE1), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(8, LoadS(IDS_STRING_AMOUNT1), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(7, LoadS(IDS_STRING_PAYMODE2), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(8, LoadS(IDS_STRING_AMOUNT2), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(7, LoadS(IDS_STRING_PAYMODE3), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(8, LoadS(IDS_STRING_AMOUNT3), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(13, LoadS(IDS_STRING_TRANSNO), LVCFMT_LEFT, 80);
*/
	m_Payment_List.InsertColumn(6, "龟肂", LVCFMT_LEFT, 80);

//	m_Payment_List.InsertColumn(7, LoadS(IDS_STRING_PAYMODE1), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(7, "瞷", LVCFMT_LEFT, 80);
//	m_Payment_List.InsertColumn(9, LoadS(IDS_STRING_PAYMODE2), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(8, "笷硄蹿", LVCFMT_LEFT, 80);
//	m_Payment_List.InsertColumn(11, LoadS(IDS_STRING_PAYMODE3), LVCFMT_LEFT, 80);
	m_Payment_List.InsertColumn(9, "纗蹿", LVCFMT_LEFT, 80);
//	m_Payment_List.InsertColumn(10, LoadS(IDS_STRING_TRANSNO), LVCFMT_LEFT, 160);

	//记帐
}

BOOL CDlgPayment::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//对话框背景
	m_brush.CreateSolidBrush(RGB(212, 208, 200));  //bg colour
	
	InitControl();	//初始化所有的静态文本的标题，颜色.
	//登陆时帐目信息
	m_AutoXFileDoneFlag = false;
	SetTimer(1, 30000, 0);
	SetTimer(2, 1000, 0);
	m_strWMode = "礚";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CDlgPayment::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor ==CTLCOLOR_DLG)
		return m_brush;//对话框
	if (pWnd->m_hWnd == m_TipCtrl.m_hWnd)
	{
		long l = GetTickCount() / 1000;
		// flashing - alternate text colour between blue and red
		/*if (l % 2 == 0) SetTextColor(pDC->m_hDC, RGB(255, 0, 0));
		else SetTextColor(pDC->m_hDC, RGB(0, 0, 255));*/

		// [PY]: 06 Jun 2005 - changed color of upper msg listbox to BLUE; no flashing
		SetTextColor(pDC->m_hDC, RGB(0, 0, 255));
	}

	// [PY]: 06 Jun 2005 - set font color of lower msg listbox to grey
	if (pWnd->m_hWnd == m_TipCtrl2.m_hWnd)
		SetTextColor(pDC->m_hDC, RGB(128, 128, 128));

	return hbr;
}

void CDlgPayment::OnOK() 
{
	// TODO: Add extra validation here
	::AfxMessageBox("OK",MB_SYSTEMMODAL);
	//CDialog::OnOK();
}

void CDlgPayment::OnCancel() 
{
	::AfxMessageBox("Cancel",MB_SYSTEMMODAL);
	
	//CDialog::OnCancel();
}
// Show Tip
LRESULT CDlgPayment::OnTip(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 0){//on message
		//在列表开始处插入一条信息
		m_TipCtrl.DeleteString(0); // [PY]: 06 Jun 2005 - clear upper msg listbox
		m_TipCtrl.DeleteString(1); // delete 1st and 2nd lines. no 'clear' method to clear the listbox?

		m_TipCtrl.InsertString(0, (CString)(LPCTSTR)wParam);
		m_TipCtrl2.InsertString(0, (CString)(LPCTSTR)wParam); // [PY]: 06 Jun 2005 - insert new msg to lower msg listbox
		/*
		if (m_TipCtrl.GetCount() == 10)
			m_TipCtrl.DeleteString(10);
		if (m_TipCtrl.GetCount() >= 10)
		{
			m_TipCtrl.DeleteString(11);
			m_TipCtrl.DeleteString(10);
		}
		*/
	}else {//on w.mode
		m_strWMode = (CString)(LPCTSTR)wParam;
		UpdateData(FALSE);
		Invalidate();
		UpdateWindow();
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
//充值操作


void CDlgPayment::OnOtpCardAddValue()  // press add value button (add value check point 001)
{
	if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 500))
	{
		showTip("笷硄矪瞶い, 礚猭ㄏノ糤! 叫р笷硄ǐ", true);
		return;
	}
	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(false);
	
	//处理错误的OTP卡.
	CCustomer::COtpUserAddValue OtpUserAddValue;
	OtpUserAddValue.Trade();
//TA11A 2009 Item3 for addvalue bug: cann't running if shutdown MOP when addvalue
/////old
//	CCmdOtp::Instance()->WaitForOtpRemove();
////new
;
////end
	ReleaseMutex(g_System.m_OprBusyMutex);	
//	showTip("叫╃笷硄┪础合...", true, false);
	showTip("叫╃笷硄┪苯核兵絏布...", true, false); //UCH 3-barcode message tips
	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(true);
	Sleep(1000);
}

void CDlgPayment::OnErrorKdeCard() // (Damage Ticket Check Point 001)
{
	GetDlgItem(IDC_ERROR_KDE_CARD)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	{	//处理错误的KDE卡.
		//CCustomer::CKdeUserExitCarPark KdeUserExitCarPark;
		//KdeUserExitCarPark.Trade();
		CDlgPaymentKDETicketNo dlg;
		dlg.m_Type = 0;
		dlg.DoModal();
	}
	GetDlgItem(IDC_ERROR_KDE_CARD)->EnableWindow(true);
}

void CDlgPayment::OnTimesynchronize() 
{
	GetDlgItem(IDC_TIMESYNCHRONIZE)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	if (!CCmdMntSend::Instance()->IsNormal())
	{

//		::AfxMessageBox("This function cannot be utilized becasue of the bad communication!");
		::AfxMessageBox("硄癟い耞礚猭秈︽丁˙巨!",MB_SYSTEMMODAL);		
	}else {
	CDlgExitConfirm  dlg;
	dlg.DoModal();}
	GetDlgItem(IDC_TIMESYNCHRONIZE)->EnableWindow(true);
}

void CDlgPayment::OnErrorOtpCard() 
{
	GetDlgItem(IDC_ERROR_OTP_CARD)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	{	//处理错误的OTP卡.
		//CCustomer::COtpUserExitCarPark OtpUserExitCarPark;
		//OtpUserExitCarPark.TradeError();
		CDlgPaymentKDETicketNo dlg;
		dlg.m_Type = 1;
		dlg.DoModal();
	}
	GetDlgItem(IDC_ERROR_OTP_CARD)->EnableWindow(true);
}

void CDlgPayment::AddPaymentLog(CString	CardNo,
								CString		Category,
								CString		CarType,
								CString		StationID,
								CString		Paytime,
								CString		ReceiptNo,
								CString		Amount,
								//CString		PayMode1,
								CString		Amount1,
								//CString		PayMode2,
								CString		Amount2,
								//CString		PayMode3,
								CString		Amount3,
								CString		TransactionNo)
{
	int nCount = 0;
	m_pThis->m_Payment_List.InsertItem(nCount, CardNo);
	m_pThis->m_Payment_List.SetItemText(nCount, 1, Category);
	m_pThis->m_Payment_List.SetItemText(nCount, 2, CarType);
	m_pThis->m_Payment_List.SetItemText(nCount, 3, StationID);
	m_pThis->m_Payment_List.SetItemText(nCount, 4, Paytime);
	m_pThis->m_Payment_List.SetItemText(nCount, 5, ReceiptNo);
	m_pThis->m_Payment_List.SetItemText(nCount, 6, Amount);
//	m_pThis->m_Payment_List.SetItemText(nCount, 7, PayMode1);
	m_pThis->m_Payment_List.SetItemText(nCount, 7, Amount1);
//	m_pThis->m_Payment_List.SetItemText(nCount, 9, PayMode2);
	m_pThis->m_Payment_List.SetItemText(nCount, 8, Amount2);
//	m_pThis->m_Payment_List.SetItemText(nCount, 11, PayMode3);
	m_pThis->m_Payment_List.SetItemText(nCount, 9, Amount3);
//	m_pThis->m_Payment_List.SetItemText(nCount, 10, TransactionNo);
}

void CDlgPayment::AddAccountLog() // Shift Close Account Check Point (Add Account Log)
{
	CSetting * pSetting = CSetting::Instance();
	double mcash, motp, msv, mamt, mcashmaintain; // Shift information
	double m_tcash, m_totp, m_tsv, m_tamt, m_tcashmaintain; // total information
	long mpaynum;
	long m_tpaynum[9];
	COleDateTime tmpDutyStart;
	pSetting->m_Account.GetCurrentAccount(mamt, mcash, motp, msv, tmpDutyStart, mpaynum, mcashmaintain); // Shift information
	pSetting->m_Account.GetTotalAccount(m_tamt, m_tcash, m_totp, m_tsv, m_tpaynum, m_tcashmaintain); // Total information
	CString mDutyStart = tmpDutyStart.Format("%H:%M");
	CString mCurOptr = g_System.Operator.CurUserName;
	CString tmpstr;
	HWND _hGUI = g_System.RunTime.hOtpPaymentDlg;

	tmpstr.Format("$%8.2f", mcash);
	::SetDlgItemText(_hGUI, IDC_EDIT_SHIFT_CASHAMT, tmpstr);

	tmpstr.Format("$%8.2f", motp);
	::SetDlgItemText(_hGUI, IDC_EDIT_SHIFT_OTPAMT, tmpstr);

	tmpstr.Format("$%8.2f", msv);
	::SetDlgItemText(_hGUI, IDC_EDIT_SHIFT_SVAMT, tmpstr);

	tmpstr.Format("$%8.2f", mamt);
	::SetDlgItemText(_hGUI, IDC_EDIT_SHIFT_TOTALAMT, tmpstr);


	tmpstr.Format("$%8.2f", m_tcash);
	::SetDlgItemText(_hGUI, IDC_EDIT_CASHAMT, tmpstr);

	tmpstr.Format("$%8.2f", m_tcashmaintain);
	::SetDlgItemText(_hGUI, IDC_EDIT_CASHMAINTAIN, tmpstr);

	tmpstr.Format("$%8.2f", m_tcash-m_tcashmaintain);// m_tcash-m_tcashmaintain
	::SetDlgItemText(_hGUI, IDC_EDIT_CASHKEEP, tmpstr);

	tmpstr.Format("$%8.2f", m_totp);
	::SetDlgItemText(_hGUI, IDC_EDIT_OTPAMT, tmpstr);

	tmpstr.Format("$%8.2f", m_tsv);
	::SetDlgItemText(_hGUI, IDC_EDIT_SVAMT, tmpstr);

	tmpstr.Format("$%8.2f", m_tamt);
	::SetDlgItemText(_hGUI, IDC_EDIT_TOTALAMT, tmpstr);



	::SetDlgItemText(_hGUI, IDC_EDIT_CUROPTR, mCurOptr);
	::SetDlgItemText(_hGUI, IDC_EDIT_DUTYSTART, mDutyStart);
	tmpstr.Format("%d", mpaynum);
	::SetDlgItemText(_hGUI, IDC_EDIT_PAYNUM, tmpstr);
}
/////////////////////////////////////////////////////////////////////////
//
void CDlgPayment::OnShiftAccount() 
{
	GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	{	//换班
		CCustomer::CShiftAccount ShiftAccount;
		ShiftAccount.Trade();
		CDlgLogin dlgLogin;		//让下一个操作员登陆
		dlgLogin.DoModal();
	}
	GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(true);
}

void CDlgPayment::OnCloseaccount() 
{
	_TicketProcessCate  = 0;
	GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	//换班
	CCustomer::CCloseAccount CloseAccount;
	CloseAccount._AutoShift=false;
	if (CloseAccount.Trade() == ERROR_CANCEL)
	{
		GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(true);		//  关闭系统
	}
	else
	{
		GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(true);		//  关闭系统
		CCmdMntSend * pSend = CCmdMntSend::Instance();
		pSend->SendCurrentExistXFiles();
		this->GetParent()->GetParent()->PostMessage(WM_CLOSE);
	}
	
//	this->GetParent()->GetParent()->DestroyWindow();
}

void CDlgPayment::OnCloseaccount1(LPVOID wParam,LPVOID lParam) //FOR AutoShift CC
{
	GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	//换班
	CCustomer::CCloseAccount CloseAccount;
	CloseAccount._AutoShift=true;
	if (CloseAccount.Trade() == ERROR_CANCEL)
	{
		GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(true);		//  关闭系统
	}
	else
	{
		GetDlgItem(IDC_SHIFT_ACCOUNT)->EnableWindow(true);		//  关闭系统
		CCmdMntSend * pSend = CCmdMntSend::Instance();
		pSend->SendCurrentExistXFiles();
		this->GetParent()->GetParent()->PostMessage(WM_CLOSE);
	}
}

void CDlgPayment::OnButton1() 
{
	// TODO: Add your control notification handler code here
	g_nCurrentStatus = 1;
//	showTip("秈琩布家Α",true, true);
}

void CDlgPayment::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//process x files
	int m_nAutoFuncTimeInMin; 
	int CurTimeInMin;
	CSetting::CBaseSystemSetting BaseSystemSetting;
//	long l;
	switch (nIDEvent)
	{
	case 1:
		AddAccountLog();
		BaseSystemSetting = CSetting::Instance()->m_BaseSystemSetting;
		m_nAutoFuncTimeInMin = BaseSystemSetting.AutoFunctionTime().Minutes() + _ttol(CSetting::Instance()->m_Communicate.StationID()) - 1;
		CurTimeInMin = (CTime::GetCurrentTime().GetHour()) * 60 + CTime::GetCurrentTime().GetMinute();
		
		if ((CurTimeInMin - m_nAutoFuncTimeInMin < 3) 
					&& (CurTimeInMin >= m_nAutoFuncTimeInMin)
						&& (!m_AutoXFileDoneFlag))
			{//if time to autofunction and haven't do it today
				m_AutoXFileDoneFlag = TRUE; //have do it today;
				CCmdMntSend::Instance()->UploadOtpXFile();
			}

		if (CurTimeInMin - m_nAutoFuncTimeInMin > 10) 
			m_AutoXFileDoneFlag = FALSE;//after 20 min, reset the flag
		break;
	case 2:
/*		l = GetTickCount() / 1000;
		if (l % 2 == 0)
		{
			SetTextColor(m_TipCtrl.GetDC()->m_hDC, RGB(255, 0, 0));
		}else{
			SetTextColor(m_TipCtrl.GetDC()->m_hDC, RGB(0, 0, 255));
		}
*/		m_TipCtrl.Invalidate();
//		m_TipCtrl.UpdateWindow();
		
		break;
	}
}
void CDlgPayment::OnSelDiscount() // 
{
/*	pRMPM->OpenDev();
	pRMPM->Send_RMPM_Cmd(1,TRUE);
	Sleep(1000);
	pRMPM->Send_RMPM_Cmd(1,FALSE);
	pRMPM->CloseDev();
	return;
*///HA-delete open barrier manually
	if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 500))
	{
		showTip("笷硄矪瞶い, 礚猭ㄏノ纔磃矪瞶! 叫р笷硄ǐ", true);
		return;
	}
//	GetDlgItem(IDC_SEL_DISCOUNT)->EnableWindow(false);
	
	CDlgPaymentSelectDiscount dlg;
	dlg.SetDiscount(g_nTransDiscountID);
	if (dlg.DoModal() == IDOK) 	
	{
		g_nTransDiscountID = dlg.DiscountID();
		CString x = CSetting::Instance()->m_DiscountPlan.DiscountModeName(g_nTransDiscountID);
		x.TrimRight();
		showTip(x,true, true);
	}else{
		showTip("礚",true, true);
		g_nTransDiscountID = -1;
	}
	ReleaseMutex(g_System.m_OprBusyMutex);	
	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(true);
}

void CDlgPayment::OnEntCreate() 
{
	GetDlgItem(IDC_ERROR_KDE_CARD)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	{	
		CDlgEntCreate dlg;
		dlg.DoModal();
	}
	GetDlgItem(IDC_ERROR_KDE_CARD)->EnableWindow(true);
}

void CDlgPayment::OnLast4record() 
{ 
	
	CDlgOTP4Record dlg;
	if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 500))
	{
//		showTip("笷硄矪瞶い, 礚猭ㄏノ糤! 叫р笷硄ǐ", true);
		return;
	}
//	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(false);

	if(IDOK!=dlg.DoModal())
	{
		return;
	}
	
	ReleaseMutex(g_System.m_OprBusyMutex);	
//	showTip("叫╃笷硄┪础合...", true, false);
//	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(true);
	Sleep(1000);

}

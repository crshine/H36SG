// DlgPaymentParkFee11.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\setting.h"
#include "..\CmdOtp.h"
#include "DlgInput.h"
#include "dlgpaymentparkfee11.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentParkFee1 dialog


CDlgPaymentParkFee1::CDlgPaymentParkFee1(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentParkFee1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentParkFee1)
	m_Amount = "";
	m_Cash = "";
	m_Change = "";
	m_Octopus = "";
	m_OctopusRemain = "";
	m_StoreValue = "";
	m_StoreValueRemain = "";
	m_Unpaid = "";
	//}}AFX_DATA_INIT
}

CDlgPaymentParkFee1::~CDlgPaymentParkFee1()
{
//	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
//	pCmdOtp->Kill_Async_Poll();
}

void CDlgPaymentParkFee1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentParkFee1)
	DDX_Text(pDX, AMOUNT, m_Amount);
	DDX_Text(pDX, CASH, m_Cash);
	DDX_Text(pDX, CHANGE, m_Change);
	DDX_Text(pDX, OCTOPUS, m_Octopus);
	DDX_Text(pDX, OCTOPUS_REMAIN, m_OctopusRemain);
	DDX_Text(pDX, STOREVALUE, m_StoreValue);
	DDX_Text(pDX, STOREVALUE_REMAIN, m_StoreValueRemain);
	DDX_Text(pDX, UNPAID, m_Unpaid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentParkFee1, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentParkFee1)
	ON_EN_UPDATE(CASH, OnUpdateCASH)
	ON_EN_KILLFOCUS(CASH, OnKillfocusCASH)
	ON_BN_CLICKED(PRINT_RECEIPT, OnReceipt)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentParkFee1 message handlers

BOOL CDlgPaymentParkFee1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	this->CenterWindow();
	if (_Amount < 0.009) _bForbiddenOtp = true;
	if (!CCmdOtp::Instance()->IsConnection()) _bForbiddenOtp = true;

	if (_bForbiddenOtp) {
		//GetDlgItem(ID_WAIT_OTP_POLL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ENABLEOTP)->ShowWindow(SW_HIDE);
	}else 
	{
		CCmdOtp::Instance()->OTP_DisplayBeforeDeduct(_Amount);
		showTip("請拍八達通卡或以現金付款...");
//		showTip("Present Octopus Card for Automatic Deduction OR Pay by Cash...");
		SetTimer(1, 1000, 0);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentParkFee1::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//党蜊趼极
	GetDlgItem(AMOUNT)->SetFont(&pSetting->FontBig());
	GetDlgItem(CASH)->SetFont(&pSetting->FontBig());
	GetDlgItem(OCTOPUS)->SetFont(&pSetting->FontBig());
	GetDlgItem(STOREVALUE)->SetFont(&pSetting->FontBig());
	GetDlgItem(UNPAID)->SetFont(&pSetting->FontMid());
	GetDlgItem(CHANGE)->SetFont(&pSetting->FontMid());
	GetDlgItem(OCTOPUS_REMAIN)->SetFont(&pSetting->FontMid());
	GetDlgItem(STOREVALUE_REMAIN)->SetFont(&pSetting->FontMid());

	//岆瘁湖荂楷き
	if (_PrintReceipt) ((CButton * )GetDlgItem(PRINT_RECEIPT))->SetCheck(1);
	else ((CButton * )GetDlgItem(PRINT_RECEIPT))->SetCheck(0);

//	_Octopus_CardNo.Empty(); 
	SetDlgItemText(IDC_STOREVALUE_CARDNO, _StoreValue_CardNo);
	SetDlgItemText(IDC_OTP_CARDNO, _Octopus_CardNo);
	SetDlgItemText(CARDNO, _Octopus_CardNo);

	_OctopusRemain = _Octopus = _StoreValueRemain = _StoreValue = 0.0;
	_Cash = _Amount;
	_Change = (_Cash - _Amount + _Octopus + _StoreValue);	//梑錨 = 0
	_Unpaid = (_Amount - _Cash - _Octopus - _StoreValue);	//帤葆 = 0

	//党蜊怀�踸藰�
	m_Amount = show( _Amount );
	m_Cash = show( _Cash );
	m_Change = show( _Change );
	m_Octopus = show( _Octopus );
	m_OctopusRemain = show( _OctopusRemain);
	m_StoreValue = show( _StoreValue );
	m_StoreValueRemain = show( _StoreValueRemain );
	m_Unpaid = show( _Octopus_CardNo);
	
	UpdateData(false);

}

void CDlgPaymentParkFee1::OnUpdateCASH() 
{
	//蜊曹腔婦嬤(_Cash, _Unpaid, _Change)
	UpdateData(true);
	CString s = m_Cash;
	s.Replace('$',' ');
	_Cash = atof( s );

	_Change = _Cash - (_Amount - _Octopus);
    _Unpaid = _Amount - _Cash  - _Octopus - _StoreValue;

	m_Change = show( _Change );
	m_Unpaid = show( _Unpaid );
	UpdateData(false);
}

void CDlgPaymentParkFee1::OnKillfocusCASH() 
{
	m_Cash = show(_Cash);
	UpdateData(false);
}


void CDlgPaymentParkFee1::OnOK() 
{
	KillTimer(1);
	if ("0" != show(_Cash).Right(1))
	{
		::AfxMessageBox("現金輸入不正確!\n系統只支持小數點後一位數", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("現金輸入不正確! 系統只支持小數點後一位數",true);
		GetDlgItem(CASH)->SetFocus();
		SetTimer(1, 1000, 0);
		return;
	}
	if (_Unpaid > 0.0001)
	{
		::AfxMessageBox("現金付費不足!", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("現金付費不足!",true);
		GetDlgItem(CASH)->SetFocus();
		SetTimer(1, 1000, 0);
		return;
	}

	_OctopusRemain = _Octopus = _StoreValueRemain = _StoreValue = 0.0;
	CDialog::OnOK();
}

//岆瘁湖荂楷き
void CDlgPaymentParkFee1::OnReceipt() 
{
	if ( 0 == ((CButton * )GetDlgItem(PRINT_RECEIPT))->GetCheck()) _PrintReceipt = false;
	else _PrintReceipt = true;
}

void CDlgPaymentParkFee1::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(1);
	CDialog::OnCancel();
}

void CDlgPaymentParkFee1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);

	_OctopusRemain = 0.0;
	_Octopus_CardNo = "";
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	
	if (!pCmdOtp->OTP_Poll(CardInfo))
	{
		if (pCmdOtp->GetLastError() != 32) 
		{
			CString dsp;
			dsp.Format("發現錯誤 : [%s]" , pCmdOtp->Translate());
//			::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
//TA11A ken20090817
			if (pCmdOtp->GetLastError() != 22)
				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
			showTip(dsp, true);
			pCmdOtp->WaitForOtpRemove();
		}
		SetTimer(1, 1000, 0);
		return;
	}
	else
	{
		if (!this) return;
		/*
		double x = CardInfo._AvailableAmount;
		x = CardInfo._Remain + 35 + x;
		if (x < _Amount) 
		{
			showTip("八達通卡餘額不足,請換卡重試或使用現金付款!", true);
			pCmdOtp->WaitForOtpRemove();
			SetTimer(1, 1000, 0);
			return;
		}
		*/
		_Octopus = _Amount;
		_Octopus_CardNo = CardInfo._CardNo;
		if (!pCmdOtp->OTP_Deduct(_Octopus, _OctopusRemain, 
							CSetting::Instance()->m_Account.GetReceiptNo(), 0, _Octopus_CardNo))
		{
			CString dsp;
			dsp.Format("發現錯誤[%s], 請換卡重試!", pCmdOtp->Translate());
//TA11A 2009
if(pCmdOtp->GetLastError()!=22)
			::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
			showTip(dsp, true);
			pCmdOtp->WaitForOtpRemove();
			SetTimer(1, 1000, 0);
			_Octopus = 0;
			return;
		}
		else
		{
			_Cash = 0;
			_Change = 0;	//梑錨 = 0
			_Unpaid = 0;	//帤葆 = 0
		}
		pCmdOtp->WaitForOtpRemove();

		CDialog::OnOK();
	}
	SetTimer(1, 1000, 0);
	CDialog::OnTimer(nIDEvent);
}


/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentParkFee11 message handlers

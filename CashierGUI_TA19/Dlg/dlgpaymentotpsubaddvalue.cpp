// dlgpaymentotpsubaddvalue.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdOtp.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentotpsubaddvalue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPSubAddvalue dialog
double CDlgPaymentOTPSubAddvalue::_Amount = 0.0;
double CDlgPaymentOTPSubAddvalue::_OctopusRemain = 0.0;
CString CDlgPaymentOTPSubAddvalue::_OctopusCardNo = "";
CDlgPaymentOTPSubAddvalue * CDlgPaymentOTPSubAddvalue::pThis = NULL;

CDlgPaymentOTPSubAddvalue::CDlgPaymentOTPSubAddvalue(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentOTPSubAddvalue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentOTPSubAddvalue)
	m_Amount = _T("");
	m_OctopusCardNo = _T("");
	m_OctopusRemain = _T("");
	//}}AFX_DATA_INIT
	pThis = this;
}

CDlgPaymentOTPSubAddvalue::~CDlgPaymentOTPSubAddvalue()
{
	pThis = NULL;
}

void CDlgPaymentOTPSubAddvalue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentOTPSubAddvalue)
	DDX_Text(pDX, AMOUNT, m_Amount);
	DDX_Text(pDX, OCTOPUS_CARDNO, m_OctopusCardNo);
	DDX_Text(pDX, OCTOPUS_REMAIN, m_OctopusRemain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentOTPSubAddvalue, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentOTPSubAddvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPSubAddvalue message handlers

void CDlgPaymentOTPSubAddvalue::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//修改字体
	GetDlgItem(OCTOPUS_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(AMOUNT)->SetFont(&pSetting->FontBig());
	GetDlgItem(OCTOPUS_CARDNO)->SetFont(&pSetting->FontBig());

	//修改输入框值
	m_Amount = show( _Amount );
	m_OctopusRemain = show( _OctopusRemain );
	m_OctopusCardNo = show( _OctopusCardNo );
	UpdateData(false);

	//创建检测八达通卡的线程

}

void CDlgPaymentOTPSubAddvalue::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(false);
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
//	if (!pCmdOtp->OTP_AddValue(_OctopusCardNo, _Amount)) 
	{	//充值失败
//TA11A ken20090817
//		AfxMessageBox(pCmdOtp->Translate());
		GetDlgItem(IDOK)->EnableWindow(true);
//		OtpErrProcess();
		return;
	}
//	else
	{
		showTip( (LPCTSTR)TIP_SUCCESSFUL_ADDVALUE );
	}	

	CDialog::OnOK();
}

BOOL CDlgPaymentOTPSubAddvalue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

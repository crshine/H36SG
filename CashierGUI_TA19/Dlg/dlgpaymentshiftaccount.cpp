// dlgpaymentshiftaccount.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgpaymentshiftaccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentShiftAccount dialog
double CDlgPaymentShiftAccount::_CashRemain = 0;			//现金余额
double CDlgPaymentShiftAccount::_StoreValueRemain = 0;		//储值余额
double CDlgPaymentShiftAccount::_OctopusRemain = 0;			//八达通余额
double CDlgPaymentShiftAccount::_CashKeepRemain = 0;
long         CDlgPaymentShiftAccount::_PayNum = 0;
CString CDlgPaymentShiftAccount::_Operator = "";
COleDateTime CDlgPaymentShiftAccount::_DutyStart;

CDlgPaymentShiftAccount::CDlgPaymentShiftAccount(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentShiftAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentShiftAccount)
	m_AmountRemain = _T("");
	m_CashRemain = _T("");
	m_OctopusRemain = _T("");
	m_StoreValueRemain = _T("");
	m_Operator = _T("");
	m_DutyTime = _T("");
	m_lPayNum = 0;
	m_CashKeepRemain = _T("");
	m_ShiftCashMaintain = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPaymentShiftAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentShiftAccount)
	DDX_Text(pDX, AMOUNT_REMAIN, m_AmountRemain);
	DDX_Text(pDX, CASH_REMAIN, m_CashRemain);
	DDX_Text(pDX, OCTOPUS_REMAIN, m_OctopusRemain);
	DDX_Text(pDX, STOREVALUE_REMAIN, m_StoreValueRemain);
	DDX_Text(pDX, IDC_EDIT1, m_Operator);
	DDX_Text(pDX, IDC_EDIT2, m_DutyTime);
	DDX_Text(pDX, IDC_EDIT3, m_lPayNum);
	DDX_Text(pDX, CASHKEEP_REMAIN, m_CashKeepRemain);
	DDX_Text(pDX, SHIFT_CASHMAINTAIN, m_ShiftCashMaintain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentShiftAccount, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentShiftAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentShiftAccount message handlers

void CDlgPaymentShiftAccount::OnOK() 
{
	GetDlgItemText(SHIFT_CASHMAINTAIN, m_ShiftCashMaintain);
	CDialog::OnOK();
}

void CDlgPaymentShiftAccount::InitControl()
{
	//修改字体
	CSetting * pSetting = CSetting::Instance();
	GetDlgItem(AMOUNT_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(CASH_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(OCTOPUS_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(STOREVALUE_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(CASHKEEP_REMAIN)->SetFont(&pSetting->FontBig()); // [BW] 20051105
	GetDlgItem(SHIFT_CASHMAINTAIN)->SetFont(&pSetting->FontBig());
	double AmountRemain = _CashRemain + _StoreValueRemain + _OctopusRemain;// - Amount;

	m_AmountRemain	= show( AmountRemain );
	m_CashRemain	= show( _CashRemain);
	m_OctopusRemain	= show( _OctopusRemain);
	m_StoreValueRemain	= show( _StoreValueRemain);
	m_CashKeepRemain = show( _CashKeepRemain);
	m_ShiftCashMaintain = m_CashKeepRemain;
	m_Operator = _Operator;
	m_lPayNum = _PayNum;
	m_DutyTime.Format("%s - %s", _DutyStart.Format("%H:%M %d %b"), COleDateTime::GetCurrentTime().Format("%H:%M %d %b"));
	UpdateData(false);

	//让无意义输入框只读
}

BOOL CDlgPaymentShiftAccount::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	return TRUE;
}

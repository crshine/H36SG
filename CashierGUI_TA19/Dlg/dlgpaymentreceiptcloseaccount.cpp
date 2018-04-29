// dlgpaymentreceiptcloseaccount.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DlgInput.h"
#include "dlgpaymentreceiptcloseaccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptCloseAccount dialog


CDlgPaymentReceiptCloseAccount::CDlgPaymentReceiptCloseAccount(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentReceiptCloseAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentReceiptCloseAccount)
	m_Balance = _T("");
	m_LoginTime = _T("");
	m_LogoutTime = _T("");
	m_OldBalance = _T("");
	m_Operater = _T("");
	m_ReceiptNo = _T("");
	m_WithDrawal = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPaymentReceiptCloseAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentReceiptCloseAccount)
	DDX_Text(pDX, IDC_BALANCE, m_Balance);
	DDX_Text(pDX, IDC_LOGINTIME, m_LoginTime);
	DDX_Text(pDX, IDC_LOGOUTTIME, m_LogoutTime);
	DDX_Text(pDX, IDC_OLDBALANCE, m_OldBalance);
	DDX_Text(pDX, IDC_OPERATER, m_Operater);
	DDX_Text(pDX, IDC_RECEIPTNO, m_ReceiptNo);
	DDX_Text(pDX, IDC_WITHDRAWAL, m_WithDrawal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentReceiptCloseAccount, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentReceiptCloseAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptCloseAccount message handlers

void CDlgPaymentReceiptCloseAccount::OnOK() 
{
	/*	使用以下字符串值打印凭据.
		CString	m_Balance;
		CString	m_Data;
		CString	m_OldBalance;
		CString	m_Operater;
		CString	m_ReceiptNo;
		CString	m_LoginTime;
		CString	m_LogoutTime;
		CString	m_WithDrawal;
		if (NULL != g_pReceiptPrn)
			g_pReceiptPrn->PrintShiftAccountReceipt();
	*/
	CDialog::OnOK();
}

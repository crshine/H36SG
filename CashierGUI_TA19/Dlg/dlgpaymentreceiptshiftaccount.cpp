// dlgpaymentreceiptshiftaccount.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdPrint.h"
#include "dlgpaymentreceiptshiftaccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _System		g_System;

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptShiftAccount dialog
double CDlgPaymentReceiptShiftAccount::_Balance = 0.0;
double CDlgPaymentReceiptShiftAccount::_Cash = 0.0;
double CDlgPaymentReceiptShiftAccount::_Octupos = 0.0;
double CDlgPaymentReceiptShiftAccount::_StoreValue = 0.0;
COleDateTime CDlgPaymentReceiptShiftAccount::_ActionTime;
CString CDlgPaymentReceiptShiftAccount::_ReceiptNo = "";

CDlgPaymentReceiptShiftAccount::CDlgPaymentReceiptShiftAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaymentReceiptShiftAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentReceiptShiftAccount)
	//}}AFX_DATA_INIT
}


void CDlgPaymentReceiptShiftAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentReceiptShiftAccount)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentReceiptShiftAccount, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentReceiptShiftAccount)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceiptShiftAccount message handlers

void CDlgPaymentReceiptShiftAccount::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(false);
	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
//	pCmdPrint->PrintShiftAccount();
	/*	使用以下字符串值打印凭据.
		CString	m_Balance;
		CString	m_Data;
		CString	m_OldBalance;
		CString	m_Operater;
		CString	m_ReceiptNo;
		CString	m_Time;
		CString	m_WithDrawal;
	*/
	CDialog::OnOK();
}

BOOL CDlgPaymentReceiptShiftAccount::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentReceiptShiftAccount::InitControl()
{
	const CString title_Operater	= "Operater :\t";
	const CString title_OldBalance	= "Old Balance :\t";
	const CString title_Balance		= "Balance :\t";
	const CString title_Cash		= "Cash:\t\t";
	const CString title_Octupos		= "Octupos:\t";
	const CString title_StoreValue	= "Store Value:\t";
	const CString title_Total		= "Total:\t\t";
	const CString title_Date		= "Date :\t\t";
	const CString title_Time		= "Time :\t\t";
	const CString title_ReceiptNo	= "Receipt No. : \t";

	double Total = _Cash + _Octupos + _StoreValue;
	double OldBalance = _Balance + Total;

	SetDlgItemText( OPERATER,	title_Operater		+ show(g_System.Operator.CurUserName) );
	SetDlgItemText( OLDBALANCE, title_OldBalance	+ show(OldBalance) );
	SetDlgItemText( BALANCE,	title_Balance		+ show(_Balance) );
	SetDlgItemText( CASH,		title_Cash			+ show(_Cash) );
	SetDlgItemText( OCTUPOS,	title_Octupos		+ show(_Octupos) );
	SetDlgItemText( STOREVALUE, title_StoreValue	+ show(_StoreValue) );
	SetDlgItemText( TOTAL,		title_Total			+ show(Total) );
	SetDlgItemText( DATE,		title_Date			+ showDate(_ActionTime) );
	SetDlgItemText( TIME,		title_Time			+ showHHMMSS(_ActionTime) );
	SetDlgItemText( RECEIPTNO,	title_ReceiptNo		+ show(_ReceiptNo) );
}
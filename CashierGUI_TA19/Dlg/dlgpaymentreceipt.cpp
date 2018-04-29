// dlgpaymentreceipt.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "..\CmdPrint.h"
#include "dlgpaymentreceipt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceipt dialog
CString CDlgPaymentReceipt::_ReceiptNo = "--------";

CDlgPaymentReceipt::CDlgPaymentReceipt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaymentReceipt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentReceipt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPaymentReceipt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentReceipt)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentReceipt, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentReceipt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentReceipt message handlers

BOOL CDlgPaymentReceipt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentReceipt::InitControl()
{
	CSetting * pSetting = CSetting::Instance();

	SetDlgItemText(IDC_TITLE1, pSetting->m_Receipt.Title1());
	SetDlgItemText(IDC_TITLE2, pSetting->m_Receipt.Title1());
	SetDlgItemText(IDC_TITLE3, pSetting->m_Receipt.Title1());

	SetDlgItemText(RECEIPTNO, _ReceiptNo);
	
	SetDlgItemText(IDC_TAX_NAME, pSetting->m_Receipt.TaxName());
	SetDlgItemText(IDC_TAX_REG_NO, pSetting->m_Receipt.TaxRegNo());
	SetDlgItemText(IDC_TAX_PECENTAGE_RATE, showPercentage(pSetting->m_Receipt.TaxPercentageRate()));

	SetDlgItemText(IDC_END1, pSetting->m_Receipt.Ending1());
	SetDlgItemText(IDC_END2, pSetting->m_Receipt.Ending2());
}

void CDlgPaymentReceipt::OnOK() 
{
	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
//	ASSERT(1!=1);
/*
	pCmdPrint->PrintParkingReceipt(0L, (char *)&g_System.CurPayment.CAN, 
							(char *)&g_System.CurPayment.CAN, false, 
							(char *)&CardCategory, g_System.CurPayment.timeEntry, 
							"", g_System.CurPayment.dParkingAmount, 0L, 0L, 0L);
*/
	CDialog::OnOK();
}

void CDlgPaymentReceipt::OnCancel() 
{
	if ( IDYES==MessageBox(	(CString)(LPCTSTR)SYS_MSG_CANCEL_OPERATE,
							(CString)(LPCTSTR)SYS_MSG_WARNING,
							MB_YESNO| MB_ICONWARNING  ) )
	{
		CDialog::OnCancel();
	}
}

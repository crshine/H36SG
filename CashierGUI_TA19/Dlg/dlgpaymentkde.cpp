// dlgpaymentkde.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgpaymentkde.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDE dialog


CDlgPaymentKDE::CDlgPaymentKDE(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaymentKDE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentKDE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPaymentKDE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentKDE)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentKDE, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentKDE)
	ON_BN_CLICKED(ID_PAY, OnPay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDE message handlers

void CDlgPaymentKDE::OnPay() 
{
	
}

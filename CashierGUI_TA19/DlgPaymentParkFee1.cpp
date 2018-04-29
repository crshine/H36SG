// DlgPaymentParkFee1.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "DlgPaymentParkFee1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgPaymentParkFee1 dialog


DlgPaymentParkFee1::DlgPaymentParkFee1(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPaymentParkFee1::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPaymentParkFee1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgPaymentParkFee1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPaymentParkFee1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPaymentParkFee1, CDialog)
	//{{AFX_MSG_MAP(DlgPaymentParkFee1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgPaymentParkFee1 message handlers

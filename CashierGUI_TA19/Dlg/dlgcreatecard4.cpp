// dlgcreatecard4.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgcreatecard4.h"
#include "dlgcreatecard.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard4 property page

IMPLEMENT_DYNCREATE(CDlgCreateCard4, CPropertyPage)

CDlgCreateCard4::CDlgCreateCard4()
{
	//{{AFX_DATA_INIT(CDlgCreateCard4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCreateCard4::~CDlgCreateCard4()
{
}

void CDlgCreateCard4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateCard4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateCard4, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateCard4)
	ON_WM_DESTROY()   
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard4 message handlers
void CDlgCreateCard4::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//修改字体
	GetDlgItem(PERIOD_AMOUNT)->SetFont(&pSetting->FontMid());
	GetDlgItem(TRANSACTION_AMOUNT)->SetFont(&pSetting->FontMid());
	GetDlgItem(JOINING_FEE)->SetFont(&pSetting->FontMid());
	GetDlgItem(CARD_FEE)->SetFont(&pSetting->FontMid());
	GetDlgItem(TOTAL)->SetFont(&pSetting->FontMid());
	GetDlgItem(STORE_VALUE)->SetFont(&pSetting->FontMid());
	double _Amount = ((CDlgCreateCard *)m_pDlg)->Calculate();	//所有用户需要选择的都已选择，可以计算了。
	short ID = ((CDlgCreateCard *)m_pDlg)->_CardTypeId;

	if ( pSetting->m_CardType.IsPeriodWorkMode(ID) )
	{
		SetDlgItemText( PERIOD, showDate(((CDlgCreateCard *)m_pDlg)->_ValidFrom) + "  -->  " + showDate(((CDlgCreateCard *)m_pDlg)->_ValidTo));
		SetDlgItemText( PERIOD_PRICE, pSetting->m_CardType.showPrice(ID) );
	}
	else
	{
		SetDlgItemText( PERIOD, "--- --,--  -->  --- --,--");
		SetDlgItemText( PERIOD_PRICE, "----");
	}
	SetDlgItemText( PERIOD_AMOUNT, show(((CDlgCreateCard *)m_pDlg)->_PeriodFee));

	if ( pSetting->m_CardType.IsTimesWorkMode(ID) )
	{
		SetDlgItemText( TRANSACTION, show(((CDlgCreateCard *)m_pDlg)->_ValidTranTimes) );
		SetDlgItemText( TRANSACTION_PRICE, pSetting->m_CardType.showPrice(ID) );
	}
	else
	{
		SetDlgItemText( TRANSACTION, "----");
		SetDlgItemText( TRANSACTION_PRICE, "----");
	}
	SetDlgItemText( TRANSACTION_AMOUNT, show(((CDlgCreateCard *)m_pDlg)->_TransactionFee));

	SetDlgItemText( JOINING_FEE, show(((CDlgCreateCard *)m_pDlg)->_JoiningFee) );
	SetDlgItemText( CARD_FEE, show(((CDlgCreateCard *)m_pDlg)->_CardFee) );
	SetDlgItemText( STORE_VALUE, show(((CDlgCreateCard *)m_pDlg)->_StoreValueFee) );
	SetDlgItemText( TOTAL, show(_Amount) );
}

BOOL CDlgCreateCard4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitControl();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgCreateCard4::CheckInput()
{
	return true;
}

void CDlgCreateCard4::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
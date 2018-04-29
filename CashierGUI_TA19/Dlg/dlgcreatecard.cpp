// dlgcreatecard.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgCreateCard1.h"
#include "DlgCreateCard2.h"
#include "DlgCreateCard3.h"
#include "DlgCreateCard4.h"
#include "dlgcreatecard.h"
#include "..\cmdotp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard dialog


CDlgCreateCard::CDlgCreateCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateCard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCreateCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateCard)
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_NEXT);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_BACK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateCard, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateCard)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard message handlers

void CDlgCreateCard::OnButtonBack() 
{
	ASSERT( m_CurrentStep != 1 );
	--m_CurrentStep;
	ShowStep();
}

void CDlgCreateCard::OnButtonNext() 
{
	if	(1 == m_CurrentStep)
	{
		if ( !static_cast<CDlgCreateCard1 *>(m_pDlg)->CheckInput() ) return;
	}
	else if (2 == m_CurrentStep)
	{
		if ( !static_cast<CDlgCreateCard2 *>(m_pDlg)->CheckInput() ) return;
	}
	/*else if (3 == m_CurrentStep)
	{
		if ( !static_cast<CDlgCreateCard4 *>(m_pDlg)->CheckInput() ) return;
	}*/
	else//	(4 == m_CurrentStep)
	{
		if ( !static_cast<CDlgCreateCard4 *>(m_pDlg)->CheckInput() ) return;
	}

	++m_CurrentStep;
	if (4 == m_CurrentStep) OnOK();
	ShowStep();
}

double CDlgCreateCard::Calculate()
{//.跟据用户的输入,计算相应的费用
	CSetting * pSetting = CSetting::Instance();
	
	_PeriodFee		= pSetting->m_CardType.PeriodFee(_CardTypeId, _ValidFrom, _ValidTo);
	_TransactionFee	= pSetting->m_CardType.TimesFee(_CardTypeId, _ValidTranTimes);
	_JoiningFee		= pSetting->m_CardType.JoiningFee(_CardTypeId);
	_CardFee		= pSetting->m_CardType.CardFee(_CardTypeId); 
	
	return _PeriodFee + _TransactionFee + _JoiningFee + _CardFee + _StoreValueFee;
}


void CDlgCreateCard::OnCancel() 
{
	if (!_CardNo.IsEmpty())
		CCmdOtp::Instance()->WaitForOtpRemove(true);
	CDialog::OnCancel();
}

BOOL CDlgCreateCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_CurrentStep = 1;	//mean step one;
	m_pDlg = NULL;
	ShowStep();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateCard::ShowStep()
{
	const CString Caption1 = "Create special card - step 1";
	const CString Caption2 = "Create special card - step 2";
	const CString Caption3 = "Create special card - step 3";
	const CString Caption4 = "Create special card - step 4";

	if (m_pDlg != NULL)
	{
		m_pDlg->DestroyWindow();
		delete m_pDlg;
		m_pDlg = NULL;
	}

	if	(2 == m_CurrentStep)
	{
		m_pDlg = new CDlgCreateCard2;
		((CDlgCreateCard2 *)m_pDlg)->SetParentDlg(this);
		m_pDlg->Create(CDlgCreateCard2::IDD,this);
		SetWindowText(Caption2);
		m_BACK.EnableWindow(true);
	}
	else if (3 == m_CurrentStep)
	{
		m_pDlg = new CDlgCreateCard4;
		((CDlgCreateCard4 *)m_pDlg)->SetParentDlg(this);
		m_pDlg->Create(CDlgCreateCard4::IDD,this);
		SetWindowText(Caption3);
	}
	/*else if (4 == m_CurrentStep)
	{
		m_pDlg = new CDlgCreateCard4;
		m_pDlg->Create(CDlgCreateCard4::IDD,this);
		SetWindowText(Caption4);
	}*/
	else//	(1 == m_CurrentStep)
	{
		m_pDlg = new CDlgCreateCard1;
		((CDlgCreateCard1 *)m_pDlg)->SetParentDlg(this);
		m_pDlg->Create(CDlgCreateCard1::IDD,this);
		SetWindowText(Caption1);
		m_BACK.EnableWindow(false);
	}
	m_pDlg->ShowWindow(SW_SHOW);
}

CDlgCreateCard::~CDlgCreateCard()
{
	if (m_pDlg != NULL)
	{
		m_pDlg->DestroyWindow();
		delete m_pDlg;
		m_pDlg = NULL;
	}
}
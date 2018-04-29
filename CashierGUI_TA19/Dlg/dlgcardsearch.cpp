// dlgcardsearch.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdMntSend.h"
#include "dlgcardsearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCardSearch dialog


CDlgCardSearch::CDlgCardSearch(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgCardSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCardSearch)
	m_CardNo = _T("");
	m_CardType = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCardSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCardSearch)
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Text(pDX, IDC_CARD_NO, m_CardNo);
	DDX_CBString(pDX, IDC_CARD_TYPE, m_CardType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCardSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgCardSearch)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCardSearch message handlers

void CDlgCardSearch::OnSearch() 
{
	AfxGetApp()->BeginWaitCursor();
	GetDlgItem(IDC_SEARCH)->EnableWindow(FALSE);

	UpdateData(true);
	CCmdMntSend::_STRUCT_CardStatus CardStatus;
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	if (pCmd->QueryCardStatus(m_CardType.Left(1) + m_CardNo.Left(16), CardStatus))
	{
		m_Description.SetWindowText(CardStatus.GetDescription());
	}
	else
	{
		m_Description.SetWindowText("No response or Error response.");
	}

	GetDlgItem(IDC_SEARCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEARCH)->SetFocus();
}

BOOL CDlgCardSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	static_cast<CComboBox *>(GetDlgItem(IDC_CARD_TYPE))->SetCurSel(0);
	GetDlgItem(IDC_CARD_TYPE)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

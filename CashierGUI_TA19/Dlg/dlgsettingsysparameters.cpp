// dlgsettingsysparameters.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\setting.h"
#include "dlgsettingsysparameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingSysParameters dialog


CDlgSettingSysParameters::CDlgSettingSysParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingSysParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingSysParameters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingSysParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingSysParameters)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingSysParameters, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingSysParameters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingSysParameters message handlers

BOOL CDlgSettingSysParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 190);
	m_list.InsertColumn(1, LoadS(IDS_STRING_DESCRIP), LVCFMT_LEFT, 350);

	Show();//显示内容	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//显示内容	
void CDlgSettingSysParameters::Show()
{
	CSetting::CBaseSystemSetting BaseSystemSetting = CSetting::Instance()->m_BaseSystemSetting;

	int Index = 0;
	m_list.DeleteAllItems();

	m_list.InsertItem(Index, "System Name");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.SystemName()));

	m_list.InsertItem(Index, "System ID");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.SystemID()));

	m_list.InsertItem(Index, "Auto Function Time");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.AutoFunctionTime().Description()));

	m_list.InsertItem(Index, "Card Category AntiPassback");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.CardCateAntiPassback()));

	m_list.InsertItem(Index, "Operator Language");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.OperatorLanguage()));

	m_list.InsertItem(Index, "Customer Language");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.CustomerLanguage()));

	m_list.InsertItem(Index, "Entry Or Exit");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.EntryOrExit()));

	m_list.InsertItem(Index, "LowestYN");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.LowestYN()));

	m_list.InsertItem(Index, "Cash Card Mode ID");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.CashCardModeID()));

	m_list.InsertItem(Index, "Cash Back Mode ID");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.CashBackModeID()));

	m_list.InsertItem(Index, "Store Value Mode ID");
	m_list.SetItemText(Index++, 1, show(BaseSystemSetting.StoreValueModeID()));
}

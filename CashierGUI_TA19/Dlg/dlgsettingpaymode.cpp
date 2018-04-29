// DlgSettingPaymode.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DlgSettingPaymode.h"
#include "..\setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPaymode dialog


CDlgSettingPaymode::CDlgSettingPaymode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingPaymode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingPaymode)
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSettingPaymode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingPaymode)
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingPaymode, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingPaymode)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPaymode message handlers

BOOL CDlgSettingPaymode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ShowTheRule();
	return TRUE;
}

void CDlgSettingPaymode::ShowTheRule()
{
	SetDlgItemText(MODECASHCARD, g_Setting->m_PayModeDefinition.ModeName(g_Setting->m_BaseSystemSetting.CashCardModeID()) );
	SetDlgItemText(MODECASHBACK, g_Setting->m_PayModeDefinition.ModeName(g_Setting->m_BaseSystemSetting.CashBackModeID()) );
	SetDlgItemText(MODESTROEVALUE, g_Setting->m_PayModeDefinition.ModeName(g_Setting->m_BaseSystemSetting.StoreValueModeID()) );
	// cashcard   -> Cash payment
	// cashback   -> Octopus 
	// StoreValue -> Store Value
	m_Check1 = g_Setting->m_PayModeDefinition.NeedCashChanges(g_Setting->m_BaseSystemSetting.CashCardModeID());
	m_Check2 = g_Setting->m_PayModeDefinition.NeedCashChanges(g_Setting->m_BaseSystemSetting.CashBackModeID());
	m_Check3 = g_Setting->m_PayModeDefinition.NeedCashChanges(g_Setting->m_BaseSystemSetting.StoreValueModeID());
	UpdateData(FALSE);
}

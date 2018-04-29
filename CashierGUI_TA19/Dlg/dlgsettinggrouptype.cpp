// dlgsettinggrouptype.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgsettinggrouptype.h"
#include "..\Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGroupType dialog


CDlgSettingGroupType::CDlgSettingGroupType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingGroupType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingGroupType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingGroupType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingGroupType)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingGroupType, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingGroupType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGroupType message handlers

BOOL CDlgSettingGroupType::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_PLOTS), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, LoadS(IDS_STRING_DESCRIP), LVCFMT_LEFT, 380);

	ShowTheRule();//ÏÔÊ¾ÄÚÈÝ	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CDlgSettingGroupType::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_GroupType.m_Map
#define __iter pSetting->m_GroupType.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._Lots));
		m_list.SetItemText(nCount, 2, __iter->second._Description);
		nCount ++;
	}
#undef __iter
#undef __map
}

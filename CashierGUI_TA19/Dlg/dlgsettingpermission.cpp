// dlgsettingpermission.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\setting.h"
#include "dlgsettingpermission.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPermission dialog


CDlgSettingPermission::CDlgSettingPermission(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingPermission::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingPermission)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingPermission::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingPermission)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingPermission, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingPermission)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPermission message handlers

void CDlgSettingPermission::Show()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_Permission.m_Map
#define __iter pSetting->m_Permission.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._Caption));
		m_list.SetItemText(nCount, 2, showStationTypeName(__iter->second._StationType));
		m_list.SetItemText(nCount, 3, show(__iter->second._ValidForGuest));
		m_list.SetItemText(nCount, 4, show(__iter->second._ValidForOperator));
		m_list.SetItemText(nCount, 5, show(__iter->second._ValidForSupervisor));
		m_list.SetItemText(nCount, 6, show(__iter->second._ValidForManager));
		m_list.SetItemText(nCount, 7, show(__iter->second._ValidForAdmin));
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgSettingPermission::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, LoadS(IDS_STRING_STNTYPE), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, LoadS(IDS_STRING_GUEST), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, LoadS(IDS_STRING_OPTRLVL), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, LoadS(IDS_STRING_SUPR), LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, LoadS(IDS_STRING_MGR), LVCFMT_LEFT, 100);
	m_list.InsertColumn(7, LoadS(IDS_STRING_ADMIN), LVCFMT_LEFT, 100);

	Show();//œ‘ æƒ⁄»›	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

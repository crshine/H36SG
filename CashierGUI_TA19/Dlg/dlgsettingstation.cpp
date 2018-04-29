// dlgsettingstation.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgsettingstation.h"
#include "..\setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;
/////////////////////////////////////////////////////////////////////////////
// CDlgSettingStation dialog


CDlgSettingStation::CDlgSettingStation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingStation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingStation)
	//}}AFX_DATA_INIT
}


void CDlgSettingStation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingStation)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingStation, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingStation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingStation message handlers

void CDlgSettingStation::ShowTheRule()
{
#define __map g_Setting->m_StationInformation.m_Map
#define __iter g_Setting->m_StationInformation.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._StationName));
		m_list.SetItemText(nCount, 2, showStationTypeName(__iter->second._StationType));
		m_list.SetItemText(nCount, 3, show(__iter->second._IPAddr));
		m_list.SetItemText(nCount, 4, show(__iter->second._GroupID));
		m_list.SetItemText(nCount, 5, show(__iter->second._Brief));
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgSettingStation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 150);
	m_list.InsertColumn(2, LoadS(IDS_STRING_TYPE), LVCFMT_LEFT, 50);
	m_list.InsertColumn(3, LoadS(IDS_STRING_IPADDR), LVCFMT_LEFT, 150);
	m_list.InsertColumn(4, LoadS(IDS_STRING_GROUPID), LVCFMT_LEFT, 50);
	m_list.InsertColumn(5, LoadS(IDS_STRING_DESCRIP), LVCFMT_LEFT, 150);

	ShowTheRule();//œ‘ æƒ⁄»›
	return TRUE; 
}

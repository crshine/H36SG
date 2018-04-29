// dlgsettingcartype.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgsettingcartype.h"
#include "..\setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCarType dialog


CDlgSettingCarType::CDlgSettingCarType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingCarType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingCarType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingCarType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingCarType)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingCarType, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingCarType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCarType message handlers

BOOL CDlgSettingCarType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_VEHTYPE), LVCFMT_LEFT, 200);

	ShowTheRule();//ÏÔÊ¾ÄÚÈÝ
	return TRUE; 
}

void CDlgSettingCarType::ShowTheRule()
{
#define __map g_Setting->m_VehicleType.m_Map
#define __iter g_Setting->m_VehicleType.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._TypeName));
		nCount ++;
	}
#undef __iter
#undef __map
}

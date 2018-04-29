// DlgSettingDiscountPlan.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DlgSettingDiscountPlan.h"
#include "..\Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingDiscountPlan dialog


CDlgSettingDiscountPlan::CDlgSettingDiscountPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingDiscountPlan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingDiscountPlan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingDiscountPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingDiscountPlan)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingDiscountPlan, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingDiscountPlan)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingDiscountPlan message handlers

void CDlgSettingDiscountPlan::ShowTheRule()
{
#define __map g_Setting->m_DiscountPlan.m_Map
#define __iter g_Setting->m_DiscountPlan.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._DiscountName));
		m_list.SetItemText(nCount, 2, show(__iter->second._Discount));
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgSettingDiscountPlan::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, LoadS(IDS_STRING_DISCOUNT), LVCFMT_LEFT, 200);

	ShowTheRule();//œ‘ æƒ⁄»›	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

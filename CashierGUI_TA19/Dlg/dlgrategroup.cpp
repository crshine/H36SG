// dlgrategroup.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgrategroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateGroup dialog


CDlgRateGroup::CDlgRateGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateGroup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateGroup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateGroup)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateGroup, CDialog)
	//{{AFX_MSG_MAP(CDlgRateGroup)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateGroup message handlers

void CDlgRateGroup::OnButtonRefrash() 
{
	ShowTheRule();
}

void CDlgRateGroup::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_GroupRule.m_Map
#define __iter pSetting->m_GroupRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._CRsIdOfGroupType0) );
		m_list.SetItemText(nCount, 2, show(__iter->second._CRsIdOfGroupType1) );
		m_list.SetItemText(nCount, 3, show(__iter->second._CRsIdOfGroupType2) );
		m_list.SetItemText(nCount, 4, show(__iter->second._CRsIdOfGroupType3) );
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgRateGroup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, LoadS(IDS_STRING_RULEID), LVCFMT_LEFT, 100);
	CString x;
	x.Format("%s%d", LoadS(IDS_STRING_GROUPID),0);
	m_list.InsertColumn(1, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_GROUPID),1);
	m_list.InsertColumn(2, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_GROUPID),2);
	m_list.InsertColumn(3, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_GROUPID),3);
	m_list.InsertColumn(4, x, LVCFMT_LEFT, 110);
	ShowTheRule();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRateGroup::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

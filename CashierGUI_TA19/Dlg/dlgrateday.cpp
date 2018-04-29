// dlgrateday.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgrateday.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateDay dialog

CDlgRateDay::CDlgRateDay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateDay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateDay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateDay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateDay)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateDay, CDialog)
	//{{AFX_MSG_MAP(CDlgRateDay)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateDay message handlers

BOOL CDlgRateDay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, LoadS(IDS_STRING_DATEWEEK), LVCFMT_LEFT, 140);
	m_list.InsertColumn(1, LoadS(IDS_STRING_GROUPID), LVCFMT_LEFT, 140);
	ShowTheRule();//ÏÔÊ¾ÄÚÈÝ
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgRateDay::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_DateRule.m_Map
#define __iter pSetting->m_DateRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		if (COleDateTime::invalid == __iter->second._date.GetStatus())
			m_list.InsertItem(nCount, showDayOfWeek(__iter->second._DayOfWeek) );
		else
			m_list.InsertItem(nCount, showDate(__iter->second._date) );

		m_list.SetItemText(nCount, 1, show(__iter->second._GroupRulesId) );
		nCount ++;
	}
#undef __iter
#undef __map
}

void CDlgRateDay::OnButtonRefrash() 
{
	ShowTheRule();
}

void CDlgRateDay::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//m_list.GetHotItem();
	int index = (int )m_list.GetFirstSelectedItemPosition() - 1;
	if (-1 != index){
		CString dataStr = m_list.GetItemText (index, 1 ) ; 
		//Group fee rules for this or this type of day: 'Group Fee Rules Code ??'.
		CString info;
		info.Format("Group fee rules for this or this type of day: 'Group Fee Rules Code %s'.", dataStr);
		SetDlgItemText(IDC_STATIC1, info);
	}
	*pResult = 0;
}

void CDlgRateDay::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

// dlgratetimezone.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgratetimezone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateTimezone dialog


CDlgRateTimezone::CDlgRateTimezone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateTimezone::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateTimezone)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateTimezone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateTimezone)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateTimezone, CDialog)
	//{{AFX_MSG_MAP(CDlgRateTimezone)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateTimezone message handlers

void CDlgRateTimezone::OnButtonRefrash() 
{
	ShowTheRule();
}

void CDlgRateTimezone::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_TimeZoneRule.m_Map
#define __iter pSetting->m_TimeZoneRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, showHHMM(__iter->second._BegTime1) );
		m_list.SetItemText(nCount, 2, showHHMM(__iter->second._EndTime1) );
		m_list.SetItemText(nCount, 3, show(__iter->second._UnitRulesId1) );
		m_list.SetItemText(nCount, 4, showHHMM(__iter->second._BegTime2) );
		m_list.SetItemText(nCount, 5, showHHMM(__iter->second._EndTime2) );
		m_list.SetItemText(nCount, 6, show(__iter->second._UnitRulesId2) );
		m_list.SetItemText(nCount, 7, showHHMM(__iter->second._BegTime3) );
		m_list.SetItemText(nCount, 8, showHHMM(__iter->second._EndTime3) );
		m_list.SetItemText(nCount, 9, show(__iter->second._UnitRulesId3) );
		m_list.SetItemText(nCount,10, showHHMM(__iter->second._BegTime4) );
		m_list.SetItemText(nCount,11, showHHMM(__iter->second._EndTime4) );
		m_list.SetItemText(nCount,12, show(__iter->second._UnitRulesId4) );
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgRateTimezone::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.InsertColumn(0, LoadS(IDS_STRING_RULEID), LVCFMT_LEFT, 70);
	for (int i=1; 4 >= i; i++)
	{
		CString s;
		s.Format("%d",i);
		m_list.InsertColumn(i+i+i-2, LoadS(IDS_STRING_START)+s, LVCFMT_LEFT, 90);
		m_list.InsertColumn(i+i+i-1, LoadS(IDS_STRING_END)+s, LVCFMT_LEFT, 90);
		m_list.InsertColumn(i+i+i, LoadS(IDS_STRING_FEERULE), LVCFMT_LEFT, 90);
	}
	ShowTheRule();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRateTimezone::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

CString CDlgRateTimezone::showHHMM(short mins)
{
	CString HHMM;
	short hours=0;
	while (mins > 59)
	{
		hours++;
		mins -= 60; 
	}
	HHMM.Format("%2d:%2d", hours, mins);
	return HHMM;
}

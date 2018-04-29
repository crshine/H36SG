// dlgratefix.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgratefix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFix dialog


CDlgRateFix::CDlgRateFix(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateFix::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateFix)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateFix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateFix)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateFix, CDialog)
	//{{AFX_MSG_MAP(CDlgRateFix)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFix message handlers

void CDlgRateFix::OnButtonRefrash() 
{
	ShowTheRule();
}

void CDlgRateFix::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_FixRule.m_Map
#define __iter pSetting->m_FixRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, showHHMM(__iter->second._InZoneStart) );
		m_list.SetItemText(nCount, 2, showHHMM(__iter->second._InZoneEnd) );
		if (COleDateTime::invalid == __iter->second._Indate.GetStatus())
			m_list.SetItemText(nCount, 3, showDayOfWeek(__iter->second._InDayOfWeek) );
		else
			m_list.SetItemText(nCount, 3, showDate(__iter->second._Indate) );
		m_list.SetItemText(nCount, 4, showHHMM(__iter->second._OutZoneStart) );
		m_list.SetItemText(nCount, 5, showHHMM(__iter->second._OutZoneEnd) );
		if (COleDateTime::invalid == __iter->second._Outdate.GetStatus())
			m_list.SetItemText(nCount, 6, showDayOfWeek(__iter->second._OutDayOfWeek) );
		else
			m_list.SetItemText(nCount, 6, showDate(__iter->second._Outdate) );
		m_list.SetItemText(nCount, 7, show(__iter->second._IODayDiff) );
		m_list.SetItemText(nCount, 8, show(__iter->second._Discount) );
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgRateFix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_list.InsertColumn(0, LoadS(IDS_STRING_RULEID), LVCFMT_LEFT, 70);
	m_list.InsertColumn(1, LoadS(IDS_STRING_INZONESTART), LVCFMT_LEFT, 90);
	m_list.InsertColumn(2, LoadS(IDS_STRING_INZONEEND), LVCFMT_LEFT, 90);
	m_list.InsertColumn(3, LoadS(IDS_STRING_INZONEDATE), LVCFMT_LEFT, 90);
	m_list.InsertColumn(4, LoadS(IDS_STRING_OUTZONESTART), LVCFMT_LEFT, 90);
	m_list.InsertColumn(5, LoadS(IDS_STRING_OUTZONESTART), LVCFMT_LEFT, 90);
	m_list.InsertColumn(6, LoadS(IDS_STRING_OUTZONEDATE), LVCFMT_LEFT, 90);
	m_list.InsertColumn(7, LoadS(IDS_STRING_IODAYDIFF), LVCFMT_LEFT,90);
	m_list.InsertColumn(8, LoadS(IDS_STRING_DISCOUNT), LVCFMT_LEFT, 220);
	ShowTheRule();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRateFix::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

CString CDlgRateFix::showHHMM(short min)
{
	CString HHMM;
	short hour=0;
	while (min > 59)
	{
		hour++;
		min -= 60; 
	}
	HHMM.Format("%2d:%2d", hour, min);
	return HHMM;
}

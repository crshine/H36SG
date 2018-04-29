// dlgratefee.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgratefee.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFee dialog


CDlgRateFee::CDlgRateFee(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateFee::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateFee)
	//}}AFX_DATA_INIT
}


void CDlgRateFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateFee)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateFee, CDialog)
	//{{AFX_MSG_MAP(CDlgRateFee)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateFee message handlers

void CDlgRateFee::OnButtonRefrash() 
{
	ShowTheRule();
}

void CDlgRateFee::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_UnitRule.m_Map
#define __iter pSetting->m_UnitRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, __iter->second.Unit(0) );
		m_list.SetItemText(nCount, 2, __iter->second.Charge(0) );
		m_list.SetItemText(nCount, 3, __iter->second.Unit(1) );
		m_list.SetItemText(nCount, 4, __iter->second.Charge(1) );
		m_list.SetItemText(nCount, 5, __iter->second.Unit(2) );
		m_list.SetItemText(nCount, 6, __iter->second.Charge(2) );
		m_list.SetItemText(nCount, 7, __iter->second.Unit(3) );
		m_list.SetItemText(nCount, 8, __iter->second.Charge(3) );
		m_list.SetItemText(nCount, 9, __iter->second.Unit(4) );
		m_list.SetItemText(nCount,10, __iter->second.Charge(4) );
		m_list.SetItemText(nCount,11, __iter->second.Unit(5) );
		m_list.SetItemText(nCount,12, __iter->second.Charge(5) );
		m_list.SetItemText(nCount,13, __iter->second.Unit(6) );
		m_list.SetItemText(nCount,14, __iter->second.Charge(6) );
		m_list.SetItemText(nCount,15, __iter->second.Unit(7) );
		m_list.SetItemText(nCount,16, __iter->second.Charge(7) );
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgRateFee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_RULEID), LVCFMT_LEFT, 70);
	for (int i=1; 8 >= i; i++)
	{
		CString s;
		s.Format("%d",i);
		m_list.InsertColumn(i+i-1, LoadS(IDS_STRING_TIMEUNIT)+s, LVCFMT_LEFT, 90);
		m_list.InsertColumn(i+i, LoadS(IDS_STRING_CHARGE)+s, LVCFMT_LEFT, 90);
	}
	ShowTheRule();//ÏÔÊ¾ÄÚÈÝ
	return TRUE; 
}

void CDlgRateFee::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

CString CDlgRateFee::showHH(short sec)
{
	CString HH;
	double hour = sec / 3600;
	HH.Format("%.2f", hour);
	return HH;
}

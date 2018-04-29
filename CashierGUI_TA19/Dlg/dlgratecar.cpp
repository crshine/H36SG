// dlgratecar.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgratecar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCar dialog


CDlgRateCar::CDlgRateCar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateCar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateCar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateCar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateCar)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateCar, CDialog)
	//{{AFX_MSG_MAP(CDlgRateCar)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCar message handlers

void CDlgRateCar::OnButtonRefrash() 
{
	
}

BOOL CDlgRateCar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	CString x = LoadS(IDS_STRING_RULEID);
	m_list.InsertColumn(0, x, LVCFMT_LEFT, 100);
	x.Format("%s%d", LoadS(IDS_STRING_VEHTYPE),0);
	m_list.InsertColumn(1, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_VEHTYPE),1);
	m_list.InsertColumn(2, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_VEHTYPE),2);
	m_list.InsertColumn(3, x, LVCFMT_LEFT, 110);
	x.Format("%s%d", LoadS(IDS_STRING_VEHTYPE),3);
	m_list.InsertColumn(4, x, LVCFMT_LEFT, 110);
	ShowTheRule();//ÏÔÊ¾ÄÚÈÝ
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRateCar::ShowTheRule()
{
	CSetting * pSetting = CSetting::Instance();
#define __map pSetting->m_CarRule.m_Map
#define __iter pSetting->m_CarRule.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();__iter++)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._TZRsIdOfCarType0) );
		m_list.SetItemText(nCount, 2, show(__iter->second._TZRsIdOfCarType1) );
		m_list.SetItemText(nCount, 3, show(__iter->second._TZRsIdOfCarType2) );
		m_list.SetItemText(nCount, 4, show(__iter->second._TZRsIdOfCarType3) );
		nCount ++;
	}
#undef __iter
#undef __map
}

void CDlgRateCar::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

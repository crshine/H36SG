// dlgsettingcardtype.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgsettingcardtype.h"
#include "..\setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;
/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCardType dialog


CDlgSettingCardType::CDlgSettingCardType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingCardType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingCardType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingCardType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingCardType)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingCardType, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingCardType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCardType message handlers

void CDlgSettingCardType::ShowTheRule()
{
#define __map g_Setting->m_CardType.m_Map
#define __iter g_Setting->m_CardType.m_Iter
	int nCount = 0;
	m_list.DeleteAllItems();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_list.InsertItem(nCount, show(__iter->first));
		m_list.SetItemText(nCount, 1, show(__iter->second._Name));
		m_list.SetItemText(nCount, 2, show(__iter->second._WorkMode));
		m_list.SetItemText(nCount, 3, show(__iter->second._JoiningFee));
		m_list.SetItemText(nCount, 4, show(__iter->second._CardFee));
		m_list.SetItemText(nCount, 5, show(__iter->second.showPrice()));
		m_list.SetItemText(nCount, 6, show(__iter->second._WarningLevel));
		m_list.SetItemText(nCount, 7, show(__iter->second._Discount));
		m_list.SetItemText(nCount, 8, show(__iter->second._StoreValue));
		nCount ++;
	}
#undef __iter
#undef __map
}

BOOL CDlgSettingCardType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 150);
	m_list.InsertColumn(2, LoadS(IDS_STRING_WORKMODE), LVCFMT_LEFT, 50);
	m_list.InsertColumn(3, LoadS(IDS_STRING_JOINFEE), LVCFMT_LEFT, 50);
	m_list.InsertColumn(4, LoadS(IDS_STRING_CARDFEE), LVCFMT_LEFT, 50);
	m_list.InsertColumn(5, LoadS(IDS_STRING_UNITPRICE), LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, LoadS(IDS_STRING_WARNLVL), LVCFMT_LEFT, 50);
	m_list.InsertColumn(7, LoadS(IDS_STRING_DISCOUNT), LVCFMT_LEFT, 150);
	m_list.InsertColumn(8, LoadS(IDS_STRING_ISSV), LVCFMT_LEFT, 50);

	ShowTheRule();//œ‘ æƒ⁄»›
	return TRUE; 
}

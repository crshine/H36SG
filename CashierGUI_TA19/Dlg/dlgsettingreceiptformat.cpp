// dlgsettingreceiptformat.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\Setting.h"
#include "dlgsettingreceiptformat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingReceiptFormat dialog


CDlgSettingReceiptFormat::CDlgSettingReceiptFormat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingReceiptFormat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingReceiptFormat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingReceiptFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingReceiptFormat)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingReceiptFormat, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingReceiptFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingReceiptFormat message handlers

BOOL CDlgSettingReceiptFormat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, LoadS(IDS_STRING_SETTING), LVCFMT_LEFT, 330);
	Show();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSettingReceiptFormat::Show()
{
	CSetting * pSetting = CSetting::Instance();
	m_list.DeleteAllItems();
	m_list.InsertItem(0, "Title1");
	m_list.SetItemText(0, 1, pSetting->m_Receipt.Title1());
	m_list.InsertItem(1, "Title2");
	m_list.SetItemText(1, 1, pSetting->m_Receipt.Title2());
	m_list.InsertItem(2, "Title3");
	m_list.SetItemText(2, 1, pSetting->m_Receipt.Title3());
	m_list.InsertItem(3, "Ending1");
	m_list.SetItemText(3, 1, pSetting->m_Receipt.Ending1());
	m_list.InsertItem(4, "Ending2");
	m_list.SetItemText(4, 1, pSetting->m_Receipt.Ending2());
	m_list.InsertItem(5, "Tax Pecent Agerate");
	m_list.SetItemText(5, 1, showPercentage(pSetting->m_Receipt.TaxPercentageRate()));
	m_list.InsertItem(6, "Tax Name");
	m_list.SetItemText(6, 1, pSetting->m_Receipt.TaxName());
	m_list.InsertItem(7, "Tax Reg No");
	m_list.SetItemText(7, 1, pSetting->m_Receipt.TaxRegNo());
	m_list.InsertItem(8, "Left Black Spaces");
	m_list.SetItemText(8, 1, show(pSetting->m_Receipt.LeftBlackSpaces()));
	m_list.InsertItem(9, "Line Spaces");
	m_list.SetItemText(9, 1, show(pSetting->m_Receipt.LineSpaces()));
	m_list.InsertItem(10, "Feed Lines");
	m_list.SetItemText(10, 1, show(pSetting->m_Receipt.FeedLines()));
}

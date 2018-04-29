// dlgpaymentselectdiscount.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "dlgpaymentselectdiscount.h"
#include "..\Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentSelectDiscount dialog
CDiscount CDlgPaymentSelectDiscount::_Discount;
int CDlgPaymentSelectDiscount::_DiscountModeID;
CDlgPaymentSelectDiscount::CDlgPaymentSelectDiscount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaymentSelectDiscount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentSelectDiscount)
	m_OrgDiscountStr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPaymentSelectDiscount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentSelectDiscount)
	DDX_Control(pDX, ID_DISCOUNT_LIST, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_OrgDiscountStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentSelectDiscount, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentSelectDiscount)
	ON_NOTIFY(NM_CLICK, ID_DISCOUNT_LIST, OnClickDiscountList)
	ON_NOTIFY(NM_DBLCLK, ID_DISCOUNT_LIST, OnDblclkDiscountList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentSelectDiscount message handlers

BOOL CDlgPaymentSelectDiscount::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_list.InsertColumn(0, LoadS(IDS_STRING_INDEX), LVCFMT_LEFT, 45);
	m_list.InsertColumn(1, LoadS(IDS_STRING_NAME), LVCFMT_LEFT, 190);
	m_list.InsertColumn(2, LoadS(IDS_STRING_DISCOUNT), LVCFMT_LEFT, 175);

	ShowTheRule();//珆尨囀��	
	
	if (g_Setting->m_DiscountPlan.Valid(_DiscountModeID))
	{
		_Discount = g_Setting->m_DiscountPlan.Discount(_DiscountModeID);
		m_OrgDiscountStr = g_Setting->m_DiscountPlan.DiscountModeName(_DiscountModeID);
		m_OrgDiscountStr.TrimRight();
		m_OrgDiscountStr += "/" + _Discount.GetDescription();
	}else{
		_Discount = "123";
		m_OrgDiscountStr = "No Discount";
//		m_OrgDiscountStr = " "; //test  for UCH interface modify
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentSelectDiscount::ShowTheRule()
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

void CDlgPaymentSelectDiscount::OnOK()
{
	CSetting * pSetting = CSetting::Instance();
	int index = (int )m_list.GetFirstSelectedItemPosition() - 1;
	if (-1 == index)
	{
		::AfxMessageBox(TIP_NEED_DISCOUNT, MB_ICONSTOP|MB_SYSTEMMODAL);
		return;
	}

	_DiscountModeID = atoi(m_list.GetItemText(index, 0));

	if ( pSetting->m_DiscountPlan.Valid(_DiscountModeID) )
	{
		_Discount = pSetting->m_DiscountPlan.Discount(_DiscountModeID);
	}
	else
	{
		::AfxMessageBox(TIP_NEED_DISCOUNT , MB_ICONSTOP|MB_SYSTEMMODAL);
		return;
	}
	CDialog::OnOK();
}

void CDlgPaymentSelectDiscount::OnCancel() 
{
//	GetDlgItem(IDC_SEL_DISCOUNT)->EnableWindow(true);	
	CDialog::OnCancel();
}

void CDlgPaymentSelectDiscount::OnClickDiscountList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
//	showTip("進入優惠處理模式2",true, true);

	*pResult = 0;
}

void CDlgPaymentSelectDiscount::OnDblclkDiscountList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CSetting * pSetting = CSetting::Instance();
	int index = (int )m_list.GetFirstSelectedItemPosition() - 1;
	if (-1 == index)
	{
		::AfxMessageBox(TIP_NEED_DISCOUNT, MB_ICONSTOP|MB_SYSTEMMODAL );
		return;
	}

	_DiscountModeID = atoi(m_list.GetItemText(index, 0));

	if ( pSetting->m_DiscountPlan.Valid(_DiscountModeID) )
	{
		_Discount = pSetting->m_DiscountPlan.Discount(_DiscountModeID);
	}
	else
	{
		::AfxMessageBox(TIP_NEED_DISCOUNT , MB_ICONSTOP|MB_SYSTEMMODAL);
		return;
	}
	CDialog::OnOK();
	*pResult = 0;
}

// dlgcardcategory.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgcardcategory.h"

extern _System g_System;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgCardCategory dialog


CDlgCardCategory::CDlgCardCategory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCardCategory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCardCategory)
	//}}AFX_DATA_INIT
}


void CDlgCardCategory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCardCategory)
	DDX_Control(pDX, IDC_CATEGORY, m_Category);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCardCategory, CDialog)
	//{{AFX_MSG_MAP(CDlgCardCategory)
	ON_BN_CLICKED(IDC_BUTTON_REFRASH, OnButtonRefrash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCardCategory message handlers

BOOL CDlgCardCategory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ShowTheRule();//œ‘ æƒ⁄»›
	return TRUE;
}

void CDlgCardCategory::ShowTheRule()
{
/*
#define __mapRule g_System.m_Card.mapCardCategory 
#define __iterRule g_System.m_Card.iterCardCategory 
	CString s = "";
	for (__iterRule = __mapRule.begin();__iterRule!=__mapRule.end();__iterRule++)
	{
		s += (CCard::__structCardCategory ((*__iterRule).second)).GetDescription();
		s += "--------------------------------------------------------------------------------------------------------------\r\n";
	}
	if ("" == s)
		m_Category.SetWindowText("No Card Category Exist.");
	else
		m_Category.SetWindowText(s);
#undef __iterRule
#undef __Rule
		*/
}

void CDlgCardCategory::OnButtonRefrash() 
{
	ShowTheRule();
}

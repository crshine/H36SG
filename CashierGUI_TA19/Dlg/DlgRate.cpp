// dlgrate.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgrate.h"
#include "dlgrateday.h"
#include "dlgratecar.h"
#include "dlgratefee.h"
#include "dlgratefix.h"
#include "dlgrategroup.h"
#include "dlgratetimezone.h"
#include "dlgratecalculate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRate dialog


CDlgRate::CDlgRate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRate)
	DDX_Control(pDX, IDC_TAB_RATE, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRate, CDialog)
	//{{AFX_MSG_MAP(CDlgRate)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRate message handlers

BOOL CDlgRate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDialog::CenterWindow();
/*
	CDialog * m_pdlgFee;
	CDialog * m_pdlgTimezone;
	CDialog * m_pdlgCar;
	CDialog * m_pdlgGroup;
	CDialog * m_pdlgDay;
	CDialog * m_pdlgFix;
*/
	//Day Rule
	m_pdlgDay = new CDlgRateDay;
	m_pdlgDay->Create(IDD_RATE_DAY, &m_tab);
	m_tab.AddItem(m_pdlgDay,LoadS(IDS_STRING_DAYRULE).GetBuffer(244));
	//Group Rule
	m_pdlgGroup = new CDlgRateGroup;
	m_pdlgGroup->Create(IDD_RATE_GROUP, &m_tab);
	m_tab.AddItem(m_pdlgGroup,LoadS(IDS_STRING_GROUPRULE).GetBuffer(244));
	//Car Rule
	m_pdlgCar = new CDlgRateCar;
	m_pdlgCar->Create(IDD_RATE_CARTYPE, &m_tab);
	m_tab.AddItem(m_pdlgCar,LoadS(IDS_STRING_VEHRULE).GetBuffer(244));
	//Timezone Rule
	m_pdlgTimezone = new CDlgRateTimezone;
	m_pdlgTimezone->Create(IDD_RATE_TIMEZONE, &m_tab);
	m_tab.AddItem(m_pdlgTimezone,LoadS(IDS_STRING_TZRULE).GetBuffer(244));
	//Fee Rule
	m_pdlgFee = new CDlgRateFee;
	m_pdlgFee->Create(IDD_RATE_FEE, &m_tab);
	m_tab.AddItem(m_pdlgFee,LoadS(IDS_STRING_FEERULE).GetBuffer(244));
	//Fix Rule
	m_pdlgFix = new CDlgRateFix;
	m_pdlgFix->Create(IDD_RATE_FIX, &m_tab);
	m_tab.AddItem(m_pdlgFix,LoadS(IDS_STRING_FIXRULE).GetBuffer(244));
	//Calculate
	m_pdlgCalculate = new CDlgRateCalculate;
	m_pdlgCalculate->Create(IDD_RATE_CALCULATE, &m_tab);
	m_tab.AddItem(m_pdlgCalculate,LoadS(IDS_STRING_CALCULATE).GetBuffer(244));
	//Éè½¹µã
	m_pdlgDay->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRate::OnDestroy() 
{
	CDialog::OnDestroy();
	delete m_pdlgDay;
	delete this;
}

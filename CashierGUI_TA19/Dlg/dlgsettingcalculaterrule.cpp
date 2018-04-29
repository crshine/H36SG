// dlgsettingcalculaterrule.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlgsettingcalculaterrule.h"
#include "..\setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetting * g_Setting;

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCalculaterRule dialog


CDlgSettingCalculaterRule::CDlgSettingCalculaterRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingCalculaterRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingCalculaterRule)
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSettingCalculaterRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingCalculaterRule)
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingCalculaterRule, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingCalculaterRule)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCalculaterRule message handlers

void CDlgSettingCalculaterRule::ShowTheRule()
{
	//Show three grace TimeSpan;
	SetDlgItemText(ENTERGRACETIME, show(g_Setting->m_ParkingFee.EnterGrace()) );
	SetDlgItemText(PAIDGRACETIME, show(g_Setting->m_ParkingFee.PaidGrace()) );
	SetDlgItemText(TZONEGRACETIME, show(g_Setting->m_ParkingFee.TZoneGrace()) );

	//Show three currency value;
	SetDlgItemText(LOSTTICKETPENALTY, show(g_Setting->m_ParkingFee.LostAmount()));
	SetDlgItemText(CREDITLIMIT, show(g_Setting->m_ParkingFee.CreditLimit()));
	SetDlgItemText(PERENTRYAMT, show(g_Setting->m_ParkingFee.PerEntryAmt()));

	//show three calculater rule check value;
	m_Check1 = g_Setting->m_ParkingFee.CutByTimeZone();
	m_Check2 = g_Setting->m_ParkingFee.HandleLostTicket();
	m_Check3 = g_Setting->m_ParkingFee.FixTimeRule();

	UpdateData(FALSE);
}

void CDlgSettingCalculaterRule::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	ShowTheRule();
}

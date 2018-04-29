// DlgSetting.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DlgSetting.h"
#include "DlgSettingCommunicate.h"
#include "DlgSettingPeripheral.h"

extern _System g_System;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetting)
	DDX_Control(pDX, IDC_TAB_SETTING, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSetting)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting message handlers

void CDlgSetting::OnDestroy() 
{
	CDialog::OnDestroy();
	delete m_pdlgsystem;
	delete m_pdlgperipheral;
	delete this;
}

  
BOOL CDlgSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDialog::CenterWindow();
	//系统设置	
	m_pdlgsystem = new CDlgSettingCommunicate;
	m_pdlgsystem->Create(IDD_SETTING_COMMUNICATE, &m_tab);
	m_tab.AddItem(m_pdlgsystem,LoadS(IDS_STRING_COMM).GetBuffer(244));
	//外围设备
	m_pdlgperipheral = new CDlgSettingPeripheral;
	m_pdlgperipheral->Create(IDD_SETTING_PERIPHERAL, &m_tab);
	m_tab.AddItem(m_pdlgperipheral,LoadS(IDS_STRING_PERIP).GetBuffer(244));
	//设焦点
	m_pdlgsystem->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

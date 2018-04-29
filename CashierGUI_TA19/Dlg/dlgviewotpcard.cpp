// dlgviewotpcard.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\CmdOtp.h"
#include "dlgviewotpcard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _System		g_System;
/////////////////////////////////////////////////////////////////////////////
// CDlgViewOtpCard dialog


CDlgViewOtpCard::CDlgViewOtpCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewOtpCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewOtpCard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgViewOtpCard::~CDlgViewOtpCard()
{
}

void CDlgViewOtpCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewOtpCard)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewOtpCard, CDialog)
	//{{AFX_MSG_MAP(CDlgViewOtpCard)
	ON_BN_CLICKED(ID_WAIT_OTP_POLL, OnWaitOtpPoll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOtpCard message handlers

void CDlgViewOtpCard::OnWaitOtpPoll() 
{
	GetDlgItem(ID_WAIT_OTP_POLL)->EnableWindow(false);

	SetDlgItemText( IDC_CARD_NO,			"" );
	SetDlgItemText( IDC_REMAIN,				"" );
	SetDlgItemText( IDC_ADD_VALUE_DETAIL,	"" );
	SetDlgItemText( IDC_LAST_ADD_VALUE_DEVICE,		"" );
	SetDlgItemText( IDC_CLASS,				"" );
	SetDlgItemText( IDC_LANGUAGE,			"" );
	SetDlgItemText( IDC_AVAILABLE_AMOUNT,	"" );
	SetDlgItemText( IDC_MANUFACTURE_ID,		"" );

	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON_LOG PatronLog;

	if (!pCmdOtp->OTP_Poll( PatronLog, 30 )) //ÑÓÊ±3Ãë
	{	//¶Á¿¨Ê§°Ü
		AfxMessageBox(pCmdOtp->Translate());
//		OtpErrProcess();
		GetDlgItem(ID_WAIT_OTP_POLL)->EnableWindow(true);
		return;
	}

	SetDlgItemText( IDC_CARD_NO,			PatronLog._CardNo );
	SetDlgItemText( IDC_REMAIN,				show(PatronLog._Remain) );
	SetDlgItemText( IDC_ADD_VALUE_DETAIL,	PatronLog._AddValueDetail );
	SetDlgItemText( IDC_LAST_ADD_VALUE_DEVICE,		PatronLog._LastAddValueDevice );
	SetDlgItemText( IDC_CLASS,				show(PatronLog._Class) );
	SetDlgItemText( IDC_LANGUAGE,			(0 == PatronLog._Language ? "Chinese" : "English" ) );
	SetDlgItemText( IDC_AVAILABLE_AMOUNT,	show(PatronLog._AvailableAmount) );
	SetDlgItemText( IDC_MANUFACTURE_ID,		PatronLog._ManufactureID );

	m_list.DeleteAllItems();
	for (int i = 0; i < 10; i++)
	{
		m_list.InsertItem(i, show(PatronLog._Log[i]._SP_ID));
		m_list.SetItemText(i, 1, show(PatronLog._Log[i]._TransactionAmt) );
		m_list.SetItemText(i, 2, show(PatronLog._Log[i]._TransactionTime) );
		m_list.SetItemText(i, 3, show(PatronLog._Log[i]._MachineID) );
		m_list.SetItemText(i, 4, show(PatronLog._Log[i]._ServiceInfo) );
	}

	GetDlgItem(ID_WAIT_OTP_POLL)->EnableWindow(true);
}


BOOL CDlgViewOtpCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, LoadS(IDS_STRING_SPID), LVCFMT_LEFT, 140);
	m_list.InsertColumn(1, LoadS(IDS_STRING_AMOUNT), LVCFMT_LEFT, 140);
	m_list.InsertColumn(2, LoadS(IDS_STRING_TIME), LVCFMT_LEFT, 140);
	m_list.InsertColumn(3, LoadS(IDS_STRING_MID), LVCFMT_LEFT, 140);
	m_list.InsertColumn(4, LoadS(IDS_STRING_MSG), LVCFMT_LEFT, 140);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

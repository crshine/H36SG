// dlgsettingcommunicate.cpp : implementation file
//

#include "stdafx.h"
#include <winsock2.h>
#include <afxsock.h>
#include "..\cashiergui.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgsettingcommunicate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCommunicate dialog


CDlgSettingCommunicate::CDlgSettingCommunicate(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgSettingCommunicate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingCommunicate)
	m_MNT_ID = 0;
	m_RecvPort = 0;
	m_SendPort = 0;
	m_SendTreadStep = 0;
	m_StationID = 0;
	m_StationName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSettingCommunicate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingCommunicate)
	DDX_Control(pDX, IDC_STATION_IP, m_StationIP);
	DDX_Control(pDX, IDC_MNT_IP, m_MNT_IP);
	DDX_Text(pDX, IDC_MNT_ID, m_MNT_ID);
	DDV_MinMaxInt(pDX, m_MNT_ID, 0, 99);
	DDX_Text(pDX, IDC_RECV_PORT, m_RecvPort);
	DDV_MinMaxInt(pDX, m_RecvPort, 1000, 9999);
	DDX_Text(pDX, IDC_SEND_PORT, m_SendPort);
	DDV_MinMaxInt(pDX, m_SendPort, 1000, 9999);
	DDX_Text(pDX, IDC_SEND_THREAD_STEP, m_SendTreadStep);
	DDV_MinMaxInt(pDX, m_SendTreadStep, 0, 1000);
	DDX_Text(pDX, IDC_STATION_ID, m_StationID);
	DDV_MinMaxInt(pDX, m_StationID, 1, 99);
	DDX_Text(pDX, IDC_STATION_NAME, m_StationName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingCommunicate, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingCommunicate)
	ON_EN_UPDATE(IDC_STATION_ID, OnUpdateStationId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingCommunicate message handlers

void CDlgSettingCommunicate::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	GetLocalIP();	//显示本机IP;
	m_MNT_IP.SetWindowText( pSetting->m_Communicate.ManagementIP() );
	m_StationID = _ttol( pSetting->m_Communicate.StationID() );
	m_MNT_ID = _ttol( pSetting->m_Communicate.ManagementID() );
	m_RecvPort = pSetting->m_Communicate.RecvSocketPort();
	m_SendPort = pSetting->m_Communicate.SendSocketPort();
	m_SendTreadStep = pSetting->m_Communicate.SendThreadStep();

	//显示名字如果有的话.
	if (pSetting->m_StationInformation.Valid( m_StationID ))
		m_StationName = pSetting->m_StationInformation.StationName( m_StationID );
	else
		m_StationName = "";
	UpdateData(false);
}

void CDlgSettingCommunicate::OnUpdateStationId() 
{
	CSetting * pSetting = CSetting::Instance();
	if (!UpdateData(true)) return ;
	if (pSetting->m_StationInformation.Valid( m_StationID ))
		m_StationName = pSetting->m_StationInformation.StationName( m_StationID );
	else
		m_StationName = "";
	UpdateData(false);
}

BOOL CDlgSettingCommunicate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSettingCommunicate::OnOK() 
{
	CSetting * pSetting = CSetting::Instance();
	if (!UpdateData(true)) return ;
	CString s;
	m_MNT_IP.GetWindowText(s);
	pSetting->m_Communicate.SetCommunicate(m_StationID, m_SendTreadStep, 
		m_SendPort, m_RecvPort, s, m_MNT_ID);
	showTip( (LPCTSTR)TIP_SUCCESSFUL_SAVE_SETTING );
}

void CDlgSettingCommunicate::OnCancel() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

void CDlgSettingCommunicate::GetLocalIP()
{
	WORD wVersionRequested; 
	WSADATA wsaData; 
	char name[255]; 
	CString ip; 
	PHOSTENT hostinfo; 
	wVersionRequested = MAKEWORD( 2, 0 ); 
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 ) 
	{ 
		if( gethostname ( name, sizeof(name)) == 0) 
		{ 
			if((hostinfo = gethostbyname(name)) != NULL) 
			{ 
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
				m_StationIP.SetWindowText(ip);
			} 
		} 
		WSACleanup();
	}
}

// dlgsettingperipheral.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgsettingperipheral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPeripheral dialog


CDlgSettingPeripheral::CDlgSettingPeripheral(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgSettingPeripheral::IDD, pParent), NULL_PORT(0)
{
	//{{AFX_DATA_INIT(CDlgSettingPeripheral)
	m_KdeThreadStep = 0;
	m_LcdThreadStep = 0;
	m_OtpThreadStep = 0;
	m_PrinterThreadStep = 0;
	//}}AFX_DATA_INIT
}

void CDlgSettingPeripheral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingPeripheral)
	DDX_Control(pDX, IDC_PRINTER_BAUD_RATE, PrinterBaudRateBox);
	DDX_Control(pDX, IDC_OTP_BAUD_RATE, OtpBaudRateBox);
	DDX_Control(pDX, IDC_LCD_BAUD_RATE, LcdBaudRateBox);
	DDX_Control(pDX, IDC_KDE_BAUD_RATE, KdeBaudRateBox);
	DDX_Control(pDX, IDC_PRINTER_PORT, PrinterPortBox);
	DDX_Control(pDX, IDC_OTP_PORT, OtpPortBox);
	DDX_Control(pDX, IDC_LCD_PORT, LcdPortBox);
	DDX_Control(pDX, IDC_KDE_PORT, KdePortBox);
	DDX_Text(pDX, IDC_KDE_STEP, m_KdeThreadStep);
	DDV_MinMaxInt(pDX, m_KdeThreadStep, 0, 1000);
	DDX_Text(pDX, IDC_LCD_STEP, m_LcdThreadStep);
	DDV_MinMaxInt(pDX, m_LcdThreadStep, 0, 5000);
	DDX_Text(pDX, IDC_OTP_STEP, m_OtpThreadStep);
	DDV_MinMaxInt(pDX, m_OtpThreadStep, 0, 1000);
	DDX_Text(pDX, IDC_PRINTER_STEP, m_PrinterThreadStep);
	DDV_MinMaxInt(pDX, m_PrinterThreadStep, 0, 1000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSettingPeripheral, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingPeripheral)
	ON_CBN_SELCHANGE(IDC_OTP_PORT, OnSelchangeOtpPort)
	ON_CBN_SELCHANGE(IDC_LCD_PORT, OnSelchangeLcdPort)
	ON_CBN_SELCHANGE(IDC_KDE_PORT, OnSelchangeKdePort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPeripheral message handlers

void CDlgSettingPeripheral::OnOK() 
{
	CSetting * pSetting = CSetting::Instance();
	CString s;
	PrinterBaudRateBox.GetWindowText(s);
	m_PrinterBaudRate = _ttol(s);
	OtpBaudRateBox.GetWindowText(s);
	m_OtpBaudRate = _ttol(s);
	LcdBaudRateBox.GetWindowText(s);
	m_LcdBaudRate = _ttol(s);
	KdeBaudRateBox.GetWindowText(s);
	m_KdeBaudRate = _ttol(s);

	m_PrinterPort = PrinterPortBox.GetCurSel();
	this->UpdateData(true);
	m_PrinterPort = PrinterPortBox.GetCurSel();
	pSetting->m_Peripheral.SetOtpParameter(m_OtpPort_Tmp, m_OtpThreadStep, m_OtpBaudRate);
	pSetting->m_Peripheral.SetKdeParameter(m_KdePort_Tmp, m_KdeThreadStep, m_KdeBaudRate);
	pSetting->m_Peripheral.SetLcdParameter(m_LcdPort_Tmp, m_LcdThreadStep, m_LcdBaudRate);
	pSetting->m_Peripheral.SetPrinterParameter(m_PrinterPort, m_PrinterThreadStep, m_PrinterBaudRate);

	showTip( (LPCTSTR)TIP_SUCCESSFUL_SAVE_SETTING );
}

void CDlgSettingPeripheral::OnCancel() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

BOOL CDlgSettingPeripheral::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSettingPeripheral::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	pSetting->m_Peripheral.GetKdeParameter(m_KdePort, m_KdeThreadStep, m_KdeBaudRate);
	pSetting->m_Peripheral.GetOtpParameter(m_OtpPort, m_OtpThreadStep, m_OtpBaudRate);
	pSetting->m_Peripheral.GetLcdParameter(m_LcdPort, m_LcdThreadStep, m_LcdBaudRate);
	pSetting->m_Peripheral.GetPrinterParameter(m_PrinterPort, m_PrinterThreadStep, m_PrinterBaudRate);
	this->UpdateData(false);
	//m_***Port_Tmp的值可能被用户的临时选则修改.
	//m_***Port的值只有在用户明确选择后才修改.
	m_KdePort_Tmp = m_KdePort;
	m_LcdPort_Tmp = m_LcdPort;
	m_OtpPort_Tmp = m_OtpPort;
	SyncComboBox();		//同步串口选择框的值.

	PrinterPortBox.SetCurSel(m_PrinterPort);

	PrinterBaudRateBox.SelectString(0, show(m_PrinterBaudRate));
	OtpBaudRateBox.SelectString(0, show(m_OtpBaudRate));
	LcdBaudRateBox.SelectString(0, show(m_LcdBaudRate));
	KdeBaudRateBox.SelectString(0, show(m_KdeBaudRate));
}

void CDlgSettingPeripheral::SyncComboBox()
{
	OtpPortBox.SetCurSel(m_OtpPort_Tmp);
	KdePortBox.SetCurSel(m_KdePort_Tmp);
	LcdPortBox.SetCurSel(m_LcdPort_Tmp);
}


void CDlgSettingPeripheral::OnSelchangeOtpPort() 
{
	m_OtpPort_Tmp = m_OtpPort = OtpPortBox.GetCurSel();
	//恢复临时改变
	SetLastValidValue();
	//不能有相同的选择.
	if (m_KdePort_Tmp == m_OtpPort) m_KdePort_Tmp = NULL_PORT;
	if (m_LcdPort_Tmp == m_OtpPort) m_LcdPort_Tmp = NULL_PORT;
	SyncComboBox();
}

void CDlgSettingPeripheral::OnSelchangeLcdPort() 
{
	m_LcdPort_Tmp = m_LcdPort = LcdPortBox.GetCurSel();
	//恢复临时改变
	SetLastValidValue();
	//不能有相同的选择.
	if (m_OtpPort_Tmp == m_LcdPort) m_OtpPort_Tmp = NULL_PORT;
	if (m_KdePort_Tmp == m_LcdPort) m_KdePort_Tmp = NULL_PORT;
	SyncComboBox();
}

void CDlgSettingPeripheral::OnSelchangeKdePort() 
{
	m_KdePort_Tmp = m_KdePort = KdePortBox.GetCurSel();
	//恢复临时改变
	SetLastValidValue();
	//不能有相同的选择.
	if (m_OtpPort_Tmp == m_KdePort) m_OtpPort_Tmp = NULL_PORT;
	if (m_LcdPort_Tmp == m_KdePort) m_LcdPort_Tmp = NULL_PORT;
	SyncComboBox();
}

void CDlgSettingPeripheral::SetLastValidValue()
{	//如果临时值为空,并且上一值不等于其他任何值,则恢复.
	if (( m_OtpPort_Tmp == NULL_PORT ) &&
	    ( m_OtpPort != m_KdePort_Tmp ) &&
	    ( m_OtpPort != m_LcdPort_Tmp ) )
		m_OtpPort_Tmp = m_OtpPort;
	if (( m_KdePort_Tmp == NULL_PORT ) &&
	    ( m_KdePort != m_LcdPort_Tmp ) &&
	    ( m_KdePort != m_OtpPort_Tmp ) )
		m_KdePort_Tmp = m_KdePort;
	if (( m_LcdPort_Tmp == NULL_PORT ) &&
	    ( m_LcdPort != m_KdePort_Tmp ) &&
	    ( m_LcdPort != m_OtpPort_Tmp ) )
		m_LcdPort_Tmp = m_LcdPort;
}

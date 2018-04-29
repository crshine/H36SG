// dlgpaymentotpentry.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentotpentry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPEntry dialog
COleDateTime CDlgPaymentOTPEntry::_EntryTime = COleDateTime::GetCurrentTime();
COleDateTime CDlgPaymentOTPEntry::_ExitTime = COleDateTime::GetCurrentTime();
short CDlgPaymentOTPEntry::_EntryStation = 0;
short CDlgPaymentOTPEntry::_VehicleId = 0;

CDlgPaymentOTPEntry::CDlgPaymentOTPEntry(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentOTPEntry::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentOTPEntry)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPaymentOTPEntry::DoDataExchange(CDataExchange* pDX)
{
	CDlgInput::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentOTPEntry)
	DDX_Control(pDX, IDC_VEHICLETYPE, m_VehicleType);
	DDX_Control(pDX, IDC_EXITTIME, m_ExitTime);
	DDX_Control(pDX, IDC_EXITDATE, m_ExitDate);
	DDX_Control(pDX, IDC_ENTRYTIME, m_EntryTime);
	DDX_Control(pDX, IDC_ENTRYSTATION, m_EntryStation);
	DDX_Control(pDX, IDC_ENTRYDATE, m_EntryDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentOTPEntry, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentOTPEntry)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPEntry message handlers

void CDlgPaymentOTPEntry::OnOK() 
{
	COleDateTimeSpan ts;
	COleDateTime	tempDate, tempTime;
	//获得EntryTime;
	m_EntryDate.GetTime(tempDate);
	m_EntryTime.GetTime(tempTime);
	_EntryTime.SetDateTime(tempDate.GetYear(), tempDate.GetMonth(), tempDate.GetDay(),
							tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());

	//获得ExitTime
	m_ExitDate.GetTime(tempDate);
	m_ExitTime.GetTime(tempTime);
	_ExitTime.SetDateTime(tempDate.GetYear(), tempDate.GetMonth(), tempDate.GetDay(),
							tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
	//检验
	if (_EntryTime >= _ExitTime)
	{
		showTip( (LPCTSTR)TIP_INVALID_IO_TIME );
		return;
	}

	CString Temp;

	_VehicleId = 0;
	m_VehicleType.GetWindowText(Temp);
	if (0 != Temp.GetLength())
	{
		sscanf(Temp, "(%d)", &_VehicleId);
	}

	_EntryStation = 0;
	m_EntryStation.GetWindowText(Temp);
	if (0 != Temp.GetLength())
	{
		sscanf(Temp, "(%d)", &_EntryStation);
	}

	CDlgInput::OnOK();
}

BOOL CDlgPaymentOTPEntry::OnInitDialog() 
{
	CDlgInput::OnInitDialog();
	InitControl();//控件外观

	this->SetForegroundWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPaymentOTPEntry::InitControl()
{
	CSetting * pSetting = CSetting::Instance();

	//改变文字大小
	GetDlgItem(IDC_STATIC1)->SetFont(&pSetting->FontMid());
	GetDlgItem(IDC_STATIC2)->SetFont(&pSetting->FontMid());
	GetDlgItem(IDC_STATIC3)->SetFont(&pSetting->FontMid());
	GetDlgItem(IDC_STATIC4)->SetFont(&pSetting->FontMid());

	GetDlgItem(IDC_ENTRYDATE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_ENTRYTIME)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EXITDATE)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_EXITTIME)->SetFont(&m_fontEdit);
	//控件初始值
	COleDateTime m_MinDate, m_MaxDate;//, m_CurDate;
	m_MinDate.SetDate(2000,1,1);
	m_MaxDate.SetDate(2100,1,1);
//	m_CurDate = COleDateTime::GetCurrentTime();
	m_EntryDate.SetRange(&m_MinDate, &m_MaxDate);
	m_ExitDate.SetRange(&m_MinDate, &m_MaxDate);

	//生成形如"(id)Vehicle_Type_name"的字符串
	#define __map pSetting->m_VehicleType.m_Map
	#define __iter pSetting->m_VehicleType.m_Iter
	m_VehicleType.ResetContent();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_VehicleType.AddString("("+show(__iter->first)+")"+show(__iter->second._TypeName));
	}
	m_VehicleType.SetCurSel(0);
	#undef __iter
	#undef __map

	//生成形如"(id)station_name"的字符串
	#define __map pSetting->m_StationInformation.m_Map
	#define __iter pSetting->m_StationInformation.m_Iter
	m_EntryStation.ResetContent();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		if (pSetting->m_StationInformation.IsEntryStation(__iter->second._StationType))
		{
			m_EntryStation.AddString("("+show(__iter->first)+")"+show(__iter->second._StationName));
		}
	}
	m_EntryStation.SetCurSel(0);
	#undef __iter
	#undef __map
}

HBRUSH CDlgPaymentOTPEntry::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CSetting * pSetting = CSetting::Instance();
	if ( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(pSetting->AbnormityColor()); //改变静态空控件字体颜色
	}
	return pSetting->AbnormityBrush();//使用一种表示特殊操作的醒目颜色
}

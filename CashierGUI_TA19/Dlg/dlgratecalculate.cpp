// dlgratecalculate.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "..\FeeCalculate.h"
#include "dlgratecalculate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCalculate dialog
CDlgRateCalculate * CDlgRateCalculate::pThis = NULL;

CDlgRateCalculate::CDlgRateCalculate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRateCalculate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRateCalculate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRateCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRateCalculate)
	DDX_Control(pDX, IDC_DETAILS, m_DetailList);
	DDX_Control(pDX, IDC_VEHICLETYPE, m_VehicleType);
	DDX_Control(pDX, IDC_EXITTIME, m_ExitTime);
	DDX_Control(pDX, IDC_EXITDATE, m_ExitDate);
	DDX_Control(pDX, IDC_ENTRYTIME, m_EntryTime);
	DDX_Control(pDX, IDC_GROUPTYPE, m_GroupType);
	DDX_Control(pDX, IDC_ENTRYDATE, m_EntryDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRateCalculate, CDialog)
	//{{AFX_MSG_MAP(CDlgRateCalculate)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_BN_CLICKED(IDC_CHANGELISTWIDTH, OnChangelistwidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCalculate message handlers

BOOL CDlgRateCalculate::OnInitDialog() 
{
	CDlgRateCalculate::pThis = this;
	CDialog::OnInitDialog();

	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgRateCalculate::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP)
	{
		
		CButton* pButton=(CButton*)GetDlgItem(IDOK);
		HWND hOKWnd=pButton->m_hWnd;
		if (pMsg->wParam == VK_ESCAPE) return true;//eat "ESC"
		if (pMsg->hwnd!=hOKWnd)//do nothing if at the button "IDOK"
			if (pMsg->wParam == VK_RETURN)
				pMsg->wParam = VK_TAB;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgRateCalculate::OnCalculate() 
{
	UpdateData(false);
	COleDateTimeSpan ts;
	COleDateTime	tempDate, tempTime;
	COleDateTime	EntryTime, ExitTime;
	
	//获得EntryTime;
	m_EntryDate.GetTime(tempDate);
	m_EntryTime.GetTime(tempTime);
	EntryTime.SetDateTime(tempDate.GetYear(), tempDate.GetMonth(), tempDate.GetDay(),
							tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
	//获得ExitTime
	m_ExitDate.GetTime(tempDate);
	m_ExitTime.GetTime(tempTime);
	ExitTime.SetDateTime(tempDate.GetYear(), tempDate.GetMonth(), tempDate.GetDay(),
							tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
	//检验
	if (EntryTime >= ExitTime)
	{
		showTip( (LPCTSTR)TIP_INVALID_IO_TIME );
		return;
	}
	//车辆种类
	CString Temp;
	short VehicleTypeId = 0;
	m_VehicleType.GetWindowText(Temp);
	if (0 != Temp.GetLength())
		sscanf(Temp, "(%d)", &VehicleTypeId);
	//组种类
	short GroupTypeId = 0;
	m_GroupType.GetWindowText(Temp);
	if (0 != Temp.GetLength())
		sscanf(Temp, "(%d)", &GroupTypeId);
	//返回参数
	double Amount;
	CDiscount Discount;
	Discount.Clear();
	CFeeCalculate FeeCalculate;
	short Result;
	//参数准备完毕
	m_DetailList.DeleteAllItems();
	UINT x;
	Result = FeeCalculate.Calculate(Amount, Discount, EntryTime, ExitTime, 
							VehicleTypeId, GroupTypeId, false, x, ShowDetail);
	CString info;
	if (Calculate_Success <= Result)
	{
		info.Format("%s%0.2f", _T("Calculate Success!\nParkingAmount :\n   "), Amount);
	}
	else
	{
		info = FeeCalculate.GetErrorMessage(Result);
	}
	AfxMessageBox(info);	
}

void CDlgRateCalculate::OnOK() 
{
	this->GetParent()->GetParent()->DestroyWindow();
}

void CALLBACK CDlgRateCalculate::ShowDetail(CString Detail)
{
	if (CDlgRateCalculate::pThis->m_DetailList.GetItemCount() > 200) return;
	CDlgRateCalculate::pThis->m_DetailList.InsertItem(CDlgRateCalculate::pThis->m_DetailList.GetItemCount(), Detail);
	if (CDlgRateCalculate::pThis->m_DetailList.GetItemCount() == 200)
		CDlgRateCalculate::pThis->m_DetailList.InsertItem(CDlgRateCalculate::pThis->m_DetailList.GetItemCount(), "Max Show 200 lines, but no effect the Calculate result  ..... ");
}

void CDlgRateCalculate::OnChangelistwidth() 
{
	RECT wndRect,listRect,aimRect;
	CWnd * pWnd; 
	pWnd = m_DetailList.GetParent();
	pWnd->GetWindowRect(&wndRect);
	m_DetailList.GetWindowRect(&listRect);
	
	aimRect.left = listRect.left - wndRect.left;
	aimRect.top = listRect.top - wndRect.top;
	aimRect.right = listRect.right - listRect.left;
	if (aimRect.right < 400 )
		aimRect.right *= 2;
	else
		aimRect.right /= 2;
	aimRect.bottom = listRect.bottom - listRect.top;
	m_DetailList.MoveWindow(aimRect.left, 
							aimRect.top, 
							aimRect.right, 
							aimRect.bottom, SWP_SHOWWINDOW);
}

void CDlgRateCalculate::InitControl()
{
	//控件初始值
	COleDateTime m_MinDate, m_MaxDate;//, m_CurDate;
	m_MinDate.SetDate(2000,1,1);
	m_MaxDate.SetDate(2100,1,1);
//	m_CurDate = COleDateTime::GetCurrentTime();
	m_EntryDate.SetRange(&m_MinDate, &m_MaxDate);
	m_ExitDate.SetRange(&m_MinDate, &m_MaxDate);

	CSetting * pSetting = CSetting::Instance();
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
	#define __map pSetting->m_GroupType.m_Map
	#define __iter pSetting->m_GroupType.m_Iter
	m_GroupType.ResetContent();
	for (__iter = __map.begin();__iter!=__map.end();++__iter)
	{
		m_GroupType.AddString("("+show(__iter->first)+")"+show(__iter->second._Description));
	}
	m_GroupType.SetCurSel(0);
	#undef __iter
	#undef __map

	m_DetailList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_DetailList.InsertColumn(0, LoadS(IDS_STRING_DESCRIP), LVCFMT_LEFT, 535);
}

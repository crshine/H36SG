// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CashierGUI.h"

#include "CmdMntRecv.h"		//与管理站通讯接收部分
#include "CmdMntSend.h"		//有关管理站命令(发送)
#include "CmdKde.h"			//KDE读卡器
#include "CmdJmdm.h"		
#include "CmdOtp.h"			//八达通读卡器
#include "dlg\dlglogin.h"
#include "Customer.h"		//客户

#include "dlg\dlgsetting.h"				//	设置
#include "dlg\dLGOtpTest.h"				//	八达通卡
#include "dlg\DlgEventLog.h"			//	日志
#include "dlg\DlgRate.h"				//	收费标准
#include "dlg\DlgCardCategory.h"		//	显示卡类别
#include "dlg\DlgCardSearch.h"			//	查询卡信息
#include "dlg\DlgSettingPaymode.h"		//	当前付款模式
#include "dlg\DlgSettingDiscountPlan.h"	//	折扣计划
#include "dlg\DlgSettingCalculaterRule.h"	//	收费计算相关参数
#include "dlg\DlgSettingStation.h"		//	所有子站的设置
#include "dlg\DlgSettingCardType.h"		//	显示卡种类
#include "dlg\DlgSettingGroupType.h"	//	显示组种类
#include "dlg\DlgSettingPaymodeType.h"	//	付款种类
#include "dlg\DlgSettingCarType.h"		//	车辆种类
#include "dlg\DlgSettingReceiptFormat.h"
#include "dlg\DlgSettingPermission.h"	//	各个功能的授权情况
#include "dlg\DlgSettingOTPReader.h"	//	八达通设置
#include "dlg\DlgSettingSysParameters.h"//	显示系统基本设置

#include "dlg\DlgViewOtpCard.h"			//	查询八达通卡信息
#include "dlg\DlgViewKdeCard.h"			//	查询KDE卡信息
#include "setting.h"
#include "dlg\DlgPaymentAccount.h"
#include "dlg\dlgtrymnt.h"				//检测与管理站的通讯

#include "dlg\DlgOTP4Record.h"				//Last4record

#include "MainFrm.h"
#include "..\\helpCashier\\htmlhelp.h"
#pragma comment(lib, "..\\helpCashier\\htmlhelp.lib")
#pragma message("Automatic link the htmlhelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CRegistry *		g_pReg;
extern CDialog *		g_pDlg;
extern _System			g_System;
extern CLog *			g_pLog;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const UINT ID_RA_MSG =::RegisterWindowMessage(ra_MSG);

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_OPERATOR_BAR, OnViewOperatorBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPERATOR_BAR, OnUpdateViewOperatorBar)
	ON_COMMAND(ID_VIEW_TIME_BAR, OnViewTimeBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TIME_BAR, OnUpdateViewTimeBar)
	ON_COMMAND(ID_SETTING_SYSTEM, OnSettingSystem)
	ON_COMMAND(ID_SETTING_TRYOTPREADER, OnSettingOtpReader)
	ON_COMMAND(ID_EVENT_LOG, OnEventLog)
	ON_COMMAND(ID_CALCULATE, OnCalculate)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateViewStatusBar)
	ON_COMMAND(ID_SETTING_FEERATE, OnSettingFeeRate)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SETTING_CARDCATEGORY, OnSettingCardcategory)
	ON_COMMAND(ID_CARD_SEARCH, OnCardSearch)
	ON_COMMAND(ID_SETTING_PAYMODE, OnSettingPaymode)
	ON_COMMAND(ID_SETTING_DISCOUNTPLAN, OnSettingDiscountplan)
	ON_COMMAND(ID_SETTING_CALCULATERULE, OnSettingCalculaterule)
	ON_COMMAND(ID_SETTING_STATION, OnSettingStation)
	ON_COMMAND(ID_SETTING_CARDTYPE, OnSettingCardtype)
	ON_COMMAND(ID_SETTING_GROUPTYPE, OnSettingGrouptype)
	ON_COMMAND(ID_SETTING_PAYMODETYPE, OnSettingPaymodetype)
	ON_COMMAND(ID_SETTING_CARTYPE, OnSettingCartype)
	ON_COMMAND(ID_TRY_MNT, OnTryMnt)
	ON_COMMAND(ID_VIEW_ACCOUNT, OnViewAccount)
	ON_COMMAND(ID_SETTING_RECEIPT_FORMAT, OnSettingReceiptFormat)
	ON_COMMAND(ID_SETTING_PERMISSION, OnSettingPermission)
	ON_COMMAND(ID_SETTING_SYS_PARAMETERS, OnSettingSysParameters)
	ON_COMMAND(ID_TOOL_VIEW_KDE_CARD, OnToolViewKdeCard)
	ON_COMMAND(ID_TOOL_VIEW_OTP_CARD, OnToolViewOtpCard)
	ON_COMMAND(ID_CARD_CREATE, OnCardCreate)
	ON_COMMAND(ID_CARD_TOPUP, OnCardTopup)
	ON_COMMAND(ID_MNT_SET_START, OnMntSetStart)
	ON_COMMAND(ID_MNT_SET_STOP, OnMntSetStop)
	ON_COMMAND(ID_KDE_SET_START, OnKdeSetStart)
	ON_COMMAND(ID_KDE_SET_STOP, OnKdeSetStop)
	ON_COMMAND(ID_OTP_SET_START, OnOtpSetStart)
	ON_COMMAND(ID_OTP_SET_STOP, OnOtpSetStop)
	ON_COMMAND(ID_SETTING_OTP_READER, OnSettingOtpReader)
	ON_COMMAND(ID_OTP_RECORD, OnOtpRecord)
	//}}AFX_MSG_MAP
//	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
//	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
//	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_REGISTERED_MESSAGE(ID_RA_MSG, OnRaMsg)
	ON_MESSAGE(WM_USER_SETCOMMSTATUS, OnSetCommStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
	g_System.RunTime.hMainFrame = NULL;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 300, 300), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	m_wndView.OnInitialUpdate();

	//允许移动工具栏
	EnableDocking(CBRS_ALIGN_ANY);

	//主工具栏
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//显示通讯状态工具栏
	if (!m_wndToolBarStatus.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarStatus.LoadToolBar(IDR_STATUS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//初始设置
//	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)111);//停止
	if (CCmdOtp::IsConnection()) OnSetCommStatus(0, 222);
	else OnSetCommStatus(0, 212);
	m_wndToolBarStatus.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarLeftOf(&m_wndToolBarStatus ,&m_wndToolBar );

	//显示时间工具栏	
	if (!m_wndToolBarTime.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarTime.LoadToolBar(IDR_TIME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.GetToolBarCtrl().SetState(ID_FILE_NEW,TBSTATE_HIDDEN);


	int pos = m_wndToolBarTime.CommandToIndex(ID_CURRENT_TIME);
	CRect rect;
	m_wndToolBarTime.GetItemRect(pos,&rect);
	m_ZZClockTextClock.Create(_T("hihi"),WS_CHILD|WS_VISIBLE,rect,&m_wndToolBarTime,ID_CURRENT_TIME);
	m_ZZClockTextClock.Start();
	m_wndToolBarTime.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	DockControlBarLeftOf(&m_wndToolBarTime ,&m_wndToolBarStatus );
	
	//显示操作员工具栏
	if (!m_wndToolBarOperator.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarOperator.LoadToolBar(IDR_OPERATOR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	CRect rectTemp;
	m_wndToolBarOperator.GetItemRect(pos,&rectTemp);
	m_ZZTitleStaticOperator.Create(_T("hihi"),WS_CHILD|WS_VISIBLE,rect,&m_wndToolBarOperator,ID_CURRENT_TIME);

	m_ZZTitleStaticOperator.SetBackgroundColor(RGB(010,010,010));
	m_ZZTitleStaticOperator.SetTextColor(RGB(255,255,255));
	m_ZZTitleStaticOperator.SetTextColor(RGB(255,255,255), TRUE);
	m_ZZTitleStaticOperator.SetMargins(1, 0, TRUE);
	m_ZZTitleStaticOperator.SetMargins(58, 18);
	m_ZZTitleStaticOperator.SetWindowText(g_System.Operator.CurUserLevel, TRUE);
	m_ZZTitleStaticOperator.SetWindowText(g_System.Operator.CurUserName);
	m_wndToolBarOperator.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	DockControlBarLeftOf(&m_wndToolBarOperator ,&m_wndToolBarTime );
//ShowControlBar(&m_wndToolBarStatus, FALSE, FALSE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.cx = 800;
	cs.cy = 600;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	ShowOwnedPopups(FALSE);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::DockControlBarLeftOf(CControlBar *Bar, CControlBar *LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout(TRUE);

	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP: n;
	n = (dw&CBRS_ALIGN_BOTTOM&& n==0) ? AFX_IDW_DOCKBAR_BOTTOM: n;
	n = (dw&CBRS_ALIGN_LEFT&& n==0) ? AFX_IDW_DOCKBAR_LEFT: n;
	n = (dw&CBRS_ALIGN_RIGHT&& n==0) ? AFX_IDW_DOCKBAR_RIGHT: n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line. By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

void CMainFrame::OnUpdateViewOperatorBar(CCmdUI* pCmdUI) 
{
	BOOL bVisible = ((m_wndToolBarOperator.GetStyle() & WS_VISIBLE) != 0);
	pCmdUI->SetCheck(bVisible);
}
void CMainFrame::OnUpdateViewTimeBar(CCmdUI* pCmdUI) 
{
	BOOL bVisible = ((m_wndToolBarTime.GetStyle() & WS_VISIBLE) != 0);
	pCmdUI->SetCheck(bVisible);
}
void CMainFrame::OnViewOperatorBar() 
{
	BOOL bVisible = ((m_wndToolBarOperator.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndToolBarOperator, !bVisible, FALSE);
	RecalcLayout();
}
void CMainFrame::OnViewTimeBar() 
{
	BOOL bVisible = ((m_wndToolBarTime.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndToolBarTime, !bVisible, FALSE);
	RecalcLayout();
}

LRESULT CMainFrame::OnRaMsg(WPARAM wParam, LPARAM lParam)
{
	SetForegroundWindow();
	ShowWindow(SW_RESTORE);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
//	状态显示灯
LRESULT CMainFrame::OnSetCommStatus(WPARAM wParam, LPARAM lParam)
{
// lParam :contain the value of status change;
// 1 = stop, 2 = normal, 3 = busy, 4 = error, 5 = dont change;
	CString s;
	s.Format("%03d",lParam);
	char cMNT, cOTP, cKDE;
	cMNT = s[0];
	cOTP = s[1];
	cKDE = s[2];

	UINT StateStop, StateNormal, StateError, StateBusy;

	if (cMNT != '5')
	{
		StateStop =	StateNormal = StateBusy = StateError = TBSTATE_HIDDEN;
		if (cMNT == '4')
			StateError =	TBSTATE_ENABLED;
		else if (cMNT == '3')
			StateNormal =	TBSTATE_ENABLED;
		else if (cMNT == '2')
			StateNormal =	TBSTATE_ENABLED;
		else   //cMNT == '1'
			StateStop =		TBSTATE_ENABLED;

		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_MNT_STOP,StateStop);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_MNT_NORMAL,StateNormal);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_MNT_BUSY,StateBusy);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_MNT_ERROR,StateError);
	}

	if (cKDE != '5')
	{
		StateStop =	StateNormal = StateBusy = StateError = TBSTATE_HIDDEN;
		if (cKDE == '4')
			StateError =	TBSTATE_ENABLED;
		else if (cKDE == '3')
			StateNormal =	TBSTATE_ENABLED;
		else if (cKDE == '2')
			StateNormal =	TBSTATE_ENABLED;
		else   //cKDE == '1'
			StateStop =		TBSTATE_ENABLED;

		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_KDE_STOP,StateStop);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_KDE_NORMAL,StateNormal);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_KDE_BUSY,StateBusy);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_KDE_ERROR,StateError);
	}

	if (cOTP != '5')
	{	
		StateStop =	StateNormal = StateBusy = StateError = TBSTATE_HIDDEN;
		if (cOTP == '4')
			StateError =	TBSTATE_ENABLED;
		else if (cOTP == '3')
			StateNormal =	TBSTATE_ENABLED;
		else if (cOTP == '2')
			StateNormal =	TBSTATE_ENABLED;
		else   //cOTP == '1'
			StateStop =		TBSTATE_ENABLED;

		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_OTP_STOP,StateStop);
//		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_OTP_NORMAL,StateNormal);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_OTP_BUSY,StateBusy);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_OTP_ERROR,StateError);
		m_wndToolBarStatus.GetToolBarCtrl().SetState(ID_STATUS_OTP_NORMAL,StateNormal);
	}
	return 0;
}

void CMainFrame::OnCalculate() 
{
	SHELLEXECUTEINFO Info;
	ZeroMemory(&Info, sizeof(Info));
	Info.cbSize = sizeof(Info);
	Info.lpVerb = "open";
	Info.lpFile = "calc.exe";
	Info.lpParameters = "";
	Info.fMask = SEE_MASK_NOCLOSEPROCESS;
	Info.nShow = SW_SHOWDEFAULT;
	if (!ShellExecuteEx(&Info))
		::AfxMessageBox ("Create process fail",MB_SYSTEMMODAL);
}

void CMainFrame::OnViewStatusBar() 
{
	BOOL bVisible = ((m_wndToolBarStatus.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndToolBarStatus, !bVisible, FALSE);
	RecalcLayout();
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI* pCmdUI) 
{
	BOOL bVisible = ((m_wndToolBarStatus.GetStyle() & WS_VISIBLE) != 0);
	pCmdUI->SetCheck(bVisible);
}

void CMainFrame::OnHelp() 
{
	// 设置显示的初始页面
	//strPath += "::a.htm";
	char cCommandLine[MAX_PATH];
	::strcpy(cCommandLine, g_System.RunTime.sHelpFilePath);
	// 显示CHM帮助文件
	HtmlHelp(GetSafeHwnd(), cCommandLine, HH_DISPLAY_TOPIC, 0);	
}

void CMainFrame::OnClose() 
{
	CSetting * pSettings = CSetting::Instance();	//logout the program
	
  	if (pSettings->m_Account.GetHasAccount())
	{
		if(IDOK != MessageBox(LoadS(IDS_STRING_EXITSYS), LoadS(SYS_MSG_WARNING),MB_OKCANCEL))
			return;
	}

	CDlgLogin dlgLogin;
	
	CCmdJmdm * pkde = CCmdJmdm::Instance();  //
//	CCmdKde * pkde = CCmdKde::Instance();  //
	CCustomer * pCustomer = new CCustomer;
	pkde->CloseKDE();// [cc temp]060803 deleted for test  

//	pCustomer -> CBase::OTPstop();
//	Customer::OTPstop()
	CCmdOtp * potp = CCmdOtp::Instance();
//	potp->Stop();
	potp->OTP_StopRead(true);

//	CCmdOtp::OTP_Sleep(1);

	if(FindWindow(NULL,"登錄/登出")) return;//[cc]0825 
	int nResponse = dlgLogin.DoModal();
	if (nResponse == IDOK)
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Login successful."));
		pkde->OpenKDE();  //[JC]20060309  SOLVE the logout could pay problem 002  [cc temp]060803 deleted for test 

		//		potp->Start();
//		showTip("叫╃笷硄┪础合...");
		showTip("叫╃笷硄┪苯核兵絏布...", true, false); //UCH 3-barcode message tips
		potp->OTP_StopRead(false);

		return;
	}
	CFrameWnd::OnClose();	
}
////////////////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnViewAccount() 
{	//	查看当前帐目
	CDlgPaymentAccount * pDlg = new CDlgPaymentAccount;
	pDlg->Create(CDlgPaymentAccount::IDD);
	pDlg->ShowWindow(SW_SHOW);

}

void CMainFrame::OnSettingFeeRate() 
{	//	收费标准
	CDlgRate * pDlg = new CDlgRate;
	pDlg->Create(CDlgRate::IDD);
	pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnSettingOtpReader() 
{	//	八达通设置
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	操作员忙
	CDlgSettingOtpReader Dlg;
	Dlg.DoModal();
	ReleaseMutex(g_System.m_OprBusyMutex);					//	操作员闲
}
void CMainFrame::OnSettingSystem() 
{	//	系统设置
	CDlgSetting * pDlg = new CDlgSetting;
	pDlg->Create(CDlgSetting::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingReceiptFormat() 
{	// 打印机格式
	CDlgSettingReceiptFormat * pDlg = new CDlgSettingReceiptFormat;
	pDlg->Create(CDlgSettingReceiptFormat::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnEventLog() 
{	//	日志
	CDlgEventLog * pDlg = new CDlgEventLog;
	pDlg->Create(CDlgEventLog::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingCardcategory() 
{	//显示卡类别
	CDlgCardCategory * pDlg = new CDlgCardCategory;
	pDlg->Create(CDlgCardCategory::IDD);
	pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnSettingPermission() 
{	//各个功能的授权情况.
	CDlgSettingPermission * pDlg = new CDlgSettingPermission;
	pDlg->Create(CDlgSettingPermission::IDD);
	pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnCardSearch() 
{	//查询卡信息
	CDlgCardSearch * g_pDlg = new CDlgCardSearch;
	g_pDlg->Create(CDlgCardSearch::IDD);
	g_pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnSettingPaymode() 
{	//显示当前付款模式
	CDlgSettingPaymode * g_pDlg = new CDlgSettingPaymode;
	g_pDlg->Create(CDlgSettingPaymode::IDD);
	g_pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnSettingDiscountplan() 
{	//折扣计划
	CDlgSettingDiscountPlan * pDlg = new CDlgSettingDiscountPlan;
	pDlg->Create(CDlgSettingDiscountPlan::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingCalculaterule() 
{	//收费计算相关参数
	CDlgSettingCalculaterRule * pDlg = new CDlgSettingCalculaterRule;
	pDlg->Create(CDlgSettingCalculaterRule::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingStation() 
{	//所有子站的设置
	CDlgSettingStation * pDlg = new CDlgSettingStation;
	pDlg->Create(CDlgSettingStation::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingCardtype() 
{	//显示卡种类
	CDlgSettingCardType * pDlg = new CDlgSettingCardType;
	pDlg->Create(CDlgSettingCardType::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingGrouptype() 
{	//显示组种类
	CDlgSettingGroupType * pDlg = new CDlgSettingGroupType;
	pDlg->Create(CDlgSettingGroupType::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingSysParameters() 
{	//显示系统基本设置
	CDlgSettingSysParameters *pDlg = new CDlgSettingSysParameters;
	pDlg->Create(CDlgSettingSysParameters::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnSettingPaymodetype() 
{	//付款种类
	CDlgSettingPaymodeType * pDlg = new CDlgSettingPaymodeType;
	pDlg->Create(CDlgSettingPaymodeType::IDD);
	pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnSettingCartype() 
{	//车辆种类
	CDlgSettingCarType * pDlg = new CDlgSettingCarType;
	pDlg->Create(CDlgSettingCarType::IDD);
	pDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnTryMnt() 
{	//检测与管理站的通讯
	CDlgTryMnt * pDlg = new CDlgTryMnt;
	pDlg->Create(CDlgTryMnt::IDD);
	pDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnToolViewOtpCard() 
{
	//查询八达通卡信息
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	操作员忙
	CDlgViewOtpCard Dlg;
	Dlg.DoModal();
	ReleaseMutex(g_System.m_OprBusyMutex);	
}
void CMainFrame::OnToolViewKdeCard() 
{
	//查询KDE卡信息
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	操作员忙
	CDlgViewKdeCard Dlg;
	Dlg.DoModal();
	ReleaseMutex(g_System.m_OprBusyMutex);	
}
void CMainFrame::OnMntSetStart() 
{	//开始与管理站的通讯
	/*const CString Caption = "Start communicate with 'MNT'";
	const CString Msg = LPCTSTR(CONFIRM_MNT_START);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_YESNO) )
	{
		CCmdMntRecv * pCmdMntRecv = CCmdMntRecv::Instance();
		pCmdMntRecv->Start();
		CCmdMntSend * pCmdMntSend = CCmdMntSend::Instance();
		pCmdMntSend->Start();
		::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)255);//空闲
	}*/
}

void CMainFrame::OnMntSetStop() 
{	//结束与管理站的通讯
	/*const CString Caption = "Stop communicate with 'MNT'";
	const CString Msg = LPCSTR(CONFIRM_MNT_STOP);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONEXCLAMATION | MB_YESNO) )
	{
		CCmdMntRecv * pCmdMntRecv = CCmdMntRecv::Instance();
		pCmdMntRecv->Stop();
		CCmdMntSend * pCmdMntSend = CCmdMntSend::Instance();
		pCmdMntSend->Stop();
		::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)155);//停止
	}*/
}

void CMainFrame::OnKdeSetStart() 
{	//开始与KDE读卡器的通讯
	/*const CString Caption = "'KDE' reader start";
	const CString Msg = LPCSTR(CONFIRM_KDE_START);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_YESNO) )
	{
		CCmdKde * pCmd = CCmdKde::Instance();
		pCmd->Start();
	}*/	
}

void CMainFrame::OnKdeSetStop() 
{	//停止与KDE读卡器的通讯
	/*const CString Caption = "'KDE' reader stop";
	const CString Msg = LPCTSTR(CONFIRM_KDE_STOP);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_YESNO) )
	{
		CCmdKde * pCmd = CCmdKde::Instance();
		pCmd->Stop();
	}*/		
}

void CMainFrame::OnOtpSetStart() 
{	//开始与八达通读卡器的通讯
	//开始与KDE读卡器的通讯
	const CString Caption = "'OTP' reader start";
	const CString Msg = LPCTSTR(CONFIRM_OTP_START);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_YESNO) )
	{
		CCmdOtp * pCmd = CCmdOtp::Instance();
		pCmd->Start();
	}		
}

void CMainFrame::OnOtpSetStop() 
{	//停止与八达通读卡器的通讯
	const CString Caption = "'OTP' reader stop";
	const CString Msg = LPCTSTR(CONFIRM_OTP_STOP);
	if ( IDYES == MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_YESNO) )
	{
		CCmdOtp * pCmd = CCmdOtp::Instance();
		pCmd->Stop();
	}			
}

void CMainFrame::OnCardCreate() 
{
	// TODO: Add your command handler code here
	if (WaitForSingleObject(g_System.m_OprBusyMutex, 1000) == WAIT_TIMEOUT)
	{
		showTip("笷硄矪瞶い, 礚猭ㄏノ承疭! 叫р笷硄ǐ", TRUE, FALSE);
		return;
	}
	CCustomer::CCreateSpecialCard addspeccard;
	addspeccard.Trade();
//	showTip("叫╃笷硄┪础合...", true, false);
	showTip("叫╃笷硄┪苯核兵絏布...", true, false); //UCH 3-barcode message tips
	ReleaseMutex(g_System.m_OprBusyMutex);
}
 
void CMainFrame::OnCardTopup() 
{
	// TODO: Add your command handler code here
	if (WaitForSingleObject(g_System.m_OprBusyMutex, 1000) == WAIT_TIMEOUT)
	{
		showTip("笷硄矪瞶い, 礚猭ㄏノ承疭! 叫р笷硄ǐ", TRUE, FALSE);
		return;
	}
	CCustomer::CCreateSpecialCard addspeccard(true);
	addspeccard.Trade();
//	showTip("叫╃笷硄┪础合...", true, false);
	showTip("叫╃笷硄┪苯核兵絏布...", true, false); //UCH 3-barcode message tips
	ReleaseMutex(g_System.m_OprBusyMutex);	
}


void CMainFrame::OnOtpRecord() 
{
	CDlgOTP4Record dlg;
	if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 500))
	{
//		showTip("笷硄矪瞶い, 礚猭ㄏノ糤! 叫р笷硄ǐ", true);
		return;
	}
//	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(false);

	if(IDOK!=dlg.DoModal())
	{
		return;
	}
	
	ReleaseMutex(g_System.m_OprBusyMutex);	
//	showTip("叫╃笷硄┪础合...", true, false);
//	GetDlgItem(IDC_OTP_CARD_ADD_VALUE)->EnableWindow(true);
	Sleep(1000);
}

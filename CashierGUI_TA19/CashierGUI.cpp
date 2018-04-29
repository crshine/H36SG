// CashierGUI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CashierGUI.h"

#include "MainFrm.h"
#include "dlg\DlgSplash.h"	// ��������
#include "dlg\dlglogin.h"	// ��½
#include "dlg\dlgmessage.h"	// ��½
#include "Setting.h"		// ϵͳ����趨
#include "Customer.h"		// ���ֹ˿�
#include "CmdMntRecv.h"		// �����վͨѶ���ղ���
#include "CmdMntSend.h"		// �йع���վ����(����)
//#include "CmdKde.h"			// KDE������
#include "CmdJmdm.h"		
#include "CmdOtp.h"
#include "CmdPrint.h"
#include "CmdLcd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef int (CALLBACK* LPFNDLLFUNC1)(UINT,char vv[30]); 
typedef UINT (CALLBACK* LPFNDLLFUNC3)(int *days); 

const UINT ID_RA_MSG =::RegisterWindowMessage(ra_MSG);

//ȫ�ֱ���
CRegistry *		g_pReg=NULL;
CLog *			g_pLog=NULL;
CString			g_sAppPath;
CDialog *		g_pDlg=NULL;
CSetting *		g_Setting = CSetting::Instance();
struct _System  g_System;


CString show(const short i)
{
	CString s;
	s.Format("%d", i);
	return s;
}

CString show(const long i)
{
	CString s;
	s.Format("%d", i);
	return s;
}

CString show(const unsigned int i)
{
	CString s;
	s.Format("%d", i);
	return s;
}

CString show(const double d)
{	//�����ʾ'���'���ַ���
	CString s;
	s.Format("%.2f",d);
	s = "$" + s;
	return s;
}

CString show(const COleDateTime t)
{
	CString s;
	s = t.Format((CString)(LPCSTR)SYS_SHOW_DATETIME);
	return s;
}

CString showPercentage(const double d)
{	//�����ʾ'�ٷ���'���ַ���
	CString s;
	s.Format("%.0f",d * 100);
	s = s + '%';
	return s;
}

CString showDate(const COleDateTime t)
{
	CString s;
	s = t.Format((CString)(LPCSTR)SYS_SHOW_DATE);
	return s;
}
CString showHHMMSS(const COleDateTime t)
{
	CString s;
	s = t.Format((CString)(LPCSTR)SYS_SHOW_HHMMSS);
	return s;
}
CString showDayOfWeek(const short DayOfWeek)
{
	ASSERT((DayOfWeek >= 0) && (DayOfWeek <= 7));
	CString s;
	switch(DayOfWeek)
	{
		case 1:		s = "Sunday";		break;
		case 2:		s = "Monday";		break;
		case 3:		s = "Tuesday";		break;
		case 4:		s = "Wednesday";	break;
		case 5:		s = "Thursday";		break;
		case 6:		s = "Friday";		break;
		case 7:		s = "Saturday";		break;
		default:	s = "Undefine";
	}
	return s;
}

CString show(const COleDateTimeSpan ts)
{	//�����ʾ'ʱ���'���ַ���
	const COleDateTimeSpan aDay(1,0,0,0), anHour(0,1,0,0);

	if (anHour > ts)
		return ts.Format("%M mins");
	else if (aDay > ts)
		return ts.Format("%H Hours %M");
	else
		return ts.Format("%D Days, %H : %M");
}

CString show(const CString s)
{
	return s;
}
CString g_cszString;
CString LoadS(UINT nID)
{
	int nSize = 0;
    int nLen = -1;

    g_cszString.Empty();
    nSize += 255;
    //Load String Resource
    nLen = ::LoadString( GetModuleHandle(NULL), nID,
                            g_cszString.GetBuffer(nSize-1), nSize);
	g_cszString.ReleaseBuffer();
    return g_cszString;
}

CString show(CDiscount dis)
{
	return dis.GetDescription();
}

CString show(const bool b)
{
	return (b ? "True" : "False");
}
CString showSpecialCardTypeName(const short ID)
{
	if (ID == 0) return "Hourly"; //"�ɯ���";
	if (ID == 7) return "Damage"; //"�l�a��"; // [BW] 20051003 changed 6 -> 7 
	if (ID == 8) return "Lost"; //"�򥢲�";   // [BW] 20051003 changed 7 -> 8 
//	if (ID == 8) return "VIP"; //"VIP��";
	CSetting * pSetting = CSetting::Instance();
	CString s;
	if ( !pSetting->m_CardType.Valid(ID) )
		s = "";
	else
		s = pSetting->m_CardType.Name(ID);
	return s;
}
CString showVehicleTypeName(const short ID)
{
	CSetting * pSetting = CSetting::Instance();
	CString s;
	if ( !pSetting->m_VehicleType.Valid(ID) )
		s = "Common Card";
	else
		s = pSetting->m_VehicleType.Name(ID);
	return s;
}
CString showStationID(const short ID)
{
	CString s;
	s.Format("%02d", ID);
	return s;
}
CString showStationName(const short ID)
{
	CSetting * pSetting = CSetting::Instance();
	CString s;
	if ( !pSetting->m_StationInformation.Valid(ID) )
		s = "Invalid station";
	else
		s = pSetting->m_StationInformation.StationName(ID);
	return s;
}
CString showStationTypeName(const short ID)
{
	CString s;
	switch (ID)
	{
	case 1: 
		s = "Entry"; break;
	case 2: 
		s =  "Exit"; break;
	case 3: 
		s =  "Autopay"; break;
	case 4: 
		s =  "Cashier"; break;
	default: 
		s =  "Undefine";
	}
	return s;	
}
//������ʾ��Ϣ���û����档
void showTip(LPCTSTR Tip, bool urgent, bool wmode)
{
	DWORD x = (!wmode ? 0:1);
	if (NULL != g_System.RunTime.hOtpPaymentDlg)
	{
		if (!urgent)
			::PostMessage(g_System.RunTime.hOtpPaymentDlg, WM_USER_TIP, (WPARAM)Tip, (LPARAM)x);
		else{
			::SendMessage(g_System.RunTime.hOtpPaymentDlg, WM_USER_TIP, (WPARAM)Tip, (LPARAM)x);
			CWnd * x = ::AfxGetMainWnd()->FromHandle(g_System.RunTime.hOtpPaymentDlg);
			x->Invalidate();
			x->UpdateWindow();
		}
	}
}


bool IsBigger(const COleDateTime BigDate, const COleDateTime SmallDate)
{
	static COleDateTimeSpan tsOneSec;
	tsOneSec.SetDateTimeSpan(0,0,0,1);
	COleDateTimeSpan ts = BigDate - SmallDate;
	return (ts > tsOneSec ? true : false);
}
/////////////////////////////////////////////////////////////////////////////
_System::_System()
{
	m_OprBusyMutex = CreateMutex(NULL, FALSE, NULL);
}
/////////////////////////////////////////////////////////////////////////////

CDialog * CCashierGUIApp::g_pDlgMessage = NULL;// ��Ϣ�Ի���ָ��
void CCashierGUIApp::ShowMessage(CString sMsg)// ��ʾ��Ϣ
{
	if(g_pDlgMessage==NULL)
	{
		g_pDlgMessage=new CDlgMessage;
		g_pDlgMessage->Create(IDD_MESSAGEBOX);
		g_pDlgMessage->ShowWindow(SW_SHOW);
		g_pDlgMessage->CenterWindow();
	}
	else
	{
		g_pDlgMessage->ShowWindow(SW_SHOW);
	}
	g_pDlgMessage->BringWindowToTop();
	g_pDlgMessage->SetDlgItemText(IDC_STATIC_MESSAGE, sMsg);
}
/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp

BEGIN_MESSAGE_MAP(CCashierGUIApp, CWinApp)
	//{{AFX_MSG_MAP(CCashierGUIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_STATUS_MNT_STOP, OnMntSetStart)
	ON_COMMAND(ID_STATUS_MNT_NORMAL, OnMntSetStop)
	ON_COMMAND(ID_STATUS_MNT_BUSY, OnNULL)
	ON_COMMAND(ID_STATUS_MNT_ERROR, OnMntSetStart)
	ON_COMMAND(ID_STATUS_OTP_STOP, OnOtpSetStart)
	ON_COMMAND(ID_STATUS_OTP_NORMAL, OnOtpSetStop)
	ON_COMMAND(ID_STATUS_OTP_BUSY, OnNULL)
	ON_COMMAND(ID_STATUS_OTP_ERROR, OnOtpSetStart)
	ON_COMMAND(ID_STATUS_KDE_STOP, OnKdeSetStart)
	ON_COMMAND(ID_STATUS_KDE_NORMAL, OnKdeSetStop)
	ON_COMMAND(ID_STATUS_KDE_BUSY, OnNULL)
	ON_COMMAND(ID_STATUS_KDE_ERROR, OnKdeSetStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp construction

CCashierGUIApp::CCashierGUIApp()
{
	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);	//	����Աæ
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCashierGUIApp object

CCashierGUIApp	theApp;

/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp initialization

BOOL CCashierGUIApp::InitInstance()
{
	//����Ƿ��Ѿ�����
	m_SourceNeedRelease = NoSourceNeedRelease;
	m_hOneInstance = ::CreateMutex( NULL, FALSE, UNIQE_NAME);
	if ( GetLastError() == ERROR_ALREADY_EXISTS )
	{

		DWORD dwRecipients = BSM_APPLICATIONS;
		::BroadcastSystemMessage( BSF_NOHANG,&dwRecipients,
			ID_RA_MSG, // registered window message
			0,0 ); // user defined parameters
		return FALSE;
	}
	m_SourceNeedRelease = SomeSourceNeedRelease;

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif 

	HINSTANCE hLibrary;
	LPFNDLLFUNC1 lpFunc;
	LPFNDLLFUNC3 lpFunc3;
	char hid[20];
	hLibrary=LoadLibrary("HDrv.DLL"); 

	if(hLibrary) //���سɹ� 
	{
		lpFunc=(LPFNDLLFUNC1)GetProcAddress(hLibrary,"CheckHID"); 
		if(lpFunc) 
		{
			if((*lpFunc)(101,hid)!=1972)
			{
				lpFunc3=(LPFNDLLFUNC3)GetProcAddress(hLibrary,"RegCmp"); 
				int days[2];
				if(lpFunc3) 
				if((*lpFunc3)(days)!=1972)
				{
					MessageBox(NULL,"Invalid version,contact with the vendor please!","Error1",0); 
#ifndef _DEBUG
					exit(-1);	
#endif
				}
				else
				{
					CString msg;
					if(days[0]>=10)
					msg.Format("Demo version, You have 30 days for testing.",days[0]);
					else
					msg.Format("Demo version, it will expire after several days! ",days[0]);
					MessageBox(NULL,msg,"Warning",0); 
				}
			}
		}
		else{
					MessageBox(NULL,"Invalid version,contact with the vendor please.","Error2",0); 
					exit(-1);	
		}
		FreeLibrary(hLibrary); 
	} 
	else{
		MessageBox(NULL,"Library file missing, the program will exit!","Error",0); 
 		exit(-1);	
	}	
	
	// ��������
	CDlgSplash *m_pSplashWindow = new CDlgSplash;
	m_pSplashWindow->Create(IDD_SPLASH);
	m_pSplashWindow->CenterWindow();
	m_pSplashWindow->ShowWindow(SW_SHOW);
	DWORD starttick = GetTickCount();
	m_pSplashWindow->ShowText("System initial...");
	//ȡ��Ӧ�ó���·��
    GetModuleFileName(NULL, g_sAppPath.GetBuffer(MAX_PATH), MAX_PATH);
    g_sAppPath.ReleaseBuffer();
    int n = g_sAppPath.ReverseFind('\\');
    g_sAppPath = g_sAppPath.Left(n);

	// ϵͳ��־ģ��
	try { g_pLog = new CLog; }
	catch (...) 
	{AfxMessageBox(_T("can not find file EventLog.dll"));
	//ɾ����������
	delete m_pSplashWindow;
	return false;}
	g_pLog->SetLogPath(g_sAppPath+_T("\\Log"));
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("System initialize"));
	TRACE("ϵͳ��־ģ����سɹ�\n");
	m_pSplashWindow->ShowText("Load Log model successful...");
	::Sleep(1);

	// ��ȡע�����Ϣ
	try { g_pReg = new CRegistry(DEFAULT_REGISTRY_PATH); }
	catch (...) 
	{AfxMessageBox(_T("can not find file Registry.dll"));
	//ɾ����������
	delete m_pSplashWindow;
	return false;}
	TRACE("��ȡע�����Ϣ\n");
	m_pSplashWindow->ShowText("Load Registry model successful...");
	::Sleep(10);
	SerializeReg();

	//��ȡϵͳ����
	TRACE("��ȡϵͳ����\n");
	g_Setting->Load();
	::Sleep(10);
 
	//�����վ��ͨѶ�߳�----����
	TRACE("�����վ��ͨѶ�߳�----����\n");
	CCmdMntRecv* pCmdMntRecv = CCmdMntRecv::Instance();
	m_pSplashWindow->ShowText("Communication with Management recv model successful...");
	if (!pCmdMntRecv->Start())
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("socket listen start failure!"));
		AfxMessageBox(_T("Socket listen start failure!\n\nPlease check the setting of system!"));
	}
	::Sleep(10);

	m_pSplashWindow->ShowText("Communication with Management send model sucessful...");
	//�����վ��ͨѶ�߳�----����
	TRACE("�����վ��ͨѶ�߳�----����\n");
	::Sleep(10);
	CCmdMntSend* pCmdMntSend = CCmdMntSend::Instance();
	if (!pCmdMntSend->Start())
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Start communication with management thread failure!"));
		AfxMessageBox(_T("Start communication with management thread failure!\n\nPlease check the setting of system!"));
	}

	//��½�Ի���
	m_pSplashWindow->ShowText("Waiting for operator login...");
	CDlgLogin dlgLogin;
//	CDlgTest dlgLogin;
	int nResponse = dlgLogin.DoModal();
	if (nResponse == IDOK)
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Login successful."));
		pCmdMntSend->TimeSynchronize(); //make the time synchronize at start up.
	}
	else if (nResponse == IDCANCEL)
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Login failure!"));
		//ɾ����������
		delete m_pSplashWindow;
		return false;
	}
	TRACE("��½�Ի������\n");
	::Sleep(10);


	//Һ����ʾ��
	m_pSplashWindow->ShowText("LCD support start...");
	CCmdLcd* pCmdLcd = CCmdLcd::Instance();
	pCmdLcd->Start();
	pCmdLcd->LCD_DisplayIdle();
	TRACE("Һ����ʾ��\n");
	::Sleep(10);

#ifndef _DEBUG
	//�˴�ͨ������
	TRACE("�˴�ͨ������\n");
	m_pSplashWindow->ShowText("Try Communication with OtpReader...");
	CCmdOtp* pCmdOtp = CCmdOtp::Instance();
	if (!pCmdOtp->Start())
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Start communication with OtpReader thread failure!"));
		m_pSplashWindow->ShowText(_T("Start communication with OtpReader thread failure!\n\nPlease check the setting of system!"));
	}
	m_pSplashWindow->ShowText("Communication with OtpReader successful...");
	::Sleep(500);
#endif

	//Barcode������
	TRACE("Barcode������\n");
	m_pSplashWindow->ShowText("Try Communication with Barcode Reader...");
	CCmdJmdm* pCmdKde = CCmdJmdm::Instance();
	if (!pCmdKde->Start())
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Start communication with Barcode Reader thread failure!"));
		AfxMessageBox(_T("Start communication with Barcode Reader thread failure!\n\nPlease check the setting of system!"));
	}
	m_pSplashWindow->ShowText("Communication with Barcode Reader successful...");
	::Sleep(500);

/*	
	//KDE������
	TRACE("KDE������\n");
	m_pSplashWindow->ShowText("Try Communication with KDEReader...");
	CCmdKde* pCmdKde = CCmdKde::Instance();
	if (!pCmdKde->Start())
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Start communication with KDEReader thread failure!"));
		AfxMessageBox(_T("Start communication with KDEReader thread failure!\n\nPlease check the setting of system!"));
	}
	m_pSplashWindow->ShowText("Communication with KDEReader successful...");
	::Sleep(500);
*/
#ifndef _DEBUG

	//��ӡ��
	TRACE("���ش�ӡ��\n");
	m_pSplashWindow->ShowText("Try initialize the 'Receipt Printer'...");
	CSetting * pSetting = CSetting::Instance();
	if ((pSetting->m_Receipt.TaxName() == "") || (pSetting->m_Receipt.TaxName() == ""))
	{
		m_pSplashWindow->ShowText("Initialize the receipt printer failure...");
		AfxMessageBox(_T("Initialize the receipt printer failure!\n\nPlease check the setting of receipt printer!"));
	}
	else
	{
//		CCmdPrint * pCmdPrint = CCmdPrint::Instance();
		m_pSplashWindow->ShowText("Initialize the receipt printer successful...");
	}
	::Sleep(1);
#endif

	
	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//�������
//	AddFontResource(g_System.RunTime.sAppPath + _T("\\LCDN.TTF"));
//	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	//����������ʾ
	TRACE("����������ʾ�ɹ�\n");
	starttick = GetTickCount() - starttick;
//	if (starttick < 1000) Sleep(1000 - starttick);//Delay 4 Second
	m_pSplashWindow->DestroyWindow(); //Destroy Splash Window
	delete m_pSplashWindow;


	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	pFrame->CenterWindow();
	g_System.RunTime.hMainFrame = pFrame->m_hWnd;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	ReleaseMutex(g_System.m_OprBusyMutex);	//	����Ա��

//	showTip("�Щ�K�F�q�d�δ��J�ϥd...", true, false);
	showTip("�Щ�K�F�q�α��˱��X��...", true, false); //UCH 3-barcode message tips
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp message handlers





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCashierGUIApp::OnNULL()
{
	NULL;
}

void CCashierGUIApp::OnMntSetStart()
{
	
	static_cast<CMainFrame *>(m_pMainWnd)->OnMntSetStart();
}
void CCashierGUIApp::OnMntSetStop()
{
	static_cast<CMainFrame *>(m_pMainWnd)->OnMntSetStop();
}
void CCashierGUIApp::OnKdeSetStart()
{
	static_cast<CMainFrame *>(m_pMainWnd)->OnKdeSetStart();
}
void CCashierGUIApp::OnKdeSetStop()
{
	static_cast<CMainFrame *>(m_pMainWnd)->OnKdeSetStop();
}
void CCashierGUIApp::OnOtpSetStart()
{
	static_cast<CMainFrame *>(m_pMainWnd)->OnOtpSetStart();
}
void CCashierGUIApp::OnOtpSetStop()
{
	static_cast<CMainFrame *>(m_pMainWnd)->OnOtpSetStop();
}

// App command to run the dialog
void CCashierGUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp message handlers

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//�������ܣ��ṩ��������������еĻ�������
void CCashierGUIApp::SerializeReg()
{
	//ȡ��Ӧ�ó���·��
	GetModuleFileName(NULL, g_System.RunTime.sAppPath.GetBuffer(MAX_PATH), MAX_PATH);
    g_System.RunTime.sAppPath.ReleaseBuffer();
    g_System.RunTime.sAppPath = g_System.RunTime.sAppPath.Left(g_System.RunTime.sAppPath.ReverseFind('\\'));
	//�����ļ�·��
	g_System.RunTime.sHelpFilePath = g_System.RunTime.sAppPath + "\\help.chm";
	//�������д���
	g_pReg->SetRegistryPath();
	int iRunTimes = g_pReg->ReadIntKey(REG_KEY_SYSTEM_RUN_TIMES, 0);
	iRunTimes++;
	g_pReg->WriteIntKey(REG_KEY_SYSTEM_RUN_TIMES, iRunTimes);
	//��һ������
	//running first time;
	if (1 == iRunTimes){
		//д��Ĭ��ֵ
		g_pReg->WriteSZKey(REG_CASHIERSTATIONNAME,	"Unnamed Station");
		g_pReg->WriteIntKey(REG_CASHIERSTATIONID,	0);
		g_pReg->WriteIntKey(REG_CASHIERSTATIONADDRESSID,	0);
		g_pReg->WriteIntKey(REG_CASHIERSTATIONSENDSOCKETPORT, 6501);
		g_pReg->WriteIntKey(REG_CASHIERSTATIONRECEIVESOCKETPORT, 6500);
		g_pReg->WriteSZKey(REG_CARPARKMANAGEMENTIP,	"127.0.0.1");
		g_pReg->WriteIntKey(REG_CARPARKMANAGEMENTADDRESSID,	0);
	}

	//д������ʱ��
	g_pReg->WriteTMKey(REG_KEY_SYSTEM_START_TIME, CTime::GetCurrentTime());
	//�������ݵ�ȫ�ֱ���
	//ϵͳ����
	//�˴�ͨ������
	//KDE������
	//LCD��ʾ��
	//��ӡ��
	//����ʱ������ʼ��
	g_System.RunTime.hMainFrame = NULL;
	g_System.RunTime.hOtpPaymentDlg = NULL;
}

int CCashierGUIApp::ExitInstance() 
{
//ɾ������
//	RemoveFontResource(g_System.RunTime.sAppPath + _T("\\LCDN.TTF"));
//	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	if (NoSourceNeedRelease == m_SourceNeedRelease) return CWinApp::ExitInstance();
//	TRACE("System normal exit.\n");

	//����ϵͳ����
//	g_Setting->Store();

	SaveSysData();
	SaveReg();

	if(g_pReg) delete g_pReg;

	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
	delete pCmdPrint;
	//
	CCmdJmdm* pCmdKde = CCmdJmdm::Instance();
	delete pCmdKde;
	//
	CCmdOtp* pCmdOtp = CCmdOtp::Instance();
	delete pCmdOtp;
	//
	CCmdMntRecv* pCmdMntRecv = CCmdMntRecv::Instance();
	delete pCmdMntRecv;

	//�����˳�ϵͳ��Ϣ
	CCmdMntSend* pCmdMntSend = CCmdMntSend::Instance();
	pCmdMntSend->OperatorActionLog("System normal exit");
	delete pCmdMntSend;

	//�˳�lcd��ʾ
	CCmdLcd * pCmdLcd = CCmdLcd::Instance();
	pCmdLcd->Stop();
	delete pCmdLcd;
	if(g_pLog)
	{

		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("System normal exit."));
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"));
		delete g_pLog;
	}
	//
	CSetting* pSetting = CSetting::Instance();
	delete pSetting;
	//һ������ʵ��, �ź���
	CloseHandle(m_hOneInstance);
	return CWinApp::ExitInstance();
}

BOOL CCashierGUIApp::SaveSysData()
{
	/*
	 * Ĭ���ļ��� SysFile.dat
	 * ��д���ļ� SysFileTmp.dat
	 * ɾ�����ļ� SysFile.dat
	 * ����       SysFileTmp.dat ��Ϊ SysFile.dat
	 */
/*
	CFile pFile;
	if (!pFile.Open(g_System.RunTime.sAppPath + _T("\\SysFileTmp.dat"), CFile::modeCreate|CFile::modeWrite)) return false;
	char buf[4096];
	USHORT iLen = 0;

	//д������
#define __Serialize(FUNC, TYPE)						\
		pFile.Write(TYPE , sizeof(TYPE)-1);			\
		g_System.m_Rate.FUNC(buf, iLen);			\
		pFile.Write(buf, iLen);						\
		pFile.Write("\r\n" , sizeof("\r\n")-1);

#ifndef _DEBUG
	__Serialize(GetDateRule, "26");//�շѱ�׼,����"����"�ֱ�
#else	
	//	����Ĵ���������ĺ궨���չ��.
	//	���㵥������
	pFile.Write("26" , sizeof("26")-1);
	g_System.m_Rate.GetDateRule(buf, iLen);
	pFile.Write(buf, iLen);
	pFile.Write("\r\n" , sizeof("\r\n")-1);
#endif
	__Serialize(GetGroupRule, "27");//�շѱ�׼,����"����"�ֱ�
	__Serialize(GetVehicleRule, "28");//�շѱ�׼,����"����"�ֱ�
	__Serialize(GetTimezoneRule, "29");//�շѱ�׼,����"ʱ���"�ֱ�
	__Serialize(GetFeeRule, "30");//�շѱ�׼
	__Serialize(GetFixTimeRule, "31");//����涨
#undef __Serialize//__Serialize(FUNC, TYPE)	

	pFile.Close();
	//ɾ�����ļ�
	DeleteFile(g_System.RunTime.sAppPath + _T("\\SysFile.dat"));
	//�����ļ�����.SysFileTmp.dat -> SysFile.dat;
	if (!MoveFileEx(g_System.RunTime.sAppPath + _T("\\SysFileTmp.dat"), g_System.RunTime.sAppPath + _T("\\SysFile.dat"), MOVEFILE_REPLACE_EXISTING)) return false;
	*/
	return true;
}


void CCashierGUIApp::SaveReg()
{
	//�������б���
//	g_pReg->WriteSZKey(REG_CASHIERSTATIONNAME, g_System.Setting_System.CashierStationName);
	//�˴�ͨ������
	//KDE������
	//LCD��ʾ��
	//��ӡ��
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnOK();
}

void CCashierGUIApp::LoadSettings()
{
	//���ļ�
	CFile f;
//	f.Open();
}

void CCashierGUIApp::SaveSettings()
{
	/*
	 * Ĭ���ļ��� SysSettings.dat
	 * ��д���ļ� SysSettingsTmp.dat
	 * ɾ�����ļ� SysSettings.dat
	 * ����       SysSettingsTmp.dat ��Ϊ SysSettings.dat
	 */
/*
	CFile pFile;
	if (!pFile.Open(g_System.RunTime.sAppPath + _T("\\Data\\SysFileTmp.dat"), CFile::modeCreate|CFile::modeWrite)) return ;
	char buf[4096];
	USHORT iLen = 0;

	//д������
#define __Serialize(FUNC, TYPE)						\
		pFile.Write(TYPE , sizeof(TYPE)-1);			\
		g_System.m_Rate.FUNC(buf, iLen);			\
		pFile.Write(buf, iLen);						\
		pFile.Write("\r\n" , sizeof("\r\n")-1);
 
#ifndef _DEBUG
	__Serialize(GetDateRule, "26");//�շѱ�׼,����"����"�ֱ�
#else	
	//	����Ĵ���������ĺ궨���չ��.
	//	���㵥������
	pFile.Write("26" , sizeof("26")-1);
	g_System.m_Rate.GetDateRule(buf, iLen);
	pFile.Write(buf, iLen);
	pFile.Write("\r\n" , sizeof("\r\n")-1);
#endif
	__Serialize(GetGroupRule, "27");//�շѱ�׼,����"����"�ֱ�
	__Serialize(GetVehicleRule, "28");//�շѱ�׼,����"����"�ֱ�
	__Serialize(GetTimezoneRule, "29");//�շѱ�׼,����"ʱ���"�ֱ�
	__Serialize(GetFeeRule, "30");//�շѱ�׼
	__Serialize(GetFixTimeRule, "31");//����涨
#undef __Serialize//__Serialize(FUNC, TYPE)	

	pFile.Close();
	//ɾ�����ļ�
	DeleteFile(g_System.RunTime.sAppPath + _T("\\SysFile.dat"));
	//�����ļ�����.SysFileTmp.dat -> SysFile.dat;
	if (!MoveFileEx(g_System.RunTime.sAppPath + _T("\\SysFileTmp.dat"), g_System.RunTime.sAppPath + _T("\\SysFile.dat"), MOVEFILE_REPLACE_EXISTING)) return ;
	return ;
	*/
}



// dlglogin.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlglogin.h"
#include "..\CmdMntSend.h"

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
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
#ifdef _DEBUG
	m_sOperatorName = _T("NORVASEA");
	m_sPassword = _T("X65536");
#endif
	//}}AFX_DATA_INIT
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Text(pDX, IDC_OPERATORNAME, m_sOperatorName);
	DDV_MaxChars(pDX, m_sOperatorName, 20);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDV_MaxChars(pDX, m_sPassword, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

BOOL CDlgLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg) 
{
	if(WM_KEYDOWN == pMsg->message || WM_KEYUP == pMsg->message)
	{
		if (VK_DOWN == pMsg->wParam)
		{//"DOWN" -> "TAB"
			pMsg->wParam = VK_TAB;	
		}
		else if(VK_UP == pMsg->wParam)
		{//"UP" ->"SHIFT" + "TAB"
			if (WM_KEYDOWN == pMsg->message)
			{	keybd_event(VK_SHIFT,0,0,0);	
				keybd_event(VK_TAB,0,0,0);	}
			else
			{	keybd_event(VK_SHIFT,0,2,0);	
				keybd_event(VK_TAB,0,2,0);	}
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgLogin::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(false);
	AfxGetApp()->BeginWaitCursor();
	ASSERT(g_pLog != NULL);
	UpdateData(true);
	CString info;	
/////////////////////////////////////////////////
	struct LoginInfo{
		char LoginUserName[12];
		char LoginUserPwd[8];
	} _LoginInfo;
	char ChPwd[8];
	char ChName[12];
	CString SPwd;
	CString SName;
	CFile f;
//////////////////////////////////////////////////////////////////////////
//	char ChPwd[8] = "";
//	char ChName[12] = "";

//      strcpy(ChPwd, m_sPassword);
//		strcpy(ChName, m_sOperatorName);


	if (!f.Open(g_System.RunTime.sAppPath + "\\Operator.dat", CFile::modeReadWrite))  // 20060320 [JC]
	{
			
//		_LoginInfo.LoginUserName = "BE    ";
//	   	_LoginInfo.LoginUserPwd  = "12345678";
		
		f.Open("\\Operator.dat", CFile::modeWrite | CFile::modeCreate);
		f.Write(&_LoginInfo, sizeof(_LoginInfo));
		f.Flush();
		f.Close();
		
	}else
	{
		f.Read(&_LoginInfo, sizeof(_LoginInfo));
//		_LoginInfo.LoginUserPwd[9]/0;
//		ChPwd = (_LoginInfo.LoginUserPwd);
//		ChName = (_LoginInfo.LoginUserName);	
		

/*
		ChPwd = _LoginInfo.LoginUserPwd;
		ChPwd.TrimRight();
		ChName = _LoginInfo.LoginUserName;
		ChName.TrimRight();*/
//		strcpy(ChPwd , m_sPassword);
//		strcpy(ChName, m_sOperatorName);

		SName= _LoginInfo.LoginUserName;
		SPwd = _LoginInfo.LoginUserPwd;
		SName.TrimRight();
//		SPwd.Mid(0,2);
//		SName.Mid(0,12);
//		if ((_LoginInfo.LoginUserPwd == ChPwd) && (_LoginInfo.LoginUserName == ChName) )
//		if ((m_sPassword == _LoginInfo.LoginUserPwd) && (m_sOperatorName == _LoginInfo.LoginUserName))
		if ((m_sPassword == SPwd) && (m_sOperatorName == SName))
		{	
			g_System.Operator.CurUserID = m_sOperatorName;
			g_System.Operator.CurUserName = m_sOperatorName;
			g_System.Operator.CurUserPwd = "Operator";
			g_System.Operator.CurUserLevel = "Operator";
			g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
			info.Format("login by \"%s\",\"%s\"", "Deepool", "Operator");
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
			CDialog::OnOK();
			return;
		}

		f.SeekToBegin();
		f.Write(&_LoginInfo, sizeof(_LoginInfo));
		f.Flush();
		f.Close();
	}



/*
	CFile f;		// [JC]20060314
	//char* pFileName = "\\Operator.dat";
	if (!f.Open( "\\Operator.dat", CFile::modeRead)
	{
		;
	char pbuf[100];
	f.Read(pbuf, sizeof(pbuf));
	CString abc = pbuf;
//	for (int i=0; i<sizeof(pbuf); (i+53))
//	{
		if ((m_sOperatorName == abc.Mid(0,12)) && (m_sPassword == abc.Mid(12,8)))
		{	
			g_System.Operator.CurUserID = abc.Mid(12,8);
			g_System.Operator.CurUserName = abc.Mid(0,12);
			g_System.Operator.CurUserPwd = "Operator";
			g_System.Operator.CurUserLevel = "Operator";
			g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
			info.Format("login by \"%s\",\"%s\"", "Deepool", "Operator");
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
			CDialog::OnOK();
		}return;
//	}
*/
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	if ((m_sOperatorName == "debug") && (m_sPassword == ""))
	{
		g_System.Operator.CurUserID = "Debug";
		g_System.Operator.CurUserName = "Debug";
		g_System.Operator.CurUserPwd = "Programer";
		g_System.Operator.CurUserLevel = "Super";
		g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
		info.Format("login by \"%s\",\"%s\"", "Deepool", "Programer");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
		CDialog::OnOK();
		return;
	}
#endif
	if ((m_sOperatorName == "") || (m_sPassword == ""))
	{
		AfxMessageBox( (CString)(LPCTSTR)TIP_EMPTY_NAME_PWD );
		GetDlgItem(IDOK)->EnableWindow(true);
		return;
	}



	if ((m_sOperatorName == "NORVASEA") && (m_sPassword == "X65536"))
	{
		//超级用户
		g_System.Operator.CurUserID = m_sOperatorName;
		g_System.Operator.CurUserName = m_sOperatorName;
		g_System.Operator.CurUserPwd = m_sPassword;
		g_System.Operator.CurUserLevel = "Super";
		g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
		info.Format("login by \"%s\",\"%s\"", m_sOperatorName, m_sPassword);
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
	
		CDialog::OnOK();
		return;
	}
//////////////////////////////////////////////////////////////
	if ((m_sOperatorName == "Commdown") && (m_sPassword == "123456"))  // 20060320 [JC] add another user for offline use
	{
		//超级用户
		g_System.Operator.CurUserID = m_sOperatorName;
		g_System.Operator.CurUserName = m_sOperatorName;
		g_System.Operator.CurUserPwd = m_sPassword;
		g_System.Operator.CurUserLevel = "Operator";
		g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
		info.Format("login by \"%s\",\"%s\"", m_sOperatorName, m_sPassword);
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
		CDialog::OnOK();
		return;
	}
////////////////////////////////////////////////////////////////
	if (CheckThroughNet())
	{	//普通用户
		CDialog::OnOK();
	}
	GetDlgItem(IDOK)->EnableWindow(true);
}

BOOL CDlgLogin::CheckThroughNet()
{
	CString info;
	//发送命令
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	CCmdMntSend::_STRUCT_Operator Operator;

	if (!pCmd->QueryOperator(m_sOperatorName, m_sPassword, Operator))
		AfxMessageBox( (CString)(LPCTSTR)TIP_COMM_ERROR );	//通讯错误
	else
	{
		if (!Operator.ValidFlag())
		{//无效用户
			info.Format("Try to login by \"%s\",\"%s\"", m_sOperatorName, m_sPassword);
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
			AfxMessageBox( (CString)(LPCTSTR)TIP_INVALID_NAME_PWD );
		}
		else
		{//成功登陆
			g_System.Operator.CurUserID = Operator.UserID();
			g_System.Operator.CurUserName = Operator.Name();
			g_System.Operator.CurUserPwd = m_sPassword;
			g_System.Operator.CurUserLevel = "Operator";
			g_System.Operator.CurUserLoginTime = COleDateTime::GetCurrentTime();
			info.Format("login by \"%s\",\"********\"", m_sOperatorName);
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
			return true;
		}
	}
	return false;
}

void CDlgLogin::OnCancel() 
{
	CDialog::OnCancel();
}

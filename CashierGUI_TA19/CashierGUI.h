// CashierGUI.h : main header file for the CASHIERGUI application
//

#if !defined(AFX_CASHIERGUI_H__E481D067_BAAB_437B_BB9A_F6E9398666B0__INCLUDED_)
#define AFX_CASHIERGUI_H__E481D067_BAAB_437B_BB9A_F6E9398666B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <vector>
using namespace std;

#define UNIQE_NAME "{1AB792D6-EEF2-4528-9A84-91356811E7A4}"//定义唯一的，以免冲突
#define ra_MSG "{D48CA923-4925-41cb-8F56-000000000001}"

#define _ADD_UTILITIES_DLL_
#define _ADD_REGISTRY_DLL_
#define _ADD_LOG_DLL_
#define _ADD_RECEIPTPRN_DLL_
#include "..\loaddll.h"  
#include "..\define.h"

#include "Card.h"

/*	系统返回值体系
 *	
 *	具体失败 < 未定义失败 < 失败基准 = 成功基准 < 未定义成功 < 定义成功
 *
 */
typedef const short SYSRESULT;	//标准返回类型
SYSRESULT SUCCESS_STANDARD	= 0;					//成功基准
SYSRESULT ERROR_STANDARD	= SUCCESS_STANDARD;		//失败基准
SYSRESULT SUCCESS			= SUCCESS_STANDARD + 1; //未定义成功
SYSRESULT SUCCESS_CANCEL	= SUCCESS + 1;			//成功意义上的取消操作
SYSRESULT ERROR_UNDEFINE	= ERROR_STANDARD - 1;	//未定义失败
SYSRESULT ERROR_CANCEL		= ERROR_UNDEFINE - 1;	//失败功意义上的取消操作
 
//资源释放标记
const USHORT NoSourceNeedRelease = 1;
const USHORT SomeSourceNeedRelease = 2;

struct CCardHolder	//持卡人信息
{
public:
	void Clear()
	{
		_ID = _Name = _IC = _Tel = _Plate = _Addr1 = _Addr2 = _Addr3 = _Zip = "";
	};
	CString _ID;
	CString _Name;
	CString _IC;
	CString _Tel;
	CString _Plate;
	CString _Addr1;
	CString _Addr2;
	CString _Addr3;
	CString _Zip;
};

struct _System
{
	HANDLE m_OprBusyMutex;//name:"OprBusyMutex", use: Operator do one thing at one time!
	struct _RunTime
	{
		HWND hMainFrame;
		HWND hOtpPaymentDlg;
		HWND hOtpAddvalueDlg;
		CString sAppPath;
		CString sHelpFilePath;
		CDaoDatabase * CurDatabase;		//当前数据库
	} RunTime;
	struct _OperatorMsg
	{
		CString CurUserID;
		CString CurUserName;
		CString CurUserPwd;
		CString CurUserLevel;
		COleDateTime CurUserLoginTime;
	} Operator;

	CStringFile SysFile;
public:
	_System();
};

CString show(const short);
CString show(const long);
CString show(const unsigned int i);
CString show(const double);
CString show(const COleDateTime);
CString show(const COleDateTimeSpan);
CString show(const CString);
CString show(const CDiscount);
CString show(const bool);
CString showPercentage(const double);
CString showDate(const COleDateTime);
CString showHHMMSS(const COleDateTime);
CString showDayOfWeek(const short DayOfWeek);
CString showStationID(const short);
CString showStationTypeName(const short);
CString showStationName(const short);
CString showSpecialCardTypeName(const short);
CString showVehicleTypeName(const short);
void showTip(LPCTSTR Tip, bool urgent = false, bool wmode = false);
void OtpErrProcess();
bool IsBigger(const COleDateTime BigDate, const COleDateTime SmallDate);
/////////////////////////////////////////////////////////////////////////////
// CCashierGUIApp:
// See CashierGUI.cpp for the implementation of this class
//

class CCashierGUIApp : public CWinApp
{
public:
	CCashierGUIApp();
	static CDialog * g_pDlgMessage;			//信息对话框指针
	static void ShowMessage(CString sMsg);  //显示信息
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCashierGUIApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	USHORT m_SourceNeedRelease;
	void SaveReg();
	BOOL SerializeFile();
	BOOL SaveSysData();
	HANDLE m_hOneInstance;
	void SerializeReg();
	//{{AFX_MSG(CCashierGUIApp)
	afx_msg void OnAppAbout();
	afx_msg void OnNULL();
	afx_msg void OnMntSetStart();
	afx_msg void OnMntSetStop();
	afx_msg void OnKdeSetStart();
	afx_msg void OnKdeSetStop();
	afx_msg void OnOtpSetStart();
	afx_msg void OnOtpSetStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveSettings();
	void LoadSettings();
};

CString LoadS(UINT nID);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CASHIERGUI_H__E481D067_BAAB_437B_BB9A_F6E9398666B0__INCLUDED_)

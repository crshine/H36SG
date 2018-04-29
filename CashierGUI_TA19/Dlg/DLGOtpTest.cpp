// DLGOtpTest.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DLGOtpTest.h"
#include "..\OtpReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COtpReader * pReader;

/////////////////////////////////////////////////////////////////////////////
// CDLGOtpTest dialog

CDLGOtpTest::CDLGOtpTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGOtpTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGOtpTest)
	m_nSound = -1;
	m_strAmt1 = _T("");
	m_strAmt2 = _T("");
	m_bGreen = FALSE;
	m_bRed = FALSE;
	m_arPath1 = _T("");
	m_arPath2 = _T("");
	m_nBaudRate = 0;
	m_szBListPath = _T("");
	m_szCCHSPath = _T("");
	m_nDayKeep = 0;
	m_szEODPath = _T("");
	m_szFWarePath = _T("");
	m_nHouseKeepType = 0;
	m_nPortNum = 0;
	m_nTimeOut = 0;
	m_szXPath = _T("");
	m_bNegVal = FALSE;
	m_nAps = 0;
	m_nAvDetail = 0;
	m_nAvMach = 0;
	m_szCAN = _T("");
	m_nClass = 0;
	m_nLang = 0;
	m_szRmtV = _T("");
	m_szTranTime = _T("");
	m_nMID = 0;
	m_szddamt = _T("");
	m_fddAmt = 0.0;
	m_fddRmt = 0.0;
	m_favAmt = 0.0;
	m_favRmt = 0.0;
	m_dwErrCode = 0;
	m_dwVerBList = 0;
	m_dwCompID = 0;
	m_dwVerCCHS = 0;
	m_dwVerDev = 0;
	m_dwDevTime = 0;
	m_dwVerEOD = 0;
	m_dwVerFWare = 0;
	m_dwVerKey = 0;
	m_dwLocID = 0;
	m_dwNewLocID = 0;
	m_dwOptrID = 0;
	m_szNewXFile = _T("");
	//}}AFX_DATA_INIT
}


void CDLGOtpTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGOtpTest)
	DDX_Radio(pDX, IDC_RADIO1, m_nSound);
	DDX_Text(pDX, IDC_AMT_LINE1, m_strAmt1);
	DDX_Text(pDX, IDC_AMT_LINE2, m_strAmt2);
	DDX_Check(pDX, IDC_CHECK_Green, m_bGreen);
	DDX_Check(pDX, IDC_CHECK_Red, m_bRed);
	DDX_Text(pDX, IDC_EDIT_ARPATH1, m_arPath1);
	DDX_Text(pDX, IDC_EDIT_ARPATH2, m_arPath2);
	DDX_Text(pDX, IDC_EDIT_BAUDRATE, m_nBaudRate);
	DDX_Text(pDX, IDC_EDIT_BLISTPATH, m_szBListPath);
	DDX_Text(pDX, IDC_EDIT_CCHSPATH, m_szCCHSPath);
	DDX_Text(pDX, IDC_EDIT_DAYKEEP, m_nDayKeep);
	DDX_Text(pDX, IDC_EDIT_EODPATH, m_szEODPath);
	DDX_Text(pDX, IDC_EDIT_FWAREPATH, m_szFWarePath);
	DDX_Text(pDX, IDC_EDIT_HOUSEKEP_TYPE, m_nHouseKeepType);
	DDX_Text(pDX, IDC_EDIT_PORTNUM, m_nPortNum);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeOut);
	DDX_Text(pDX, IDC_EDIT_XFILEPATH, m_szXPath);
	DDX_Check(pDX, IDC_CHECK_NEGVAL, m_bNegVal);
	DDX_Text(pDX, IDC_EDIT_APS, m_nAps);
	DDX_Text(pDX, IDC_EDIT_AVDETAIL, m_nAvDetail);
	DDX_Text(pDX, IDC_EDIT_AVMACH, m_nAvMach);
	DDX_Text(pDX, IDC_EDIT_CAN, m_szCAN);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_nClass);
	DDX_Text(pDX, IDC_EDIT_LANG, m_nLang);
	DDX_Text(pDX, IDC_EDIT_RMT, m_szRmtV);
	DDX_Text(pDX, IDC_EDIT_TIME, m_szTranTime);
	DDX_Text(pDX, IDC_EDIT_MID, m_nMID);
	DDX_Text(pDX, IDC_EDIT_RMT2, m_szddamt);
	DDX_Text(pDX, IDC_EDIT_DDAMT, m_fddAmt);
	DDX_Text(pDX, IDC_EDIT_DDRMT, m_fddRmt);
	DDX_Text(pDX, IDC_EDIT_AVAMT, m_favAmt);
	DDX_Text(pDX, IDC_EDIT_AVRMT, m_favRmt);
	DDX_Text(pDX, IDC_EDIT_ERRCODE, m_dwErrCode);
	DDX_Text(pDX, IDC_EDIT_BLIST, m_dwVerBList);
	DDX_Text(pDX, IDC_EDIT_COMPID, m_dwCompID);
	DDX_Text(pDX, IDC_EDIT_CCHS, m_dwVerCCHS);
	DDX_Text(pDX, IDC_EDIT_DEVID, m_dwVerDev);
	DDX_Text(pDX, IDC_EDIT_DEVTIME, m_dwDevTime);
	DDX_Text(pDX, IDC_EDIT_EOD, m_dwVerEOD);
	DDX_Text(pDX, IDC_EDIT_FWARe, m_dwVerFWare);
	DDX_Text(pDX, IDC_EDIT_KEY, m_dwVerKey);
	DDX_Text(pDX, IDC_EDIT_LOCID, m_dwLocID);
	DDX_Text(pDX, IDC_EDIT_NEWLOCID, m_dwNewLocID);
	DDX_Text(pDX, IDC_EDIT_OPTRID, m_dwOptrID);
	DDX_Text(pDX, IDC_EDIT_NEWXFILE, m_szNewXFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGOtpTest, CDialog)
	//{{AFX_MSG_MAP(CDLGOtpTest)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGOtpTest message handlers

BOOL CDLGOtpTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// TODO: Add extra initialization here
	pReader = new COtpReader(180);
	RefreshSettings();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDLGOtpTest::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if (!pReader->OpenReader()) ::AfxMessageBox("Error",MB_SYSTEMMODAL);
}

void CDLGOtpTest::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	delete pReader;
	CDialog::OnClose();
}

void CDLGOtpTest::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	double l1, l2;
	l1 = Str2Dbl(m_strAmt1, 0);
	l2 = Str2Dbl(m_strAmt2, 0);
	int i=0;
	if (m_bRed) i+=8;
	if (m_bGreen) i+= 2;
	pReader->RefreshDisplay(l1, l2, i, m_nSound);
	
}

void CDLGOtpTest::RefreshSettings()
{
	pReader->AccessReaderSetting(_T("USENEGVAL"), &m_bNegVal);
	BYTE tmpByte;
	pReader->AccessReaderSetting(_T("HOUSEKEEPTYPE"), &tmpByte);
	m_nHouseKeepType = tmpByte;
	pReader->AccessReaderSetting(_T("PORTNUM"), &tmpByte);
	m_nPortNum = tmpByte;
	DWORD tmpDW;
	pReader->AccessReaderSetting(_T("BAUDRATE"), &tmpDW);
	m_nBaudRate = tmpDW;
	pReader->AccessReaderSetting(_T("TIMEOUT"), &tmpByte);
	m_nTimeOut = tmpByte;
	pReader->AccessReaderSetting(_T("KEEPDAYS"), &tmpByte);
	m_nDayKeep = tmpByte;
	pReader->AccessReaderSetting(_T("XPATH"), m_szXPath.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("EODPATH"), m_szEODPath.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("CCHSPATH"), m_szCCHSPath.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("AR1PATH"), m_arPath1.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("AR2PATH"), m_arPath2.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("BLPATH"), m_szBListPath.GetBuffer(_MAX_PATH));
	pReader->AccessReaderSetting(_T("FWPATH"), m_szFWarePath.GetBuffer(_MAX_PATH));
	m_szXPath.ReleaseBuffer();
	m_szEODPath.ReleaseBuffer();
	m_szCCHSPath.ReleaseBuffer();
	m_arPath1.ReleaseBuffer();
	m_arPath2.ReleaseBuffer();
	m_szBListPath.ReleaseBuffer();
	m_szFWarePath.ReleaseBuffer();
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	pReader->AccessReaderSetting(_T("USENEGVAL"), &m_bNegVal, 0);
	BYTE tmpByte = m_nHouseKeepType;
	pReader->AccessReaderSetting(_T("HOUSEKEEPTYPE"), &tmpByte, 0);
	tmpByte = m_nPortNum;
	pReader->AccessReaderSetting(_T("PORTNUM"), &tmpByte, 0);
	DWORD tmpDW = m_nBaudRate;
	pReader->AccessReaderSetting(_T("BAUDRATE"), &tmpDW, 0);
	tmpByte = m_nTimeOut;
	pReader->AccessReaderSetting(_T("TIMEOUT"), &tmpByte, 0);
	tmpByte = m_nDayKeep;
	pReader->AccessReaderSetting(_T("KEEPDAYS"), &tmpByte, 0);
	pReader->AccessReaderSetting(_T("XPATH"), m_szXPath.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("EODPATH"), m_szEODPath.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("CCHSPATH"), m_szCCHSPath.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("AR1PATH"), m_arPath1.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("AR2PATH"), m_arPath2.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("BLPATH"), m_szBListPath.GetBuffer(_MAX_PATH), 0);
	pReader->AccessReaderSetting(_T("FWPATH"), m_szFWarePath.GetBuffer(_MAX_PATH), 0);
	pReader->SaveSettings();
}

void CDLGOtpTest::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	double rmtBal;
	BYTE tmpclass, tmplang, tmpaps;
	WORD tmpavdetails;
	LPOTPTRAN lpTran = new HOTPTRAN;
	DWORD tmpavmach;
	if (!pReader->OtpDetect(m_szCAN.GetBuffer(10), rmtBal, lpTran, &tmpclass, &tmpavdetails, &tmpavmach, &tmplang, &tmpaps))
	{
		m_dwErrCode = pReader->GetLastError();
		delete lpTran;
		UpdateData(FALSE);
		return;
	}
	m_szCAN.ReleaseBuffer();
	m_szRmtV.Format("$%.2f", rmtBal);
	m_nAps = tmpaps;
	m_nAvDetail = tmpavdetails;
	m_nAvMach = tmpavmach;
	m_nClass = tmpclass;
	m_nLang = tmplang;
	m_szddamt.Format("$%.2f", lpTran->Amount);
	m_nMID = lpTran->Mid;
	m_szTranTime.Format("%s", lpTran->TransTime.Format("%d/%m/%y,%H:%M:%S"));
	delete lpTran;
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton8() 
{
	// TODO: Add your control notification handler code here
	//deduct
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	if (!pReader->OtpDeduct(m_fddAmt, m_fddRmt))
	{
		m_dwErrCode = pReader->GetLastError();
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	if (!pReader->Topup(m_favAmt, 1, m_favRmt, 0))
	{
		m_dwErrCode = pReader->GetLastError();
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton10() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	if (!pReader->SetTimeVerID(m_dwNewLocID))
	{
		m_dwErrCode = pReader->GetLastError();
		UpdateData(FALSE);
		return;
	}
	m_dwCompID = pReader->GetVersion(_T("COMPID"));
	m_dwDevTime = pReader->GetVersion(_T("DEVTIME")); 
	m_dwLocID = pReader->GetVersion(_T("CSSER"));
	m_dwOptrID = pReader->GetVersion(_T("OPTRID"));
	m_dwVerBList = pReader->GetVersion(_T("BLVER"));
	m_dwVerCCHS = pReader->GetVersion(_T("CCHSVER"));
	m_dwVerDev = pReader->GetVersion(_T("DEVID"));
	m_dwVerEOD = pReader->GetVersion(_T("EODVER"));
	m_dwVerFWare = pReader->GetVersion(_T("FIRMVER"));
	m_dwVerKey = pReader->GetVersion(_T("KEYVER"));
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton3() 
{
	// TODO: Add your control notification handler code here
	pReader->OtpReset();
}


void CDLGOtpTest::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	if (!pReader->GenerateXFile(m_szNewXFile.GetBuffer(_MAX_PATH)))
	{
		m_dwErrCode = pReader->GetLastError();
		UpdateData(FALSE);
		return;
	}
	m_szNewXFile.ReleaseBuffer();
	UpdateData(FALSE);
}

void CDLGOtpTest::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_dwErrCode = 0;
	((CEdit *)GetDlgItem(IDC_EDIT_ERRCODE))->SetWindowText("0");
	UpdateData();
	if (!pReader->OtpHouseKeeping())
	{
		m_dwErrCode = pReader->GetLastError();
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

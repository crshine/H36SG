// dlgsettingotpreader.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\CmdOtp.h"
#include "dlgsettingotpreader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingOtpReader dialog


CDlgSettingOtpReader::CDlgSettingOtpReader(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingOtpReader::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingOtpReader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettingOtpReader::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingOtpReader)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingOtpReader, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingOtpReader)
	ON_BN_CLICKED(ID_SET_FOLDERS, OnSetFolders)
	ON_BN_CLICKED(ID_READ_FOLDERS, OnReadFolders)
	ON_BN_CLICKED(ID_SET_TIME_READ_VER, OnSetTimeReadVer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingOtpReader message handlers

BOOL CDlgSettingOtpReader::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnReadFolders();
	OnSetTimeReadVer();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSettingOtpReader::OnSetFolders() 
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::RWL_SETTINGS RWL_Settings;

	GetDlgItemText( IDC_XFILEPATH,		RWL_Settings._Exchange );
	GetDlgItemText( IDC_BLISTPATH,		RWL_Settings._Blacklist );
	GetDlgItemText( IDC_FWAREPATH,		RWL_Settings._Firmware );
	GetDlgItemText( IDC_EODPATH,		RWL_Settings._EOD );
	GetDlgItemText( IDC_CCHSPATH,		RWL_Settings._CCHS );
	GetDlgItemText( IDC_ARPATH1,		RWL_Settings._AR1 );
	GetDlgItemText( IDC_ARPATH2,		RWL_Settings._AR2 );

	pCmdOtp->OTP_Folders_Write(RWL_Settings);
}

void CDlgSettingOtpReader::OnReadFolders() 
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::RWL_SETTINGS RWL_Settings;
	pCmdOtp->OTP_Folders_Read(RWL_Settings);

	SetDlgItemText( IDC_XFILEPATH,		RWL_Settings._Exchange );
	SetDlgItemText( IDC_BLISTPATH,		RWL_Settings._Blacklist );
	SetDlgItemText( IDC_FWAREPATH,		RWL_Settings._Firmware );
	SetDlgItemText( IDC_EODPATH,		RWL_Settings._EOD );
	SetDlgItemText( IDC_CCHSPATH,		RWL_Settings._CCHS );
	SetDlgItemText( IDC_ARPATH1,		RWL_Settings._AR1 );
	SetDlgItemText( IDC_ARPATH2,		RWL_Settings._AR2 );
}

void CDlgSettingOtpReader::OnSetTimeReadVer() 
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::VER_TIME TimeVer;
	COleDateTime t;
	t = COleDateTime::GetCurrentTime();

	if (!pCmdOtp->OTP_TimeVer(TimeVer ))
	{	//¶Á¿¨Ê§°Ü
		AfxMessageBox(pCmdOtp->Translate());
//		OtpErrProcess();
		return;
	}
	SetDlgItemText( IDC_DEVID,		show(TimeVer._DevID) );
	SetDlgItemText( IDC_OPERID,		show(TimeVer._OperID) );
	SetDlgItemText( IDC_DEVTIME,	show(TimeVer._DevTime) );
	SetDlgItemText( IDC_COMPID,		show(TimeVer._CompID) );
	SetDlgItemText( IDC_KEYVER,		show(TimeVer._KeyVer) );
	SetDlgItemText( IDC_EODVER,		show(TimeVer._EODVer) );
	SetDlgItemText( IDC_BLVER,		show(TimeVer._BLVer) );
	SetDlgItemText( IDC_FIRMVER,	show(TimeVer._FIRMVer) );
	SetDlgItemText( IDC_CCHSVER,	show(TimeVer._CCHSVer) );
	SetDlgItemText( IDC_LOCID,		show(TimeVer._CSSer) );
}

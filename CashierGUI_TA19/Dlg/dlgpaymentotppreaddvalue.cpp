// dlgpaymentotppreaddvalue.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdOtp.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentotppreaddvalue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int	_TicketProcessCate;

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPPreAddvalue dialog
double CDlgPaymentOTPPreAddvalue::_Amount = 0.0;
double CDlgPaymentOTPPreAddvalue::_OctopusRemain = 0.0;
CString CDlgPaymentOTPPreAddvalue::_OctopusCardNo = "";
CDlgPaymentOTPPreAddvalue * CDlgPaymentOTPPreAddvalue::pThis = NULL;

CDlgPaymentOTPPreAddvalue::CDlgPaymentOTPPreAddvalue(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentOTPPreAddvalue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentOTPPreAddvalue)
	m_Amount = _T("");
	m_OctopusCardNo = _T("");
	m_OctopusRemain = _T("");
	m_AvSel = -1;
	m_CUR_STATUS = _T("");
	//}}AFX_DATA_INIT
	pThis = this;
}

CDlgPaymentOTPPreAddvalue::~CDlgPaymentOTPPreAddvalue()
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	pCmdOtp->Kill_Async_Poll();
	pThis = NULL;
}

void CDlgPaymentOTPPreAddvalue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentOTPPreAddvalue)
	DDX_Text(pDX, AMOUNT, m_Amount);
	DDX_Text(pDX, OCTOPUS_CARDNO, m_OctopusCardNo);
	DDX_Text(pDX, OCTOPUS_REMAIN, m_OctopusRemain);
	DDX_CBIndex(pDX, ID_AVSEL, m_AvSel);
	DDX_Text(pDX, CUR_STATUS, m_CUR_STATUS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentOTPPreAddvalue, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentOTPPreAddvalue)
	ON_EN_KILLFOCUS(AMOUNT, OnKillfocusAMOUNT)
	ON_BN_CLICKED(ID_WAIT_OTP_POLL, OnWaitOtpPoll)
	ON_BN_CLICKED(ID_AV50, OnAv50)
	ON_BN_CLICKED(ID_AV100, OnAv100)
	ON_BN_CLICKED(ID_AV200, OnAv200)
	ON_BN_CLICKED(ID_AV300, OnAv300)
	ON_BN_CLICKED(ID_AV400, OnAv400)
	ON_BN_CLICKED(ID_AV500, OnAv500)
	ON_CBN_EDITCHANGE(ID_AVSEL, OnEditchangeAvsel)
	ON_CBN_SELCHANGE(ID_AVSEL, OnSelchangeAvsel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPPreAddvalue message handlers

void CDlgPaymentOTPPreAddvalue::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//党蜊趼极
	GetDlgItem(OCTOPUS_REMAIN)->SetFont(&pSetting->FontBig());
	GetDlgItem(AMOUNT)->SetFont(&pSetting->FontBig());
	GetDlgItem(OCTOPUS_CARDNO)->SetFont(&pSetting->FontBig());

	_OctopusRemain = 0.0;		//匐湛籵豻塗
	_Amount = 0.0;				//喳硉踢塗
	_OctopusCardNo = "";

	//党蜊怀�踸藰�
	m_Amount = show( _Amount );
	m_OctopusRemain = " ";//show( _OctopusRemain );
	m_OctopusCardNo = show( _OctopusCardNo );
	m_CUR_STATUS = "請放八達通卡於讀卡器上...";
	UpdateData(false);

	//斐膘潰聆匐湛籵縐腔盄最
//	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
//	pCmdOtp->Async_Poll(PollDetect);
}

void CDlgPaymentOTPPreAddvalue::OnOK() 
{
	const double MinAddValue = 50.0;
	const double MaxAddValue = 1000.0;
	//淕燴怀�鄵�
	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = atof( s );

	if (m_OctopusCardNo.GetLength() != 9 && m_OctopusCardNo.GetLength() != 11) //TA19- 10 byte card number
///		if (m_OctopusCardNo.GetLength() != 9)
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	//潰聆硉腔衄虴俶
	if (MinAddValue > _Amount)
	{
		::AfxMessageBox("增值金額過少", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過少",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	if (0 != Amt100Cents)
	{
		::AfxMessageBox("增值金額必須是50的倍數！", MB_ICONSTOP|MB_SYSTEMMODAL);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	CDialog::OnOK();
}

BOOL CDlgPaymentOTPPreAddvalue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();	
	CardStatus = FALSE;

	_TicketProcessCate=0;

	m_OctopusRemain = " ";
	m_CUR_STATUS = "請放八達通卡於讀卡器上...";

	SetTimer(1,1000,0);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CDlgPaymentOTPPreAddvalue::OnKillfocusAMOUNT() 
{

	UpdateData(true);
	CString s = m_Amount;
	s.Replace('$',' ');
	_Amount = atof( s );
	m_Amount = show( _Amount );
	UpdateData(false);

}

void CDlgPaymentOTPPreAddvalue::OnWaitOtpPoll() 
{
	GetDlgItem(ID_WAIT_OTP_POLL)->EnableWindow(false);
	_OctopusCardNo = "";	//匐湛籵縐瘍
	_OctopusRemain = 0;		//匐湛籵豻塗
	m_OctopusRemain = show( _OctopusRemain );
	m_OctopusCardNo = show( _OctopusCardNo );
	UpdateData(false);
	GetDlgItem(AMOUNT)->SetFocus();
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	if (!pCmdOtp->OTP_Poll(CardInfo))
	{
		if (pCmdOtp->GetLastError() != 32) 
			AfxMessageBox((LPCTSTR)TIP_OTP_NO_CARD, MB_ICONSTOP|MB_SYSTEMMODAL );
	}
	else
	{
		PollDetect(CardInfo);
	}
	//pCmdOtp->Async_Poll(PollDetect);
	GetDlgItem(ID_WAIT_OTP_POLL)->EnableWindow(true);
}

void CALLBACK CDlgPaymentOTPPreAddvalue::PollDetect(const CCmdOtp::PATRON &CardInfo)
{
	if (NULL == CDlgPaymentOTPPreAddvalue::pThis) return;
	_OctopusCardNo = CardInfo._CardNo;	//匐湛籵縐瘍
	_OctopusRemain = CardInfo._Remain;		//匐湛籵豻塗
	CDlgPaymentOTPPreAddvalue::pThis->SetDlgItemText(OCTOPUS_REMAIN, show(CardInfo._Remain));
	CDlgPaymentOTPPreAddvalue::pThis->SetDlgItemText(OCTOPUS_CARDNO, show(CardInfo._CardNo));
}

void CDlgPaymentOTPPreAddvalue::OnAv50() 
{
	//const double MinAddValue = 50.0;
    const double MaxAddValue = 1000.0;
	//淕燴怀�鄵�
	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 50;

	//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	//潰聆硉腔衄虴俶
//	if (MinAddValue > _Amount)
//	{
//		::AfxMessageBox("增值金額過少", MB_ICONSTOP|MB_SYSTEMMODAL);
//		GetDlgItem(AMOUNT)->SetFocus();
//		return;
//	}

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

//	if (0 != Amt100Cents)
//	{
//		::AfxMessageBox("金額必須是50的倍數！", MB_ICONSTOP|MB_SYSTEMMODAL);
//		GetDlgItem(AMOUNT)->SetFocus();
//		return;
//	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnAv100() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 100;

//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnAv200() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 200;

	//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnAv300() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 300;

	//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnAv400() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 400;

	//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnAv500() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = 500;

	//	if (m_OctopusCardNo.GetLength() != 8)
	if (m_OctopusCardNo.GetLength() != 8 && m_OctopusCardNo.GetLength() != 10) //TA19- 10 byte card number
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}

	CDialog::OnOK();
}

void CDlgPaymentOTPPreAddvalue::OnEditchangeAvsel()  // *** NO USE *** 
{
/*    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	_Amount = m_AvSel;

	if (m_OctopusCardNo.GetLength() != 8)
	{
		::AfxMessageBox("請先拍八達通卡", MB_ICONSTOP|MB_SYSTEMMODAL);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_APPLMODAL|MB_ICONSTOP|MB_SYSTEMMODAL);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}

	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}
*/
	CDialog::OnOK();	
}

void CDlgPaymentOTPPreAddvalue::OnSelchangeAvsel() 
{
    const double MaxAddValue = 1000.0;

	UpdateData(true);
	CString s;
	s = m_OctopusRemain;
	s.Replace('$',' ');
	_OctopusRemain = atof( s );

	s = m_Amount;
	s.Replace('$',' ');
	
	
	_Amount = (m_AvSel * 50) +50;

	if (m_OctopusCardNo.GetLength() != 8)
	{
		::AfxMessageBox("請先拍八達通卡", MB_APPLMODAL|MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("請先拍八達通卡",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	_OctopusCardNo = m_OctopusCardNo;

	m_OctopusRemain = show(_OctopusRemain);
	m_Amount = show(_Amount);
	UpdateData(false);

	if (MaxAddValue <= _Amount + _OctopusRemain)
	{
		::AfxMessageBox("增值金額過多", MB_APPLMODAL|MB_ICONSTOP|MB_SYSTEMMODAL);
		showTip("增值金額過多",true);
		GetDlgItem(AMOUNT)->SetFocus();
		return;
	}
	ULONG Amt100Cents = _Amount * 100;
	while (Amt100Cents >= 5000)
	{
		Amt100Cents -= 5000;
	}
	CDialog::OnOK();	
}

//TA11A 2009 ITEM2
void CDlgPaymentOTPPreAddvalue::OnTimer(UINT nIDEvent) 
{	
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	if (!pCmdOtp->OTP_Poll())
	{

//TA2009 shut down MOP once ADDVALUE, software slow down.
		if (pCmdOtp->GetLastError() ==1 ||pCmdOtp->GetLastError() ==5)
		{
			SetTimer(1,3600000,0);
//			AfxMessageBox("Reader disconnected, please check!", MB_ICONSTOP|MB_SYSTEMMODAL );
			return;
		}

		if (pCmdOtp->GetLastError() != 32) 
;//			AfxMessageBox(TIP_OTP_NO_CARD, MB_ICONSTOP|MB_SYSTEMMODAL );
		m_OctopusRemain = " ";//show( _OctopusRemain );
		m_OctopusCardNo = show( _OctopusCardNo = " " );	
		m_CUR_STATUS = "請放八達通卡於讀卡器上...";
		
		GetDlgItem(ID_AV50)->EnableWindow(false);
		GetDlgItem(ID_AV100)->EnableWindow(false);
		GetDlgItem(ID_AV200)->EnableWindow(false);
		GetDlgItem(ID_AV300)->EnableWindow(false);
		GetDlgItem(ID_AV400)->EnableWindow(false);
		GetDlgItem(ID_AV500)->EnableWindow(false);
		GetDlgItem(ID_AVSEL)->EnableWindow(false);

		CardStatus = FALSE;
	}
	else if(!CardStatus)
	if (pCmdOtp->OTP_Poll(CardInfo))
	{
		PollDetect(CardInfo);
		m_OctopusRemain = show( _OctopusRemain );
		m_OctopusCardNo = show( _OctopusCardNo.Mid(1,8) );
		m_OctopusCardNo = show( _OctopusCardNo.Mid(1,10) );//TA19- for 10 bytes card number testing
		m_CUR_STATUS = "請選擇增值金額";
		
		GetDlgItem(ID_AV50)->EnableWindow(true);
		GetDlgItem(ID_AV100)->EnableWindow(true);
		GetDlgItem(ID_AV200)->EnableWindow(true);
		GetDlgItem(ID_AV300)->EnableWindow(true);
		GetDlgItem(ID_AV400)->EnableWindow(true);
		GetDlgItem(ID_AV500)->EnableWindow(true);
		GetDlgItem(ID_AVSEL)->EnableWindow(true);
		CardStatus = TRUE;
	}
	
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
	
}

/*
void CDlgPaymentOTPPreAddvalue::OnTimer(UINT nIDEvent) 
{

	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	if (!pCmdOtp->OTP_Poll(CardInfo))
	{
		if (pCmdOtp->GetLastError() != 32) 
			AfxMessageBox(TIP_OTP_NO_CARD, MB_ICONSTOP|MB_SYSTEMMODAL );
		m_OctopusRemain = " ";//show( _OctopusRemain );
		m_OctopusCardNo = show( _OctopusCardNo = " " );	
		m_CUR_STATUS = "請放八達通卡於讀卡器上...";

		GetDlgItem(ID_AV50)->EnableWindow(false);
		GetDlgItem(ID_AV100)->EnableWindow(false);
		GetDlgItem(ID_AV200)->EnableWindow(false);
		GetDlgItem(ID_AV300)->EnableWindow(false);
		GetDlgItem(ID_AV400)->EnableWindow(false);
		GetDlgItem(ID_AV500)->EnableWindow(false);
		GetDlgItem(ID_AVSEL)->EnableWindow(false);
	}
	else
	{
		PollDetect(CardInfo);
		m_OctopusRemain = show( _OctopusRemain );
		m_OctopusCardNo = show( _OctopusCardNo.Mid(1,8) );
		m_CUR_STATUS = "請選擇增值金額";

		GetDlgItem(ID_AV50)->EnableWindow(true);
		GetDlgItem(ID_AV100)->EnableWindow(true);
		GetDlgItem(ID_AV200)->EnableWindow(true);
		GetDlgItem(ID_AV300)->EnableWindow(true);
		GetDlgItem(ID_AV400)->EnableWindow(true);
		GetDlgItem(ID_AV500)->EnableWindow(true);
		GetDlgItem(ID_AVSEL)->EnableWindow(true);
	}

	UpdateData(false);
	CDialog::OnTimer(nIDEvent);

}
*/
// DlgPaymentOperate.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentoperate.h"
#include "..\customer.h"
#include "..\FeeCalculate.h"
#include "..\CmdLcd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CFont Font;
//	VERIFY(Font.CreateFont(28,0,0, 0,1400,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, _T("Arial")));             

extern int _TicketProcessCate;
extern int _TicketPro_Vehicle;
extern CSetting * g_Setting;
/////////////////////////////////////////////////////////////////////////////
// DlgPaymentOperate dialog
CString DlgPaymentOperate::_TicketNo = "";

DlgPaymentOperate::DlgPaymentOperate(CWnd* pParent /*=NULL*/)
	: CDlgInput(DlgPaymentOperate::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPaymentOperate)
	m_ExitDate = COleDateTime::GetCurrentTime();
	m_ExitTime = COleDateTime::GetCurrentTime();
	m_EntryDate = COleDateTime::GetCurrentTime();
	m_EntryTime = COleDateTime::GetCurrentTime();
	m_EntryStation = -1;
	m_VehicleType = -1;
	m_CardType = -1;
	m_ProcessType = -1;
	m_sEntrytime = _T("");
	m_sPaytime = _T("");
	//}}AFX_DATA_INIT
}


void DlgPaymentOperate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPaymentOperate)
	DDX_Control(pDX, IDC_AMOUNT, m_Amount);
	DDX_CBIndex(pDX, IDC_EDIT_ENTRYSTATION, m_EntryStation);
	DDX_CBIndex(pDX, IDC_VEHICLETYPE, m_VehicleType);
	DDX_Text(pDX, IDC_EDIT_ENTERTIME, m_sEntrytime);
	DDX_Text(pDX, IDC_EDIT_PAYTIME, m_sPaytime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPaymentOperate, CDialog)
	//{{AFX_MSG_MAP(DlgPaymentOperate)
	ON_WM_CTLCOLOR()
//	ON_BN_CLICKED(IDOK3, GetCardInfo)
	ON_BN_CLICKED(IDC_BTN_OTP, OnBtnOtp)
	ON_CBN_SELCHANGE(IDC_VEHICLETYPE, OnSelchangeVehicletype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgPaymentOperate message handlers
	
void DlgPaymentOperate::OnOK() // cash payment
{
	PaywithOTP=FALSE;

	UpdateData();

	long a,b;
	double c, d;
	a = m_EntryDate;
	c = (double)m_EntryTime - (long)m_EntryTime;
	b = m_ExitDate;
	d = (double)m_ExitTime - (long)m_ExitTime;

	m_cVehicleType = m_VehicleType;	
	
	m_cEntryTime = COleDateTime(a+c);
	m_cExitTime = COleDateTime(b+d);
	m_cEntryStationID = m_EntryStation+1;

	m_cManTicketNo = m_TicketNo;
	m_Type = m_ProcessType;
 
	_Cash = _Amount;
 
	parker->ReCalculate(this);

	if (parker) {delete parker; parker = NULL;}
	CDialog::OnOK();
}

BOOL DlgPaymentOperate::OnInitDialog() // (Damage ticket check point 002)
{
	CDialog::OnInitDialog();
	parker = NULL;
	parker = new CCustomer::CKdeUserExitCarPark(); 

	m_bFindInfoFromNet = FALSE;

	m_ProcessType = 3;

	((CButton *)GetDlgItem(IDOK))->EnableWindow(FALSE);
	InitControl();

	this->SetForegroundWindow();
	m_CardType = 0;
	m_VehicleType = 0;
	m_bFindInfoFromNet = FALSE;
	m_EntryStation = 0;

	GetCardInfo();

	VERIFY(Font.CreateFont(26,0,0, 0,1400,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, _T("Arial")));             

	GetDlgItem(IDC_TICKETNO)->SetFont(&Font,true);
	GetDlgItem(IDC_AMOUNT)->SetFont(&Font,true);
	
	UpdateData(FALSE);
	
	if(_TicketProcessCate==1)
		GetDlgItem(IDC_BTN_OTP)->GetFocus();
//	else
//		(CButton *)GetDlgItem(IDC_BTN_OTP)->ShowWindow(FALSE);

	//HBITMAP bmp = ::LoadBitmap(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_CARDKDE));  
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CARDKDE);
	((CStatic *)GetDlgItem(IDC_IMAGE_OTP))->SetBitmap(bmp);

	GetDlgItem(IDC_VEHICLETYPE)->SetFont(&Font,true);

	SetTimer(1,1000,0);
//	((CEdit *)GetDlgItem(IDC_TICKETNO))->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
} 

void DlgPaymentOperate::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//蜊曹恅趼湮苤
	// Change Text Size
//	GetDlgItem(IDC_TICKETNO)->SetFont(&m_fontEdit);
//	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&pSetting->FontMid());

	SetDlgItemText(IDC_TICKETNO,m_TicketNo);

//	SetDlgItemText(IDC_VEHICLETYPE,1);

}

HBRUSH DlgPaymentOperate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
/*	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CSetting * pSetting = CSetting::Instance();
	if ( nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(pSetting->AbnormityColor()); //蜊曹噙怓諾諷璃趼极晇伎
	}
	return pSetting->AbnormityBrush();//妏蚚珨笱桶尨杻忷紱釬腔倳醴晇伎
*/
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_EDIT)
	{
//		pDC->SetTextColor(RGB(222,0,0));
	}
	if(nCtlColor==CTLCOLOR_STATIC && (pWnd==&m_Amount) )
	{
//		pDC->SetTextColor(RGB(196,0,0));
	}
	return hbr;


}

void DlgPaymentOperate::OnCancel2() 
{
	// TODO: Add your control notification handler code here
	if (parker) delete parker;
CDialog::OnCancel();
}

void DlgPaymentOperate::OnCancel() // Cancel Button
{
	// TODO: Add extra cleanup here
	if (parker) delete parker;
	CDialog::OnCancel();

}

void DlgPaymentOperate::GetCardInfo()  // Search Button
{
	GetDlgItemText(IDC_TICKETNO, _TicketNo);
	_TicketNo.TrimLeft();
	_TicketNo.TrimRight();

	short result;
	result = parker->QueryServer(this); // Query the database   
	if (ERROR_STANDARD > result)
	{
		if (m_ProcessType == 3) // Change VehType
		{
			::AfxMessageBox("注意 : \n找不到相關泊車紀錄, \n請檢查票種類及票號後重試!", MB_ICONWARNING|MB_SYSTEMMODAL);
			showTip("注意 : 找不到相關泊車紀錄, 請檢查票種類及票號後重試!",true);
			return;
		}
		else // Damage / Lost Ticket
		{
			//enable all the disabled items and start to manual input info.
			m_bFindInfoFromNet = FALSE;
//			((CComboBox *)GetDlgItem(IDC_ENTRYSTATION))->EnableWindow(true);
			((CComboBox *)GetDlgItem(IDC_VEHICLETYPE))->EnableWindow(true);
		}
	}else
	{//retrieve the info, and display to this screen
		m_bFindInfoFromNet = TRUE;
		m_EntryDate = m_cEntryTime;
		m_EntryTime = m_cEntryTime;
		m_ExitDate = m_cExitTime;
		m_ExitTime = m_cExitTime;
		m_EntryStation = m_cEntryStationID-1;
		m_VehicleType = m_cVehicleType-1;
		if (m_ProcessType == 3) // Change VehType
			((CComboBox *)GetDlgItem(IDC_VEHICLETYPE))->EnableWindow(true);

		m_sEntrytime.Format("%04d-%02d-%02d %02d:%02d:%02d", m_cEntryTime.GetYear(),m_cEntryTime.GetMonth(),m_cEntryTime.GetDay(),m_cEntryTime.GetHour(),m_cEntryTime.GetMinute(),m_cEntryTime.GetSecond());
		m_sPaytime.Format("%04d-%02d-%02d %02d:%02d:%02d", m_cExitTime.GetYear(),m_cExitTime.GetMonth(),m_cExitTime.GetDay(),m_cExitTime.GetHour(),m_cExitTime.GetMinute(),m_cExitTime.GetSecond());

		(GetDlgItem(IDC_EDIT_ENTRYSTATION))->SetWindowText("01");
		UpdateData(FALSE);
	}
//	((CEdit *)GetDlgItem(IDC_TICKETNO))->EnableWindow(FALSE);
//	((CButton *)GetDlgItem(IDC_RADIO_OTP))->EnableWindow(FALSE);

//	((CButton *)GetDlgItem(IDOK3))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDOK))->EnableWindow(TRUE);

	OnSelchangeVehicletype();
}

/////////////////////////////////////////////////////////////////////////////
// DlgPaymentOperate message handlers

void DlgPaymentOperate::OnBtnOtp() 
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;

	if (!pCmdOtp->OTP_Poll(CardInfo)) return; //UCH 3-otp pay for barcode ticket

	_Octopus_CardNo = CardInfo._CardNo; //UCH 3-otp card pay for barcode ticket

	PaywithOTP=TRUE;
	CFeeCalculate FeeCalculate;
//	int	Result = FeeCalculate.Calculate(_Amount, _Discount, _LastPayTime, _ExitTime, _VehicleId, _GroupId, PayAgain, _OTPZeroDeductType, ShowDetail);
	parker->ReCalculate(this);
	
	if (parker) {delete parker; parker = NULL;}

	CDialog::OnOK();

//	CDialog::OnCancel();
}

static void CALLBACK ShowDetail(CString Detail){;/*do nothing*/}

void DlgPaymentOperate::OnSelchangeVehicletype() 
{
	UpdateData();

	m_cVehicleType = m_VehicleType+1;	

	long a,b;
	double c, d;
	a = m_EntryDate;
	c = (double)m_EntryTime - (long)m_EntryTime;
	b = m_ExitDate;
	d = (double)m_ExitTime - (long)m_ExitTime;
	
	m_cEntryTime = COleDateTime(a+c);
	m_cExitTime = COleDateTime(b+d);
	
	if(m_VehicleType==1)
	{
//		m_cEntryTime = COleDateTime(a+c+1.2/24.0);
	}
	m_cEntryStationID = m_EntryStation+1;
	m_cManTicketNo = m_TicketNo;
	m_Type = m_ProcessType;

	m_bFindInfoFromNet=TRUE;

	CFeeCalculate FeeCalculate;
	CDiscount dis;
	unsigned int tmpint;
	if(m_cEntryTime<m_cExitTime)
		FeeCalculate.Calculate(_Amount, dis, m_cEntryTime, m_cExitTime, m_cVehicleType, 0, 0, tmpint, ShowDetail);
	else
		_Amount=0;

	_TicketPro_Vehicle=m_cVehicleType;

	CString tmpstr;
	tmpstr.Format("%.2f",_Amount);
	SetDlgItemText(IDC_AMOUNT,tmpstr);

	parker->ReCalculate(this);

	//	parker->ManualTrade(m_Type, m_cVehicleType, m_cManTicketNo, m_cEntryTime, m_cEntryStationID);
//	if (parker) {delete parker; parker = NULL;}
	
}

void DlgPaymentOperate::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);

	_OctopusRemain = 0.0;
	_Octopus_CardNo = "";
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	
	if (!pCmdOtp->OTP_Poll(CardInfo))
	{
		if (pCmdOtp->GetLastError() != 32) 
		{
			CString dsp;
			dsp.Format("發現錯誤 : [%s]" , pCmdOtp->Translate());
//			::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
//TA11A ken20090817
			if (pCmdOtp->GetLastError() != 22)
				::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
			showTip(dsp, true);
			pCmdOtp->WaitForOtpRemove();
		}
		SetTimer(1, 1000, 0);
		return;
	}
	else
	{
		if (!this) return;
		/*
		double x = CardInfo._AvailableAmount;
		x = CardInfo._Remain + 35 + x;
		if (x < _Amount) 
		{
			showTip("八達通卡餘額不足,請換卡重試或使用現金付款!", true);
			pCmdOtp->WaitForOtpRemove();
			SetTimer(1, 1000, 0);
			return;
		}
		*/
		_Octopus = _Amount;
		_Octopus_CardNo = CardInfo._CardNo;
		if (!pCmdOtp->OTP_Deduct(_Octopus, _OctopusRemain, 
							CSetting::Instance()->m_Account.GetReceiptNo(), 0, _Octopus_CardNo))
		{
			CString dsp;
			dsp.Format("發現錯誤[%s], 請換卡重試!", pCmdOtp->Translate());
//TA11A 2009
if(pCmdOtp->GetLastError()!=22)
			::AfxMessageBox(dsp, MB_ICONSTOP|MB_SYSTEMMODAL);
			showTip(dsp, true);
			pCmdOtp->WaitForOtpRemove();
			SetTimer(1, 1000, 0);
			_Octopus = 0;
			return;
		}
		else
		{
			_Cash = 0;
			_Change = 0;	//梑錨 = 0
			_Unpaid = 0;	//帤葆 = 0
		}
		pCmdOtp->WaitForOtpRemove();

		CDialog::OnOK();
	}
	SetTimer(1, 1000, 0);
	CDialog::OnTimer(nIDEvent);
}



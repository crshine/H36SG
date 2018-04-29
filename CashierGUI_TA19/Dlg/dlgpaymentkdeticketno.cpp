// dlgpaymentkdeticketno.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentkdeticketno.h"
#include "..\customer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int _TicketProcessCate;
extern CSetting * g_Setting;
/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDETicketNo dialog
CString CDlgPaymentKDETicketNo::_TicketNo = "";

CDlgPaymentKDETicketNo::CDlgPaymentKDETicketNo(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentKDETicketNo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentKDETicketNo)
	m_ExitDate = COleDateTime::GetCurrentTime();
	m_ExitTime = COleDateTime::GetCurrentTime();
	m_EntryDate = COleDateTime::GetCurrentTime();
	m_EntryTime = COleDateTime::GetCurrentTime();
	m_EntryStation = -1;
	m_VehicleType = -1;
	m_CardType = -1;
	m_ProcessType = -1;
	//}}AFX_DATA_INIT
}


void CDlgPaymentKDETicketNo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentKDETicketNo)
	DDX_Control(pDX, IDC_ENTRYSTATION, m_ComboEntry);
	DDX_DateTimeCtrl(pDX, IDC_EXITDATE, m_ExitDate);
	DDX_DateTimeCtrl(pDX, IDC_EXITTIME, m_ExitTime);
	DDX_DateTimeCtrl(pDX, IDC_ENTRYDATE, m_EntryDate);
	DDX_DateTimeCtrl(pDX, IDC_ENTRYTIME, m_EntryTime);
	DDX_CBIndex(pDX, IDC_ENTRYSTATION, m_EntryStation);
	DDX_CBIndex(pDX, IDC_VEHICLETYPE, m_VehicleType);
	DDX_Radio(pDX, IDC_RADIO_OTP, m_CardType);
	DDX_Radio(pDX, IDC_RADIO_DAMG, m_ProcessType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentKDETicketNo, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentKDETicketNo)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK3, OnOk3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDETicketNo message handlers
	
void CDlgPaymentKDETicketNo::OnOK() // Payment button  // damage payment check point 001
{
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
    //         _||_
	//         \  /
	//          \/
	parker->RefreshDsp(this);
    //         _||_
	//         \  /
	//          \/
//	parker->ManualTrade((BOOL)m_Type, m_cVehicleType, m_cManTicketNo, m_cEntryTime, m_cEntryStationID);
	parker->ManualTrade(m_Type, m_cVehicleType, m_cManTicketNo, m_cEntryTime, m_cEntryStationID);
	if (parker) {delete parker; parker = NULL;}
	CDialog::OnCancel();
}

BOOL CDlgPaymentKDETicketNo::OnInitDialog() // (Damage ticket check point 002)
{
	CDialog::OnInitDialog();

	_TicketProcessCate=0;	//UCH

//	if (parker) delete parker;
	parker = NULL;
	parker = new CCustomer::CKdeUserExitCarPark(); 

	m_bFindInfoFromNet = FALSE;

	m_ProcessType = 0;
	((CButton *)GetDlgItem(IDOK3))->EnableWindow(TRUE); 
	((CButton *)GetDlgItem(IDOK))->EnableWindow(FALSE);

	CRect rect1, rect2;
	::AfxGetMainWnd()->GetWindowRect(&rect2);
	this->GetWindowRect(&rect1);
	rect1.TopLeft().x= rect2.BottomRight().x-402;
	rect1.BottomRight().x= rect1.TopLeft().x + 390;
	rect1.TopLeft().y=rect2.TopLeft().y+90;
	rect1.BottomRight().y=rect1.TopLeft().y+423;
	this->MoveWindow(&rect1,true);
	InitControl();
	this->SetForegroundWindow();
	m_CardType = 0;
	m_VehicleType = 0;
	m_bFindInfoFromNet = FALSE;
	m_EntryStation = 0;

	m_EntryDate = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 1, 0, 0);
	m_EntryTime = COleDateTime::GetCurrentTime() - COleDateTimeSpan(0, 1, 0, 0);
	m_ExitDate = COleDateTime::GetCurrentTime();
	m_ExitTime = COleDateTime::GetCurrentTime();
	UpdateData(FALSE);
	
	((CEdit *)GetDlgItem(IDC_TICKETNO))->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentKDETicketNo::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//改变文字大小
	// Change Text Size
	GetDlgItem(IDC_TICKETNO)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&pSetting->FontMid());
}

HBRUSH CDlgPaymentKDETicketNo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CDlgPaymentKDETicketNo::OnCancel2() 
{
	// TODO: Add your control notification handler code here
	if (parker) delete parker;
CDialog::OnCancel();
}

void CDlgPaymentKDETicketNo::OnCancel() // Cancel Button
{
	// TODO: Add extra cleanup here
	if (parker) delete parker;
	CDialog::OnCancel();

}

void CDlgPaymentKDETicketNo::OnOk3()  // Search Button
{
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_TICKETNO, _TicketNo);
	_TicketNo.TrimLeft();
	_TicketNo.TrimRight();
	//检测是否为数字

	// Check is it a number
	for (int i = 0; i < _TicketNo.GetLength(); i++)
	{
		if ( ('0' > _TicketNo.GetAt(i)) || ('9' < _TicketNo.GetAt(i)) )
		{
			showTip((LPCTSTR)TIP_CARDNO_NUMERIC);
			GetDlgItem(IDC_TICKETNO)->SetFocus();
			return;
		}
	}
	//检测长度是否合法

	// Check the length of ticket no.
	//if (1 >= _TicketNo.GetLength() || 16 <= _TicketNo.GetLength())
	if (_TicketNo.GetLength() != 8)
	{
		showTip((LPCTSTR)TIP_CARDNO_LENGTH);
		GetDlgItem(IDC_TICKETNO)->SetFocus();
		return;
	}
	UpdateData();
	if (m_CardType ==0) _TicketNo = "O" + _TicketNo;
	else _TicketNo = "B" + _TicketNo;//UCH 3-
//	else _TicketNo = "P" + _TicketNo;
	short result;
	this->m_TicketNo = _TicketNo;
	
	//                   refer to "CCustomer::CExitCarPark::QueryServer(CWnd * pManualWnd)"
	//		             _||_
	//                   \  /
	//                    \/
	result = parker->QueryServer(this); // Query the database   
	if (ERROR_STANDARD > result)
	{
		if (m_ProcessType == 3) // Change VehType
		{
			::AfxMessageBox("猔種 : \nтぃ闽獃ó魁, \n叫浪琩布贺摸の布腹刚!", MB_ICONWARNING|MB_SYSTEMMODAL);
			showTip("猔種 : тぃ闽獃ó魁, 叫浪琩布贺摸の布腹刚!",true);
			return;
		}
		else // Damage / Lost Ticket
		{
			//enable all the disabled items and start to manual input info.
			m_bFindInfoFromNet = FALSE;
			((CDateTimeCtrl *)GetDlgItem(IDC_ENTRYDATE))->EnableWindow(true);
//			((CDateTimeCtrl *)GetDlgItem(IDC_EXITDATE))->EnableWindow(true);
			((CDateTimeCtrl *)GetDlgItem(IDC_ENTRYTIME))->EnableWindow(true);
//			((CDateTimeCtrl *)GetDlgItem(IDC_EXITTIME))->EnableWindow(true);
//			((CComboBox *)GetDlgItem(IDC_ENTRYSTATION))->EnableWindow(true);//UCH 3-
			if (m_ProcessType == 0) //UCH 3- enable vehtype change only when damage ticket
			((CComboBox *)GetDlgItem(IDC_VEHICLETYPE))->EnableWindow(true);//
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
		if (m_ProcessType == 3) //
//		if (m_ProcessType == 0) //UCH 3- enable vehtype change only when damage ticket
			((CComboBox *)GetDlgItem(IDC_VEHICLETYPE))->EnableWindow(true);
		UpdateData(FALSE);
	}
	((CEdit *)GetDlgItem(IDC_TICKETNO))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_OTP))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_KDE))->EnableWindow(FALSE);

	((CButton *)GetDlgItem(IDC_RADIO_DAMG))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_LOST))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_CHANGE_VT))->EnableWindow(FALSE);

	((CButton *)GetDlgItem(IDOK3))->EnableWindow(FALSE);
	((CButton *)GetDlgItem(IDOK))->EnableWindow(TRUE);
	((CDateTimeCtrl *)GetDlgItem(IDC_ENTRYDATE))->SetFocus();
		
}

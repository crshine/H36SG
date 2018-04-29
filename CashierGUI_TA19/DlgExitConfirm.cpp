// DlgExitConfirm.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "DlgExitConfirm.h"
#include "cmdmntsend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExitConfirm dialog


CDlgExitConfirm::CDlgExitConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExitConfirm::IDD, pParent)
{
	m_fontEdit.CreateFont( -24, 0, 0, 0, 700, 0, 0, 0, 1,
	0, 0, 0, 0, _T("MS Sans Serif") );
	//{{AFX_DATA_INIT(CDlgExitConfirm)
	m_nTicketType = -1;
	m_nCardTypeOTP = -1;
	//}}AFX_DATA_INIT
}


void CDlgExitConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExitConfirm)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Calendar);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_Time);
	DDX_Control(pDX, IDC_EDIT_EXTSTN, m_ExitStnEdit);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nTicketType);
	DDX_Radio(pDX, IDC_RADIO_CE_OCTOPUS, m_nCardTypeOTP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExitConfirm, CDialog)
	//{{AFX_MSG_MAP(CDlgExitConfirm)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExitConfirm message handlers

BOOL CDlgExitConfirm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_nTicketType = 0;
//	m_nCardType = 0;
	m_nCardTypeOTP = 0;
	UpdateData(FALSE);

	InitControl();
	this->SetForegroundWindow();

// [BW]20050922 Confirm Exit
// change the DateTime format of the Calendar selection box	
	m_Time.SetFormat("HH':'mm':'ss");		
	m_Calendar.SetFormat("yyyy'/'MM'/'dd");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgExitConfirm::InitControl()
{
	//蜊曹趼极
	GetDlgItem(IDC_TICKETNO)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontEdit);
}

// [BW] 20050920
// Confirm Exit Check Point 001
void CDlgExitConfirm::OnOK() // >> Search Button  
{
	// TODO: Add extra validation here
	CString TicketNo;
	GetDlgItemText(IDC_TICKETNO, TicketNo);
	TicketNo.TrimLeft();
	TicketNo.TrimRight();
	for (int i = 0; i < TicketNo.GetLength(); i++)
	{
		if ( ('0' > TicketNo.GetAt(i)) || ('9' < TicketNo.GetAt(i)) )
		{
			showTip( (LPCTSTR)TIP_CARDNO_NUMERIC );
			return;
		}
	}
	UpdateData();
	if (1 > TicketNo.GetLength() || 16 < TicketNo.GetLength())
//	if (TicketNo.GetLength() != 10 && TicketNo.GetLength() != 8 && m_nCardTypeOTP!=4)//TA19- add 10 bytes card no.
//		if (TicketNo.GetLength() != 8 && m_nCardTypeOTP!=4)
	{
		showTip( (LPCTSTR)TIP_CARDNO_LENGTH );
		return;
	}
	if (TicketNo.GetLength() != 8 && m_nCardTypeOTP==4)//SG- 2018- Season card number,length=8 bytes 
	{
		showTip( "Length of ID card number should be 8!" );
		return;
	}
//	char type = (m_nTicketType == 0 ? 'P' : 'O');   // By combo box [BW] 20050922 
	
	char cardtype;
//	if (m_nCardType == 0) cardtype = 'O';   // By Radio box
//	else cardtype = 'P';

	if (m_nCardTypeOTP == 0) cardtype = 'O';
	else if (m_nCardTypeOTP == 2) cardtype = 'D';
	else if (m_nCardTypeOTP == 3) cardtype = 'L';
	else if (m_nCardTypeOTP == 4) cardtype = 'M';
	else cardtype = 'B';//UCH 3-
//	else cardtype = 'P';

	_CardNo = cardtype + TicketNo; 
	
	CCmdMntSend * pCmdSend = CCmdMntSend::Instance();
	CCmdMntSend::_STRUCT_CardStatus _CardStatus;
	bool sendresult = pCmdSend->QueryCardStatus(_CardNo, _CardStatus);
	if ((_CardStatus._HaveTransaction) && (_CardStatus._TransactionInfo._EntryStation > 0)){
		((CEdit *)GetDlgItem(IDC_EDIT_ENTTIME))->SetWindowText(_CardStatus._TransactionInfo._EntryTime.Format("%Y/%m/%d       %H:%M:%S"));
		((CEdit *)GetDlgItem(IDC_EDIT_ENTSTN))->SetWindowText(show(_CardStatus._TransactionInfo._EntryStation));
		
		if (_CardStatus._TransactionInfo._PayStation >0){
			((CEdit *)GetDlgItem(IDC_EDIT_PAYMENTTIME))->SetWindowText(_CardStatus._TransactionInfo._PayTime.Format("%Y/%m/%d       %H:%M:%S"));
			((CEdit *)GetDlgItem(IDC_EDIT_PAYMENTSTN))->SetWindowText(show(_CardStatus._TransactionInfo._PayStation));
			((CButton *)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
		}
		else {
			::AfxMessageBox("找不到此卡付款紀錄!",MB_SYSTEMMODAL);
			showTip("錯誤 : 找不到此卡付款紀錄!",true);
			((CButton *)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
		}
		
	}
	else if (_CardStatus._TransactionInfo._PayStation >0){
			((CEdit *)GetDlgItem(IDC_EDIT_PAYMENTTIME))->SetWindowText(_CardStatus._TransactionInfo._PayTime.Format("%Y/%m/%d       %H:%M:%S"));
			((CEdit *)GetDlgItem(IDC_EDIT_PAYMENTSTN))->SetWindowText(show(_CardStatus._TransactionInfo._PayStation));
			::AfxMessageBox("找不到此卡入口紀錄!",MB_SYSTEMMODAL);
			showTip("錯誤 : 找不到此卡入口紀錄!",true);
			((CButton *)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			}
	else {
		::AfxMessageBox("找不到此卡紀錄 或 此車已經離場!",MB_SYSTEMMODAL);
		showTip("錯誤 : 找不到此卡紀錄 或 此車已經離場!",true);
	}
}

void CDlgExitConfirm::OnButton2() // Confirm Button
{
	// TODO: Add your control notification handler code here
	CString ExitDate, ExitTime, ExitStn, ExitYY, ExitMM, ExitDD, ExitHH, ExitMin, ExitSS;

	m_Calendar.GetWindowText(ExitDate);   // [PY]: get Exit date
	m_Time.GetWindowText(ExitTime);		  // [PY]: get Exit time
	m_ExitStnEdit.GetWindowText(ExitStn); // [PY]: get Exit station

	ExitYY = ExitDate.Mid(2,2);
	ExitMM = ExitDate.Mid(5,2);
	ExitDD = ExitDate.Mid(8,2);
	ExitHH = ExitTime.Mid(0,2);
	ExitMin = ExitTime.Mid(3,2);
	ExitSS = ExitTime.Mid(6,2);

	
//	CCmdMntSend::Instance()->UpdateTrans(_CardNo, 0, "Exit Confirmation", ExitDate + ExitTime, ExitStn); // [PY]: 07 Jun 2005 - added last 2 args
	CCmdMntSend::Instance()->UpdateTrans(_CardNo, 0, "Exit Confirmation", ExitYY + ExitMM + ExitDD + ExitHH + ExitMin + ExitSS, ExitStn);
	//CDialog::OnOK(); // [PY]: 07 Jun 2005 - removed as this option will only be enabled when validation is successful
	CDialog::OnOK();
}

// [PY]: 07 Jun 2005 - added to set the default values of Exit date, time and stn
void CDlgExitConfirm::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	//m_ExitTimeEdit.SetWindowText(COleDateTime::GetCurrentTime().Format("%H:%S %d/%m/%y")); // display current time as default, calendar preferred instead of letting user key in
	m_ExitStnEdit.SetWindowText("02"); // display '02' as default Exit stn
}

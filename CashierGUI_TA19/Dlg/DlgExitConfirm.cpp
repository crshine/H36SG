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
	//}}AFX_DATA_INIT
}


void CDlgExitConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExitConfirm)
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_Time);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Calendar);
	DDX_Control(pDX, IDC_EDIT_EXTSTN, m_ExitStnEdit);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nTicketType);
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
	UpdateData(FALSE);

	InitControl();
	this->SetForegroundWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgExitConfirm::InitControl()
{
	//蜊曹趼极
	GetDlgItem(IDC_TICKETNO)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontEdit);
}

void CDlgExitConfirm::OnOK() 
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
	if (1 > TicketNo.GetLength() || 16 < TicketNo.GetLength())
	{
		showTip( (LPCTSTR)TIP_CARDNO_LENGTH );
		return;
	}
	UpdateData(); // retrieve dialog data
	char type = (m_nTicketType == 0 ? 'P' : 'O'); // check if 'P'aper ticket or 'O'ctopus card
	_CardNo = type + TicketNo;
	CCmdMntSend * pCmdSend = CCmdMntSend::Instance();
	CCmdMntSend::_STRUCT_CardStatus _CardStatus;
	bool sendresult = pCmdSend->QueryCardStatus(_CardNo, _CardStatus);
	if ((_CardStatus._HaveTransaction) && (_CardStatus._TransactionInfo._EntryStation > 0) &&
		(_CardStatus._TransactionInfo._ExitStation == 0) && // [PY]: 25 Jun 2005 - check that both the Exit station
		(_CardStatus._TransactionInfo._ExitTime == NULL))	// and Exit time are NULL; ie. no Exit record
	{
		((CEdit *)GetDlgItem(IDC_EDIT_ENTTIME))->SetWindowText(_CardStatus._TransactionInfo._EntryTime.Format("%H:%s %d/%m/%y"));
		((CEdit *)GetDlgItem(IDC_EDIT_ENTSTN))->SetWindowText(show(_CardStatus._TransactionInfo._EntryStation));
		((CButton *)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
	}
	else {
		::AfxMessageBox("找不到此卡入口紀錄!");
		showTip("錯誤 : 入口時間錯誤!",true);
	}
}

void CDlgExitConfirm::OnButton2() 
	// TODO: Add your control notification handler code here
	CString ExitDate, ExitTime, ExitStn;

	m_Calendar.GetWindowText(ExitDate);   // [PY]: get Exit date
	m_Time.GetWindowText(ExitTime);		  // [PY]: get Exit time
	m_ExitStnEdit.GetWindowText(ExitStn); // [PY]: get Exit station
	CCmdMntSend::Instance()->UpdateTrans(_CardNo, 0, "Exit Confirmation", ExitDate + ExitTime, ExitStn); // [PY]: 07 Jun 2005 - added last 2 args
	//CDialog::OnOK(); // [PY]: 07 Jun 2005 - removed as this option will only be enabled when validation is successful
}

// [PY]: 07 Jun 2005 - added to set the default values of Exit date, time and stn
void CDlgExitConfirm::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	//m_ExitTimeEdit.SetWindowText(COleDateTime::GetCurrentTime().Format("%H:%S %d/%m/%y")); // display current time as default, calendar preferred instead of letting user key in
	m_ExitStnEdit.SetWindowText("02"); // display '02' as default Exit stn
}

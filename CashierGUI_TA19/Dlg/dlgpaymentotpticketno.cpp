// dlgpaymentotpticketno.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgInput.h"
#include "dlgpaymentotpticketno.h"
extern _System g_System;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPTicketNo dialog
CString CDlgPaymentOTPTicketNo::_CardNo = "";

CDlgPaymentOTPTicketNo::CDlgPaymentOTPTicketNo(CWnd* pParent /*=NULL*/)
	: CDlgInput(CDlgPaymentOTPTicketNo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentOTPTicketNo)
	m_nTicketType = -1;
	//}}AFX_DATA_INIT
}


void CDlgPaymentOTPTicketNo::DoDataExchange(CDataExchange* pDX)
{
	CDlgInput::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentOTPTicketNo)
	DDX_CBIndex(pDX, IDC_COMBO1, m_nTicketType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentOTPTicketNo, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentOTPTicketNo)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPTicketNo message handlers

void CDlgPaymentOTPTicketNo::InitControl()
{
	//改变字体
	GetDlgItem(IDC_TICKETNO)->SetFont(&m_fontEdit);
	GetDlgItem(IDC_COMBO1)->SetFont(&m_fontEdit);
}

BOOL CDlgPaymentOTPTicketNo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_nTicketType = 0;
	UpdateData(FALSE);
	//对话框背景
//248,248,87
//171,21,66
//	m_brush.CreateSolidBrush(RGB(255, 255, 235)); //bg colour
//	m_brush.CreateSolidBrush(RGB(248,248,87));
	InitControl();
	this->SetForegroundWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentOTPTicketNo::OnOK() 
{
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
	UpdateData();
	char type = (m_nTicketType == 0 ? 'P' : 'O');
	_CardNo = type + TicketNo;
	CDialog::OnOK();
}

HBRUSH CDlgPaymentOTPTicketNo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

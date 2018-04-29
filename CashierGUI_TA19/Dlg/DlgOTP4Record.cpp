// DlgOTP4Record.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "DlgOTP4Record.h"
#include "..\CmdOtp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOTP4Record dialog


CDlgOTP4Record::CDlgOTP4Record(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOTP4Record::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOTP4Record)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOTP4Record::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOTP4Record)
	DDX_Control(pDX, IDC_LIST2, m_OTP_Record);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOTP4Record, CDialog)
	//{{AFX_MSG_MAP(CDlgOTP4Record)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOTP4Record message handlers

BOOL CDlgOTP4Record::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_OTP_Record.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_OTP_Record.InsertColumn(0, "", LVCFMT_RIGHT, 30);
	m_OTP_Record.InsertColumn(1, "TransactionTime", LVCFMT_RIGHT, 160);
	m_OTP_Record.InsertColumn(2, "Amount", LVCFMT_RIGHT, 80);
	m_OTP_Record.InsertColumn(3, "SP_ID", LVCFMT_RIGHT, 100);
	m_OTP_Record.InsertColumn(4, "Machine_ID", LVCFMT_RIGHT, 100);

	CardStatus = FALSE;
	ErrTmp = 0;
	Err19=Err24=0;

	SetTimer(1,2000,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//TA11A 2009 for item2.1 item6
void CDlgOTP4Record::OnTimer(UINT nIDEvent) 
{
	CString tmp;
	long devnumber;
	COleDateTime t;
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
//	CCmdOtp::PATRON CardInfo;
	CCmdOtp::PATRON_LOG CardInfo;
	if (!pCmdOtp->OTP_Poll())
	{
		pCmdOtp->OTP_DisplayAfterEnquiry();

//TA2009 shut down MOP during Enquiry, software slow down.
		if (pCmdOtp->GetLastError() ==1)
		{
			SetTimer(1,3600000,0);
//			AfxMessageBox("Reader disconnected, please check!", MB_ICONSTOP|MB_SYSTEMMODAL );
			ErrTmp = 0;
			return;
		}
		if (pCmdOtp->GetLastError() == 32) 
			ErrTmp = 0;

//			AfxMessageBox(TIP_OTP_NO_CARD, MB_ICONSTOP|MB_SYSTEMMODAL );

//TA11A OTP20090819
		if(ErrTmp!=pCmdOtp->GetLastError() )
		{		
//			if (pCmdOtp->GetLastError() == 19 ||pCmdOtp->GetLastError() == 24 ||pCmdOtp->GetLastError() == 34) 
			if (pCmdOtp->GetLastError() == 34) 
			{
				pCmdOtp->OTP_Poll_2(CardInfo);
				ErrTmp =pCmdOtp->GetLastError();
			}
		}
			if (pCmdOtp->GetLastError() == 19) 
			{
				if(Err19!=19 ) 
				{
					Err19 =19;
//					AfxMessageBox("Invalid card !", MB_ICONSTOP|MB_SYSTEMMODAL );
					pCmdOtp->AddOtpLog("Poll",100019,"");
				}
//					pCmdOtp->OTP_Poll_2(CardInfo);
				Err19 =19;
			}
			else
				Err19=0;
			if (pCmdOtp->GetLastError() == 24) 
			{
				if(Err24!=24 )
				{
					Err24 =24;
//					AfxMessageBox("Invalid card!", MB_ICONSTOP|MB_SYSTEMMODAL );
					pCmdOtp->AddOtpLog("Poll",100024,"");
				}
//					pCmdOtp->OTP_Poll_2(CardInfo);
				Err24 =24;
			}
			else
				Err24=0;
//		AfxMessageBox(pCmdOtp->Translate(),MB_SYSTEMMODAL);
		m_OTP_Record.DeleteAllItems();
		GetDlgItem(IDC_CARDNO)->SetWindowText("");
		GetDlgItem(IDC_REMAIN)->SetWindowText("");
//TA11A 2009 for 100019 display.
		if (pCmdOtp->GetLastError() != 32) 
			pCmdOtp->WaitForOtpRemove();

		CardStatus = FALSE;
	}
	else if(!CardStatus)
	if (pCmdOtp->OTP_Poll_2(CardInfo))
	{
// 		CardInfo._CardNo+="00";//TA19- test 10 bytes card number
		GetDlgItem(IDC_CARDNO)->SetWindowText(CardInfo._CardNo);
		tmp.Format("%.2f",CardInfo._Remain);
		GetDlgItem(IDC_REMAIN)->SetWindowText(tmp);
		m_OTP_Record.DeleteAllItems();
		for(int nCount = 0; nCount<4; nCount++)
		{
//			if(nCount<5);
//			MessageBox(CardInfo._AddValueDetail,"",0);
			tmp.Format("%d",nCount+1);
			m_OTP_Record.InsertItem(nCount, tmp);
			t=CardInfo._Log[nCount]._TransactionTime;
			tmp.Format("%04d-%02d-%02d %02d:%02d:%02d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			m_OTP_Record.SetItemText(nCount, 1, tmp);
//TA17- add +- before amount
			tmp.Format("%c%.2f",CardInfo._Log[nCount]._TransactionAmt>0?'+':' ',CardInfo._Log[nCount]._TransactionAmt);

//			tmp.Format("%.2f",CardInfo._Log[nCount]._TransactionAmt);
			m_OTP_Record.SetItemText(nCount, 2, tmp);

			m_OTP_Record.SetItemText(nCount, 3, CardInfo._Log[nCount]._SP_ID);
			devnumber =Str2Int( CardInfo._Log[nCount]._MachineID.GetBuffer(0),8,0 );
			tmp.Format("%X",devnumber);
//			m_OTP_Record.SetItemText(nCount, 4, CardInfo._Log[nCount]._MachineID);
			m_OTP_Record.SetItemText(nCount, 4, tmp);

		}
		CardStatus = TRUE;
		pCmdOtp->OTP_DisplayEnquiry(CardInfo._Remain);
	}
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}

/*
void CDlgOTP4Record::OnTimer(UINT nIDEvent) 
{
	CString tmp;
	COleDateTime t;
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	//	CCmdOtp::PATRON CardInfo;
	CCmdOtp::PATRON_LOG CardInfo;
	if (!pCmdOtp->OTP_Poll_2(CardInfo))
	{
		if (pCmdOtp->GetLastError() != 32) 
			;
		//			AfxMessageBox(TIP_OTP_NO_CARD, MB_ICONSTOP|MB_SYSTEMMODAL );
		m_OTP_Record.DeleteAllItems();
		GetDlgItem(IDC_CARDNO)->SetWindowText("");
		GetDlgItem(IDC_REMAIN)->SetWindowText("");
		CardStatus = FALSE;
	}
	else if(!CardStatus)
	{
		GetDlgItem(IDC_CARDNO)->SetWindowText(CardInfo._CardNo);
		tmp.Format("%.2f",CardInfo._Remain);
		GetDlgItem(IDC_REMAIN)->SetWindowText(tmp);
		m_OTP_Record.DeleteAllItems();
		//		for(int nCount = 0; nCount<4; nCount++)
		for(int nCount = 0; nCount<10; nCount++)
		{
			tmp.Format("%d",nCount+1);
			m_OTP_Record.InsertItem(nCount, tmp);
			t=CardInfo._Log[nCount]._TransactionTime;
			tmp.Format("%04d-%02d-%02d %02d:%02d:%02d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			m_OTP_Record.SetItemText(nCount, 1, tmp);
			tmp.Format("%.2f",CardInfo._Log[nCount]._TransactionAmt);
			m_OTP_Record.SetItemText(nCount, 2, tmp);
			m_OTP_Record.SetItemText(nCount, 3, CardInfo._Log[nCount]._SP_ID);
			m_OTP_Record.SetItemText(nCount, 4, CardInfo._Log[nCount]._MachineID);
		}
		CardStatus = TRUE;
	}
	
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}
*/

void CDlgOTP4Record::OnOK() 
{
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	pCmdOtp->OTP_DisplayAfterEnquiry();
	
	CDialog::OnOK();
}

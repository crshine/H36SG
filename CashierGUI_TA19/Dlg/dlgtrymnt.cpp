// dlgtrymnt.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\CmdMntSend.h"
#include "dlgtrymnt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTryMnt dialog


CDlgTryMnt::CDlgTryMnt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTryMnt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTryMnt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTryMnt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTryMnt)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTryMnt, CDialog)
	//{{AFX_MSG_MAP(CDlgTryMnt)
	ON_BN_CLICKED(IDC_OPERATORACTIONLOG, OnOperatoractionlog)
	ON_BN_CLICKED(IDC_PAYMENT, OnPayment)
	ON_BN_CLICKED(IDC_TIMESYNCHRONIZE, OnTimesynchronize)
	ON_BN_CLICKED(IDC_NONPARKINGPAYMENT, OnNonparkingpayment)
	ON_BN_CLICKED(IDC_FINANCIALMAINTAIN, OnFinancialmaintain)
	ON_BN_CLICKED(IDC_ERRORWARNNOTICELOG, OnErrorwarnnoticelog)
	ON_BN_CLICKED(IDC_UPLOADOTPXFILE, OnUploadotpxfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTryMnt message handlers

void CDlgTryMnt::OnOperatoractionlog() 
{
	const CString Caption = "Test command <Operatoractionlog>";
	const CString Msg = "Send command <Operatoractionlog>\n    Operation   : Try\n    Description : Try command 'Operatoractionlog'.";
		/*
		Send command <Operatoractionlog>
			Operation   : Try
			Description : Try command <Operatoractionlog>."
		*/

	//发送一个消息
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->OperatorActionLog("Try","Try command <Operatoractionlog>.",CCmdMntSend::lvl_Lower);
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnPayment() 
{
	const CString Caption = "Test command <Payment>";
	const CString Msg = "Send command <Payment>\n    CardNo:           'K00000000'\n    Card Type:        2\n    vehicle Category: 3\n    ReceiptNo:        '99999999'\n    Amount:           0\n    TransactionNo :   '12345678901234'.\n";
		/*
			Send command <Payment>
				CardNo:           'K00000000'
				Card Type:        2
				vehicle Category: 3
				ReceiptNo:        '99999999'
				Amount:           0
				TransactionNo :   '12345678901234'.
				Remarks :         'ABCDEFGHIJ1234567890'
		*/
	//发送一个空的停车费付款操作.
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->Payment("K00000000",2,3,COleDateTime::GetCurrentTime(),"99999999",0,0,0,0,"04060111542800","ABCDEFGHIJ1234567890");
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnTimesynchronize() 
{
	const CString Caption = "Test command 'Timesynchronize'";
	const CString Msg = "Send command 'Timesynchronize'";
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->TimeSynchronize();
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnNonparkingpayment() 
{
	const CString Caption = "Test command 'Nonparkingpayment'";
	const CString Msg = "Send command <Nonparkingpayment>\n    CardNo:           'K00000000'\n    Card Type:        2\n    ReceiptNo:        '99999999'\n    Amount:           0\n    PayAction:        1(Create special card).";
		/*
			Send command 'Nonparkingpayment'
				CardNo:           'K00000000'
				Card Type:        2
				ReceiptNo:        '99999999'
				Amount:           0
				PayAction:        1(Create special card).
		*/
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->NonParkingPayment("K00000000",2,"040601115428",CCmdMntSend::act_Create,"99999999",0,0,0,0);
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnFinancialmaintain() 
{
	const CString Caption = "Test command 'Financialmaintain'";
//	const CString Msg = "Send command 'Financialmaintain'\n    ReceiptNo:        '99999999'\n    ShiftPerson:      'Mr. Test'\n    Pay mode0:        '0 -> 0'\n    Pay mode1:        '0 -> 0'\n    Pay mode2:        '0 -> 0'.";
	const CString Msg = "Send command 'Financialmaintain'\n    ReceiptNo:        '99999999'\n    ShiftPerson:      'Mr. Test'\n    Pay mode0:        '0 -> 0'\n    Pay mode1:        '0 -> 0'\n    Pay mode2:        '0 -> 0'\n   Cash Maintain:   '0 -> 0'.";

	/*
			Send command 'Financialmaintain'
				ReceiptNo:        '99999999'
				ShiftPerson:      'Mr. Test'
				Pay mode0:        '0 -> 0'
				Pay mode1:        '0 -> 0'
				Pay mode2:        '0 -> 0'
		*/	
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	//pCmd->FinancialMaintain("040601115428","99999999","Mr. Test", 0, 0, 0, 0, 0, 0);
	MessageBox("No support any more...", Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnErrorwarnnoticelog() 
{
	const CString Caption = "Test command 'Errorwarnnoticelog'";
	const CString Msg = "Send command 'Errorwarnnoticelog'\n    Message:        'try command Errorwarnnoticelog'\n    MessageType:	'Notice'.";
		/*
			Send command 'Errorwarnnoticelog'
				Message:        'try command Errorwarnnoticelog'
				MessageType:	'Notice'
		*/	
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->ErrorWarnNoticeLog("try command Errorwarnnoticelog", CCmdMntSend::msg_Notice);
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

void CDlgTryMnt::OnUploadotpxfile() 
{
	const CString Caption = "Test command 'Uploadotpxfile'";
	const CString Msg = "Send command 'Uploadotpxfile'\n    Message:        'try command Uploadotpxfile'\n    MessageType:	'Notice'.";
		/*
			Send command 'Uploadotpxfile'
				Message:        'try command Uploadotpxfile'
				MessageType:	'Notice'
		*/	
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	pCmd->UploadOtpXFile();
	MessageBox(Msg, Caption, MB_ICONINFORMATION | MB_OK);
}

// DlgCheckCard.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "DlgCheckCard.h"
#include "cmdmntsend.h"
#include "setting.h"
#include "cmdotp.h"
#include "cmdkde.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern _System		g_System;
/////////////////////////////////////////////////////////////////////////////
// CDlgCheckCard dialog


CDlgCheckCard::CDlgCheckCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCheckCard)
	m_CAN = _T("");
	m_Cate = _T("");
	m_Holder = _T("");
	m_PayNum = 0;
	m_PayStn = 0;
	m_PayTime = _T("");
	m_RegTime = _T("");
	m_Validity = _T("");
	m_VehNo = _T("");
	m_EntStn = 0;
	m_SVAmt = _T("");
	m_EntTime = _T("");
	m_PayAmt = _T("");
	m_Kind = _T("");
	m_Credit = _T("");
	m_VehType = 0;
	m_Remarks = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCheckCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCheckCard)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT_CARDNO, m_CAN);
	DDX_Text(pDX, IDC_EDIT_CATE, m_Cate);
	DDX_Text(pDX, IDC_EDIT_HOLDER, m_Holder);
	DDX_Text(pDX, IDC_EDIT_PAYNUM, m_PayNum);
	DDX_Text(pDX, IDC_EDIT_PAYSTN, m_PayStn);
	DDX_Text(pDX, IDC_EDIT_PAYTIME, m_PayTime);
	DDX_Text(pDX, IDC_EDIT_REGTIME, m_RegTime);
	DDX_Text(pDX, IDC_EDIT_VALIDITY, m_Validity);
	DDX_Text(pDX, IDC_EDIT_VEHNO, m_VehNo);
	DDX_Text(pDX, IDC_EDIT_ENTSTN, m_EntStn);
	DDX_Text(pDX, IDC_EDIT_SVAMT, m_SVAmt);
	DDX_Text(pDX, IDC_EDIT_ENTTIME, m_EntTime);
	DDX_Text(pDX, IDC_EDIT_PAYAMT, m_PayAmt);
	DDX_Text(pDX, IDC_EDIT_KIND, m_Kind);
	DDX_Text(pDX, IDC_EDIT_CREDIT, m_Credit);
	DDX_Text(pDX, IDC_EDIT_VEHTYPE, m_VehType);
	DDX_Text(pDX, IDC_EDIT_REMARKS, m_Remarks);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCheckCard, CDialog)
	//{{AFX_MSG_MAP(CDlgCheckCard)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHANGE_VEHTYPE, OnChangeVehtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckCard message handlers

BOOL CDlgCheckCard::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
/*	CRect rect1, rect2;
	::AfxGetMainWnd()->GetWindowRect(&rect2);
	this->GetWindowRect(&rect1);
	rect1.TopLeft().x= rect2.BottomRight().x-402;
	rect1.BottomRight().x= rect1.TopLeft().x + 390;
	rect1.TopLeft().y=rect2.TopLeft().y+95;
	rect1.BottomRight().y=rect1.TopLeft().y+423;
	ScreenToClient(&rect1);
	this->MoveWindow(&rect1,true);
*/	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);


	if (!CCmdMntSend::Instance()->IsNormal()) 
	{
		::AfxMessageBox("警告:\n  由於與管理站通訊中斷, 已完成交易紀錄及特殊卡資訊無法顯示!", MB_ICONEXCLAMATION|MB_SYSTEMMODAL);
		showTip("警告: 由於與管理站通訊中斷, 已完成交易紀錄及特殊卡資訊無法顯示!",true);
		((CStatic *)GetDlgItem(IDC_STATICX))->CWnd::SetWindowText("通訊中斷, 無法找到特殊卡資訊");    
		m_List.InsertColumn(0, "", LVCFMT_LEFT, 200);
		m_List.InsertItem(0, "通訊中斷, 無法顯示已完成交易紀錄!");
	}
	else 
	{
		//m_List.SetItemText(0, 1, show(__iter->second._StationName));
		if (m_nCate == 0)
			((CStatic *)GetDlgItem(IDC_STATICX))->CWnd::SetWindowText("時票沒有特殊卡資訊");
		else
			((CStatic *)GetDlgItem(IDC_STATICX))->CWnd::SetWindowText("特殊卡資訊");
			m_List.InsertColumn(0, "ENTRY TIME", LVCFMT_LEFT, 150);
		m_List.InsertColumn(1, "EXIT TIME", LVCFMT_LEFT, 150);
		m_List.InsertColumn(2, "PAY TIME", LVCFMT_LEFT, 100);
		m_List.InsertColumn(3, "AMOUNT", LVCFMT_LEFT, 100);
		m_List.InsertColumn(4, "REMARK", LVCFMT_LEFT, 150);
//		ShowOldTrans();
	}
	
	m_CAN	=	m_lpCAN;
	m_Cate = showSpecialCardTypeName(m_nCate);
	if (m_tEntTime > 100) m_EntTime=m_tEntTime.Format("%H:%M:%S %d/%m/%y");
	else m_EntTime = "無";
	m_EntStn = m_nEntStn;
	if (m_tPayTime > 100) m_PayTime=m_tPayTime.Format("%H:%M:%S %d/%m/%y");
	else m_PayTime = "無";
	if (m_nPayStn > 0) m_PayStn = m_nPayStn;
	m_PayNum = m_nPayNum;
	m_PayAmt = show(m_dPayAmt);
	m_Kind = (m_nKind == 0 ? _T("磁條票") : _T("八達通"));
	m_Credit =(m_nKind == 0 ? show(0.0) : show(m_fCredit));
	if ((m_nCate > 0) && (m_nCate < 6))
	{
		CString x, y;
		if (m_tValidFrom > 100) x = m_tValidFrom.Format("%d/%m/%y");
		else x = "無";
		if (m_tValidTo > 100) y = m_tValidTo.Format("%d/%m/%y");
		else y = "無";
		if (m_tRegTime > 100) m_RegTime = m_tRegTime.Format("%d/%m/%y");
		else m_RegTime = "無";

		if (m_lpHolder.IsEmpty()) m_Holder = "-無持卡人資訊-";
		else m_Holder = m_lpHolder;
		if (m_lpVehNo.IsEmpty()) m_VehNo = "-無車牌資訊-";
		else m_VehNo = m_lpVehNo;
		if (CSetting::Instance()->m_CardType.IsPeriodWorkMode(m_nCate))
		{
			m_Validity.Format("有效時間: [%s] - [%s]", x, y);
		}
		else {
			m_Validity.Format("有效次數: %d 次", m_nValidTimes);
		}
		if (m_dSVAmt < 0.001) m_SVAmt = "無";
		else m_SVAmt = show(m_dSVAmt);
	}
	UpdateData(FALSE);
	if (CCmdOtp::Instance()->IsConnection()) SetTimer(1, 1500, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCheckCard::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_nKind == 0)
	{//is kde
//		if (!CCmdKde::Instance()->KDE_NeedRead()) this->OnOK();
	}else
	{//is otp
		CCmdOtp * pp = CCmdOtp::Instance();
		CCmdOtp::PATRON CardInfo;
		if (!pp->OTP_Poll(CardInfo, 1)) this->OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgCheckCard::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}


void CDlgCheckCard::ShowOldTrans()
{
	CCmdMntSend * pSend = CCmdMntSend::Instance();
	char buf[MAX_COMMAND_BUF_LENGTH];
	pSend->QueryCardEntryLog(m_lpCAN, buf);
	BYTE TransNum;


	struct String_Format		//	縐陓洘趼睫揹跡宒
	{
		BYTE			TransactNum;
		struct struct_TransactionInfo{
			char		CardNo[17];
			char		TransState;
			char		CardCate;
			char		CarType;
			char		EntryStation[2];
			char		EntryTime[12];
			char		ExitStation[2];
			char		ExitTime[12];
			char		PayStation[2];
			char		PayTime[12];
			char		PaidAmount[6];
			char		PaymentNum;
			char		DiscountPlanID[3];
			char		Remark[17];
		}_T_Info;
	}fmt;
	memcpy(&fmt, buf, sizeof(fmt));
	TransNum = mem2short(fmt.TransactNum);
	struct_TransactionInfo _Trans; 
	for (int i=0; i<TransNum; i++)
	{
		_Trans.CardNo			= mem2str(		fmt._T_Info.CardNo,			sizeof(fmt._T_Info.CardNo) );
		_Trans.TransState		= mem2bool(		fmt._T_Info.TransState		);
		_Trans.CardCate		= mem2short(	fmt._T_Info.CardCate		);
		_Trans.CarType			= mem2short(	fmt._T_Info.CarType			);
		_Trans.EntryStation	= mem2short(fmt._T_Info.EntryStation,			sizeof(fmt._T_Info.EntryStation) );
		_Trans.EntryTime		= mem2datetime(	fmt._T_Info.EntryTime		);
		_Trans.ExitStation		= mem2short(	fmt._T_Info.ExitStation,	sizeof(fmt._T_Info.ExitStation)	);
		_Trans.ExitTime		= mem2datetime(	fmt._T_Info.ExitTime		);
		_Trans.PayStation		= mem2short(	fmt._T_Info.PayStation,		sizeof(fmt._T_Info.PayStation) );
		_Trans.PayTime			= mem2datetime(	fmt._T_Info.PayTime			);
		_Trans.PaidAmount		= mem2dbl(		fmt._T_Info.PaidAmount		);
		_Trans.PaymentNum		= mem2short(	fmt._T_Info.PaymentNum		);
		_Trans.DiscountPlanID	= mem2short(	fmt._T_Info.DiscountPlanID,	sizeof(fmt._T_Info.DiscountPlanID));
		_Trans.Remark			= mem2str(		fmt._T_Info.Remark,			sizeof(fmt._T_Info.Remark));
		ShowTranRec(i, _Trans);
	}
	return ;
}

void CDlgCheckCard::ShowTranRec(int nCount, struct_TransactionInfo Trans)
{
	m_List.InsertItem(nCount,	  Trans.EntryTime.Format("%H:%M %a"));
	m_List.SetItemText(nCount, 1, Trans.ExitTime.Format("%H:%M %a"));
	m_List.SetItemText(nCount, 2, Trans.PayTime.Format("%H:%M %a"));
	m_List.SetItemText(nCount, 3, show(Trans.PaidAmount));
	m_List.SetItemText(nCount, 4, Trans.Remark);
}

void CDlgCheckCard::OnChangeVehtype() 
{
	// TODO: Add your control notification handler code here
	
}

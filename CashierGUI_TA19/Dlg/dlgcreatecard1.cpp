// dlgcreatecard1.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "..\CmdMntSend.h"
#include "dlgcreatecard1.h"
#include "dlgcreatecard.h"
#include "..\cmdotp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard1 property page

CDlgCreateCard1::CDlgCreateCard1()
{
	//{{AFX_DATA_INIT(CDlgCreateCard1)
	m_TypeBrief = _T("");
	m_NumberPart = _T("");
	m_nTypePart = 0;
	//}}AFX_DATA_INIT
}

CDlgCreateCard1::~CDlgCreateCard1()
{
}

void CDlgCreateCard1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateCard1)
	DDX_Text(pDX, IDC_TYPE_BRIEF, m_TypeBrief);
	DDX_Text(pDX, IDC_CARD_NUMBER_PART, m_NumberPart);
	DDX_CBIndex(pDX, IDC_CARD_TYPE_PART, m_nTypePart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateCard1, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateCard1)
	ON_BN_CLICKED(IDC_CATE1, OnCate1)
	ON_BN_CLICKED(IDC_CATE2, OnCate2)
	ON_BN_CLICKED(IDC_CATE3, OnCate3)
	ON_BN_CLICKED(IDC_CATE4, OnCate4)
	ON_BN_CLICKED(IDC_AUTOGAINNO, OnAutoGainNo)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_CARD_TYPE_PART, OnSelchangeCardTypePart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard1 message handlers

BOOL CDlgCreateCard1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	SetTimer(1, 1600, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateCard1::PassValue(Direction direction)
{	//对象与对话框之间值的传递
	CDlgCreateCard * pdlg = (CDlgCreateCard *)m_pDlg;
	if (dir_Obj2Dlg == direction)
	{
		m_TypeId = pdlg->_CardTypeId;
		m_nTypePart = ((pdlg->_CardNo.Left(1) == "P")? 0: 1);
		m_NumberPart = pdlg->_CardNo;
		m_NumberPart = m_NumberPart.Right(1);
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		pdlg->_CardTypeId = m_TypeId;
		pdlg->_CardNo = (m_nTypePart==0?"P":"O") + m_NumberPart;
	}
}

void CDlgCreateCard1::InitControl()
{
	PassValue(dir_Obj2Dlg);	//对话框 <--传值-- 对象
	const CString Error = LPCTSTR(TIP_CARD_CATEGORY_ABSENCE);
	//	自动添入卡类型
	static_cast<CComboBox *>(GetDlgItem(IDC_CARD_TYPE_PART))->SetWindowText((m_nTypePart==0?"P":"O"));
	CSetting  * pSetting = CSetting::Instance();
	//	检测卡种类的是否存在, 如果存在则添入相应的名称.
	//	目前最多有4种卡.
	if ( !pSetting->m_CardType.Valid(1) )
	{
		AfxMessageBox(Error);
		GetDlgItem(IDC_CATE1)->ModifyStyle(WS_VISIBLE,0);
	}
	else
	{
		GetDlgItem(IDC_CATE1)->SetWindowText(pSetting->m_CardType.Name(1));
	}
	if ( !pSetting->m_CardType.Valid(2) )
		GetDlgItem(IDC_CATE2)->ModifyStyle(WS_VISIBLE,0);
	else
		GetDlgItem(IDC_CATE2)->SetWindowText(pSetting->m_CardType.Name(2));
	if ( !pSetting->m_CardType.Valid(3) )
		GetDlgItem(IDC_CATE3)->ModifyStyle(WS_VISIBLE,0);
	else
		GetDlgItem(IDC_CATE3)->SetWindowText(pSetting->m_CardType.Name(3));
	if ( !pSetting->m_CardType.Valid(4) )
		GetDlgItem(IDC_CATE4)->ModifyStyle(WS_VISIBLE,0);
	else
		GetDlgItem(IDC_CATE4)->SetWindowText(pSetting->m_CardType.Name(4));

	//	确定被选择的种类
	if (4 == m_TypeId)
		static_cast<CButton *>(GetDlgItem(IDC_CATE4))->SetCheck(1);
	else if (3 == m_TypeId)
		static_cast<CButton *>(GetDlgItem(IDC_CATE3))->SetCheck(1);
	else if (2 == m_TypeId)
		static_cast<CButton *>(GetDlgItem(IDC_CATE2))->SetCheck(1);
	else
		static_cast<CButton *>(GetDlgItem(IDC_CATE1))->SetCheck(1);

	UpdateBrief();
}

void CDlgCreateCard1::OnCate1() 
{
	m_TypeId = 1;
	UpdateBrief();
}
void CDlgCreateCard1::OnCate2() 
{
	m_TypeId = 2;
	UpdateBrief();
}
void CDlgCreateCard1::OnCate3() 
{
	m_TypeId = 3;
	UpdateBrief();
}
void CDlgCreateCard1::OnCate4() 
{
	m_TypeId = 4;
	UpdateBrief();
}

void CDlgCreateCard1::OnAutoGainNo() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgCreateCard1::OnQuery() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgCreateCard1::UpdateBrief()
{
	short ID = m_TypeId;
	CSetting  * pSetting = CSetting::Instance();
	ASSERT(pSetting->m_CardType.Valid(ID));	//必须存在该种类
	m_TypeBrief.Empty();
	m_TypeBrief  = "Category ID :\t"			+ show(ID);
	m_TypeBrief += "\r\nMode :\t\t"				+ show(pSetting->m_CardType.showWorkMode(ID));
	m_TypeBrief += "\r\nIs Store Value :\t"	+ show(pSetting->m_CardType.StoreValue(ID));
	m_TypeBrief += "\r\nDiscount :\t"			+ show(pSetting->m_CardType.Discount(ID));
	m_TypeBrief += "\r\nPrice :\t\t"			+ pSetting->m_CardType.showPrice(ID);
	m_TypeBrief += "\r\nJoin Fee : "			+ show(pSetting->m_CardType.JoiningFee(ID));
	m_TypeBrief += "\tCard Fee : "			+ show(pSetting->m_CardType.CardFee(ID));
	GetDlgItem(IDC_TYPE_BRIEF)->SetWindowText(m_TypeBrief);
}

bool CDlgCreateCard1::CheckInput()
{
	PassValue(dir_Dlg2Obj);	//对话框 --传值--> 对象

	//检测卡号, '不为空'且'不存在'.
	if ( 1 == ((CDlgCreateCard *)m_pDlg)->_CardNo.GetLength() )
	{
		showTip( (LPCTSTR)TIP_EMPTY_CARDNO );	//输入错误
		return false;
	}
	CCmdMntSend::_STRUCT_CardStatus CardStatus;
	if (!CCmdMntSend::Instance()->QueryCardStatus(((CDlgCreateCard *)m_pDlg)->_CardNo, CardStatus))
	{
		showTip((LPCTSTR)TIP_ERROR_QUERY );	//通讯错误
		return false;
	}
	if ( CardStatus._IsSpecialCard )
	{
		::AfxMessageBox(TIP_EXIST_CARDNO, MB_ICONSTOP|MB_SYSTEMMODAL);	//已经存在
		return false;
	}
	return true;
}

void CDlgCreateCard1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	if (pCmdOtp->OTP_Poll(CardInfo))
	{
		m_nTypePart = 1;
		m_NumberPart = CardInfo._CardNo.Mid(1);
		((CEdit *)GetDlgItem(IDC_CARD_NUMBER_PART))->SetReadOnly(TRUE);
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgCreateCard1::OnSelchangeCardTypePart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_nTypePart == 1) 
	{
		((CEdit *)GetDlgItem(IDC_CARD_NUMBER_PART))->SetReadOnly(TRUE);
		m_NumberPart = "";
	}else{
		((CEdit *)GetDlgItem(IDC_CARD_NUMBER_PART))->SetReadOnly(FALSE);
		m_NumberPart = "";
	}
}

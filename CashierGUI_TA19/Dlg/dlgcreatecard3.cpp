// dlgcreatecard3.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Customer.h"
#include "..\CmdMntSend.h"
#include "dlgcreatecard3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard3 property page

IMPLEMENT_DYNCREATE(CDlgCreateCard3, CPropertyPage)

CDlgCreateCard3::CDlgCreateCard3()
{
	//{{AFX_DATA_INIT(CDlgCreateCard3)
	m_addr1 = _T("");
	m_addr2 = _T("");
	m_addr3 = _T("");
	m_ic = _T("");
	m_id = _T("");
	m_name = _T("");
	m_plate = _T("");
	m_tel = _T("");
	m_zip = _T("");
	//}}AFX_DATA_INIT
}

CDlgCreateCard3::~CDlgCreateCard3()
{
}

void CDlgCreateCard3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateCard3)
	DDX_Text(pDX, IDC_ADDR1, m_addr1);
	DDV_MaxChars(pDX, m_addr1, 40);
	DDX_Text(pDX, IDC_ADDR2, m_addr2);
	DDV_MaxChars(pDX, m_addr2, 40);
	DDX_Text(pDX, IDC_ADDR3, m_addr3);
	DDV_MaxChars(pDX, m_addr3, 40);
	DDX_Text(pDX, IDC_IC, m_ic);
	DDV_MaxChars(pDX, m_ic, 16);
	DDX_Text(pDX, IDC_ID, m_id);
	DDV_MaxChars(pDX, m_id, 4);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 30);
	DDX_Text(pDX, IDC_PLATE, m_plate);
	DDV_MaxChars(pDX, m_plate, 12);
	DDX_Text(pDX, IDC_TEL, m_tel);
	DDV_MaxChars(pDX, m_tel, 15);
	DDX_Text(pDX, IDC_ZIP, m_zip);
	DDV_MaxChars(pDX, m_zip, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateCard3, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateCard3)
	ON_BN_CLICKED(RADIO_NEW, OnNewHolder)
	ON_BN_CLICKED(RADIO_NO, OnNoHolder)
	ON_BN_CLICKED(RADIO_EXIST, OnExistHolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard3 message handlers
void CDlgCreateCard3::PassValue(Direction direction)
{	//对象与对话框之间值的传递

}

void CDlgCreateCard3::InitControl()
{
	PassValue(dir_Obj2Dlg);	//对话框 <--传值-- 对象
	if (1 == static_cast<CButton *>(GetDlgItem(RADIO_NEW))->GetCheck())
		OnNewHolder();
	else if (1 == static_cast<CButton *>(GetDlgItem(RADIO_EXIST))->GetCheck())
		OnExistHolder();
	else //(1 == static_cast<CButton *>(GetDlgItem(RADIO_NO))->GetCheck())
		OnNoHolder();
}

void CDlgCreateCard3::OnNewHolder() 
{
	static_cast<CEdit *>(GetDlgItem(IDC_ID))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_NAME))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_PLATE))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_TEL))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_IC))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR1))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR2))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR3))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_ZIP))->SetReadOnly(false);
}

void CDlgCreateCard3::OnNoHolder() 
{
	static_cast<CEdit *>(GetDlgItem(IDC_ID))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_NAME))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_PLATE))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_TEL))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_IC))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR1))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR2))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR3))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ZIP))->SetReadOnly();
}

void CDlgCreateCard3::OnExistHolder() 
{
	static_cast<CEdit *>(GetDlgItem(IDC_ID))->SetReadOnly(false);
	static_cast<CEdit *>(GetDlgItem(IDC_NAME))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_PLATE))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_TEL))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_IC))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR1))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR2))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ADDR3))->SetReadOnly();
	static_cast<CEdit *>(GetDlgItem(IDC_ZIP))->SetReadOnly();
}

BOOL CDlgCreateCard3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitControl();	
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgCreateCard3::CheckInput()
{
	PassValue(dir_Dlg2Obj);	//对话框 --传值--> 对象
	if (1 == static_cast<CButton *>(GetDlgItem(RADIO_NO))->GetCheck())
	{
		return true;
	}
	m_id.TrimLeft(' ');
	if ( m_id.IsEmpty() )			//输入错误	
	{
		showTip( (LPCTSTR)TIP_EMPTY_HOLDERID );
		return false;
	}
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	CCmdMntSend::_STRUCT_HolderInfo HolderInfo;

	if		(1 == static_cast<CButton *>(GetDlgItem(RADIO_NEW))->GetCheck())
	{
		if ( HolderInfo._HaveHolder )
		{
			showTip( (LPCTSTR)TIP_DUPLICATE_HOLDERID );//已经存在错误
			return false;
		}
	}
	else if (1 == static_cast<CButton *>(GetDlgItem(RADIO_EXIST))->GetCheck())
	{
		if ( !HolderInfo._HaveHolder )
		{
			showTip( (LPCTSTR)TIP_INEXISTENCE_HOLDERID );//尚未存在错误
			return false;
		}
	}

	return true;
}

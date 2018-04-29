// DlgPaymentAccount.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "DlgPaymentAccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentAccount dialog


CDlgPaymentAccount::CDlgPaymentAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPaymentAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPaymentAccount)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPaymentAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPaymentAccount)
	DDX_Control(pDX, IDC_LIST1, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPaymentAccount, CDialog)
	//{{AFX_MSG_MAP(CDlgPaymentAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentAccount message handlers

void CDlgPaymentAccount::InitControl()
{
	//ÐÞ¸Ä×ÖÌå
	CSetting * pSetting = CSetting::Instance();
	GetDlgItem(AMOUNT)->SetFont(&pSetting->FontMid());
	GetDlgItem(CASH)->SetFont(&pSetting->FontMid());
	GetDlgItem(OCTOPUS)->SetFont(&pSetting->FontMid());
	GetDlgItem(STOREVALUE)->SetFont(&pSetting->FontMid());
	GetDlgItem(AMOUNT_TOTAL)->SetFont(&pSetting->FontMid());
	GetDlgItem(CASH_TOTAL)->SetFont(&pSetting->FontMid());
	GetDlgItem(OCTOPUS_TOTAL)->SetFont(&pSetting->FontMid());
	GetDlgItem(STOREVALUE_TOTAL)->SetFont(&pSetting->FontMid());
}

void CDlgPaymentAccount::ShowAccount() // Shift Close Account Check Point (Show Account)
{
	double Amount, Cash, Octopus, StoreValue, CashMaintain;
	CSetting * pSetting = CSetting::Instance();
	COleDateTime x;
	long y;
	pSetting->m_Account.GetCurrentAccount(Amount, Cash, Octopus, StoreValue, x, y, CashMaintain);
	SetDlgItemText(AMOUNT, show(Amount));
	SetDlgItemText(CASH, show(Cash));
	SetDlgItemText(OCTOPUS, show(Octopus));
	SetDlgItemText(STOREVALUE, show(StoreValue));

	long trans[9];
	pSetting->m_Account.GetTotalAccount(Amount, Cash, Octopus, StoreValue, trans, CashMaintain);

	SetDlgItemText(AMOUNT_TOTAL, show(Amount));
	SetDlgItemText(CASH_TOTAL,show(Cash));
	SetDlgItemText(OCTOPUS_TOTAL, show(Octopus));
	SetDlgItemText(STOREVALUE_TOTAL, show(StoreValue));

	for (int i=0;i < m_cList.GetCount();i++) m_cList.DeleteString( i );
	CString catename, tmpstr;
	for (i = 0; i< 9; i++)
	{
		catename = showSpecialCardTypeName(i);
		catename.TrimRight();
		if (catename.IsEmpty()) continue;
/*		if (i==0) catename = "Hourly";
		else if (i < 6) 
		{
			catename = pSetting->m_CardType.Name(i);
			if (catename.IsEmpty()) continue;
		}
		else if (i == 7) catename = "Lost";
		else if (i == 8) catename = "Damage";
		else catename = "Other";*/
		tmpstr.Format("%6d : %s: ", trans[i],catename);
		m_cList.AddString(tmpstr);
	}
	long a, b;CString ab; 
	pSetting->m_Account.GetOtherInfo(Amount, a, Cash, b);
	SetDlgItemText(ADAMT, show(Amount));
	SetDlgItemText(SCMGNAMT,show(Cash));
	ab.Format("%d", a);
	SetDlgItemText(ADNUM, ab);
	ab.Format("%d", b);
	SetDlgItemText(SCMGNNUM, ab);

}

BOOL CDlgPaymentAccount::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect rect1, rect2;
	::AfxGetMainWnd()->GetWindowRect(&rect2);
	this->GetWindowRect(&rect1);
	rect1.TopLeft().x= rect2.BottomRight().x-402;
	rect1.BottomRight().x= rect1.TopLeft().x + 390;
	rect1.TopLeft().y=rect2.TopLeft().y+95;
	rect1.BottomRight().y=rect1.TopLeft().y+423;
	this->MoveWindow(&rect1,true);
	InitControl();
	this->SetForegroundWindow();
	InitControl();

	ShowAccount();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPaymentAccount::OnOK() 
{
	ShowAccount();
}

void CDlgPaymentAccount::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

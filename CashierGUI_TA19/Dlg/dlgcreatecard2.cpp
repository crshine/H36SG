// dlgcreatecard2.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "..\Setting.h"
#include "dlgcreatecard2.h"
#include "dlgcreatecard.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard2 property page

IMPLEMENT_DYNCREATE(CDlgCreateCard2, CPropertyPage)

CDlgCreateCard2::CDlgCreateCard2()
{
	//{{AFX_DATA_INIT(CDlgCreateCard2)
	m_ValidFrom = COleDateTime::GetCurrentTime();
	m_ValidTo = COleDateTime::GetCurrentTime();
	m_StoreValue = _T("");
	m_TransTimes = 0;
	//}}AFX_DATA_INIT
}

CDlgCreateCard2::~CDlgCreateCard2()
{
}

void CDlgCreateCard2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateCard2)
	DDX_DateTimeCtrl(pDX, PERIODFROM, m_ValidFrom);
	DDX_DateTimeCtrl(pDX, PERIODTO, m_ValidTo);
	DDX_Text(pDX, STOREVALUE, m_StoreValue);
	DDX_Text(pDX, TRANSTIMES, m_TransTimes);
	DDV_MinMaxInt(pDX, m_TransTimes, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateCard2, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateCard2)
	ON_BN_CLICKED(RADIO_1M, On1m)
	ON_BN_CLICKED(RADIO_2M, On2m)
	ON_BN_CLICKED(RADIO_3M, On3m)
	ON_BN_CLICKED(RADIO_6M, On6m)
	ON_BN_CLICKED(RADIO_12M, On12m)
	ON_BN_CLICKED(RADIO_24M, On24m)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard2 message handlers
void CDlgCreateCard2::PassValue(Direction direction)
{	//对象与对话框之间值的传递
	CDlgCreateCard * pdlg = (CDlgCreateCard *)m_pDlg;
	if (dir_Obj2Dlg == direction)
	{
		m_ValidFrom		= pdlg->_ValidFrom;
		m_ValidTo		= pdlg->_ValidTo;
		m_StoreValue	= show(pdlg->_StoreValueFee);
		m_TransTimes	= pdlg->_ValidTranTimes;
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		pdlg->_ValidFrom		= m_ValidFrom;
		pdlg->_ValidTo			= m_ValidTo;
		m_StoreValue.Replace('$',' ');
		pdlg->_StoreValueFee	= atof(m_StoreValue);
		pdlg->_ValidTranTimes	= m_TransTimes;
	}
}

void CDlgCreateCard2::InitControl()
{
	CSetting * pSetting = CSetting::Instance();
	//修改字体
	GetDlgItem(TRANSTIMES)->SetFont(&pSetting->FontMid());
	GetDlgItem(STOREVALUE)->SetFont(&pSetting->FontMid());

	COleDateTime t = COleDateTime::GetCurrentTime();
	m_ValidFrom.SetDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);
	m_ValidTo.SetDateTime(t.GetYear(), t.GetMonth(), t.GetDay(), 0, 0, 0);

	PassValue(dir_Obj2Dlg);	//对话框 <--传值-- 对象
	short ID = ((CDlgCreateCard *)m_pDlg)->_CardTypeId;

	if ( pSetting->m_CardType.IsPeriodWorkMode(ID) )
	{
		GetDlgItem(PERIODFROM)->EnableWindow();
		GetDlgItem(PERIODTO)->EnableWindow();
		GetDlgItem(RADIO_1M)->EnableWindow();
		GetDlgItem(RADIO_2M)->EnableWindow();
		GetDlgItem(RADIO_3M)->EnableWindow();
		GetDlgItem(RADIO_6M)->EnableWindow();
		GetDlgItem(RADIO_12M)->EnableWindow();
		GetDlgItem(RADIO_24M)->EnableWindow();
	}
	else
	{
		GetDlgItem(PERIODFROM)->EnableWindow(false);
		GetDlgItem(PERIODTO)->EnableWindow(false);
		GetDlgItem(RADIO_1M)->EnableWindow(false);
		GetDlgItem(RADIO_2M)->EnableWindow(false);
		GetDlgItem(RADIO_3M)->EnableWindow(false);
		GetDlgItem(RADIO_6M)->EnableWindow(false);
		GetDlgItem(RADIO_12M)->EnableWindow(false);
		GetDlgItem(RADIO_24M)->EnableWindow(false);
	}

	if ( pSetting->m_CardType.IsTimesWorkMode(ID) )
		GetDlgItem(TRANSTIMES)->EnableWindow();
	else
		GetDlgItem(TRANSTIMES)->EnableWindow(false);

	if ( pSetting->m_CardType.StoreValue(ID) )
		GetDlgItem(STOREVALUE)->EnableWindow();
	else
		GetDlgItem(STOREVALUE)->EnableWindow(false);
}

void CDlgCreateCard2::On1m() 
{
	AddMonth(1);
}

void CDlgCreateCard2::On2m() 
{
	AddMonth(2);
}

void CDlgCreateCard2::On3m() 
{
	AddMonth(3);
}

void CDlgCreateCard2::On6m() 
{
	AddMonth(6);
}

void CDlgCreateCard2::On12m() 
{
	AddMonth(12);
}

void CDlgCreateCard2::On24m() 
{
	AddMonth(24);
}

BOOL CDlgCreateCard2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateCard2::AddMonth(short Month)
{
	UpdateData(true);
	short Year = m_ValidFrom.GetYear();
	Month += m_ValidFrom.GetMonth();
	
	while (Month > 12)
	{
		Month -= 12;
		++Year;
	}
	short day = m_ValidFrom.GetDay();
	if ((day >= 29) && (Month == 2)) {day =1; Month = 3;}
	if (day == 31)
	{
		if ((Month == 2) || (Month == 4) ||(Month == 6) ||(Month == 9) ||(Month == 11)) 
		{
			day = 1; Month ++;
		}
	}
	m_ValidTo.SetDateTime(Year, Month, day, 0, 0, 0);
	UpdateData(false);
}

bool CDlgCreateCard2::CheckInput()
{
	if ( !UpdateData(true) ) return false;

	PassValue(dir_Dlg2Obj);	//对话框 --传值--> 对象
	//检测时间的有效性
	if ( m_ValidTo < m_ValidFrom )
	{
		showTip( (LPCTSTR)TIP_INVALID_PERIOD );
		return false;
	}
	//检测有效次数
	//检测储值
	return true;
}


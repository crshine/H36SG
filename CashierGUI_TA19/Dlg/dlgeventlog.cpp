// DlgEventLog.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "DlgEventLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLog *		g_pLog;


/////////////////////////////////////////////////////////////////////////////
// CDlgEventLog dialog


CDlgEventLog::CDlgEventLog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEventLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEventLog)
	m_sKey = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEventLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEventLog)
	DDX_Control(pDX, IDC_EVENTLOG_TYPE, m_ComboType);
	DDX_Control(pDX, IDC_EVENTLOG_LIST, m_listLog);
	DDX_Text(pDX, IDC_EVENTLOG_KEY, m_sKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEventLog, CDialog)
	//{{AFX_MSG_MAP(CDlgEventLog)
	ON_BN_CLICKED(IDSEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEventLog message handlers

BOOL CDlgEventLog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//init ButtonN
	//按钮样式
	VERIFY(m_Colorbtn[0].Attach(IDOK, this));
	VERIFY(m_Colorbtn[1].Attach(IDSEARCH, this));
	VERIFY(m_Colorbtn[2].Attach(IDPRINT, this));
	//init ComboBox
	//组合框
	CString xyz; int nSize = 256;
	::LoadString( GetModuleHandle(NULL),IDS_MSG_TYPE_ALL, xyz.GetBuffer(nSize-1), nSize); xyz.ReleaseBuffer();
	m_ComboType.AddString(xyz);//LoadS(IDS_MSG_TYPE_ALL));
	xyz.Empty();
	::LoadString( GetModuleHandle(NULL),IDS_MSG_TYPE_SYSTEM, xyz.GetBuffer(nSize-1), nSize); xyz.ReleaseBuffer();
	m_ComboType.AddString(xyz);//LoadS(IDS_MSG_TYPE_SYSTEM));
	::LoadString( GetModuleHandle(NULL),IDS_MSG_TYPE_WARNING, xyz.GetBuffer(nSize-1), nSize); xyz.ReleaseBuffer();
	m_ComboType.AddString(xyz);//LoadS(IDS_MSG_TYPE_WARNING));
	::LoadString( GetModuleHandle(NULL),IDS_MSG_TYPE_OPERATOR, xyz.GetBuffer(nSize-1), nSize); xyz.ReleaseBuffer();
	m_ComboType.AddString(xyz);//LoadS(IDS_MSG_TYPE_OPERATOR));
	::LoadString( GetModuleHandle(NULL),IDS_MSG_TYPE_ERROR, xyz.GetBuffer(nSize-1), nSize); xyz.ReleaseBuffer();
	m_ComboType.AddString(xyz);//LoadS(IDS_MSG_TYPE_ERROR));
	m_ComboType.SetCurSel(0);
	//init listlog
	//列表框
	m_listLog.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listLog.InsertColumn(0, LoadS(IDS_STRING_TIME), LVCFMT_LEFT, 140);
	m_listLog.InsertColumn(1, LoadS(IDS_STRING_TYPE), LVCFMT_LEFT, 80);
	m_listLog.InsertColumn(2, LoadS(IDS_STRING_MSG), LVCFMT_LEFT, 1000);
	//init search condition
	UpdateData(false);

	//时间
	COleDateTime m_MinDate, m_MaxDate, m_CurDate;
	m_MinDate.SetDate(2000,1,1);
	m_MaxDate.SetDate(2100,1,1);
	m_CurDate.GetCurrentTime();

	CDateTimeCtrl * m_DateTimeCtrl;
	m_DateTimeCtrl = (CDateTimeCtrl *)GetDlgItem(IDC_DLGEVENTLOG_DATE_BEGIN);
	m_DateTimeCtrl->SetRange(&m_MinDate, &m_MaxDate);
	m_DateTimeCtrl->SetTime(m_CurDate);
	m_DateTimeCtrl = (CDateTimeCtrl *)GetDlgItem(IDC_DLGEVENTLOG_DATE_END);
	m_DateTimeCtrl->SetRange(&m_MinDate, &m_MaxDate);
	m_DateTimeCtrl->SetTime(m_CurDate);
	
	return true;
}

void CDlgEventLog::OnSearch() 
{
	//show the search result!
	//test the condition of search.
	//show the result to the list top 500.
	UpdateData(true);

	COleDateTime m_DateBegin, m_DateEnd;
	CDateTimeCtrl * m_DateTimeCtrl;
	m_DateTimeCtrl = (CDateTimeCtrl *)GetDlgItem(IDC_DLGEVENTLOG_DATE_BEGIN);
	m_DateTimeCtrl->GetTime(m_DateBegin);
	m_DateTimeCtrl = (CDateTimeCtrl *)GetDlgItem(IDC_DLGEVENTLOG_DATE_END);
	m_DateTimeCtrl->GetTime(m_DateEnd);

	CString sType;
	int sel=m_ComboType.GetCurSel();
	m_ComboType.GetLBText(sel,sType);
	m_sKey.TrimLeft();
	m_sKey.TrimRight();
	m_listLog.DeleteAllItems();

	COleDateTimeSpan OneDay;
	OneDay.SetDateTimeSpan(1,0,0,0);

	int iCount = 0;
	BOOL bResult = true;
	CString sLogName;
	//如果 结束日期<= 开始日期，那么显示开始日期那天的日志。
	//如果 结束日期 > 开始日期，那么从结束日期开始直到开始日期或到1000个记录。
	if (m_DateEnd < m_DateBegin)
		m_DateEnd = m_DateBegin;

	while (m_DateEnd >= m_DateBegin) {
		sLogName = m_DateEnd.Format(_T("%Y-%m-%d"));
		sLogName += ".log";
		bResult = g_pLog->ReadLog(reinterpret_cast<DWORD> (&m_listLog), sLogName, sType, iCount, m_sKey);
		if (iCount >= 1000) break;
		m_DateEnd -= OneDay;
	}

	if ((0 == iCount)&&(bResult)){
		SetDlgItemText(IDC_TEXT_RESULT, "Result:    Log file Read failure." );
	}else if ((0 == iCount)&&(!bResult)){
		SetDlgItemText(IDC_TEXT_RESULT, "Result:    Sorry find nothing." );
	}else if (1000 == iCount){
		SetDlgItemText(IDC_TEXT_RESULT, "Result:    Only show the top 1000 result." );
	}else{
		CString sTmp;
		sTmp.Format("Result:    find %i result.", iCount);   
		SetDlgItemText(IDC_TEXT_RESULT, sTmp);
	}
}

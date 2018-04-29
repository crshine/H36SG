// DlgProgress.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "DlgProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProgress dialog

CDlgProgress::CDlgProgress(UINT Second, CString OperateName, CWnd* pParent/* = NULL*/)
	: CDialog(CDlgProgress::IDD, pParent)
	, _EventID(1), _TimerStep(100)
{
	_Operate = OperateName;	//操作名称
	_TotalStep = Second * 1000 / _TimerStep;
}

void CDlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProgress)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProgress, CDialog)
	//{{AFX_MSG_MAP(CDlgProgress)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProgress message handlers

void CDlgProgress::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == _EventTimerID)
	{
		int Lower, Upper, Pos = m_Progress.GetPos();
		m_Progress.GetRange(Lower, Upper);
		SetDlgItemText(IDC_ELAPSE, show((long)(Pos * _TimerStep / 1000 )) + " / " + 
								   show((long)(Upper * _TimerStep / 1000 )) + "Second");
		if (Pos >= Upper) 
		{
			KillTimer(_EventTimerID);
			CDialog::OnOK();
		}
		else
		{
			m_Progress.SetPos(++Pos);
		}
	}	
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProgress::InitControl()
{
	SetDlgItemText(IDC_OPERATE, _Operate);	//操作名称
	const int Lower = 0, Step = 1;
	m_Progress.SetRange(Lower, _TotalStep);
	m_Progress.SetStep(Step);
	m_Progress.SetPos(Lower);
	_EventTimerID = SetTimer(_EventID, _TimerStep, NULL);
}

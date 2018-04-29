// PayMode.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "PayMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PayMode dialog

PayMode::PayMode(CWnd* pParent /*=NULL*/)
: CDlgInput(PayMode::IDD, pParent)

//PayMode::PayMode(CWnd* pParent /*=NULL*/)
//	: CDialog(PayMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(PayMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PayMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PayMode)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PayMode, CDialog)
	//{{AFX_MSG_MAP(PayMode)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PayMode message handlers

BOOL PayMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	SetWindowPos(HWND_TOP,0,0,0,0,0 );
	
//	this->SetWindowPos(wndTop   , 0, 0, 110,110,		SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	SetTimer(1,1000,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PayMode::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

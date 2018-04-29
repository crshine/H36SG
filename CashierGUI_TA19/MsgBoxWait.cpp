// MsgBoxWait.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "MsgBoxWait.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsgBoxWait dialog


MsgBoxWait::MsgBoxWait(CWnd* pParent /*=NULL*/)
	: CDialog(MsgBoxWait::IDD, pParent)
{
	//{{AFX_DATA_INIT(MsgBoxWait)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MsgBoxWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MsgBoxWait)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MsgBoxWait, CDialog)
	//{{AFX_MSG_MAP(MsgBoxWait)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgBoxWait message handlers

void MsgBoxWait::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL MsgBoxWait::OnInitDialog() 
{
	CDialog::OnInitDialog();
MessageBox("aaa","");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

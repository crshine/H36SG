// DlgEntCreate.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "DlgEntCreate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEntCreate dialog


//DEL CDlgEntCreate::CDlgEntCreate(CWnd* pParent /*=NULL*/)
//DEL 	: CDialog(CDlgEntCreate::IDD, pParent)
//DEL {
//DEL 	//{{AFX_DATA_INIT(CDlgEntCreate)
//DEL 		// NOTE: the ClassWizard will add member initialization here
//DEL 	//}}AFX_DATA_INIT
//DEL }


//DEL void CDlgEntCreate::DoDataExchange(CDataExchange* pDX)
//DEL {
//DEL 	CDialog::DoDataExchange(pDX);
//DEL 	//{{AFX_DATA_MAP(CDlgEntCreate)
//DEL 		// NOTE: the ClassWizard will add DDX and DDV calls here
//DEL 	//}}AFX_DATA_MAP
//DEL }


BEGIN_MESSAGE_MAP(CDlgEntCreate, CDialog)
	//{{AFX_MSG_MAP(CDlgEntCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEntCreate message handlers

//DEL BOOL CDlgEntCreate::OnInitDialog() //[BW] 20050803
//DEL {
//DEL 	CDialog::OnInitDialog();
//DEL 	
//DEL 	CRect rect1, rect2;
//DEL 	::AfxGetMainWnd()->GetWindowRect(&rect2);
//DEL 	this->GetWindowRect(&rect1);
//DEL 	rect1.TopLeft().x= rect2.BottomRight().x-402;
//DEL 	rect1.BottomRight().x= rect1.TopLeft().x + 395;
//DEL 	rect1.TopLeft().y=rect2.TopLeft().y+90;
//DEL 	rect1.BottomRight().y=rect1.TopLeft().y+423;
//DEL 	this->MoveWindow(&rect1,true);
//DEL 	this->SetForegroundWindow();
//DEL 
//DEL 	return TRUE;	
//DEL }

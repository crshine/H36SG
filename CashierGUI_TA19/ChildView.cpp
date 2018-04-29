// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "CashierGUI.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern _System		g_System;

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
	delete m_pDlgPayment;
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnInitialUpdate()
{
	//创建主窗体
	m_pDlgPayment=new CDlgPayment;
	m_pDlgPayment->Create(IDD_PAYMENT, this);
	m_pDlgPayment->MoveWindow(0, 0, 14400, 14400);
	m_pDlgPayment->ShowWindow(SW_SHOW);
	g_System.RunTime.hOtpPaymentDlg = m_pDlgPayment->m_hWnd;
	CDlgPayment::AddAccountLog();
}


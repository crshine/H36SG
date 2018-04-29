// ZZCtrltoolbar.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "ZZCtrltoolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZZCtrlToolBar

CZZCtrlToolBar::CZZCtrlToolBar()
{
}

CZZCtrlToolBar::~CZZCtrlToolBar()
{
}


BEGIN_MESSAGE_MAP(CZZCtrlToolBar, CToolBar)
	//{{AFX_MSG_MAP(CZZCtrlToolBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZZCtrlToolBar message handlers

BOOL CZZCtrlToolBar::LoadToolBarEx(UINT nIDResource, UINT nID)
{
	BOOL bRet;
	bRet = CToolBar::LoadToolBar(nIDResource);
	// find where our ctrl will go
	int pos = CommandToIndex(nID);
	
	//convert button in toolbar into a spacer for our ctrl 
	SetButtonInfo(pos, nID, TBBS_SEPARATOR, 200);
	// create our ctrl
	CRect rect;
	GetItemRect(pos,&rect);
	rect.bottom+=300;
	
	m_ZZClockText.Create(_T("hihi"),WS_CHILD|WS_VISIBLE,rect,this,nID);
	m_ZZClockText.Start();
	return bRet;
}


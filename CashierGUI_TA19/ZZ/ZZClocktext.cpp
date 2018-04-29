// ZZClocktext.cpp : implementation file
//

#include "stdafx.h"
#include "ZZClocktext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZZClockText

CZZClockText::CZZClockText()
{
}

CZZClockText::~CZZClockText()
{
	if (m_thrParam.hThrHandle)
	{
		m_thrParam.bRun = FALSE;
		::WaitForSingleObject(m_thrParam.hThrHandle, 1500);
	}
}


BEGIN_MESSAGE_MAP(CZZClockText, CStatic)
	//{{AFX_MSG_MAP(CZZClockText)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZZClockText message handlers

void CZZClockText::OnPaint() 
{
	CZZTitleStatic::OnPaint();	
}

BOOL CZZClockText::OnEraseBkgnd(CDC* pDC) 
{
	return CZZTitleStatic::OnEraseBkgnd(pDC);
}

UINT CZZClockText::thrClock(LPVOID pParam)
{
	STRUCT_THRCLOCK* p;
	CZZClockText* pParent;

	p = (STRUCT_THRCLOCK*)pParam;
	pParent = (CZZClockText*)p->pParent;

	TRACE(_T("thrClock: Enter \n"));

	// Main loop
	while (p->bRun == TRUE)
	{
		pParent->Refresh();

		::Sleep(1000);
	} // while

	TRACE(_T("thrClock: Exit \n"));

	return 0;
}

void CZZClockText::Refresh()
{
	SYSTEMTIME	csTime;
	// Get current date and time
	::GetLocalTime(&csTime);

	CTime t(csTime);
//	CString sDate = t.Format( "%b %d. %Y     [%a]" );
//	CString sTime = t.Format( "%H:%M:%S" );
	sTitle = t.Format( "%b %d. %Y     [%a]" );
	sText = t.Format( "%H:%M:%S" );
	
	if (IsWindow(m_hWnd))
		RedrawWindow();

//	SetWindowText(sDate, TRUE);
//	SetWindowText(sTime);

}

BOOL CZZClockText::Start()
{
//	SetBackgroundColor(RGB(00,102,153));
	SetBackgroundColor(RGB(010,010,010));
	SetTextColor(RGB(255,255,255));
	SetTextColor(RGB(255,255,255), TRUE);
	SetMargins(1, 0, TRUE);
	SetMargins(80, 18);

	::ZeroMemory(&m_thrParam, sizeof(m_thrParam));
	m_thrParam.pParent = this;
	m_thrParam.bRun = TRUE;

    CWinThread* cw = AfxBeginThread( &thrClock, (LPVOID)&m_thrParam );
	if (cw == NULL)
	{
		return FALSE;
	}
	m_thrParam.hThrHandle = cw->m_hThread;
	m_thrParam.dwThrId = cw->m_nThreadID;

	return TRUE;
}


// dlginput.cpp : implementation file
//

#include "stdafx.h"
#include "..\CashierGUI.h"
#include "dlginput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog


CDlgInput::CDlgInput(UINT uResourceID, CWnd* pParent)
: CDialog(uResourceID, pParent)
{
	m_fontEdit.CreateFont( -24, 0, 0, 0, 700, 0, 0, 0, 1,
	0, 0, 0, 0, _T("MS Sans Serif") );
}

void CDlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInput, CDialog)
	//{{AFX_MSG_MAP(CDlgInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInput message handlers

BOOL CDlgInput::PreTranslateMessage(MSG* pMsg) 
{
	if(WM_KEYDOWN == pMsg->message || WM_KEYUP == pMsg->message)
	{
		if (VK_DOWN == pMsg->wParam)
		{//"DOWN" -> "TAB"
			pMsg->wParam = VK_TAB;	
		}
		else if(VK_UP == pMsg->wParam)
		{//"UP" ->"SHIFT" + "TAB"
			if (WM_KEYDOWN == pMsg->message)
			{	keybd_event(VK_SHIFT,0,0,0);	
				keybd_event(VK_TAB,0,0,0);	}
			else
			{	keybd_event(VK_SHIFT,0,2,0);	
				keybd_event(VK_TAB,0,2,0);	}
			return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////////
//取消操作提示
void CDlgInput::OnCancel() 
{
//	if ( IDYES==MessageBox(	(CString)(LPCTSTR)SYS_MSG_CANCEL_OPERATE,
//							(CString)(LPCTSTR)SYS_MSG_WARNING,
//							MB_YESNO| MB_ICONWARNING  ) )
//	{
		CDialog::OnCancel();
//	}
}

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A975881A_4D4F_41EC_A59E_307005A3C9BB__INCLUDED_)
#define AFX_MAINFRM_H__A975881A_4D4F_41EC_A59E_307005A3C9BB__INCLUDED_

#include "ZZ\ZZTitleStatic.h"
#include "ZZ\ZZClockText.h"
#include "ChildView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DockControlBarLeftOf(CControlBar* Bar, CControlBar* LeftOf);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar		m_wndToolBar;
	CToolBar		m_wndToolBarTime;
	CToolBar		m_wndToolBarOperator;
	CToolBar		m_wndToolBarStatus;
	CChildView		m_wndView;
	CZZClockText	m_ZZClockTextClock;
	CZZTitleStatic	m_ZZTitleStaticOperator;
	CZZTitleStatic	m_ZZTitleStaticAccount;
// Generated message map functions
public:
	afx_msg void OnMntSetStart();
	afx_msg void OnMntSetStop();
	afx_msg void OnKdeSetStart();
	afx_msg void OnKdeSetStop();
	afx_msg void OnOtpSetStart();
	afx_msg void OnOtpSetStop();

protected:
	afx_msg LRESULT OnRaMsg(WPARAM wParam,LPARAM lParam );
	afx_msg LRESULT OnSetCommStatus(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewOperatorBar();
	afx_msg void OnUpdateViewOperatorBar(CCmdUI* pCmdUI);
	afx_msg void OnViewTimeBar();
	afx_msg void OnUpdateViewTimeBar(CCmdUI* pCmdUI);
	afx_msg void OnSettingSystem();
	afx_msg void OnSettingOtpReader();
	afx_msg void OnEventLog();
	afx_msg void OnCalculate();
	afx_msg void OnViewStatusBar();
	afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnSettingFeeRate();
	afx_msg void OnHelp();
	afx_msg void OnClose();
	afx_msg void OnSettingCardcategory();
	afx_msg void OnCardSearch();
	afx_msg void OnSettingPaymode();
	afx_msg void OnSettingDiscountplan();
	afx_msg void OnSettingCalculaterule();
	afx_msg void OnSettingStation();
	afx_msg void OnSettingCardtype();
	afx_msg void OnSettingGrouptype();
	afx_msg void OnSettingPaymodetype();
	afx_msg void OnSettingCartype();
	afx_msg void OnTryMnt();
	afx_msg void OnViewAccount();
	afx_msg void OnSettingReceiptFormat();
	afx_msg void OnSettingPermission();
	afx_msg void OnSettingSysParameters();
	afx_msg void OnToolViewKdeCard();
	afx_msg void OnToolViewOtpCard();
	afx_msg void OnCardCreate();
	afx_msg void OnCardTopup();
	afx_msg void OnOtpRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A975881A_4D4F_41EC_A59E_307005A3C9BB__INCLUDED_)

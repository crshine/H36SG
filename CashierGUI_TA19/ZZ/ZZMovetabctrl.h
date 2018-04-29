#if !defined(AFX_ZZMOVETABCTRL_H__88BFEF53_6F96_48A4_AEB0_3F261CB28579__INCLUDED_)
#define AFX_ZZMOVETABCTRL_H__88BFEF53_6F96_48A4_AEB0_3F261CB28579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZZMovetabctrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZZMoveTabCtrl window

class CZZMoveTabCtrl : public CTabCtrl
{
// Construction
public:
	CZZMoveTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZZMoveTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_ispeed;//�˶��ٶ�
	BOOL m_bMove;//�Ƿ��˶�
	int m_wndwidth;//�Ӵ���Ŀ��
	CPoint m_bottomright;//�Ӵ������½ǵ�����
	CPoint m_topleft;//�Ӵ������Ͻǵ�����
	CWnd *m_pCurWnd;//��ǰ����
	CRect m_tabrect;//Tab�ľ�������
	CPoint m_ptTabs;//���Ͻ�����
	void AddItem(CWnd *pwnd,LPTSTR name);//���ѡ�
	int m_itemcount;//Item����
	virtual ~CZZMoveTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZZMoveTabCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZZMOVETABCTRL_H__88BFEF53_6F96_48A4_AEB0_3F261CB28579__INCLUDED_)

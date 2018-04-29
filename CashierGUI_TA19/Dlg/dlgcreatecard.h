#if !defined(AFX_DLGCREATECARD_H__08DC39AE_21A5_4224_843C_6DB9B34B8A0B__INCLUDED_)
#define AFX_DLGCREATECARD_H__08DC39AE_21A5_4224_843C_6DB9B34B8A0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgcreatecard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateCard dialog
class CDlgCreateCard1;
class CDlgCreateCard2;
class CDlgCreateCard3;
class CDlgCreateCard4;

class CDlgCreateCard : public CDialog
{
// Construction
public:
	~CDlgCreateCard();
	USHORT m_CurrentStep;
	CDlgCreateCard(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgCreateCard)
	enum { IDD = IDD_CARD_CREATE };
	CButton	m_NEXT;
	CButton	m_BACK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateCard)
	afx_msg void OnButtonBack();
	afx_msg void OnButtonNext();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowStep();
	CDialog * m_pDlg;
public:
	CString	_CardNo;
	USHORT	_CardTypeId;
	COleDateTime _ValidFrom;
	COleDateTime _ValidTo;
	short  _ValidTranTimes;
	double _StoreValueFee;
	double _PeriodFee;
	double _TransactionFee;
	double _JoiningFee;
	double _CardFee; 
	double Calculate();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECARD_H__08DC39AE_21A5_4224_843C_6DB9B34B8A0B__INCLUDED_)

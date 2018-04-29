#if !defined(AFX_DLGCHECKCARD_H__47B8E62F_7B57_4101_9D42_64E508E4A955__INCLUDED_)
#define AFX_DLGCHECKCARD_H__47B8E62F_7B57_4101_9D42_64E508E4A955__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCheckCard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckCard dialog

class CDlgCheckCard : public CDialog
{
// Construction
public:
	CDlgCheckCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCheckCard)
	enum { IDD = IDD_CHECKCARD };
	CListCtrl	m_List;
	CString	m_CAN;
	CString	m_Cate;
	CString	m_Holder;
	int		m_PayNum;
	int		m_PayStn;
	CString	m_PayTime;
	CString	m_RegTime;
	CString	m_Validity;
	CString	m_VehNo;
	int		m_EntStn;
	CString	m_SVAmt;
	CString	m_EntTime;
	CString	m_PayAmt;
	CString	m_Kind;
	CString	m_Credit;
	int		m_VehType;
	CString	m_Remarks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCheckCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	struct struct_TransactionInfo{
		CString		CardNo;
		int		TransState;
		int		CardCate;
		int		CarType;
		int			EntryStation;
		COleDateTime EntryTime;
		int		ExitStation;
		COleDateTime ExitTime;
		int		PayStation;
		COleDateTime PayTime;
		double	PaidAmount;
		int		PaymentNum;
		int		DiscountPlanID;
		CString	Remark;
	};
public: 
	CString m_lpCAN;
	int m_nCate;
	COleDateTime m_tEntTime;
	int m_nEntStn;
	COleDateTime m_tPayTime;
	int m_nPayStn;
	int m_nPayNum;
	double m_dPayAmt;
	CString m_lpHolder;
	COleDateTime m_tRegTime;
	double m_dSVAmt;
	COleDateTime m_tValidFrom;
	COleDateTime m_tValidTo;
	int m_nValidTimes;
	CString m_lpVehNo; 
	double m_fCredit;
	int m_nKind;
private:
	void ShowTranRec(int nCount, struct_TransactionInfo Trans);
	void ShowOldTrans();
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCheckCard)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnChangeVehtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHECKCARD_H__47B8E62F_7B57_4101_9D42_64E508E4A955__INCLUDED_)

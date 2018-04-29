#if !defined(AFX_DLGCARDRENEW_H__88D96DB3_5B85_4303_B4BF_1E9F3FA328CB__INCLUDED_)
#define AFX_DLGCARDRENEW_H__88D96DB3_5B85_4303_B4BF_1E9F3FA328CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCardRenew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCardRenew dialog

class CDlgCardRenew : public CDialog
{

public: 
	CString	_CardNo;
	USHORT	_CardTypeId;
	int _HolderID;
	COleDateTime _ValidFrom;
	COleDateTime _ValidTo;
	COleDateTime _RegTime;
	short  _ValidTranTimes;
	double _StoreValueFee;
	double _StoreValue;
	int _Status;
	double _PeriodFee;
	double _TransactionFee;
	double _Amount;
	double Calculate();
private:
	bool hasotpcard;
	bool haskdecard;
	void AddMonth(short Month);
	BOOL Calculate(COleDateTime ValidFrom, COleDateTime ValidTo, 
			  int CardCate, COleDateTime StartTime, COleDateTime EndTime, double & Fee);
	BOOL CalculateZone(int Cate, COleDateTime StartTime, COleDateTime EndTime, double & Fee);

// Construction
public:
	CDlgCardRenew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCardRenew)
	enum { IDD = IDD_DLG_RENEW };
	CString	m_CardNum;
	CString	m_CardType;
	CString	m_NewPeriod;
	CString	m_OrgPeriod;
	int		m_OrgTransNum;
	CString	m_AmountPeriod;
	CString	m_PricePeriod;
	COleDateTime	m_ValidFrom;
	COleDateTime	m_ValidTo;
	CString	m_AmountSV;
	CString	m_AmountTotal;
	CString	m_AmountTransNum;
	CString	m_PriceTransNum;
	CString	m_NewSV;
	CString	m_OrgSV;
	int		m_NewTransNum;
	CString	m_AddSV;
	int		m_AddTransNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCardRenew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCardRenew)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void On1m();
	afx_msg void On2m();
	afx_msg void On3m();
	afx_msg void On6m();
	afx_msg void On12m();
	afx_msg void On24m();
	afx_msg void OnChangeADDSTOREVALUE();
	afx_msg void OnCloseupPERIODFROM(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupPERIODTO(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeADDTRANSTIMES();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARDRENEW_H__88D96DB3_5B85_4303_B4BF_1E9F3FA328CB__INCLUDED_)

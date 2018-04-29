#if !defined(AFX_DLGPAYMENTSELECTDISCOUNT_H__CBB7EFC3_8E61_4F88_B7EC_8AE42D0F2A53__INCLUDED_)
#define AFX_DLGPAYMENTSELECTDISCOUNT_H__CBB7EFC3_8E61_4F88_B7EC_8AE42D0F2A53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentselectdiscount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentSelectDiscount dialog

class CDlgPaymentSelectDiscount : public CDialog
{
// Construction
public:
	CDlgPaymentSelectDiscount(CWnd* pParent = NULL);   // standard constructor
	static void SetDiscount(int Discount){_DiscountModeID = Discount;}
	static int DiscountID(){return _DiscountModeID;}
	static CDiscount Discount(){return _Discount;}

// Dialog Data
	//{{AFX_DATA(CDlgPaymentSelectDiscount)
	enum { IDD = IDD_PAYMENT_SELECT_DISCOUNT };
	CListCtrl	m_list;
	CString	m_OrgDiscountStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentSelectDiscount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentSelectDiscount)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnClickDiscountList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkDiscountList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTheRule();
private:
	static CDiscount _Discount;
	static int _DiscountModeID;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTSELECTDISCOUNT_H__CBB7EFC3_8E61_4F88_B7EC_8AE42D0F2A53__INCLUDED_)

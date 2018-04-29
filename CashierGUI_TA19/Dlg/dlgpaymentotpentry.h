#if !defined(AFX_DLGPAYMENTOTPENTRY_H__0838DFEB_B56E_45F0_9DE1_3062B89BDF61__INCLUDED_)
#define AFX_DLGPAYMENTOTPENTRY_H__0838DFEB_B56E_45F0_9DE1_3062B89BDF61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentotpentry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentOTPEntry dialog

class CDlgPaymentOTPEntry : public CDlgInput
{
// Construction
public:
	CDlgPaymentOTPEntry(CWnd* pParent = NULL);   // standard constructor
	static COleDateTime EntryTime(){return _EntryTime;}
	static COleDateTime ExitTime(){return _ExitTime;}
	static short EntryStation(){return _EntryStation;}
	static short VehicleId(){return _VehicleId;}

// Dialog Data
	//{{AFX_DATA(CDlgPaymentOTPEntry)
	enum { IDD = IDD_PAYMENT_HAND_OTP_ENTRYTIME };
	CComboBox	m_VehicleType;
	CDateTimeCtrl	m_ExitTime;
	CDateTimeCtrl	m_ExitDate;
	CDateTimeCtrl	m_EntryTime;
	CComboBox	m_EntryStation;
	CDateTimeCtrl	m_EntryDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentOTPEntry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentOTPEntry)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	static COleDateTime _EntryTime;
	static COleDateTime _ExitTime;
	static short _EntryStation;
	static short _VehicleId;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTOTPENTRY_H__0838DFEB_B56E_45F0_9DE1_3062B89BDF61__INCLUDED_)

#if !defined(AFX_DLGPAYMENTKDETICKETNO_H__BB04DD1B_F01C_4E6D_9504_0E9D5B6847EC__INCLUDED_)
#define AFX_DLGPAYMENTKDETICKETNO_H__BB04DD1B_F01C_4E6D_9504_0E9D5B6847EC__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentkdeticketno.h : header file
//
#include "DlgInput.h"
#include "..\\customer.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentKDETicketNo dialog

class CDlgPaymentKDETicketNo : public CDlgInput
{
// Construction
public:
	CDlgPaymentKDETicketNo(CWnd* pParent = NULL);   // standard constructor
	static CString TicketNo(){return _TicketNo;}
	CCustomer::CKdeUserExitCarPark * parker;
// Dialog Data
	//{{AFX_DATA(CDlgPaymentKDETicketNo)
	enum { IDD = IDD_PAYMENT_HAND_KDE_TICKET };
	CComboBox	m_ComboEntry;
	COleDateTime	m_ExitDate;
	COleDateTime	m_ExitTime;
	COleDateTime	m_EntryDate;
	COleDateTime	m_EntryTime;
	int		m_EntryStation;
	int		m_VehicleType;
	int		m_CardType;
	int		m_ProcessType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentKDETicketNo)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public: 
	int m_Type;
	int m_cEntryStationID;
	int m_cVehicleType;
	CString m_cManTicketNo;
	COleDateTime m_cEntryTime;
	COleDateTime m_cExitTime;
	CString m_TicketNo;
	bool m_bFindInfoFromNet;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentKDETicketNo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCancel2();
	virtual void OnCancel();
	afx_msg void OnOk3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	static CString _TicketNo;	//format: "P" + "********"
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTKDETICKETNO_H__BB04DD1B_F01C_4E6D_9504_0E9D5B6847EC__INCLUDED_)

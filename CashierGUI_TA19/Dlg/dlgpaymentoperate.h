#if !defined(AFX_DLGPAYMENTOPERATE_H__490370D6_65EB_47F1_9304_C96FB7C3D695__INCLUDED_)
#define AFX_DLGPAYMENTOPERATE_H__490370D6_65EB_47F1_9304_C96FB7C3D695__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentkdeticketno.h : header file
//
#include "DlgInput.h"
#include "..\\customer.h"
/////////////////////////////////////////////////////////////////////////////
// DlgPaymentOperate dialog

class DlgPaymentOperate : public CDlgInput
{
public:
	bool	_bForbiddenOtp;
	CString _Octopus_CardNo;		//实际付费使用的八达通卡号
	CString _StoreValue_CardNo;	//实际付费使用的储值卡号
	double _Amount;				//收费总额
	double _StoreValueRemain;	//储值余额
	double _OctopusRemain;		//八达通余额
	double _Cash;				//收费现金部分
	double _StoreValue;			//收费储值部分
	double _Octopus;				//收费八达通部分
	double _Change;				//找零
	bool   _PrintReceipt;		//是否打印发票
	double _Unpaid;	//未付
	bool PaywithOTP;
// Construction
public:
	DlgPaymentOperate(CWnd* pParent = NULL);   // standard constructor
	static CString TicketNo(){return _TicketNo;}
	CCustomer::CKdeUserExitCarPark * parker;
	// Dialog Data
	//{{AFX_DATA(DlgPaymentOperate)
	enum { IDD = IDD_PAYMENT_HAND_TICKET };
	CEdit	m_Amount;
	CComboBox	m_ComboEntry;
	COleDateTime	m_ExitDate;
	COleDateTime	m_ExitTime;
	COleDateTime	m_EntryDate;
	COleDateTime	m_EntryTime;
	int		m_EntryStation;
	int		m_VehicleType;
	int		m_CardType;
	int		m_ProcessType;
	CString	m_sEntrytime;
	CString	m_sPaytime;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgPaymentOperate)
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
	//{{AFX_MSG(DlgPaymentOperate)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCancel2();
	virtual void OnCancel();
	afx_msg void GetCardInfo();
	afx_msg void OnBtnOtp();
	afx_msg void OnSelchangeVehicletype();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	static CString _TicketNo;	//format: "P" + "********"
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTOPERATE_H__490370D6_65EB_47F1_9304_C96FB7C3D695__INCLUDED_)

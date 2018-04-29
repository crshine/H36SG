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
	CString _Octopus_CardNo;		//ʵ�ʸ���ʹ�õİ˴�ͨ����
	CString _StoreValue_CardNo;	//ʵ�ʸ���ʹ�õĴ�ֵ����
	double _Amount;				//�շ��ܶ�
	double _StoreValueRemain;	//��ֵ���
	double _OctopusRemain;		//�˴�ͨ���
	double _Cash;				//�շ��ֽ𲿷�
	double _StoreValue;			//�շѴ�ֵ����
	double _Octopus;				//�շѰ˴�ͨ����
	double _Change;				//����
	bool   _PrintReceipt;		//�Ƿ��ӡ��Ʊ
	double _Unpaid;	//δ��
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

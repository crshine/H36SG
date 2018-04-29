#if !defined(AFX_DLGPAYMENTPARKFEE11_H__53B6EBC6_36A6_4345_9C76_AE800E8EFD55__INCLUDED_)
#define AFX_DLGPAYMENTPARKFEE11_H__53B6EBC6_36A6_4345_9C76_AE800E8EFD55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPaymentParkFee11.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentParkFee1 dialog

class CDlgPaymentParkFee1 : public CDlgInput
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
	
	// Construction
public:
	CDlgPaymentParkFee1(CWnd* pParent = NULL);   // standard constructor
	~CDlgPaymentParkFee1();
	
	// Dialog Data
	//{{AFX_DATA(CDlgPaymentParkFee)
	enum { IDD = IDD_PAYMENT_PARK_FEE1 };
	CString	m_Amount;
	CString	m_Cash;
	CString	m_Change;
	CString	m_Octopus;
	CString	m_OctopusRemain;
	CString	m_StoreValue;
	CString	m_StoreValueRemain;
	CString	m_Unpaid;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPaymentParkFee)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgPaymentParkFee)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateCASH();
	afx_msg void OnUpdateSTOREVALUE();
	afx_msg void OnUpdateOCTOPUS();
	afx_msg void OnKillfocusCASH();
	afx_msg void OnKillfocusOCTOPUS();
	afx_msg void OnKillfocusSTOREVALUE();
	afx_msg void OnUpdateOCTOPUSREMAIN();
	virtual void OnOK();
	afx_msg void OnReceipt();
	afx_msg void OnWaitOtpPoll();
	afx_msg void OnPayByCash();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAYMENTPARKFEE11_H__53B6EBC6_36A6_4345_9C76_AE800E8EFD55__INCLUDED_)

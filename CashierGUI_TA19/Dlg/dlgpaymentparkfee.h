#if !defined(AFX_DLGPAYMENTPARKFEE_H__4E50BC86_58DA_4682_8236_8F8E3B391962__INCLUDED_)
#define AFX_DLGPAYMENTPARKFEE_H__4E50BC86_58DA_4682_8236_8F8E3B391962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpaymentparkfee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPaymentParkFee dialog

class CDlgPaymentParkFee : public CDlgInput
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
	CDlgPaymentParkFee(CWnd* pParent = NULL);   // standard constructor
	~CDlgPaymentParkFee();

// Dialog Data
	//{{AFX_DATA(CDlgPaymentParkFee)
	enum { IDD = IDD_PAYMENT_PARK_FEE };
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

#endif // !defined(AFX_DLGPAYMENTPARKFEE_H__4E50BC86_58DA_4682_8236_8F8E3B391962__INCLUDED_)

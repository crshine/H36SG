#if !defined(AFX_DLGRECEIPTPARKINGFEE_H__B6F51648_CC43_40EF_8BC4_3C3CC135836B__INCLUDED_)
#define AFX_DLGRECEIPTPARKINGFEE_H__B6F51648_CC43_40EF_8BC4_3C3CC135836B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgreceiptparkingfee.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReceiptParkingFee dialog

class CDlgReceiptParkingFee : public CDialog
{
// Construction
public:
	static void SetReceiptPara(
			const CString		CardNo,
			const short		SpecialCardTypeId,
			const COleDateTime	TimeEntry,
			const COleDateTime  TimeLastPay,
			const COleDateTime	TimePay,
			const CDiscount	Discount,
			const CString		ReceiptNo,
			const CString		Octopus_CardNo,	//ʵ�ʸ���ʹ�õİ˴�ͨ����
			const CString		StoreValue_CardNo,	//ʵ�ʸ���ʹ�õĴ�ֵ����
			const short			PaymentTimes,
			const double		OctopusRemain,		//�˴�ͨ���
			const double		StoreValueRemain,	//��ֵ���
			const double		Amount,			//�ܶ�
			const double		Cash,				//�ֽ�
			const double		Change,			//����
			const double		Octopus,			//�˴�ͨ
			const double		StoreValue,			//��ֵ
			const short         VehicleType
		);
	CDlgReceiptParkingFee(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgReceiptParkingFee)
	enum { IDD = IDD_RECEIPT_PARKING_FEE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReceiptParkingFee)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgReceiptParkingFee)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
	static CString		_CardNo;
	static short		_SpecialCardTypeId;
	static COleDateTime	_TimeEntry;
	static COleDateTime _TimeLastPay;
	static COleDateTime	_TimePay;
	static CDiscount	_Discount;
	static CString		_ReceiptNo;
	static CString		_Octopus_CardNo;	//ʵ�ʸ���ʹ�õİ˴�ͨ����
	static CString		_StoreValue_CardNo;	//ʵ�ʸ���ʹ�õĴ�ֵ����

	static short		_PaymentTimes;		//���ѵĴ���

	static double		_OctopusRemain;		//�˴�ͨ���
	static double		_StoreValueRemain;	//��ֵ���
	static double		_Amount;			//�ܶ�
	static double		_Cash;				//�ֽ�
	static double		_Change;			//����
	static double		_Octopus;			//�˴�ͨ
	static double		_StoreValue;		//��ֵ
	static short        _VehicleType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECEIPTPARKINGFEE_H__B6F51648_CC43_40EF_8BC4_3C3CC135836B__INCLUDED_)

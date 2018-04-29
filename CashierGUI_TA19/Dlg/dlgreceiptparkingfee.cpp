// dlgreceiptparkingfee.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\Setting.h"
#include "..\CmdPrint.h"
#include "dlgreceiptparkingfee.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReceiptParkingFee dialog
CString		CDlgReceiptParkingFee::_CardNo = "";
short		CDlgReceiptParkingFee::_SpecialCardTypeId = 0;
COleDateTime	CDlgReceiptParkingFee::_TimeEntry = COleDateTime::GetCurrentTime();
COleDateTime    CDlgReceiptParkingFee::_TimeLastPay = COleDateTime::GetCurrentTime();
COleDateTime	CDlgReceiptParkingFee::_TimePay = COleDateTime::GetCurrentTime();
CDiscount	CDlgReceiptParkingFee::_Discount;
CString		CDlgReceiptParkingFee::_ReceiptNo = "";
CString		CDlgReceiptParkingFee::_Octopus_CardNo = "";	//ʵ�ʸ���ʹ�õİ˴�ͨ����
CString		CDlgReceiptParkingFee::_StoreValue_CardNo = "";	//ʵ�ʸ���ʹ�õĴ�ֵ����

short		CDlgReceiptParkingFee::_PaymentTimes=0;		//���ѵĴ���

double		CDlgReceiptParkingFee::_OctopusRemain = 0;		//�˴�ͨ���
double		CDlgReceiptParkingFee::_StoreValueRemain = 0;	//��ֵ���
double		CDlgReceiptParkingFee::_Amount = 0;			//�ܶ�
double		CDlgReceiptParkingFee::_Cash = 0;			//�ֽ�
double		CDlgReceiptParkingFee::_Change = 0;			//����
double		CDlgReceiptParkingFee::_Octopus = 0;		//�˴�ͨ
double		CDlgReceiptParkingFee::_StoreValue = 0;		//��ֵ
short       CDlgReceiptParkingFee::_VehicleType = 0;

CDlgReceiptParkingFee::CDlgReceiptParkingFee(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReceiptParkingFee::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReceiptParkingFee)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgReceiptParkingFee::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReceiptParkingFee)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReceiptParkingFee, CDialog)
	//{{AFX_MSG_MAP(CDlgReceiptParkingFee)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReceiptParkingFee message handlers

BOOL CDlgReceiptParkingFee::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitControl();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgReceiptParkingFee::InitControl()
{
	CSetting::CReceipt * pReceipt = &CSetting::Instance()->m_Receipt;
	SetDlgItemText( IDC_TITLE1,		pReceipt->Title1() );
	SetDlgItemText( IDC_TITLE2,		pReceipt->Title2() );
	SetDlgItemText( IDC_TITLE3,		pReceipt->Title3() );

	const CString TAX_NAME		= "Tax name :\t";
	const CString TAX_REG_NO	= "Tax reg. no :\t";
	const CString TAX_PECENTAGE = "Tax pecentage :\t";

	SetDlgItemText( IDC_TAX_NAME,	TAX_NAME + pReceipt->TaxName() );
	SetDlgItemText( IDC_TAX_REG_NO, TAX_REG_NO + pReceipt->TaxRegNo() );
	SetDlgItemText( IDC_TAX_PECENTAGE, TAX_PECENTAGE + showPercentage(pReceipt->TaxPercentageRate()) );
	SetDlgItemText( IDC_END1,		pReceipt->Ending1() );
	SetDlgItemText( IDC_END2,		pReceipt->Ending2() );

	CSetting::CCommunicate * pCommunicate = &CSetting::Instance()->m_Communicate;

	const CString STATION_ID	= "STATION ID :\t";

	SetDlgItemText( IDC_STATION_ID,	STATION_ID + pCommunicate->StationID() );
/*
	static CString		_CardNo;
	static short		_SpecialCardTypeId;
	static COleDateTime	_TimeEntry;
	static COleDateTime	_TimePay;
	static CString		_Discount;
	static CString		_ReceiptNo;
	static CString		_Octopus_CardNo;	//ʵ�ʸ���ʹ�õİ˴�ͨ����
	static CString		_StoreValue_CardNo;	//ʵ�ʸ���ʹ�õĴ�ֵ����
*/
	const CString RECEIPT_NO	= "Receipt No :\t";
	const CString CARD_NO		= "Card No :\t";
	const CString PAY_CARD_NO	= "Pay card No :\t";
	const CString CARD_CATEGORY = "Card category :\t";
	const CString TIME_ENTRY	= "Time entry :\t";
	const CString TIME_PAY		= "Time pay :\t";
	const CString DISCOUNT		= "Discount :\t";
	SetDlgItemText( IDC_RECEIPT_NO,		RECEIPT_NO + _ReceiptNo );
	SetDlgItemText( IDC_CARD_NO,		CARD_NO + _CardNo );
	SetDlgItemText( IDC_PAY_CARD_NO,	PAY_CARD_NO + _Octopus_CardNo + _StoreValue_CardNo );
	SetDlgItemText( IDC_CARD_CATEGORY,	CARD_CATEGORY + showSpecialCardTypeName(_SpecialCardTypeId) );
	SetDlgItemText( IDC_TIME_ENTRY,		TIME_ENTRY + show(_TimeEntry) );
	SetDlgItemText( IDC_TIME_PAY,		TIME_PAY + show(_TimePay) );
	SetDlgItemText( IDC_DISCOUNT,		DISCOUNT + show(_Discount) );
/*
	static double		_OctopusRemain;		//�˴�ͨ���
	static double		_StoreValueRemain;	//��ֵ���
	static double		_Amount;			//�ܶ�
	static double		_Cash;				//�ֽ�
	static double		_Change;			//����
	static double		_Octopus;			//�˴�ͨ
	static double		_StoreValue;		//��ֵ
*/
	const CString _AMOUNT		= "Amount :\t";
	const CString _PAID			= "Paid :\t";
	const CString _CHANGE		= "Change :\t";
	const CString _CARD_REMAIN	= "Card remain :\t";
	const CString _STORE_VALUE	= "Store value :\t";
	SetDlgItemText( IDC_AMOUNT,		_AMOUNT + show(_Amount) );
	SetDlgItemText( IDC_PAID,		_PAID + show(_Cash + _Octopus + _StoreValue - _Change) );
	SetDlgItemText( IDC_CHANGE,		_CHANGE + show(_Change) );
	SetDlgItemText( IDC_CARD_REMAIN,_CARD_REMAIN + show(_OctopusRemain) );
	SetDlgItemText( IDC_STORE_VALUE,_STORE_VALUE + show(_StoreValueRemain) );
}	

void CDlgReceiptParkingFee::SetReceiptPara(
			const CString		CardNo,
			const short		SpecialCardTypeId,
			const COleDateTime	TimeEntry,
			const COleDateTime  TimeLastPay,
			const COleDateTime	TimePay,
			const CDiscount	Discount,
			const CString		ReceiptNo,
			const CString		Octopus_CardNo,		//ʵ�ʸ���ʹ�õİ˴�ͨ����
			const CString		StoreValue_CardNo,	//ʵ�ʸ���ʹ�õĴ�ֵ����
			const short			PaymentTimes,
			const double		OctopusRemain,		//�˴�ͨ���
			const double		StoreValueRemain,	//��ֵ���
			const double		Amount,				//�ܶ�
			const double		Cash,				//�ֽ�
			const double		Change,				//����
			const double		Octopus,			//�˴�ͨ
			const double		StoreValue,			//��ֵ
			const short         VehicleType
		)
{
	_CardNo				=	CardNo;
	_SpecialCardTypeId	=	SpecialCardTypeId;
	_TimeEntry			=	TimeEntry;
	_TimeLastPay        =   TimeLastPay;
	_TimePay			=	TimePay;
	_Discount			=	Discount;
	_ReceiptNo			=	ReceiptNo;
	_Octopus_CardNo		=	Octopus_CardNo;	//ʵ�ʸ���ʹ�õİ˴�ͨ����
	_StoreValue_CardNo	=	StoreValue_CardNo;	//ʵ�ʸ���ʹ�õĴ�ֵ����
	_PaymentTimes		=	PaymentTimes;
	_OctopusRemain		=	OctopusRemain;		//�˴�ͨ���
	_StoreValueRemain	=	StoreValueRemain;	//��ֵ���
	_Amount				=	Amount;			//�ܶ�
	_Cash				=	Cash;				//�ֽ�
	_Change				=	Change;			//����
	_Octopus			=	Octopus;			//�˴�ͨ
	_StoreValue			=	StoreValue;		//��ֵ
	_VehicleType        =   VehicleType;
}
void CDlgReceiptParkingFee::OnOK() 
{
	GetDlgItem(IDOK)->EnableWindow(false);
	CCmdPrint * pCmdPrint = CCmdPrint::Instance();
	pCmdPrint->PrintParkingFee(
				_CardNo,
				_SpecialCardTypeId,
				_TimeEntry,
				_TimeLastPay,
				_TimePay,
				_Discount,
				_ReceiptNo,
				_Octopus_CardNo,
				_StoreValue_CardNo,
				_PaymentTimes,
				_OctopusRemain,
				_StoreValueRemain,
				_Amount,
				_Cash,
				_Change,
				_Octopus,
				_StoreValue,
				_VehicleType);
	CDialog::OnOK();
}

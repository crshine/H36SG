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
CString		CDlgReceiptParkingFee::_Octopus_CardNo = "";	//实际付费使用的八达通卡号
CString		CDlgReceiptParkingFee::_StoreValue_CardNo = "";	//实际付费使用的储值卡号

short		CDlgReceiptParkingFee::_PaymentTimes=0;		//付费的次数

double		CDlgReceiptParkingFee::_OctopusRemain = 0;		//八达通余额
double		CDlgReceiptParkingFee::_StoreValueRemain = 0;	//储值余额
double		CDlgReceiptParkingFee::_Amount = 0;			//总额
double		CDlgReceiptParkingFee::_Cash = 0;			//现金
double		CDlgReceiptParkingFee::_Change = 0;			//找零
double		CDlgReceiptParkingFee::_Octopus = 0;		//八达通
double		CDlgReceiptParkingFee::_StoreValue = 0;		//储值
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
	static CString		_Octopus_CardNo;	//实际付费使用的八达通卡号
	static CString		_StoreValue_CardNo;	//实际付费使用的储值卡号
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
	static double		_OctopusRemain;		//八达通余额
	static double		_StoreValueRemain;	//储值余额
	static double		_Amount;			//总额
	static double		_Cash;				//现金
	static double		_Change;			//找零
	static double		_Octopus;			//八达通
	static double		_StoreValue;		//储值
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
			const CString		Octopus_CardNo,		//实际付费使用的八达通卡号
			const CString		StoreValue_CardNo,	//实际付费使用的储值卡号
			const short			PaymentTimes,
			const double		OctopusRemain,		//八达通余额
			const double		StoreValueRemain,	//储值余额
			const double		Amount,				//总额
			const double		Cash,				//现金
			const double		Change,				//找零
			const double		Octopus,			//八达通
			const double		StoreValue,			//储值
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
	_Octopus_CardNo		=	Octopus_CardNo;	//实际付费使用的八达通卡号
	_StoreValue_CardNo	=	StoreValue_CardNo;	//实际付费使用的储值卡号
	_PaymentTimes		=	PaymentTimes;
	_OctopusRemain		=	OctopusRemain;		//八达通余额
	_StoreValueRemain	=	StoreValueRemain;	//储值余额
	_Amount				=	Amount;			//总额
	_Cash				=	Cash;				//现金
	_Change				=	Change;			//找零
	_Octopus			=	Octopus;			//八达通
	_StoreValue			=	StoreValue;		//储值
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

// CmdPrint.h: interface for the CCmdPrint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDPRINT_H__51B8B433_C028_4AF3_BB70_D34F011195F8__INCLUDED_)
#define AFX_CMDPRINT_H__51B8B433_C028_4AF3_BB70_D34F011195F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

	BOOL PrintParkingReceipt(
			LONG ReceiptNo, 
			LPSTR CAN, 
			LPSTR PayCAN, 
			BOOL IsReply,
			LPSTR Cate, 
			double EnterTime,
			double LastPayTime,
			double PayTime,
			LPSTR DiscountStr,									  
			double fFareCardAmt, 
			double fFareCardBal,
			double fStoreValueAmt, 
			double fStoreValueBal,								 
			double ReceiptCash, 
			double ReceiptChange,short veh
			,CString r);//TA18-

	BOOL CReceiptPrn::PrintAddValueReceipt(
			LONG    av_ReceiptNo, 
			CString av_ReceiptOtpNo,
			COleDateTime av_ReceiptPayTime,
			double av_ReceiptAmt, 
		    double av_ReceiptOtpOldBal, 
			double av_ReceiptOtpNewBal,
            double av_ReceiptCash, 
			double av_ReceiptChange
			);




class CCmdPrint  
{
	typedef struct STRUCT_ParkingFeePara
	{
		CString		_ReceiptNo;
		CString		_CardNo;
		CString		_PayCardNo;
		bool		_IsRepay;
		CString		_CardType;
		COleDateTime _EntryTime;
		COleDateTime _LastPayTime;
		COleDateTime _PayTime;
		CString		_Discount;
		double		_CardAmt;
		double		_CardBal;
		double		_StoreValueAmt;
		double		_StoreValueBal;
		double      _Cash;
		double      _Change;
		short       _VehicleType;
	}* HPARKINGFEEPARA, PARKINGFEEPARA;

/*	typedef struct STRUCT_AddValuePara
	{
		CString      _av_No, //receipt no. 
		CString      _av_OtpNo,
		COleDateTime _av_PayTime,
		double       _av_Amt, 
		double       _av_OtpOldBal, 
		double       _av_OtpNewBal,
        double       _av_Cash, 
		double       _av_Change;
	}* HADDVALUEPARA, ADDVALUEPARA;
*/

public:
	bool PrintAddValue(
			CString      av_No, //receipt no. 
			CString      av_OtpNo,
			COleDateTime av_PayTime,
			double       av_Amt, 
		    double       av_OtpOldBal, 
			double       av_OtpNewBal,
            double       av_Cash, 
			double       av_Change
			);
	bool PrintSeasonCreate(
			CString      sc_No, 
			CString      sc_CardNo, 
			COleDateTime sc_PayTime,
			COleDateTime sc_ValidFrom,
			COleDateTime sc_ValidTo,
			double       sc_Amt, 
			double       sc_Cash,
			double       sc_Change
			);
	bool PrintSeasonExtend(
			CString      se_No, 
			CString      se_CardNo, 
			COleDateTime se_PayTime,
			COleDateTime se_ExtendFrom,
			COleDateTime se_ExtendTo,
			double       se_Amt, 
			double       se_Cash,
			double       se_Change
			);
	void ResetPrinter();
	bool PrintShiftAccount(CString Operator, CString ReceiptNo, COleDateTime DutyStart, int Paynum, double Cash, double Octopus, double StoreValue, double ShiftCashMaintain);
	bool PrintParkingFee(
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
			);
	
	static CCmdPrint* Instance();
	virtual ~CCmdPrint();
protected:
    CCmdPrint();
	CCmdPrint(const CCmdPrint&);
	CCmdPrint& operator=(const CCmdPrint&);

private:
	bool PrintEnding();
	bool PrintHeader();
	static UINT thrPrintShiftAccount(LPVOID);
	static UINT thrPrintParkingFee(LPVOID/* HPARKINGFEEPARA*/);
    static CCmdPrint* _instance;
	CReceiptPrn * _pPrinter;
};

#endif // !defined(AFX_CMDPRINT_H__51B8B433_C028_4AF3_BB70_D34F011195F8__INCLUDED_)

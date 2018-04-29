// Customer.h: interface for the CCustomer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMER_H__860F6CEE_98D1_4F80_A8F9_98D69C0614C7__INCLUDED_)
#define AFX_CUSTOMER_H__860F6CEE_98D1_4F80_A8F9_98D69C0614C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CmdOtp.h"
#include "cmdmntsend.h"
class CCustomer  
{
public:
	CCustomer();
	virtual ~CCustomer();
	class CBase
	{
	public:
		void OTPstop();
		SYSRESULT Trade();//交易
		bool _AutoShift;
		CBase();
		~CBase();
	protected:
		//7个交易步骤
		virtual void		Init(){;}						//.初始化交易.(将要进行的交易的一些初值设定)
		virtual SYSRESULT	Pre_Trade(){ return SUCCESS;}	//.付款前操作.(操作员需要进行的一些操作)
		virtual SYSRESULT	Calculate(){ return SUCCESS;}	//.计算.(根据交易参数计算交易额)
		virtual SYSRESULT	Payment();						//.付款.
		virtual SYSRESULT	Sub_Trade(){ return SUCCESS;}	//.付款后操作.(包括发卡,写卡等等)
		virtual SYSRESULT	PrintReceipt();					//.打印发票.(Print receipt);
		virtual void		LogTransaction(){;}				//.记录这次交易.(log this transaction);
		virtual void Account();		//整理交易发生金额.
		//func
		virtual void		ClearGUI();
	protected:
		HWND				_hGUI;			//图形界面句柄
		COleDateTime		_ActionTime;	//交易时间
		CString _Octopus_CardNo;		//实际付费使用的八达通卡号
		CString	_Barcode_CardNo;			//卡号
		CString _StoreValue_CardNo;		//实际付费使用的储值卡号
		double _OctopusRemain;		//八达通余额
		double _StoreValueRemain;	//储值余额
		double _CashMaintainRemain;
		double _ShiftCashMaintain;
		double _Amount;				//总额
		double _Cash;				//现金
		double _Change;				//找零
		double _Octopus;			//八达通
		double _StoreValue;			//储值
		bool   _ForbiddenOtp;
		CString _ReceiptNo;			//发票号
		static bool	_PrintReceipt;	//是否打印发票
		bool _DisableOTPPay;     // disable the otp button
		UINT				_OTPZeroDeductType;
	};
	//
	class CExitCarPark : public CBase
	{
	public:
		CExitCarPark();
		virtual SYSRESULT	QueryServer(CWnd * pWnd = NULL);		//.查询信息.
		void RefreshDsp(CWnd * pWnd = NULL);
		void ReCalculate(CWnd * pWnd = NULL);
	protected:
		//特殊交易步骤
		virtual SYSRESULT	Calculate();		//.计算.(根据交易参数计算交易额)
		virtual SYSRESULT	PrintReceipt();		//.打印发票.(Print receipt);
		virtual void		LogTransaction();	//.记录这次交易.(log this transaction);
		virtual SYSRESULT	SelectDiscount();	//.为非特殊卡选择一个折扣类型
		static void CALLBACK ShowDetail(CString Detail){;/*do nothing*/}
		CString LoadManualCardNo(bool isLost);
	protected:
		CString				_CardNo;			//卡号
		CString				_DamageLostCardNo;
		COleDateTime		_EntryTime;			//入场时间
		short				_GroupId;			//用户组
		short				_VehicleId;			//车辆种类
		short				_SpecialCardTypeId;	//特殊卡种类('0': 普通卡)
		CString				_TransactionNo;		//交易编码
		CDiscount			_Discount;			//记录用户最终获得的折扣
		short				_EntryStationID;
		short				_PayStationID;
		short               _VehicleType;       // [BW] 20050928 (1 or 2)
		double				_PaidAmtBefore;
		CString             _Remarks;           // [BW] 20051024
		//上次付费信息
		COleDateTime		_ExitTime;			//出场时间
		short				_PaymentTimes;		//付费的次数
		COleDateTime		_LastPayTime;		//上次付款时间
		CCmdMntSend::HCARDSTATUS _CardStatus;
		static bool	_PrintReceipt;	//是否打印发票
	};
	//使用KDE卡离开停车场的客户
	class CKdeUserExitCarPark : public CExitCarPark
	{
	public:
		CKdeUserExitCarPark();
		~CKdeUserExitCarPark();
		SYSRESULT ManualTrade(int _ProcessType, int _VehType, CString _ManTicketNo, COleDateTime _ManEntryTime, short _ManEntryStationID);
	protected:
		//特殊交易步骤
		virtual void		Init();				//.初始化交易.(将要进行的交易的一些初值设定)
		virtual SYSRESULT	Pre_Trade();		//.付款前操作.(操作员需要进行的一些操作)
		virtual SYSRESULT	InputTicketNo();	//.手动输入卡号.
		virtual SYSRESULT	Sub_Trade();		//.付款后操作.(包括发卡,写卡等等)
	};
	//使用OTP卡离开停车场的客户
	class COtpUserExitCarPark : public CExitCarPark
	{
	public:
		COtpUserExitCarPark();
		SYSRESULT TradeCommon(const CCmdOtp::PATRON& CardInfo);
		SYSRESULT TradeError();
	private:
		SYSRESULT Trade(){ASSERT(1!=1);return SUCCESS;}//不可使用本函数
		//特殊交易步骤
		virtual void		Init();				//.初始化交易.(将要进行的交易的一些初值设定)
		virtual SYSRESULT	Pre_Trade();		//.付款前操作.(操作员需要进行的一些操作)
		virtual SYSRESULT	InputTicketNo();	//.手动输入卡号.
		virtual SYSRESULT	Sub_Trade();		//.付款后操作.(包括发卡,写卡等等)
	};
	//OTP卡充值
	class COtpUserAddValue : public CBase  // Define CBase is father and COtpUserAddValue is son 
		                                   //(add value check point 002)
	{
	public:
		COtpUserAddValue();
	protected:
		//特殊交易步骤
		virtual void		Init();
		virtual SYSRESULT	Pre_Trade();
		virtual SYSRESULT	PrintReceipt();
		virtual SYSRESULT	Sub_Trade();
		virtual void		LogTransaction();
	private:
		CString		_CardNo;			//卡号
		double		_ValueBeforeAdd;	//冲值前金额.
		static bool	_PrintReceipt;		//是否打印发票
	};
	//换班
	class CShiftAccount : public CBase
	{
	public:
		CShiftAccount();
	private:
		//特殊交易步骤
		virtual SYSRESULT	Pre_Trade();
		virtual SYSRESULT	Payment(){ return SUCCESS;}
		virtual void Account() { }
		virtual SYSRESULT	Sub_Trade();
		virtual SYSRESULT	PrintReceipt();
		virtual void		LogTransaction();
	private:	
		//交易信息
		COleDateTime	_EntryTime;		//到岗时间
		double			_AmountRemain;
		double			_CashRemain;
		COleDateTime	_DutyStart;
		long			_PayNum;
		static bool	_PrintReceipt;		//是否打印发票
	};
	//下班
	class CCloseAccount : public CShiftAccount
	{
	public:
		CCloseAccount();
	private:
		virtual void		LogTransaction();	//.记录这次交易.(log this transaction);
		virtual void Account() {}
	};
	class CCreateSpecialCard : public CBase

	{
	public:
		enum enum_Holder_Opr_Type{Opr_New, Opr_No, Opr_Exist};//操作种类(new, no, exist)
	public:		//func
		static CCreateSpecialCard* Instance();
	
		CCreateSpecialCard(bool RenewOp=false);
	private:	//func	
		//7个交易步骤
		void		Init();				//.初始化交易.(将要进行的交易的一些初值设定)
		SYSRESULT	Pre_Trade();		//.付款前操作.(操作员需要进行的一些操作)
		SYSRESULT   Sub_Trade();		//.付款后操作.(包括发卡,写卡等等)
		SYSRESULT	PrintReceipt();		//.打印发票.(Print receipt);
		void		LogTransaction();	//.记录这次交易.(log this transaction);
		virtual SYSRESULT Calculate();		//.跟据用户的输入,计算相应的费用
	private:	//member
	    static CCreateSpecialCard* _instance;
		bool _IsRenewOp;
		CString			_CardNo;
		USHORT			_CardTypeId;
		USHORT			_Status;
		COleDateTime	_RegTime;
		int				_HolderID;
		COleDateTime	_ValidFrom;
		COleDateTime	_ValidTo;
		short			_ValidTranTimes;
		double _StoreValueFee;

		double _PeriodFee;
		double _TransactionFee;
		double _JoiningFee;
		double _CardFee; 

		enum_Holder_Opr_Type	_Holder_Opr_Type;//操作种类(new, no, exist)

	};
};

#endif // !defined(AFX_CUSTOMER_H__860F6CEE_98D1_4F80_A8F9_98D69C0614C7__INCLUDED_)

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
		SYSRESULT Trade();//����
		bool _AutoShift;
		CBase();
		~CBase();
	protected:
		//7�����ײ���
		virtual void		Init(){;}						//.��ʼ������.(��Ҫ���еĽ��׵�һЩ��ֵ�趨)
		virtual SYSRESULT	Pre_Trade(){ return SUCCESS;}	//.����ǰ����.(����Ա��Ҫ���е�һЩ����)
		virtual SYSRESULT	Calculate(){ return SUCCESS;}	//.����.(���ݽ��ײ������㽻�׶�)
		virtual SYSRESULT	Payment();						//.����.
		virtual SYSRESULT	Sub_Trade(){ return SUCCESS;}	//.��������.(��������,д���ȵ�)
		virtual SYSRESULT	PrintReceipt();					//.��ӡ��Ʊ.(Print receipt);
		virtual void		LogTransaction(){;}				//.��¼��ν���.(log this transaction);
		virtual void Account();		//�����׷������.
		//func
		virtual void		ClearGUI();
	protected:
		HWND				_hGUI;			//ͼ�ν�����
		COleDateTime		_ActionTime;	//����ʱ��
		CString _Octopus_CardNo;		//ʵ�ʸ���ʹ�õİ˴�ͨ����
		CString	_Barcode_CardNo;			//����
		CString _StoreValue_CardNo;		//ʵ�ʸ���ʹ�õĴ�ֵ����
		double _OctopusRemain;		//�˴�ͨ���
		double _StoreValueRemain;	//��ֵ���
		double _CashMaintainRemain;
		double _ShiftCashMaintain;
		double _Amount;				//�ܶ�
		double _Cash;				//�ֽ�
		double _Change;				//����
		double _Octopus;			//�˴�ͨ
		double _StoreValue;			//��ֵ
		bool   _ForbiddenOtp;
		CString _ReceiptNo;			//��Ʊ��
		static bool	_PrintReceipt;	//�Ƿ��ӡ��Ʊ
		bool _DisableOTPPay;     // disable the otp button
		UINT				_OTPZeroDeductType;
	};
	//
	class CExitCarPark : public CBase
	{
	public:
		CExitCarPark();
		virtual SYSRESULT	QueryServer(CWnd * pWnd = NULL);		//.��ѯ��Ϣ.
		void RefreshDsp(CWnd * pWnd = NULL);
		void ReCalculate(CWnd * pWnd = NULL);
	protected:
		//���⽻�ײ���
		virtual SYSRESULT	Calculate();		//.����.(���ݽ��ײ������㽻�׶�)
		virtual SYSRESULT	PrintReceipt();		//.��ӡ��Ʊ.(Print receipt);
		virtual void		LogTransaction();	//.��¼��ν���.(log this transaction);
		virtual SYSRESULT	SelectDiscount();	//.Ϊ�����⿨ѡ��һ���ۿ�����
		static void CALLBACK ShowDetail(CString Detail){;/*do nothing*/}
		CString LoadManualCardNo(bool isLost);
	protected:
		CString				_CardNo;			//����
		CString				_DamageLostCardNo;
		COleDateTime		_EntryTime;			//�볡ʱ��
		short				_GroupId;			//�û���
		short				_VehicleId;			//��������
		short				_SpecialCardTypeId;	//���⿨����('0': ��ͨ��)
		CString				_TransactionNo;		//���ױ���
		CDiscount			_Discount;			//��¼�û����ջ�õ��ۿ�
		short				_EntryStationID;
		short				_PayStationID;
		short               _VehicleType;       // [BW] 20050928 (1 or 2)
		double				_PaidAmtBefore;
		CString             _Remarks;           // [BW] 20051024
		//�ϴθ�����Ϣ
		COleDateTime		_ExitTime;			//����ʱ��
		short				_PaymentTimes;		//���ѵĴ���
		COleDateTime		_LastPayTime;		//�ϴθ���ʱ��
		CCmdMntSend::HCARDSTATUS _CardStatus;
		static bool	_PrintReceipt;	//�Ƿ��ӡ��Ʊ
	};
	//ʹ��KDE���뿪ͣ�����Ŀͻ�
	class CKdeUserExitCarPark : public CExitCarPark
	{
	public:
		CKdeUserExitCarPark();
		~CKdeUserExitCarPark();
		SYSRESULT ManualTrade(int _ProcessType, int _VehType, CString _ManTicketNo, COleDateTime _ManEntryTime, short _ManEntryStationID);
	protected:
		//���⽻�ײ���
		virtual void		Init();				//.��ʼ������.(��Ҫ���еĽ��׵�һЩ��ֵ�趨)
		virtual SYSRESULT	Pre_Trade();		//.����ǰ����.(����Ա��Ҫ���е�һЩ����)
		virtual SYSRESULT	InputTicketNo();	//.�ֶ����뿨��.
		virtual SYSRESULT	Sub_Trade();		//.��������.(��������,д���ȵ�)
	};
	//ʹ��OTP���뿪ͣ�����Ŀͻ�
	class COtpUserExitCarPark : public CExitCarPark
	{
	public:
		COtpUserExitCarPark();
		SYSRESULT TradeCommon(const CCmdOtp::PATRON& CardInfo);
		SYSRESULT TradeError();
	private:
		SYSRESULT Trade(){ASSERT(1!=1);return SUCCESS;}//����ʹ�ñ�����
		//���⽻�ײ���
		virtual void		Init();				//.��ʼ������.(��Ҫ���еĽ��׵�һЩ��ֵ�趨)
		virtual SYSRESULT	Pre_Trade();		//.����ǰ����.(����Ա��Ҫ���е�һЩ����)
		virtual SYSRESULT	InputTicketNo();	//.�ֶ����뿨��.
		virtual SYSRESULT	Sub_Trade();		//.��������.(��������,д���ȵ�)
	};
	//OTP����ֵ
	class COtpUserAddValue : public CBase  // Define CBase is father and COtpUserAddValue is son 
		                                   //(add value check point 002)
	{
	public:
		COtpUserAddValue();
	protected:
		//���⽻�ײ���
		virtual void		Init();
		virtual SYSRESULT	Pre_Trade();
		virtual SYSRESULT	PrintReceipt();
		virtual SYSRESULT	Sub_Trade();
		virtual void		LogTransaction();
	private:
		CString		_CardNo;			//����
		double		_ValueBeforeAdd;	//��ֵǰ���.
		static bool	_PrintReceipt;		//�Ƿ��ӡ��Ʊ
	};
	//����
	class CShiftAccount : public CBase
	{
	public:
		CShiftAccount();
	private:
		//���⽻�ײ���
		virtual SYSRESULT	Pre_Trade();
		virtual SYSRESULT	Payment(){ return SUCCESS;}
		virtual void Account() { }
		virtual SYSRESULT	Sub_Trade();
		virtual SYSRESULT	PrintReceipt();
		virtual void		LogTransaction();
	private:	
		//������Ϣ
		COleDateTime	_EntryTime;		//����ʱ��
		double			_AmountRemain;
		double			_CashRemain;
		COleDateTime	_DutyStart;
		long			_PayNum;
		static bool	_PrintReceipt;		//�Ƿ��ӡ��Ʊ
	};
	//�°�
	class CCloseAccount : public CShiftAccount
	{
	public:
		CCloseAccount();
	private:
		virtual void		LogTransaction();	//.��¼��ν���.(log this transaction);
		virtual void Account() {}
	};
	class CCreateSpecialCard : public CBase

	{
	public:
		enum enum_Holder_Opr_Type{Opr_New, Opr_No, Opr_Exist};//��������(new, no, exist)
	public:		//func
		static CCreateSpecialCard* Instance();
	
		CCreateSpecialCard(bool RenewOp=false);
	private:	//func	
		//7�����ײ���
		void		Init();				//.��ʼ������.(��Ҫ���еĽ��׵�һЩ��ֵ�趨)
		SYSRESULT	Pre_Trade();		//.����ǰ����.(����Ա��Ҫ���е�һЩ����)
		SYSRESULT   Sub_Trade();		//.��������.(��������,д���ȵ�)
		SYSRESULT	PrintReceipt();		//.��ӡ��Ʊ.(Print receipt);
		void		LogTransaction();	//.��¼��ν���.(log this transaction);
		virtual SYSRESULT Calculate();		//.�����û�������,������Ӧ�ķ���
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

		enum_Holder_Opr_Type	_Holder_Opr_Type;//��������(new, no, exist)

	};
};

#endif // !defined(AFX_CUSTOMER_H__860F6CEE_98D1_4F80_A8F9_98D69C0614C7__INCLUDED_)

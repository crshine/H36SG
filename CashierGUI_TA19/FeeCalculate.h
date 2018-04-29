// FeeCalculate.h: interface for the CFeeCalculate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_)
#define AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define Err_Day_Rule_Absence					1		//�ò����ڵ�����
#define Err_Group_Rule_Absence					2		//�ò����ڵ�'GroupID'��ѯ
#define Err_Group_Rule_Undefined_Vehicle_Type	3		//���в����ڶ�Ӧ�ĳ������.
#define Err_Vehicle_Rule_Absence				4		//�ò����ڵ�'VehicleID'��ѯ
#define Err_Timezone_Rule_Absence				5		//�ò����ڵ�'TimezoneID'��ѯ
#define Err_Timezone_Rule_Undefined_Timezone	6		//����'Timezone'���򲻺����³���δ������շ�ʱ��δ���
#define Err_Fee_Rule_Absence					7		//�ò����ڵ�'FeeID'��ѯ
#define Err_Fee_Rule_Undefined_Unit				8		//����'Fee'���򲻺����³���δ������շ�ʱ��Ƭ����
#define Err_Fix_Discount_Rule_Broken			9		//
#define Err_Impossible_Payment_Currency			10		//
#define Err_Too_Long_Times_Calculate			11		//����ѭ�����

#define Calculate_Success							100
#define Need_Continue_Process						100
#define Zero_Fee_By_Paid_Grace_Time					101
#define Zero_Fee_By_Enter_Grace_Time				102
#define Zero_Fee_By_TZone_Grace_Time				103
#define Ahead_Result_By_Fix_Discount_Fix_Payment	104		//�̶����
#define Zero_Fee_By_Fix_Discount_Free_Hours			105
#define Ahead_Result_By_PerEntry_Time_Unit			106		//��󲻼Ʒ�

typedef void (CALLBACK* SHOWDETAILPROC)(CString Detail);
class CDiscount;
class CFeeCalculate  
{
public://func
	USHORT Calculate(double &Amount, CDiscount Discount, COleDateTime BegTime, COleDateTime EndTime, 
		short VehicleTypeID, short GroupTypeID, bool PayAgain, UINT &ZeroDeductType, SHOWDETAILPROC ShowDetail = NULL);
	const CString GetErrorMessage(USHORT nMsg);
	CFeeCalculate();
	virtual ~CFeeCalculate();
private://func
	void InitCalculate();		//������Ի�
	USHORT CheckGrace();		//������ʱ��Ƭ
	USHORT CheckTimeZoneGrace();
	void CheckFixDiscount();	//�����ۿ۹涨
	void Pre_EffectDiscount();	//use this before calculate
	void Sub_EffectDiscount();	//use this after calculate
	USHORT CalculateLoop();			//�������ѭ��
	USHORT PickTimeZoneRuleID(short &TimeZoneId);
	USHORT CalculateTimezone( const short TimeZoneRulesId );
	USHORT CalculateUnit(const short UnitRulesId, const COleDateTime TimeZoneTerminal);

private://number

	void SubtractUnit(const long &Unit,const COleDateTime &TimeZoneTerminal,int OperFlag);
	//input
	CDiscount		_Discount;		//��ͨ�ۿ�
	COleDateTime	_BegTime;		//��ʼʱ��
	COleDateTime	_EndTime;		//��ֹʱ��
	short			_CarTypeID;
	short			_GroupTypeID;
	bool			_PayAgain;		//�ٴθ���
	SHOWDETAILPROC	_ShowDetail;	//������ʾ����״����ϸ�ڵĻص�����
	//output
	double			_Amount;		//�ܶ�
	//details
	CDiscount 		_FixDiscount;	//�����ۿ�

	//Ӱ���շѵļ��������趨
//	const double _MinPriceAmount;	//��С�Ŀɼ�����շѽ��.
//	const COleDateTimeSpan _MinTimeSpan;	//��С�Ŀɼ����ʱ�䵥Ԫ.

	bool _CutByTimeZone;			//�Ƿ��и�ʱ��Ƭ
	bool _ApplyFixTimeRule;			//�Ƿ�ʹ��FixTimeRule(����涨)
	bool _IsCrossTimeZone;
	int LastFeeIndex;

	COleDateTimeSpan _PaidGraceTime;   //���ʱ��Ƭ
	COleDateTimeSpan _EnterGraceTime;  //���ʱ��Ƭ
	COleDateTimeSpan _TZoneGraceTime;  //���ʱ��Ƭ
};

#endif // !defined(AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_)

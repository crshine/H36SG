// FeeCalculate.h: interface for the CFeeCalculate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_)
#define AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define Err_Day_Rule_Absence					1		//用不存在的日期
#define Err_Group_Rule_Absence					2		//用不存在的'GroupID'查询
#define Err_Group_Rule_Undefined_Vehicle_Type	3		//组中不存在对应的车辆编号.
#define Err_Vehicle_Rule_Absence				4		//用不存在的'VehicleID'查询
#define Err_Timezone_Rule_Absence				5		//用不存在的'TimezoneID'查询
#define Err_Timezone_Rule_Undefined_Timezone	6		//由于'Timezone'规则不合理导致出现未定义的收费时间段存在
#define Err_Fee_Rule_Absence					7		//用不存在的'FeeID'查询
#define Err_Fee_Rule_Undefined_Unit				8		//由于'Fee'规则不合理导致出现未定义的收费时间片存在
#define Err_Fix_Discount_Rule_Broken			9		//
#define Err_Impossible_Payment_Currency			10		//
#define Err_Too_Long_Times_Calculate			11		//防死循环设计

#define Calculate_Success							100
#define Need_Continue_Process						100
#define Zero_Fee_By_Paid_Grace_Time					101
#define Zero_Fee_By_Enter_Grace_Time				102
#define Zero_Fee_By_TZone_Grace_Time				103
#define Ahead_Result_By_Fix_Discount_Fix_Payment	104		//固定金额
#define Zero_Fee_By_Fix_Discount_Free_Hours			105
#define Ahead_Result_By_PerEntry_Time_Unit			106		//其后不计费

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
	void InitCalculate();		//计算初试化
	USHORT CheckGrace();		//检测免费时间片
	USHORT CheckTimeZoneGrace();
	void CheckFixDiscount();	//补充折扣规定
	void Pre_EffectDiscount();	//use this before calculate
	void Sub_EffectDiscount();	//use this after calculate
	USHORT CalculateLoop();			//计算费用循环
	USHORT PickTimeZoneRuleID(short &TimeZoneId);
	USHORT CalculateTimezone( const short TimeZoneRulesId );
	USHORT CalculateUnit(const short UnitRulesId, const COleDateTime TimeZoneTerminal);

private://number

	void SubtractUnit(const long &Unit,const COleDateTime &TimeZoneTerminal,int OperFlag);
	//input
	CDiscount		_Discount;		//普通折扣
	COleDateTime	_BegTime;		//起始时间
	COleDateTime	_EndTime;		//终止时间
	short			_CarTypeID;
	short			_GroupTypeID;
	bool			_PayAgain;		//再次付款
	SHOWDETAILPROC	_ShowDetail;	//用来显示计算状况和细节的回调函数
	//output
	double			_Amount;		//总额
	//details
	CDiscount 		_FixDiscount;	//补充折扣

	//影响收费的几个环境设定
//	const double _MinPriceAmount;	//最小的可计算的收费金额.
//	const COleDateTimeSpan _MinTimeSpan;	//最小的可计算的时间单元.

	bool _CutByTimeZone;			//是否切割时间片
	bool _ApplyFixTimeRule;			//是否使用FixTimeRule(补充规定)
	bool _IsCrossTimeZone;
	int LastFeeIndex;

	COleDateTimeSpan _PaidGraceTime;   //免费时间片
	COleDateTimeSpan _EnterGraceTime;  //免费时间片
	COleDateTimeSpan _TZoneGraceTime;  //免费时间片
};

#endif // !defined(AFX_FEECALCULATE_H__F66D85BE_0CE5_47D7_8A26_CCFFA555B84F__INCLUDED_)

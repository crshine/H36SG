// FeeCalculate.cpp: implementation of the CFeeCalculate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Setting.h"
#include "FeeCalculate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFeeCalculate::CFeeCalculate()
{

}

CFeeCalculate::~CFeeCalculate()
{

}
//////////////////////////////////////////////////////////////////////
//公共接口
USHORT CFeeCalculate::Calculate(double &Amount, CDiscount Discount, 
				 COleDateTime BegTime, COleDateTime EndTime, 
				 short VehicleTypeID, short GroupTypeID, bool PayAgain, UINT &ZeroDeductType,
				 SHOWDETAILPROC ShowDetail)   // damage payment check point 004 (fee calculation)
{
	ASSERT( (0<=VehicleTypeID) && (6>=VehicleTypeID) );
	ASSERT( (0<=GroupTypeID) && (3>=GroupTypeID) ); //???
//	ASSERT( BegTime < EndTime );
	if ( IsBigger(BegTime, EndTime) )
	{
		::AfxMessageBox("岿粇 : 丁岿粇!",MB_SYSTEMMODAL);
		showTip("岿粇 : 丁岿粇!",true);
		return 0;
	}

	Amount = 0; //无论成功还是失败，都改变了Amount的值.

	_Discount		= Discount;
	_BegTime		= BegTime;
	_EndTime		= EndTime;
	_CarTypeID		= VehicleTypeID;
	_GroupTypeID	= GroupTypeID;
	_PayAgain		= PayAgain;
	_ShowDetail		= ShowDetail;
	ASSERT(NULL != _ShowDetail);

// UCH -new discount calcu
	if(VehicleTypeID==2 ||VehicleTypeID==5)
	{
//HA-		_BegTime += (1.0/24.0);
	}
	else if(VehicleTypeID==3 ||VehicleTypeID==6)
	{
		_BegTime = _EndTime;
	}
	if(VehicleTypeID==4)
	{
		_BegTime += (3.0/24.0);
	}
	
	_ShowDetail( "Calculate parking fee begin.");
	_ShowDetail( "          Parameters:");
	_ShowDetail( "          Discount:" + show(_Discount));
	_ShowDetail( "          Time:" + show(_BegTime) +" -> "+ show(_EndTime));
	_ShowDetail( "          VehicleTypeID:" + show(_CarTypeID));
	_ShowDetail( "          GroupTypeID:" + show(_GroupTypeID));
	_ShowDetail( "          Is Pay Again:" + show(_PayAgain));

	USHORT Result = Calculate_Success;
	//         _||_         // InitCalcualate
	//         \  /
	//          \/
	InitCalculate();			//初始化
	Result = CheckGrace();		//检测免费时间片
	if (Need_Continue_Process != Result) 
	{
		ZeroDeductType = 3;
		return Result;
	}
	//         _||_         // Check Fix Discount
	//         \  /
	//          \/
	CheckFixDiscount();		//补充折扣规定 
//	Pre_EffectDiscount();
	//         _||_         // Calculate loop
	//         \  /
	//          \/	
	Result = CalculateLoop();//计算费用循环
	if (Calculate_Success > Result) return Result;
	Sub_EffectDiscount();
	Amount = _Amount;
	return Calculate_Success;
}
//////////////////////////////////////////////////////////////////////
//初始化
void CFeeCalculate::InitCalculate()  // damage payment check point 005 (init calculate)
{
	_FixDiscount.Clear();
	_Amount = 0.0;
	//环境设定
	CSetting * pSetting = CSetting::Instance();
	_CutByTimeZone		= pSetting->m_ParkingFee.CutByTimeZone(); // [BW] Cross time zone ?
	_ApplyFixTimeRule	= pSetting->m_ParkingFee.FixTimeRule();
	_PaidGraceTime		= pSetting->m_ParkingFee.PaidGrace();
	_EnterGraceTime		= pSetting->m_ParkingFee.EnterGrace();
	_TZoneGraceTime		= pSetting->m_ParkingFee.TZoneGrace();

	COleDateTimeSpan ts(0, 0, 0, 0);
	//ts.SetDateTimeSpan(0, 0, 0, 0);//(0,0,2,0);.
	_IsCrossTimeZone = true;
	_TZoneGraceTime += ts;
	_EndTime -= _TZoneGraceTime;
	//	USHORT Result = CheckTimeZoneGrace();	//检测免费时间片

}
//////////////////////////////////////////////////////////////////////
USHORT CFeeCalculate::CheckGrace()
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Check 'GraceTime'.");
	if ( _PayAgain )
	{//付费离场免费时间
		if (_BegTime + _PaidGraceTime >= _EndTime)
		{
			_ShowDetail("          In 'Paid Grace Time'.");
			return Zero_Fee_By_Paid_Grace_Time;
		}
	}
	else
	{//临时进场免费时间
		if (_BegTime + _EnterGraceTime >= _EndTime)
		{
			_ShowDetail("          In 'Enter Grace Time'.");
			return Zero_Fee_By_Enter_Grace_Time;
		}
	}
	_ShowDetail("          Not in grace time.");
	return Need_Continue_Process;
}

USHORT CFeeCalculate::CheckTimeZoneGrace()
{
	_ShowDetail( "Check time zone grace.");
	
	COleDateTimeSpan ts = _TZoneGraceTime;
	int fi;
	fi = ts.GetDays();
	fi = ts.GetHours();
	fi = ts.GetMinutes();
	fi = ts.GetSeconds();

	ts = _EndTime - _BegTime;
	fi = ts.GetDays();
	fi = ts.GetHours();
	fi = ts.GetMinutes();
	fi = ts.GetSeconds();

	if ( _TZoneGraceTime >= ( _EndTime - _BegTime ) )
	{
		_ShowDetail("          In TimeZone Free Time. ");
		return Zero_Fee_By_TZone_Grace_Time;
	}
	return Need_Continue_Process;
}

void CFeeCalculate::CheckFixDiscount()  // damage payment check point 006 (check fix discount)
{

	if (!_ApplyFixTimeRule) return;
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Check Fix Discount.");
	CSetting * pSetting = CSetting::Instance();
	_FixDiscount = pSetting->m_FixRule.GetFixDiscount(_BegTime, _EndTime);
}

void CFeeCalculate::Pre_EffectDiscount()
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Pre Effect Discount.");
	//补充折扣
	if (_ApplyFixTimeRule)
	{
		_ShowDetail( "          Effect 'Fix Discount':" + show(_FixDiscount));
		_FixDiscount.Pre_EffectDiscount(_BegTime, _EndTime);
	}
	//普通折扣
	_ShowDetail( "          Effect 'Discount':" + show(_Discount));
	_Discount.Pre_EffectDiscount(_BegTime, _EndTime);
}

void CFeeCalculate::Sub_EffectDiscount()
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Sub Effect Discount.");
	//补充折扣
	if (_ApplyFixTimeRule)
	{	
		_ShowDetail( "          Effect 'Fix Discount':" + show(_FixDiscount));
		_FixDiscount.Sub_EffectDiscount(_Amount);
	}
	//普通折扣
	_ShowDetail( "          Effect 'Discount':" + show(_Discount));
	_Discount.Sub_EffectDiscount(_Amount);
}

const CString CFeeCalculate::GetErrorMessage(USHORT nMsg)
{
	switch (nMsg)
	{
	case Err_Day_Rule_Absence					:return "Err Day Rule Absence";				//用不存在的日期
	case Err_Group_Rule_Absence					:return "Err Group Rule Absence";			//用不存在的'GroupID'查询
	case Err_Group_Rule_Undefined_Vehicle_Type	:return "Err Group Rule Undefined Vehicle Type";//
	case Err_Vehicle_Rule_Absence				:return "Err Vehicle Rule Absence";			//用不存在的'VehicleID'查询
	case Err_Timezone_Rule_Absence				:return "Err Timezone Rule Absence";		//用不存在的'TimezoneID'查询
	case Err_Timezone_Rule_Undefined_Timezone	:return "Err Timezone Rule Undefined Timezone";		//由于'Timezone'规则不合理导致出现未定义的收费时间段存在
	case Err_Fee_Rule_Absence					:return "Err Fee Rule Absence";				//用不存在的'FeeID'查询
	case Err_Fee_Rule_Undefined_Unit			:return "Err Fee Rule Undefined Unit";		//由于'Fee'规则不合理导致出现未定义的收费时间片存在
	case Err_Fix_Discount_Rule_Broken			:return "Err Fix Discount Rule Broken";		//
	case Err_Too_Long_Times_Calculate			:return "Err Too Long Times Calculate";		//出现死循环
	case Zero_Fee_By_Paid_Grace_Time			:return "Zero Fee By Paid Grace Time";
	case Zero_Fee_By_Enter_Grace_Time			:return "Zero Fee By Enter Grace Time";
	case Zero_Fee_By_TZone_Grace_Time			:return "Zero Fee By TZone Grace Time";
	case Zero_Fee_By_Fix_Discount_Free_Hours	:return "Zero Fee By Fix Discount Free Hours";
	case Err_Impossible_Payment_Currency		:return "Impossible Payment Currency";
	case Ahead_Result_By_PerEntry_Time_Unit     :return "Ahead Result By PerEntry Time Unit";
	default :
		ASSERT(1!=1);//未定义的错误
		return "Undefined Error!";
	}	
}
//////////////////////////////////////////////////////////////////////
//计算费用循环
USHORT CFeeCalculate::CalculateLoop()  // damage payment check point 009 (calculate loop)
{
	USHORT Result;
	short ErrCalculateTimes = 1000;	//至多计算三年的费用
//	while ( _BegTime < _EndTime )
	while ( IsBigger(_EndTime, _BegTime) )
	{
		short TimeZoneRulesId;
	    //         _||_       
	    //         \  /
	    //          \/
		Result = PickTimeZoneRuleID(TimeZoneRulesId);
		if (Need_Continue_Process != Result) return Result;
		Result = CalculateTimezone(TimeZoneRulesId);
		if (Need_Continue_Process != Result) return Result;
		if (!ErrCalculateTimes--) return Err_Too_Long_Times_Calculate;
	}
	return Calculate_Success;
}
//////////////////////////////////////////////////////////////////////
//获得时间段索引
USHORT CFeeCalculate::PickTimeZoneRuleID(short &TimeZoneRulesId)
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail( "Pick Time Zone Rule Index.");
	_ShowDetail( "          Current calculate begin time:" + show(_BegTime) );
	//获得组索引
	short GroupRulesId;
	CSetting * pSetting = CSetting::Instance();
	if (!pSetting->m_DateRule.GetGroupRulesId(_BegTime, GroupRulesId))
		return Err_Day_Rule_Absence;		//日期规则缺失
	//获得车辆索引
	short CarRulesId;
	if (!pSetting->m_GroupRule.GetCarRulesId(GroupRulesId, _GroupTypeID, CarRulesId))
		return Err_Group_Rule_Absence;		//组规则缺失
	//获得时间段索引
//	CarRulesId 
	if (!pSetting->m_CarRule.GetTimeZoneRulesId(CarRulesId, _CarTypeID, TimeZoneRulesId))
		return Err_Vehicle_Rule_Absence;	//车辆规则缺失

	_ShowDetail( "          Time Zone Rules Id:" + show(TimeZoneRulesId) );
	return Need_Continue_Process;
}
//////////////////////////////////////////////////////////////////////
//计算一个时间段
USHORT CFeeCalculate::CalculateTimezone(const short TimeZoneRulesId)
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail( "Calculate Timezone.");
	CSetting * pSetting = CSetting::Instance();
	USHORT Result;
//	Result = CheckTimeZoneGrace();	//检测免费时间片
//	if (Need_Continue_Process != Result) return Result;

	short UnitRulesId;
	COleDateTime TimeZoneTerminal;
	short ErrCalculateTimes = 10;	//防止死循环 //ňゎ碻吏
	do 
	{
		//获取时间片索引, 时间段终止时间(以'_BegTime'所在的日期为准).
		//
		//莉丁ま, 丁琿沧ゎ丁('_BegTime'┮ら戳).
		//
		if (!pSetting->m_TimeZoneRule.GetUnitRulesId(TimeZoneRulesId, _BegTime, UnitRulesId, TimeZoneTerminal))
			return Err_Timezone_Rule_Undefined_Timezone;//对应的Timezone没有覆盖全天的所有时间.
													//癸莱Timezone⊿Τ滦籠ぱ┮Τ丁.
//#ifndef _DEBUG
		LastFeeIndex = UnitRulesId;
//#else
//		if (UnitRulesId == LastFeeIndex) UnitRulesId = 0;  // [CS] UCH 2010
//		else
//			LastFeeIndex = UnitRulesId;
//#endif


		if (IsBigger(TimeZoneTerminal, _EndTime))
			TimeZoneTerminal = _EndTime;				//取'结尾'与'时间段'中较小的一个.
                                                        //'挡Ю'籔'丁琿'い耕.
		//计算一个时间片
		//璸衡丁
		Result = CalculateUnit(UnitRulesId, TimeZoneTerminal);
		if (Need_Continue_Process != Result) return Result;
		if (!ErrCalculateTimes--) return Err_Too_Long_Times_Calculate;
//	}while(_BegTime < TimeZoneTerminal);	//直到计算到时间段结尾
	}while(IsBigger(TimeZoneTerminal, _BegTime));	//直到计算到时间段结尾
													//璸衡丁琿挡Ю is TimezoneTerminal > _BegTime (if y = true)
	return Need_Continue_Process;
}
//////////////////////////////////////////////////////////////////////
//计算一个时间片
USHORT CFeeCalculate::CalculateUnit(const short UnitRulesId, const COleDateTime TimeZoneTerminal)
{
	CSetting * pSetting = CSetting::Instance();

	short	RequestTimes = 0;	//请求的获取Unit和Charge的次数.
								//叫―莉Unit㎝ChargeΩ计.
	long	Unit = 0;			//时间片长度(sec. number)如果为零则长度无限.
								//丁(sec. number)狦箂玥礚.
								
	double	Charge = 0.0;		//时间片单价
								//丁虫基

	short	ErrCalculateTimes = 100;	//防止死循环
                                      	//ňゎ碻吏
	int     OperFlag = 0;

	while (IsBigger(TimeZoneTerminal, _BegTime))
	{
		//传入上次的'Unit'和'Charge', 取得本次  		
        //肚Ω'Unit'㎝'Charge', 眔セΩ
		if ( !pSetting->m_UnitRule.GetRule(UnitRulesId, RequestTimes, Unit, Charge) )
			return Err_Fee_Rule_Undefined_Unit;//对应的UnitRules有问题.
		                                       //癸莱UnitRulesΤ拜肈.

		if (0.0049 > Charge)
		{
			Charge = 0.0;
			OperFlag = 1;
		}

		SubtractUnit(Unit, TimeZoneTerminal,OperFlag);	//从要计算的时间中减去时间片//眖璶璸衡丁い搭丁 
		//if (0.0049 > Charge) Charge = 0.0;		//价格不能为负              //基ぃ璽
		_Amount += Charge;						//加上费用                  //禣ノ
		RequestTimes++;
		_ShowDetail( "     Unit Rules:" + show(UnitRulesId) + 
							"  Length (sec.):" + show(Unit) + 
							"  Charge:" + show(Charge) + 
							"  Current Time:" + show(_BegTime));
		if (!ErrCalculateTimes--) return Err_Too_Long_Times_Calculate;
	}
	return Need_Continue_Process;
}
//////////////////////////////////////////////////////////////////////
//从要计算的时间中减去时间片 眖璶璸衡丁い搭丁
void CFeeCalculate::SubtractUnit(const long &Unit,const COleDateTime &TimeZoneTerminal,int OperFlag)
{
	if (0==Unit)				//无限长时间片//礚丁
	{
		_BegTime = _EndTime;
	}
	else
	{
		COleDateTimeSpan ts;
		ts.SetDateTimeSpan(0,0,0,Unit);
		_BegTime += ts;
	}

	if ( _CutByTimeZone )		//切割时间段   //ち澄丁琿
	{
		if (_BegTime > TimeZoneTerminal && OperFlag == 1)	//不可操作时间段结尾  //ぃ巨丁琿挡Ю 
			_BegTime = TimeZoneTerminal;
	}
}
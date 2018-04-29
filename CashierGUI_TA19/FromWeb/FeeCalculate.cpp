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
//�����ӿ�
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
		::AfxMessageBox("���~ : �J�f�ɶ����~!",MB_SYSTEMMODAL);
		showTip("���~ : �J�f�ɶ����~!",true);
		return 0;
	}

	Amount = 0; //���۳ɹ�����ʧ�ܣ����ı���Amount��ֵ.

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
	InitCalculate();			//��ʼ��
	Result = CheckGrace();		//������ʱ��Ƭ
	if (Need_Continue_Process != Result) 
	{
		ZeroDeductType = 3;
		return Result;
	}
	//         _||_         // Check Fix Discount
	//         \  /
	//          \/
	CheckFixDiscount();		//�����ۿ۹涨 
//	Pre_EffectDiscount();
	//         _||_         // Calculate loop
	//         \  /
	//          \/	
	Result = CalculateLoop();//�������ѭ��
	if (Calculate_Success > Result) return Result;
	Sub_EffectDiscount();
	Amount = _Amount;
	return Calculate_Success;
}
//////////////////////////////////////////////////////////////////////
//��ʼ��
void CFeeCalculate::InitCalculate()  // damage payment check point 005 (init calculate)
{
	_FixDiscount.Clear();
	_Amount = 0.0;
	//�����趨
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
	//	USHORT Result = CheckTimeZoneGrace();	//������ʱ��Ƭ

}
//////////////////////////////////////////////////////////////////////
USHORT CFeeCalculate::CheckGrace()
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Check 'GraceTime'.");
	if ( _PayAgain )
	{//�����볡���ʱ��
		if (_BegTime + _PaidGraceTime >= _EndTime)
		{
			_ShowDetail("          In 'Paid Grace Time'.");
			return Zero_Fee_By_Paid_Grace_Time;
		}
	}
	else
	{//��ʱ�������ʱ��
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
	//�����ۿ�
	if (_ApplyFixTimeRule)
	{
		_ShowDetail( "          Effect 'Fix Discount':" + show(_FixDiscount));
		_FixDiscount.Pre_EffectDiscount(_BegTime, _EndTime);
	}
	//��ͨ�ۿ�
	_ShowDetail( "          Effect 'Discount':" + show(_Discount));
	_Discount.Pre_EffectDiscount(_BegTime, _EndTime);
}

void CFeeCalculate::Sub_EffectDiscount()
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail("Sub Effect Discount.");
	//�����ۿ�
	if (_ApplyFixTimeRule)
	{	
		_ShowDetail( "          Effect 'Fix Discount':" + show(_FixDiscount));
		_FixDiscount.Sub_EffectDiscount(_Amount);
	}
	//��ͨ�ۿ�
	_ShowDetail( "          Effect 'Discount':" + show(_Discount));
	_Discount.Sub_EffectDiscount(_Amount);
}

const CString CFeeCalculate::GetErrorMessage(USHORT nMsg)
{
	switch (nMsg)
	{
	case Err_Day_Rule_Absence					:return "Err Day Rule Absence";				//�ò����ڵ�����
	case Err_Group_Rule_Absence					:return "Err Group Rule Absence";			//�ò����ڵ�'GroupID'��ѯ
	case Err_Group_Rule_Undefined_Vehicle_Type	:return "Err Group Rule Undefined Vehicle Type";//
	case Err_Vehicle_Rule_Absence				:return "Err Vehicle Rule Absence";			//�ò����ڵ�'VehicleID'��ѯ
	case Err_Timezone_Rule_Absence				:return "Err Timezone Rule Absence";		//�ò����ڵ�'TimezoneID'��ѯ
	case Err_Timezone_Rule_Undefined_Timezone	:return "Err Timezone Rule Undefined Timezone";		//����'Timezone'���򲻺����³���δ������շ�ʱ��δ���
	case Err_Fee_Rule_Absence					:return "Err Fee Rule Absence";				//�ò����ڵ�'FeeID'��ѯ
	case Err_Fee_Rule_Undefined_Unit			:return "Err Fee Rule Undefined Unit";		//����'Fee'���򲻺����³���δ������շ�ʱ��Ƭ����
	case Err_Fix_Discount_Rule_Broken			:return "Err Fix Discount Rule Broken";		//
	case Err_Too_Long_Times_Calculate			:return "Err Too Long Times Calculate";		//������ѭ��
	case Zero_Fee_By_Paid_Grace_Time			:return "Zero Fee By Paid Grace Time";
	case Zero_Fee_By_Enter_Grace_Time			:return "Zero Fee By Enter Grace Time";
	case Zero_Fee_By_TZone_Grace_Time			:return "Zero Fee By TZone Grace Time";
	case Zero_Fee_By_Fix_Discount_Free_Hours	:return "Zero Fee By Fix Discount Free Hours";
	case Err_Impossible_Payment_Currency		:return "Impossible Payment Currency";
	case Ahead_Result_By_PerEntry_Time_Unit     :return "Ahead Result By PerEntry Time Unit";
	default :
		ASSERT(1!=1);//δ����Ĵ���
		return "Undefined Error!";
	}	
}
//////////////////////////////////////////////////////////////////////
//�������ѭ��
USHORT CFeeCalculate::CalculateLoop()  // damage payment check point 009 (calculate loop)
{
	USHORT Result;
	short ErrCalculateTimes = 1000;	//�����������ķ���
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
//���ʱ�������
USHORT CFeeCalculate::PickTimeZoneRuleID(short &TimeZoneRulesId)
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail( "Pick Time Zone Rule Index.");
	_ShowDetail( "          Current calculate begin time:" + show(_BegTime) );
	//���������
	short GroupRulesId;
	CSetting * pSetting = CSetting::Instance();
	if (!pSetting->m_DateRule.GetGroupRulesId(_BegTime, GroupRulesId))
		return Err_Day_Rule_Absence;		//���ڹ���ȱʧ
	//��ó�������
	short CarRulesId;
	if (!pSetting->m_GroupRule.GetCarRulesId(GroupRulesId, _GroupTypeID, CarRulesId))
		return Err_Group_Rule_Absence;		//�����ȱʧ
	//���ʱ�������
//	CarRulesId 
	if (!pSetting->m_CarRule.GetTimeZoneRulesId(CarRulesId, _CarTypeID, TimeZoneRulesId))
		return Err_Vehicle_Rule_Absence;	//��������ȱʧ

	_ShowDetail( "          Time Zone Rules Id:" + show(TimeZoneRulesId) );
	return Need_Continue_Process;
}
//////////////////////////////////////////////////////////////////////
//����һ��ʱ���
USHORT CFeeCalculate::CalculateTimezone(const short TimeZoneRulesId)
{
	_ShowDetail( "------------------------------------------------------------------------------------------------------------------------------------");
	_ShowDetail( "Calculate Timezone.");
	CSetting * pSetting = CSetting::Instance();
	USHORT Result;
//	Result = CheckTimeZoneGrace();	//������ʱ��Ƭ
//	if (Need_Continue_Process != Result) return Result;

	short UnitRulesId;
	COleDateTime TimeZoneTerminal;
	short ErrCalculateTimes = 10;	//��ֹ��ѭ�� //����`��
	do 
	{
		//��ȡʱ��Ƭ����, ʱ�����ֹʱ��(��'_BegTime'���ڵ�����Ϊ׼).
		//
		//����ɶ�������, �ɶ��q�פ�ɶ�(�H'_BegTime'�Ҧb���������).
		//
		if (!pSetting->m_TimeZoneRule.GetUnitRulesId(TimeZoneRulesId, _BegTime, UnitRulesId, TimeZoneTerminal))
			return Err_Timezone_Rule_Undefined_Timezone;//��Ӧ��Timezoneû�и���ȫ�������ʱ��.
													//������Timezone�S���л\���Ѫ��Ҧ��ɶ�.
//#ifndef _DEBUG
		LastFeeIndex = UnitRulesId;
//#else
//		if (UnitRulesId == LastFeeIndex) UnitRulesId = 0;  // [CS] UCH 2010
//		else
//			LastFeeIndex = UnitRulesId;
//#endif


		if (IsBigger(TimeZoneTerminal, _EndTime))
			TimeZoneTerminal = _EndTime;				//ȡ'��β'��'ʱ���'�н�С��һ��.
                                                        //��'����'�P'�ɶ��q'�����p���@��.
		//����һ��ʱ��Ƭ
		//�p��@�Ӯɶ���
		Result = CalculateUnit(UnitRulesId, TimeZoneTerminal);
		if (Need_Continue_Process != Result) return Result;
		if (!ErrCalculateTimes--) return Err_Too_Long_Times_Calculate;
//	}while(_BegTime < TimeZoneTerminal);	//ֱ�����㵽ʱ��ν�β
	}while(IsBigger(TimeZoneTerminal, _BegTime));	//ֱ�����㵽ʱ��ν�β
													//����p���ɶ��q���� is TimezoneTerminal > _BegTime (if y = true)
	return Need_Continue_Process;
}
//////////////////////////////////////////////////////////////////////
//����һ��ʱ��Ƭ
USHORT CFeeCalculate::CalculateUnit(const short UnitRulesId, const COleDateTime TimeZoneTerminal)
{
	CSetting * pSetting = CSetting::Instance();

	short	RequestTimes = 0;	//����Ļ�ȡUnit��Charge�Ĵ���.
								//�ШD�����Unit�MCharge������.
	long	Unit = 0;			//ʱ��Ƭ����(sec. number)���Ϊ���򳤶�����.
								//�ɶ�������(sec. number)�p�G���s�h���׵L��.
								
	double	Charge = 0.0;		//ʱ��Ƭ����
								//�ɶ������

	short	ErrCalculateTimes = 100;	//��ֹ��ѭ��
                                      	//����`��
	int     OperFlag = 0;

	while (IsBigger(TimeZoneTerminal, _BegTime))
	{
		//�����ϴε�'Unit'��'Charge', ȡ�ñ���  		
        //�ǤJ�W����'Unit'�M'Charge', ���o����
		if ( !pSetting->m_UnitRule.GetRule(UnitRulesId, RequestTimes, Unit, Charge) )
			return Err_Fee_Rule_Undefined_Unit;//��Ӧ��UnitRules������.
		                                       //������UnitRules�����D.

		if (0.0049 > Charge)
		{
			Charge = 0.0;
			OperFlag = 1;
		}

		SubtractUnit(Unit, TimeZoneTerminal,OperFlag);	//��Ҫ�����ʱ���м�ȥʱ��Ƭ//�q�n�p�⪺�ɶ�����h�ɶ��� 
		//if (0.0049 > Charge) Charge = 0.0;		//�۸���Ϊ��              //���椣�ର�t
		_Amount += Charge;						//���Ϸ���                  //�[�W�O��
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
//��Ҫ�����ʱ���м�ȥʱ��Ƭ �q�n�p�⪺�ɶ�����h�ɶ���
void CFeeCalculate::SubtractUnit(const long &Unit,const COleDateTime &TimeZoneTerminal,int OperFlag)
{
	if (0==Unit)				//���޳�ʱ��Ƭ//�L�����ɶ���
	{
		_BegTime = _EndTime;
	}
	else
	{
		COleDateTimeSpan ts;
		ts.SetDateTimeSpan(0,0,0,Unit);
		_BegTime += ts;
	}

	if ( _CutByTimeZone )		//�и�ʱ���   //���ήɶ��q
	{
		if (_BegTime > TimeZoneTerminal && OperFlag == 1)	//���ɲ���ʱ��ν�β  //���i�ާ@�ɶ��q���� 
			_BegTime = TimeZoneTerminal;
	}
}
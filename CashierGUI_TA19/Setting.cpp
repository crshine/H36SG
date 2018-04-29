// Setting.cpp: implementation of the CSetting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "CmdOtp.h"
#include "Setting.h"

extern _System		g_System;
extern CLog *		g_pLog;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetting* CSetting::_instance = 0;
//const CString CSetting::SettingFileName = "\\SettingFile.dat";



CSetting* CSetting::Instance()
{
    if (_instance == 0) {
        _instance = new CSetting;
    }
    return _instance;
}

CSetting::CSetting()
{
	_FontBig.CreateFont( -24, 0, 0, 0, 700, 0, 0, 0, 1,
						0, 0, 0, 0, _T("MS Sans Serif") );
	_FontMid.CreateFont( -18, 0, 0, 0, 700, 0, 0, 0, 1,
						0, 0, 0, 0, _T("MS Sans Serif") );
	_BrushErrDlgBackGround.CreateSolidBrush(RGB(212, 208, 200)); //bg colour

	_FontErrBig.CreateFont( -24, 0, 0, 0, 700, 0, 0, 0, 1,
						0, 0, 0, 0, _T("MS Sans Serif") );
	_FontErrMid.CreateFont( -18, 0, 0, 0, 700, 0, 0, 0, 1,
						0, 0, 0, 0, _T("MS Sans Serif") );
	//异常操作时的背景色
	_AbnormityBrush.CreateSolidBrush(RGB(212, 208, 200)); //bg colour
	//异常操作时的文字颜色
	_AbnormityColor = RGB(10,10,10);
}

CSetting::~CSetting()
{

}
/*
void CSetting::Load()
{
	CStringFile f;
	CFileException e;
	if (!f.Open(g_System.RunTime.sAppPath + SettingFileName, &e)) return;
	CString sLine;

	while (0 != f.GetNextLine(sLine))
	{
		if (2>=sLine.GetLength()) continue;//没有信息, 处理下一行
		char cType[2];
		memcpy(cType, sLine, sizeof(cType));
		sLine.Delete(0, 2);
		switch(atoi(cType))
		{
		case 1:
			m_BaseSystemSetting.Assign(sLine);
			break;
		case 2:
			m_CardType.Assign(sLine);
			break;
		case 3:
			m_DiscountPlan.Assign(sLine);
			break;
		case 4:
			m_GroupType.Assign(sLine);
			break;
		case 5:
			m_ParkingFee.Assign(sLine);
			break;
		case 6:
			m_PayModeDefinition.Assign(sLine);
			break;
		case 7:
			m_StationInformation.Assign(sLine);
			break;
		case 8:
			m_VehicleType.Assign(sLine);
			break;
		case 9:
			m_Account.Assign(sLine);
			break;
		case 10:
			m_Receipt.Assign(sLine);
			break;
		case 11:
			m_Peripheral.Assign(sLine);
			break;
		case 12:
			m_Communicate.Assign(sLine);
			break;
		case 13:
			m_Permission.Assign(sLine);
			break;
		case 20:
			m_DateRule.Assign(sLine);
			break;
		case 21:
			m_GroupRule.Assign(sLine);
			break;
		case 22:
			m_CarRule.Assign(sLine);
			break;
		case 23:
			m_TimeZoneRule.Assign(sLine);
			break;
		case 24:
			m_UnitRule.Assign(sLine);
			break;
		case 25:
			m_FixRule.Assign(sLine);
			break;
		default://错误
			ASSERT( 1 != 1 ); //there must have some error!
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("SysFile data format error."));
		}
	}
}
*/
BOOL CSetting::LoadFile(CString FileName, CString & Item)
{
	CFile f;
	CFileException e;
	
	if (!f.Open(g_System.RunTime.sAppPath + FileName, CFile::modeRead, &e)) return FALSE;
	
	//READ THEM ALL
	LPTSTR tmpbuf = Item.GetBuffer(2048);
	memset(tmpbuf, 0, 2048);
	DWORD len = f.Read((LPVOID)tmpbuf, 2048);
	Item.ReleaseBuffer();
	f.Close();
	if (len < 2) return FALSE;
	Item.Mid(2, len-2);
	return TRUE;
}

void CSetting::Load()
{
	CString Item;

	if (LoadFile(m_BaseSystemSetting.ClassID(), Item)) m_BaseSystemSetting.Assign(Item);
	else {
		m_BaseSystemSetting.StoreAndAssign("SMARON Car Park               00101950001100011012");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Basic Sys Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_CardType.ClassID(), Item)) m_CardType.Assign(Item);
	else {
		m_CardType.StoreAndAssign("1Season Card         0002000000500000005501T0000%00300002Store Value         1000000001000000000001Y0000$00500013");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Card Type Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_DiscountPlan.ClassID(), Item)) m_DiscountPlan.Assign(Item);
	else {
		m_DiscountPlan.StoreAndAssign("000Normal Hourly Parking         0000000001Redeem by Tenants             %006000002Tenant Customers              $000008003Emergency/Public Service      $000010004Bian Bee Inspection           @000000005Contractor of Tenants         H000200");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Discount Plan Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_GroupType.ClassID(), Item)) m_GroupType.Assign(Item);
	else {
		m_GroupType.StoreAndAssign("00032Bian Bee Company Pte Ltd      06300320");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Group Type Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_ParkingFee.ClassID(), Item)) m_ParkingFee.Assign(Item);
	else {
		m_ParkingFee.StoreAndAssign("010010005000000000100000100000");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Fee Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_PayModeDefinition.ClassID(), Item)) m_PayModeDefinition.Assign(Item);
	else {
		m_PayModeDefinition.StoreAndAssign("0Cash                11Cashcard            12Store Value         0");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Pay Mode Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_StationInformation.ClassID(), Item)) m_StationInformation.Assign(Item);
	else {
		m_StationInformation.StoreAndAssign("011Station 1                     0192.168.2.101  SEX TRY                       022Station 2                     0192.168.2.102  SEX IT                        034DEEPOOL                       0192.168.2.103  MR. PIAO_S CASHIER COMPUTER   ");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Station Settings File Reading Error, use init data instead!"));
	}
/*	if (LoadFile(FILE_VEHICLETYPE.ClassID(), Item)) m_VehicleType.Assign(Item);
	else {
		m_VehicleType.StoreAndAssign("");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Vehicle Type Settings File Reading Error, use init data instead!"));
	}
*/	if (LoadFile(m_Account.ClassID(), Item)) m_Account.Assign(Item);
	else {
		m_Account.StoreAndAssign("           000           000           000           000           000    01050511234546     00"
			"           000           000           000           000           000"
			"     0     0     0     0     0     0     0     0     0"
			"           000           000     0     0");

		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Accounting File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_Receipt.ClassID(), Item)) m_Receipt.Assign(Item);
	else {
		m_Receipt.StoreAndAssign("Centro Bianco                 73 Upper Paya Lebar Road                                    Thank You                     Have a Nice Day               0017GST       MR T80000-21        030303");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Receipt Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_Peripheral.ClassID(), Item)) m_Peripheral.Assign(Item);
	else {
		m_Peripheral.StoreAndAssign(" 2 100  115200 4 100  115200 1  90  115200 51000  115200");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Peripheral Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_Communicate.ClassID(), Item)) m_Communicate.Assign(Item);
	else {
		m_Communicate.StoreAndAssign("0365016500192.168.1.30   00 100");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Communication Settings File Reading Error, use init data instead!"));
	}
/*	if (LoadFile(m_Permission.ClassID(), Item)) m_Permission.Assign(Item);
	else {
		m_Permission.StoreAndAssign("");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Permission Settings File Reading Error, use init data instead!"));
	}
*/	if (LoadFile(m_DateRule.ClassID(), Item)) m_DateRule.Assign(Item);
	else {
		m_DateRule.StoreAndAssign("W0    01W1    00W2    00W3    00W4    00W5    00W6    00");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Date Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_GroupRule.ClassID(), Item)) m_GroupRule.Assign(Item);
	else {
		m_GroupRule.StoreAndAssign("00010000020101000000020000000003000000000403000000");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Group Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_CarRule.ClassID(), Item)) m_CarRule.Assign(Item);
	else {
		m_CarRule.StoreAndAssign("000101010101010000000201020001030000000004040103040502000000");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Car Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_TimeZoneRule.ClassID(), Item)) m_TimeZoneRule.Assign(Item);
	else {
		m_TimeZoneRule.StoreAndAssign("000000080003080014000214002200022200320003010000080009080014000214002200022200240003020000120002000000000000000000000000000000030000000000000000000000000000000000000000040000000000000000000000000000000000000000");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Time Zone Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_UnitRule.ClassID(), Item)) m_UnitRule.Assign(Item);
	else {
		m_UnitRule.StoreAndAssign("000000000100000000000000000000000000000000000000000000000000000000000000000000000001000060005000000000000000000000000000000000000000000000000000000000000000000000000200010004000000000000000000000000000000000000000000000000000000000000000000000000030002009900000000000000000000000000000000000000000000000000000000000000000000000004000000010000000000000000000000000000000000000000000000000000000000000000000000000500000001000000000000000000000000000000000000000000000000000000000000000000000000060000000100000000000000000000000000000000000000000000000000000000000000000000000007000000010000000000000000000000000000000000000000000000000000000000000000000000000800000001000000000000000000000000000000000000000000000000000000000000000000000000090000000100000000000000000000000000000000000000000000000000000000000000000000000010000000010000000000000000000000000000000000000000000000000000000000000000000000001100000001000000000000000000000000000000000000000000000000000000000000000000000000120000000100000000000000000000000000000000000000000000000000000000000000000000000013000000010000000000000000000000000000000000000000000000000000000000000000000000001400000001000000000000000000000000000000000000000000000000000000000000000000000000");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Unit Rule Settings File Reading Error, use init data instead!"));
	}
	if (LoadFile(m_FixRule.ClassID(), Item)) m_FixRule.Assign(Item);
	else {
		m_FixRule.StoreAndAssign("001050105002041610501050020416001@0001000110501050W5    10501050W5    002H000200021209120902041612091209020416003%000020031212122500000012121212000000005$000600");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Fix Rule Settings File Reading Error, use init data instead!"));
	}
}



/////////////////////////////////////////////////////////////////////////////////////
void CSetting::CBase::Store(const char * strSetting)
{	//马上保存设置

	CFile f;
	CFileException e;
	if( !f.Open( g_System.RunTime.sAppPath + ClassID(),  CFile::modeCreate | CFile::modeWrite, &e ) )
	{
		ASSERT(1 < 1); //"File could not be opened " + e.m_cause
		return;
	}
	f.Write(strSetting, strlen(strSetting));  //把序号也写入
	f.Flush();
	f.Close();	
}
void CSetting::CBase::StoreAndAssign(const char * strSetting, const short StrLen)
{
	Store(strSetting);
	Assign(strSetting);
}
/////////////////////////////////////////////////////////////////////////////////////
void CSetting::CBaseSystemSetting::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char SystemName[30];
		char SystemID[3];
		char AutoFunctionTime[4];
		char CardCateAntiPassback[6];
		char OperatorLanguage;
		char CustomerLanguage;
		char EntryOrExit;
		char LowestYN;
		char CashModeID;
		char CardModeID;
		char ValueModeID;
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	_SystemName =			mem2str( fmt.SystemName, sizeof(fmt.SystemName) );
	_SystemID =				mem2short( fmt.SystemID, sizeof(fmt.SystemID) );
	_AutoFunctionTime =		fmt.AutoFunctionTime;
	_CardCateAntiPassback = mem2str( fmt.CardCateAntiPassback, sizeof(fmt.CardCateAntiPassback) );
	_OperatorLanguage =		mem2short(fmt.OperatorLanguage);
	_CustomerLanguage =		mem2short(fmt.CustomerLanguage);
	_EntryOrExit =			mem2short(fmt.EntryOrExit);
	_LowestYN =				mem2short(fmt.LowestYN);
	_CashCardModeID =		mem2short(fmt.CashModeID);
	_CashBackModeID =		mem2short(fmt.CardModeID);
	_StoreValueModeID =		mem2short(fmt.ValueModeID);
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CCardType::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID;
		char		CategoryName[20];
		char		WorkMode;
		char		JoiningFee[6];
		char		CardFee[6];
		char		UnitFee[8];
		char		Unit[2];
		char		WarningLevel[4];
		char		Discount[7];
		char		StoreValue;
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		if (fmt.ID < 49 || fmt.ID>53) break;
		data._Name =	mem2str( fmt.CategoryName, sizeof(fmt.CategoryName) );
		data._WorkMode =		mem2short( fmt.WorkMode );
		data._JoiningFee =		mem2dbl( fmt.JoiningFee, sizeof(fmt.JoiningFee) );
		data._CardFee =			mem2dbl( fmt.CardFee, sizeof(fmt.CardFee) );
		data._UnitFee =			mem2dbl( fmt.UnitFee, sizeof(fmt.UnitFee) );
		data._Unit =			mem2str( fmt.Unit, sizeof(fmt.Unit) );
		data._WarningLevel =	mem2short( fmt.WarningLevel, sizeof(fmt.WarningLevel) );
		data._Discount =		fmt.Discount;
		data._StoreValue =	mem2bool( fmt.StoreValue );

		m_Map.insert(value_type(mem2short( fmt.ID ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CCardType::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

CString CSetting::CCardType::showWorkMode(short ID)
{
	ASSERT( Valid(ID) );
	const CString const_Period	= LPCTSTR(SPECIAL_CARD_MODE_PERIOD);
	const CString const_Times	= LPCTSTR(SPECIAL_CARD_MODE_TIMES);
	const CString const_Free	= LPCTSTR(SPECIAL_CARD_MODE_FREE);
	const CString const_Illegal	= LPCTSTR(SPECIAL_CARD_MODE_ILLEGAL);

	short CODE = WorkMode(ID);
	CString s="";
	if      (0 == CODE) 
		s = const_Period;
	else if (1 == CODE)
		s = const_Times;
	else if (2 == CODE)
		s = const_Free;
	else // (* == CODE)
		s = const_Illegal;
	return s;
}

CString CSetting::CCardType::_Data::showPrice()
{
	const CString InvalidUnitPrice = "Invalid Unit Price";

	ASSERT( !(2!=_Unit.GetLength()) );
	if (2!=_Unit.GetLength()) return InvalidUnitPrice;
	if		( 'Y' == _Unit[1] )
		return show(_UnitFee) + "/" + _Unit[0] + " Year";
	else if ( 'M' == _Unit[1] )
		return show(_UnitFee) + "/" + _Unit[0] + " Month";
	else if ( 'D' == _Unit[1] )
		return show(_UnitFee) + "/" + _Unit[0] + " Day";
	else if ( 'T' == _Unit[1] )
		return show(_UnitFee) + "/" + _Unit[0] + " Trans";
	else
		return InvalidUnitPrice;
}

double CSetting::CCardType::_Data::TimesFee(const short Times)
{
//	ASSERT( !(0 > Times) );
	if (0 > Times) return (double)0.0;
//	ASSERT( IsTimesWorkMode() );
	if (!IsTimesWorkMode()) return (double)0.0;
//	ASSERT( !('T' != _Unit[1]) );
	if ( 'T' != _Unit[1] ) return 0.0;
	return ( (_UnitFee * Times) / _ttoi(_Unit.Left(1)) );
}

double CSetting::CCardType::_Data::PeriodFee(const COleDateTime Beg,const COleDateTime End)
{
//	ASSERT( IsBigger(End, Beg) );
	if ( !IsBigger(End, Beg) ) return 0.0;
//	ASSERT( IsPeriodWorkMode() );
	if ( !IsPeriodWorkMode() ) return 0.0;
	
	short Unit = _ttoi(_Unit.Left(1));
	double Price = 0.0;
	if		(_Unit[1] == 'Y')
	{
		long TotalYear  = End.GetYear() - Beg.GetYear();
		if (End.GetMonth() != Beg.GetMonth())
			TotalYear += (End.GetMonth() > Beg.GetMonth() ? 1 : -1);
		else
		{
			if (End.GetDay() != Beg.GetDay())
			{
				TotalYear += (End.GetDay() > Beg.GetDay() ? 1 : -1);
			}
		}
		return _UnitFee * (TotalYear / Unit);
	}
	else if (_Unit[1] == 'M')
	{
		long TotalMonth  = (End.GetYear() - Beg.GetYear()) * 12;
		TotalMonth += End.GetMonth() - Beg.GetMonth();

		if (End.GetDay() != Beg.GetDay())
		{
			TotalMonth += (End.GetDay() > Beg.GetDay() ? 1 : -1);
		}
		return _UnitFee * (TotalMonth / Unit);
	}
	else if (_Unit[1] == 'D')
	{
		COleDateTimeSpan ts = End - Beg;
		long TotalDays = ts.GetDays() + 1;	//2004,01,01 -> 2004,01,02 算两天

		return _UnitFee * (TotalDays / Unit);
	}
	else
		return 0.0;	//有错误返回0
}

bool CSetting::CCardType::_Data::IsTimesWorkMode()
{
	return (1 == _WorkMode);
}
bool CSetting::CCardType::_Data::IsPeriodWorkMode()
{
	return (0 == _WorkMode);
}

/////////////////////////////////////////////////////////////////////////////
void CSetting::CDiscountPlan::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[3];
		char		Name[30];
		char		Discount[7];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._DiscountName = mem2str( fmt.Name, sizeof(fmt.Name) );
		data._Discount = fmt.Discount;

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}
bool CSetting::CDiscountPlan::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}
///////////////////////////////////////////////////////////////////////////
CSetting::CGroupType::CGroupType()
{
	fit();
}

void CSetting::CGroupType::Assign(const char * rhs)
{
	m_Map.clear();	//清除旧数据
	decode(rhs);
	fit();
}

void CSetting::CGroupType::fit()
{
    //                        
    const CString initStr = "00000Unnamed Group Type 0          0000000010000Unnamed Group Type 1          0000000020000Unnamed Group Type 2          0000000030000Unnamed Group Type 3          00000000";
                         //  ^    {          Description       }        ^    {          Description       }        ^    {          Description       }        ^    {          Description       }       
                         //  ID                                         ID                                         ID                                         ID                                        
	decode(initStr);
}

void CSetting::CGroupType::decode(const char *rhs)
{
	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID;
		char		Lots[4];
		char		Description[30];
		char		CtrlCategory[3];
		char		CtrlLots[4];
		char		IgnoreFullSign;
	} fmt;
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._Lots =			mem2short( fmt.Lots, sizeof(fmt.Lots) );
		data._Description =		mem2str( fmt.Description, sizeof(fmt.Description) );
		data._CtrlCategory =	mem2short( fmt.CtrlCategory, sizeof(fmt.CtrlCategory) );
		data._CtrlLots =		mem2short( fmt.CtrlLots, sizeof(fmt.CtrlLots) );
		data._IgnoreFullSign =	mem2bool( fmt.IgnoreFullSign );

		m_Map.insert(value_type(mem2short( fmt.ID ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}
bool CSetting::CGroupType::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////
void CSetting::CParkingFee::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format		//	字符串格式
	{
		char FirstEnterFreeTime[3];
		char PaidFreeTime[3];
		char OvertimeFreeTime[3];
		char LostAmount[6];
		char CreditLimit[6];
		char PerEntryAmt[6];
		char CutByTimeZone;
		char LostAddParkingFee;
		char IsFixTimeRule;
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	short min;
	min = mem2short( fmt.FirstEnterFreeTime, sizeof(fmt.FirstEnterFreeTime) );
	_EnterGrace.SetDateTimeSpan(0,0,min,0);
	min = mem2short( fmt.PaidFreeTime, sizeof(fmt.PaidFreeTime) );
	_PaidGrace.SetDateTimeSpan(0,0,min,0);
	min = mem2short( fmt.OvertimeFreeTime, sizeof(fmt.OvertimeFreeTime) );
	_TZoneGrace.SetDateTimeSpan(0,0,min,0);
	_LostAmount = mem2dbl( fmt.LostAmount, sizeof(fmt.LostAmount) );
	_CreditLimit = mem2dbl( fmt.CreditLimit, sizeof(fmt.CreditLimit) );
	_PerEntryAmt = mem2dbl( fmt.PerEntryAmt, sizeof(fmt.PerEntryAmt) );
	_CutByTimeZone = mem2bool( fmt.CutByTimeZone ); 
	_HandleLostTicket = mem2bool( fmt.LostAddParkingFee );
	_FixTimeRule = mem2bool( fmt.IsFixTimeRule );
}
/////////////////////////////////////////////////////////////////////////////////////
void CSetting::CPayModeDefinition::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format		//	字符串格式
	{
		char		ID;
		char		ModeName[20];
		char		NeedCashChanges;
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._ModeName =		mem2str( fmt.ModeName, sizeof(fmt.ModeName) );
		data._NeedCashChanges =	mem2bool( fmt.NeedCashChanges );

		m_Map.insert(value_type(mem2short( fmt.ID ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}
/*
CString CSetting::PayModeDefinition::GetModeName(char ModeID)
{
	if ( m_Map.end() == (m_Iter = m_Map.find(ModeID)) )
		return "undefined mode";								//缺失
	char tmp[21];
	memcpy(tmp, m_Map[ModeID].ModeName, 20);
	tmp[21]='\0';
	return (CString)tmp;
}

BOOL CSetting::PayModeDefinition::GetChangesSet(char ModeID)
{
	if ( m_Map.end() == (m_Iter = m_Map.find(ModeID)) )
		return TRUE;								//缺失
	return ('1'==m_Map[ModeID].NeedCashChanges);
}

CString CSetting::PayModeDefinition::GetData()
{//获取字符串形式的数据
	CString Data = "";
	int posEnd = 0;
	for (m_Iter = m_Map.begin(); m_Iter != m_Map.end(); ++m_Iter)
	{
		for(int i=0; i<sizeof(_Data); ++i)
			Data.Insert(++posEnd, ((char *)&m_Iter->second)[i]);
	};
	return Data;
}
*/
/////////////////////////////////////////////////////////////////////////////
void CSetting::CStationInformation::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format		//	字符串格式
	{
			char		ID[2];
			char		StationType;
			char		StationName[30];
			char		GroupID;
			char		IPAddr[15];
			char		Brief[30];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换

		data._StationType =	mem2short( fmt.StationType );
		data._StationName =	mem2str( fmt.StationName, sizeof(fmt.StationName) );
		data._GroupID =		mem2short( fmt.GroupID );
		data._IPAddr =		mem2str( fmt.IPAddr, sizeof(fmt.IPAddr) );
		data._Brief =		mem2str( fmt.Brief, sizeof(fmt.Brief) );

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CStationInformation::IsEntryStation(short Type)
{
	if (1 == Type)
		return true;
	else
		return false;
}

bool CSetting::CStationInformation::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CPermission::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format		//	字符串格式
	{
		char	ID[4];
		char	Caption[20];
		char	StationType;
		char	ValidForGuest;
		char	ValidForOperator;
		char	ValidForSupervisor;
		char	ValidForManager;
		char	ValidForAdmin;
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换

		data._Caption			= mem2str(   fmt.Caption, sizeof(fmt.Caption) );
		data._StationType		= mem2short( fmt.StationType		);
		data._ValidForGuest		= mem2bool(  fmt.ValidForGuest		);
		data._ValidForOperator	= mem2bool(  fmt.ValidForOperator	);
		data._ValidForSupervisor= mem2bool(  fmt.ValidForSupervisor );
		data._ValidForManager	= mem2bool(  fmt.ValidForManager	);
		data._ValidForAdmin		= mem2bool(  fmt.ValidForAdmin		);

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CPermission::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////
CSetting::CVehicleType::CVehicleType()
{
	fit();
}
void CSetting::CVehicleType::fit()
{
//  const CString initStr = "0VehicleType 1                 1VehicleType 2                 2VehicleType 3                 3VehicleType 4                 ";
 //for UCH 201007
	const CString initStr = "0VehicleType 1                 1VehicleType 2                 2VehicleType 3                 3VehicleType 4                 4VehicleType 5                 5VehicleType 6                 ";
                         //  ^               ^              ^               ^              ^               ^              ^               ^              ^               ^               
                         //  ID             Name            ID             Name            ID             Name            ID             Name            ID             Name             
	decode(initStr);
}
void CSetting::CVehicleType::Assign(const char * rhs)
{
	m_Map.clear();	//清除旧数据
	decode(rhs);
	fit();//
}
void CSetting::CVehicleType::decode(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format		//	字符串格式
	{
			char		ID;
			char		TypeName[30];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	typedef map< short, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._TypeName = mem2str( fmt.TypeName, sizeof(fmt.TypeName) );

		m_Map.insert(value_type(mem2short( fmt.ID ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}
bool CSetting::CVehicleType::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////////
CSetting::CAccount::CAccount()
{
	_TotalOctopus = _TotalCash = _TotalOctopus = _TotalStoreValue = 0;
	_CurrentAmount = _CurrentCash =	_CurrentOctopus = _CurrentStoreValue = 0;
	_PayNum = 0;
	_CurrentCashMaintain = _TotalCashMaintain = 0;
	_DutyStart = COleDateTime::GetCurrentTime();
	_ReceiptNoNumPart = 1;
	_HasAccount = true;
}

CString CSetting::CAccount::ReceiptNo()
{
	CString s;
	CSetting * pSetting = CSetting::Instance();
	s.Format(pSetting->m_Communicate.StationID() + "%06d", _ReceiptNoNumPart);
	_ReceiptNoNumPart++;
	if (_ReceiptNoNumPart > 999999) _ReceiptNoNumPart = 1;
	return s;
}
void CSetting::CAccount::LogPayAmount(double Amount, double Cash, double Octopus, double StoreValue, int TranType)
{
	_TotalAmount		+= Amount;
	_TotalCash			+= Cash;
	_TotalOctopus		+= Octopus;
	_TotalStoreValue	+= StoreValue;

	_CurrentAmount		+= Amount;
	_CurrentCash		+= Cash;
	_CurrentOctopus		+= Octopus;
	_CurrentStoreValue	+= StoreValue;
	_PayNum ++;

	if (TranType < 9) {
		_TransNum[TranType] ++;
	}else if (TranType == 9) {//add value
		_ADNum ++; _ADAmount += Amount;
	}else if (TranType == 10) {//special card managmeent
		_SCMgnNum ++; _SCMgnAmount += Amount;
	}
	
	Store(StrSetting());
}

//////////////////////////////////////////////////////////////////////////////////////////////
// ******** Should be no use [BW] 20051108 function replaced by AfterShiftCloseAccount ******
void CSetting::CAccount::Demolish()   
{
	_CurrentAmount = _CurrentCash =	_CurrentOctopus = _CurrentStoreValue = 0;
	_PayNum = 0;
	_DutyStart = COleDateTime::GetCurrentTime();
	//_ReceiptNoNumPart = 1;
	_HasAccount = false;
	Store(StrSetting());
}
//////////////////////////////////////////////////////////////////////////////////////////////


void CSetting::CAccount::CloseAcc()
{
	_TotalAmount	= 0;
	_TotalCash		= 0;
	_TotalOctopus	= 0;
	_TotalStoreValue= 0;
	_TotalCashMaintain = 0;
	for (int i=0; i<9; i++) _TransNum[i] = 0;
	_ADAmount = 0;
	_SCMgnAmount = 0;
	_ADNum = 0;
	_SCMgnNum = 0;
	Store(StrSetting());
}

void CSetting::CAccount::GetCurrentAccount(double &Amount, double &Cash, double &Octopus, double &StoreValue, COleDateTime & DutyStart, long & PayNum, double &CashMaintain)
{
	Amount = _CurrentAmount;
	Cash = _CurrentCash;
	Octopus = _CurrentOctopus;
	StoreValue = _CurrentStoreValue;
	DutyStart = _DutyStart;
	PayNum = _PayNum;
	CashMaintain = _CurrentCashMaintain; //???

}

void CSetting::CAccount::GetTotalAccount(double &Amount, double &Cash, double &Octopus, double &StoreValue, long TransNum[], double &TotalCashMaintain)
{
	Amount = _TotalAmount;
	Cash = _TotalCash;
	Octopus = _TotalOctopus;
	StoreValue = _TotalStoreValue;
	TotalCashMaintain = _TotalCashMaintain;
	for (int i=0; i<9; i++) TransNum[i] = _TransNum[i];
}

void CSetting::CAccount::GetOtherInfo(double &ADAmount, long &ADNum, double &SCAmount, long &SCNum)
{
	ADAmount = _ADAmount;
	SCAmount = _SCMgnAmount;
	ADNum = _ADNum;
	SCNum = _SCMgnNum;
}


CString CSetting::CAccount::StrSetting()
{
	struct String_Format
	{
		//系统当前状况
		char		_CurrentAmount[14];
		char		_CurrentCash[14];
		char		_CurrentOctopus[14];
		char		_CurrentStoreValue[14];
		char        _CurrentCashMaintain[14];
		//发票号由两部分组成,StationId + 6位自增循环编号;
		char		_ReceiptNoNumPart[6];
		char		_DutyStartTime[12];
		char		_PayNum[6];
		char		_HasAccount;
		char		_TotalAmount[14];
		char		_TotalCash[14];
		char		_TotalOctopus[14];
		char		_TotalStoreValue[14];
		char        _TotalCashMaintain[14];
		char		_TransNum[9][6];
		char		_ADAmount[14];
		char		_SCMgnAmount[14];
		char		_ADNum[6];
		char 		_SCMgnNum[6];

	} fmt;
	
	dbl2mem( _CurrentAmount,		fmt._CurrentAmount,		 sizeof(fmt._CurrentAmount));
	dbl2mem( _CurrentCash,			fmt._CurrentCash,		 sizeof(fmt._CurrentCash));
	dbl2mem( _CurrentOctopus,		fmt._CurrentOctopus,	 sizeof(fmt._CurrentOctopus));
	dbl2mem( _CurrentStoreValue,	fmt._CurrentStoreValue,	 sizeof(fmt._CurrentStoreValue));
	dbl2mem( _CurrentCashMaintain,	fmt._CurrentCashMaintain,sizeof(fmt._CurrentCashMaintain));

	long2mem(_ReceiptNoNumPart,		fmt._ReceiptNoNumPart,	sizeof(fmt._ReceiptNoNumPart));
	datetime2mem(_DutyStart,		fmt._DutyStartTime);
	long2mem(_PayNum,				fmt._PayNum, 6);
	bool2mem(_HasAccount,			fmt._HasAccount);
	
	dbl2mem( _TotalAmount,			fmt._TotalAmount,		sizeof(fmt._TotalAmount));	
	dbl2mem( _TotalCash,			fmt._TotalCash,			sizeof(fmt._TotalCash));	
	dbl2mem( _TotalOctopus,			fmt._TotalOctopus,		sizeof(fmt._TotalOctopus));	
	dbl2mem( _TotalStoreValue,		fmt._TotalStoreValue,	sizeof(fmt._TotalStoreValue));	
	dbl2mem( _TotalCashMaintain,    fmt._TotalCashMaintain,	sizeof(fmt._TotalCashMaintain));	
	
	for (int i=0;i<9;i++)	long2mem( _TransNum[i], fmt._TransNum[i], sizeof(fmt._TransNum[i]));
	
	dbl2mem( _ADAmount,			fmt._ADAmount,			sizeof(fmt._ADAmount	));	
	dbl2mem( _SCMgnAmount,		fmt._SCMgnAmount,		sizeof(fmt._SCMgnAmount));	
	
	long2mem( _ADNum,			fmt._ADNum,  6);
	long2mem( _SCMgnNum,		fmt._SCMgnNum, 6);

	char strFmt[sizeof(fmt)+2];
	memcpy(strFmt, &fmt, sizeof(fmt));
	strFmt[sizeof(fmt)]=0x03;	//停止位
	strFmt[sizeof(fmt)+1]=0x00;	//串尾
	return (CString)strFmt;
}

void CSetting::CAccount::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		//从系统运行起的统计结果
		char		_CurrentAmount[14];
		char		_CurrentCash[14];
		char		_CurrentOctopus[14];
		char		_CurrentStoreValue[14];
		char        _CurrentCashMaintain[14];
		char		_ReceiptNoNumPart[6];		//发票号由两部分组成,StationId + 6位自增循环编号;
		char		_DutyStartTime[12];
		char		_PayNum[6];
		char		_HasAccount;
		char		_TotalAmount[14];
		char		_TotalCash[14];
		char		_TotalOctopus[14];
		char		_TotalStoreValue[14];
        char        _TotalCashMaintain[14];
		char		_TransNum[9][6];
		char		_ADAmount[14];
		char		_SCMgnAmount[14];
		char		_ADNum[6];
		char 		_SCMgnNum[6];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	//从系统运行起的统计结果
	_CurrentAmount		= mem2dbl( fmt._CurrentAmount,		sizeof(fmt._CurrentAmount));
	_CurrentCash		= mem2dbl( fmt._CurrentCash,		sizeof(fmt._CurrentCash));
	_CurrentOctopus		= mem2dbl( fmt._CurrentOctopus,		sizeof(fmt._CurrentOctopus));
	_CurrentStoreValue	= mem2dbl( fmt._CurrentStoreValue,	sizeof(fmt._CurrentStoreValue));
	_CurrentCashMaintain= mem2dbl( fmt._CurrentCashMaintain,sizeof(fmt._CurrentCashMaintain));

	_ReceiptNoNumPart	= mem2long(fmt._ReceiptNoNumPart,	sizeof(fmt._ReceiptNoNumPart));
	_DutyStart			= mem2datetime(fmt._DutyStartTime);
	_PayNum				= mem2long(fmt._PayNum, 6);
	_HasAccount			= mem2bool(fmt._HasAccount);

	//本次交接班内的情况
	_TotalAmount		= mem2dbl( fmt._TotalAmount,		sizeof(fmt._TotalAmount));
	_TotalCash			= mem2dbl( fmt._TotalCash,		sizeof(fmt._TotalCash));
	_TotalOctopus		= mem2dbl( fmt._TotalOctopus,		sizeof(fmt._TotalOctopus));
	_TotalStoreValue	= mem2dbl( fmt._TotalStoreValue,	sizeof(fmt._TotalStoreValue));
	_TotalCashMaintain  = mem2dbl( fmt._TotalCashMaintain,  sizeof(fmt._TotalStoreValue));

	for (int i=0;i<9;i++)	
		_TransNum[i] = mem2long(fmt._TransNum[i], sizeof(fmt._TransNum[i]));
	
	_ADAmount =			mem2dbl( fmt._ADAmount,			sizeof(fmt._ADAmount	));	
	_SCMgnAmount =		mem2dbl( fmt._SCMgnAmount,		sizeof(fmt._SCMgnAmount));	
	
	 _ADNum =			mem2long(fmt._ADNum,  6);
	 _SCMgnNum =		mem2long(fmt._SCMgnNum, 6);

	if (!_HasAccount)
	{
		_DutyStart = COleDateTime::GetCurrentTime();
		_HasAccount = true;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void CSetting::CReceipt::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		Title1[30];
		char		Title2[30];
		char		Title3[30];
		char		Ending1[30];
		char		Ending2[30];
		char		TaxPercentageRate[4];
		char		TaxName[10];
		char		TaxRegNo[20];
		char		LeftBlackSpaces[2];
		char		LineSpaces[2];
		char		FeedLines[2];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	_Title1 =			mem2str( fmt.Title1,			sizeof(fmt.Title1) );
	_Title2 =			mem2str( fmt.Title2,			sizeof(fmt.Title2) );
	_Title3 =			mem2str( fmt.Title3,			sizeof(fmt.Title3) );
	_Ending1 =			mem2str( fmt.Ending1,			sizeof(fmt.Ending1) );
	_Ending2 =			mem2str( fmt.Ending2,			sizeof(fmt.Ending2) );
	_TaxPercentageRate = mem2dbl( fmt.TaxPercentageRate,	sizeof(fmt.TaxPercentageRate) );
	_TaxName =			mem2str( fmt.TaxName,			sizeof(fmt.TaxName) );
	_TaxRegNo =			mem2str( fmt.TaxRegNo,			sizeof(fmt.TaxRegNo) );
	_LeftBlackSpaces =	mem2short( fmt.LeftBlackSpaces, sizeof(fmt.LeftBlackSpaces) );
	_LineSpaces =		mem2short( fmt.LineSpaces,		sizeof(fmt.LineSpaces) );
	_FeedLines =		mem2short( fmt.FeedLines,		sizeof(fmt.FeedLines) );
}
/////////////////////////////////////////////////////////////////////////////////////
CSetting::CPeripheral::CPeripheral()
{	//默认值
	_OtpPort		=	1;
	_OtpThreadStep	=	100;
	_OtpBaudRate	=	115200;
	_KdePort		=	2;
	_KdeThreadStep	=	100;
	_KdeBaudRate	=	115200;
	_LcdPort		=	3;
	_LcdThreadStep	=	100;
	_LcdBaudRate	=	9600;
	_PrinterPort	=	4;
	_PrinterThreadStep	=	100;
	_PrinterBaudRate	=	115200;
}
void CSetting::CPeripheral::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char	_KdePort[2];
		char	_KdeThreadStep[4];
		char	_KdeBaudRate[8];
		char	_LcdPort[2];
		char	_LcdThreadStep[4];
		char	_LcdBaudRate[8];
		char	_OtpPort[2];
		char	_OtpThreadStep[4];
		char	_OtpBaudRate[8];
		char	_PrinterPort[2];
		char	_PrinterThreadStep[4];
		char	_PrinterBaudRate[8];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	_KdePort			= mem2short( fmt._KdePort,			sizeof(fmt._KdePort) );
	_KdeThreadStep		= mem2short( fmt._KdeThreadStep,	sizeof(fmt._KdeThreadStep) );
	_KdeBaudRate		= mem2long(  fmt._KdeBaudRate,		sizeof(fmt._KdeBaudRate) );
	_LcdPort			= mem2short( fmt._LcdPort,			sizeof(fmt._LcdPort) );
	_LcdThreadStep		= mem2short( fmt._LcdThreadStep,	sizeof(fmt._LcdThreadStep) );
	_LcdBaudRate		= mem2long(  fmt._LcdBaudRate,		sizeof(fmt._LcdBaudRate) );
	_OtpPort			= mem2short( fmt._OtpPort,			sizeof(fmt._OtpPort) );
	_OtpThreadStep		= mem2short( fmt._OtpThreadStep,	sizeof(fmt._OtpThreadStep) );
	_OtpBaudRate		= mem2long(  fmt._OtpBaudRate,		sizeof(fmt._OtpBaudRate) );
	_PrinterPort		= mem2short( fmt._PrinterPort,		sizeof(fmt._PrinterPort) );
	_PrinterThreadStep	= mem2short( fmt._PrinterThreadStep,sizeof(fmt._PrinterThreadStep) );
	_PrinterBaudRate	= mem2long(  fmt._PrinterBaudRate,	sizeof(fmt._PrinterBaudRate) );
}

CString CSetting::CPeripheral::StrSetting()
{
	struct String_Format
	{
		char	_KdePort[2];
		char	_KdeThreadStep[4];
		char	_KdeBaudRate[8];
		char	_LcdPort[2];
		char	_LcdThreadStep[4];
		char	_LcdBaudRate[8];
		char	_OtpPort[2];
		char	_OtpThreadStep[4];
		char	_OtpBaudRate[8];
		char	_PrinterPort[2];
		char	_PrinterThreadStep[4];
		char	_PrinterBaudRate[8];
	} fmt;
	
	short2mem( _KdePort,		fmt._KdePort,		sizeof(fmt._KdePort) );
	short2mem( _KdeThreadStep,	fmt._KdeThreadStep,	sizeof(fmt._KdeThreadStep) );
	long2mem(  _KdeBaudRate,	fmt._KdeBaudRate,	sizeof(fmt._KdeBaudRate) );
	short2mem( _OtpPort,		fmt._OtpPort,		sizeof(fmt._OtpPort) );
	short2mem( _OtpThreadStep,	fmt._OtpThreadStep,	sizeof(fmt._OtpThreadStep) );
	long2mem(  _OtpBaudRate,	fmt._OtpBaudRate,	sizeof(fmt._OtpBaudRate) );
	short2mem( _LcdPort,		fmt._LcdPort,		sizeof(fmt._LcdPort) );
	short2mem( _LcdThreadStep,	fmt._LcdThreadStep,	sizeof(fmt._LcdThreadStep) );
	long2mem(  _LcdBaudRate,	fmt._LcdBaudRate,	sizeof(fmt._LcdBaudRate) );
	short2mem( _PrinterPort,		fmt._PrinterPort,		sizeof(fmt._PrinterPort) );
	short2mem( _PrinterThreadStep,	fmt._PrinterThreadStep,	sizeof(fmt._PrinterThreadStep) );
	long2mem(  _PrinterBaudRate,	fmt._PrinterBaudRate,	sizeof(fmt._PrinterBaudRate) );

	
	char strFmt[sizeof(fmt)+2];
	memcpy(strFmt, &fmt, sizeof(fmt));
	strFmt[sizeof(fmt)]=0x03;	//停止位
	strFmt[sizeof(fmt)+1]=0x00;	//串尾

	return (CString)strFmt;
}

void CSetting::CPeripheral::GetKdeParameter(short &Port, short &ThreadStep, long &BaudRate)
{
	Port = _KdePort;
	ThreadStep = _KdeThreadStep;
	BaudRate = _KdeBaudRate;
}
void CSetting::CPeripheral::GetLcdParameter(short &Port, short &ThreadStep, long &BaudRate)
{
	Port = _LcdPort;
	ThreadStep = _LcdThreadStep;
	BaudRate = _LcdBaudRate;
}
void CSetting::CPeripheral::GetOtpParameter(short &Port, short &ThreadStep, long &BaudRate)
{
	Port = _OtpPort;
	ThreadStep = _OtpThreadStep;
	BaudRate = _OtpBaudRate;
}
void CSetting::CPeripheral::GetPrinterParameter(short &Port, short &ThreadStep, long &BaudRate)
{
	Port = _PrinterPort;
	ThreadStep = _PrinterThreadStep;
	BaudRate = _PrinterBaudRate;
}
void CSetting::CPeripheral::SetKdeParameter(const short Port, const short ThreadStep, const long BaudRate)
{
	_KdePort = Port;
	_KdeThreadStep = ThreadStep;
	_KdeBaudRate = BaudRate;
	Store(StrSetting());
}
void CSetting::CPeripheral::SetLcdParameter(const short Port, const short ThreadStep, const long BaudRate)
{
	_LcdPort = Port;
	_LcdThreadStep = ThreadStep;
	_LcdBaudRate = BaudRate;
	Store(StrSetting());
}
void CSetting::CPeripheral::SetOtpParameter(const short Port, const short ThreadStep, const long BaudRate)
{
	_OtpPort = Port;
	_OtpThreadStep = ThreadStep;
	_OtpBaudRate = BaudRate;
	Store(StrSetting());
}
void CSetting::CPeripheral::SetPrinterParameter(const short Port, const short ThreadStep, const long BaudRate)
{
	_PrinterPort = Port;
	_PrinterThreadStep = ThreadStep;
	_PrinterBaudRate = BaudRate;
	Store(StrSetting());
}
/////////////////////////////////////////////////////////////////////////////
CSetting::CCommunicate::CCommunicate()
{	//默认值
	_StationID = "99";
	_SendSocketPort = 6501;
	_RecvSocketPort = 6500;
	_ManagementIP = "127.0.0.1";
	_ManagementID = "00";
	_SendThreadStep = 100;
}
void CSetting::CCommunicate::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char	_StationID[2];
		char	_SendSocketPort[4];
		char	_RecvSocketPort[4];
		char	_ManagementIP[15];
		char	_ManagementID[2];
		char	_SendThreadStep[4];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	memcpy(&fmt, rhs, sizeof(fmt));
	//类型转换
	_StationID		= mem2str(	 fmt._StationID,		sizeof(fmt._StationID) );
	_SendSocketPort	= mem2short( fmt._SendSocketPort,	sizeof(fmt._SendSocketPort) );
	_RecvSocketPort	= mem2short( fmt._RecvSocketPort,	sizeof(fmt._RecvSocketPort) );
	_ManagementIP	= mem2str(	 fmt._ManagementIP,		sizeof(fmt._ManagementIP) );
	_ManagementID	= mem2str(	 fmt._ManagementID,		sizeof(fmt._ManagementID) );
	_SendThreadStep	= mem2short( fmt._SendThreadStep,	sizeof(fmt._SendThreadStep) );
}

CString CSetting::CCommunicate::StrSetting()
{
	struct String_Format
	{
		char	_StationID[2];
		char	_SendSocketPort[4];
		char	_RecvSocketPort[4];
		char	_ManagementIP[15];
		char	_ManagementID[2];
		char	_SendThreadStep[4];
	} fmt;
	str2mem(	_StationID,			fmt._StationID,			sizeof(fmt._StationID) );
	short2mem(	_SendSocketPort,	fmt._SendSocketPort,	sizeof(fmt._SendSocketPort) );
	short2mem(	_RecvSocketPort,	fmt._RecvSocketPort,	sizeof(fmt._RecvSocketPort) );
	str2mem(	_ManagementIP,		fmt._ManagementIP,		sizeof(fmt._ManagementIP) );
	str2mem(	_ManagementID,		fmt._ManagementID,		sizeof(fmt._ManagementID) );
	short2mem(	_SendThreadStep,	fmt._SendThreadStep,	sizeof(fmt._SendThreadStep) );
	
	char strFmt[sizeof(fmt)+2];
	memcpy(strFmt, &fmt, sizeof(fmt));
	strFmt[sizeof(fmt)]=0x03;	//停止位
	strFmt[sizeof(fmt)+1]=0x00;	//串尾

	return (CString)strFmt;
}
void CSetting::CCommunicate::SetCommunicate( const short StationID, const short SendThreadStep,  
				const short SendSocketPort, const short RecvSocketPort, 
				const CString ManagementIP, const short ManagementID )
{
	CString s;
	s.Format("%02d", StationID);
	_StationID		= s;
	_SendSocketPort	= SendSocketPort;
	_RecvSocketPort	= RecvSocketPort;
	_ManagementIP	= ManagementIP;
	s.Format("%02d", ManagementID);
	_ManagementID	= s;
	_SendThreadStep	= SendThreadStep;
	Store(StrSetting());
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CDateRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		Code[6];
		char		GroupID[2];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	short Id = 0;
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		if ( 'W' == fmt.Code[0] )
		{
			data._date.SetStatus(COleDateTime::invalid);
			data._DayOfWeek = mem2short(fmt.Code[1]) + 1;
		}
		else
		{
			data._date = mem2date(fmt.Code);
			data._DayOfWeek = 0;	//invalid Day of week;
		}
		data._GroupRulesId = mem2short(fmt.GroupID, sizeof(fmt.GroupID));

		m_Map.insert(value_type(Id, data));
		Id++;
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CDateRule::GetGroupRulesId(COleDateTime BegTime, short &GroupRulesId)
{
	for (m_Iter = m_Map.begin(); m_Iter!=m_Map.end(); ++m_Iter)
	{
		if (COleDateTime::invalid == m_Iter->second._date.GetStatus())
		{
			if ( BegTime.GetDayOfWeek() == m_Iter->second._DayOfWeek )
				break;
		}
		else
		{
			if ((BegTime.GetYear() == m_Iter->second._date.GetYear()) ||
				(BegTime.GetMonth() == m_Iter->second._date.GetMonth()) ||
				(BegTime.GetDay() == m_Iter->second._date.GetDay()) )
				break;
		}
	}
	if (m_Iter==m_Map.end())
	{
		return false;
	}
	else
	{
		GroupRulesId = m_Iter->second._GroupRulesId;
		return true;
	}
}

/////////////////////////////////////////////////////////////////////////////
void CSetting::CGroupRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[2];
		char		VehicleID0[2];
		char		VehicleID1[2];
		char		VehicleID2[2];
		char		VehicleID3[2];
	} fmt;
	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._CRsIdOfGroupType0 = mem2short( fmt.VehicleID0, sizeof(fmt.VehicleID0) );
		data._CRsIdOfGroupType1 = mem2short( fmt.VehicleID1, sizeof(fmt.VehicleID1) );
		data._CRsIdOfGroupType2 = mem2short( fmt.VehicleID2, sizeof(fmt.VehicleID2) );
		data._CRsIdOfGroupType3 = mem2short( fmt.VehicleID3, sizeof(fmt.VehicleID3) );

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}
bool CSetting::CGroupRule::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

short CSetting::CGroupRule::CarRulesIdOfGroupType(short GroupId, short GroupType)
{
	ASSERT( (0 <= GroupType) && (3 >= GroupType) ); //???
	ASSERT( Valid(GroupId) );
	if		(0 == GroupType)
		return m_Map[GroupId]._CRsIdOfGroupType0;
	else if (1 == GroupType)
		return m_Map[GroupId]._CRsIdOfGroupType1;
	else if (2 == GroupType)
		return m_Map[GroupId]._CRsIdOfGroupType2;
	else//  (3 == GroupType)
		return m_Map[GroupId]._CRsIdOfGroupType3;
}

bool CSetting::CGroupRule::GetCarRulesId(short GroupRulesId, short GroupTypeId, short &CarRulesId)
{
	if (!Valid(GroupRulesId))
		return false;
	CarRulesId = CarRulesIdOfGroupType(GroupRulesId, GroupTypeId);
	return true;
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CCarRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[2];
		char		TimezoneID0[2];
		char		TimezoneID1[2];
		char		TimezoneID2[2];
		char		TimezoneID3[2];
	} fmt;

	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._TZRsIdOfCarType0 = mem2short( fmt.TimezoneID0, sizeof(fmt.TimezoneID0) );
		data._TZRsIdOfCarType1 = mem2short( fmt.TimezoneID1, sizeof(fmt.TimezoneID1) );
		data._TZRsIdOfCarType2 = mem2short( fmt.TimezoneID2, sizeof(fmt.TimezoneID2) );
		data._TZRsIdOfCarType3 = mem2short( fmt.TimezoneID3, sizeof(fmt.TimezoneID3) );

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CCarRule::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

short CSetting::CCarRule::TimeZoneRulesIDOfCarType(short CarRulesId, short CarType)
{
	ASSERT( (0 <= CarType) && (3 >= CarType) );
	ASSERT( Valid(CarRulesId) );
	if		(0 == CarType)
		return m_Map[CarRulesId]._TZRsIdOfCarType0;
	else if (1 == CarType)
		return 1; //HA- test
//		return m_Map[CarRulesId]._TZRsIdOfCarType1;
	else if (2 == CarType)
		return 2; //HA- test
	//	return m_Map[CarRulesId]._TZRsIdOfCarType2;
	else//  (3 == CarType)
		return m_Map[CarRulesId]._TZRsIdOfCarType3;
}

bool CSetting::CCarRule::GetTimeZoneRulesId(short CarRulesId, short CarTypeId, short &TimeZoneRulesId)
{
	if (!Valid(CarRulesId))
		return false;
	TimeZoneRulesId = TimeZoneRulesIDOfCarType(CarRulesId, CarTypeId);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
void CSetting::CTimeZoneRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[2];
		/*	data:
		 *	BegTime EndTime UnitRulesId BegTime EndTime UnitRulesId ...
		 *     4       4         2         4       4         2      
		 */
		char		BegTime1[4];
		char		EndTime1[4];
		char		UnitRulesId1[2];
		char		BegTime2[4];
		char		EndTime2[4];
		char		UnitRulesId2[2];
		char		BegTime3[4];
		char		EndTime3[4];
		char		UnitRulesId3[2];
		char		BegTime4[4];
		char		EndTime4[4];
		char		UnitRulesId4[2];
	} fmt;

	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._BegTime1		= mem2short( fmt.BegTime1, 2) * 60 + mem2short( fmt.BegTime1+2, 2);
		data._EndTime1		= mem2short( fmt.EndTime1, 2) * 60 + mem2short( fmt.EndTime1+2, 2);
		data._UnitRulesId1	= mem2short( fmt.UnitRulesId1,	sizeof(fmt.UnitRulesId1) );
		data._BegTime2		= mem2short( fmt.BegTime2, 2) * 60 + mem2short( fmt.BegTime2+2, 2);
		data._EndTime2		= mem2short( fmt.EndTime2, 2) * 60 + mem2short( fmt.EndTime2+2, 2);
		data._UnitRulesId2	= mem2short( fmt.UnitRulesId2,	sizeof(fmt.UnitRulesId2) );
		data._BegTime3		= mem2short( fmt.BegTime3, 2) * 60 + mem2short( fmt.BegTime3+2, 2);
		data._EndTime3		= mem2short( fmt.EndTime3, 2) * 60 + mem2short( fmt.EndTime3+2, 2);
		data._UnitRulesId3	= mem2short( fmt.UnitRulesId3,	sizeof(fmt.UnitRulesId3) );
		data._BegTime4		= mem2short( fmt.BegTime4, 2) * 60 + mem2short( fmt.BegTime4+2, 2);
		data._EndTime4		= mem2short( fmt.EndTime4, 2) * 60 + mem2short( fmt.EndTime4+2, 2);
		data._UnitRulesId4	= mem2short( fmt.UnitRulesId4,	sizeof(fmt.UnitRulesId4) );

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

bool CSetting::CTimeZoneRule::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}

bool CSetting::CTimeZoneRule::GetUnitRulesId(const short TimeZoneRulesId, const COleDateTime BegTime, 
											 short &UnitRulesId, COleDateTime &TimeZoneTerminal)
{
	ASSERT( Valid(TimeZoneRulesId) );
	COleDateTimeSpan ts;
	short ID = TimeZoneRulesId;
	short BegMins = BegTime.GetHour() * 60 + BegTime.GetMinute();
	TimeZoneTerminal.SetDate(BegTime.GetYear(), BegTime.GetMonth(), BegTime.GetDay());

	if		( (m_Map[ID]._BegTime1 <= BegMins) && (m_Map[ID]._EndTime1 > BegMins) )
	{
		UnitRulesId = m_Map[ID]._UnitRulesId1;
		ts.SetDateTimeSpan(0, 0, m_Map[ID]._EndTime1, 0);
		//UCH 2 extend calculate function
		if(m_Map[ID]._EndTime1>=24*60 && m_Map[ID]._BegTime1 == 0)
			ts.SetDateTimeSpan(0, 0, 6*30*24*60, 0);
	}
	else if ( (m_Map[ID]._BegTime2 <= BegMins) && (m_Map[ID]._EndTime2 > BegMins) )
	{
		UnitRulesId = m_Map[ID]._UnitRulesId2;
		ts.SetDateTimeSpan(0, 0, m_Map[ID]._EndTime2, 0);
	}
	else if ( (m_Map[ID]._BegTime3 <= BegMins) && (m_Map[ID]._EndTime3 > BegMins) )
	{
		UnitRulesId = m_Map[ID]._UnitRulesId3;
		ts.SetDateTimeSpan(0, 0, m_Map[ID]._EndTime3, 0);
	}
	else if ( (m_Map[ID]._BegTime4 <= BegMins) && (m_Map[ID]._EndTime4 > BegMins) )
	{
		UnitRulesId = m_Map[ID]._UnitRulesId4;
		ts.SetDateTimeSpan(0, 0, m_Map[ID]._EndTime4, 0);
	}
	else
	{	//没有合适的时间段包含BegTime.
		return false;
	}

	TimeZoneTerminal += ts;
	return true;
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CUnitRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[2];
		union
		{
			char		Data[80];
			struct
			{
				char		Charge1[6];
				char		Unit1[4];
				char		Charge2[6];
				char		Unit2[4];
				char		Charge3[6];
				char		Unit3[4];
				char		Charge4[6];
				char		Unit4[4];
				char		Charge5[6];
				char		Unit5[4];
				char		Charge6[6];
				char		Unit6[4];
				char		Charge7[6];
				char		Unit7[4];
				char		Charge8[6];
				char		Unit8[4];
			}minutely;
		};
	} fmt;

	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		for (int i = 0; i < 8; i++)
		{
			char * curPos = fmt.Data + i*10;
			data._Special[i] = sp_None;
			if		('+' == *curPos)
			{
				data._Charge[i]  = mem2dbl(curPos + 1, 5);
				data._Special[i] = sp_Add;			//单价增加
			}
			else if ('-' == *curPos)
			{
				data._Charge[i] = mem2dbl(curPos + 1, 5);
				data._Special[i] = sp_Subtract;		//单价递减
			}
			data._Charge[i] = mem2dbl(curPos, 6);
			curPos += 6;
			data._Unit[i]	= mem2short(curPos, 4) * 36;
			if		(0 == data._Unit[i])
				data._Special[i] = sp_Ditto;		//使用上一个规则
			else if (356400 <= data._Unit[i])	//356400(sec) = 99hour
				data._Unit[i] = 0;					//时间段无限大'Infinite'
		}
		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

CString CSetting::CUnitRule::_Data::Charge(short Id)
{
	CString s;
	if		(sp_None	 == _Special[Id])
		s = show(_Charge[Id]);
	else if	(sp_Add		 == _Special[Id])
		s = "(+) " + show(_Charge[Id]);
	else if	(sp_Subtract == _Special[Id])
		s = "(-) " + show(_Charge[Id]);
	else
		s = "----";	//needless 不需要的
	return s;
}

CString CSetting::CUnitRule::_Data::Unit(short Id)
{
	CString s;
	double hour;
	if		( sp_Ditto	== _Special[Id] )
		s = "Ditto";
	else if	( 0			== _Unit[Id] )
		s = "Infinite";
	else
	{
		hour = static_cast<double>(_Unit[Id]) / 3600;
		s.Format("%.2f", hour);
	}
	return s;
}
////////////////////////////////////////////////////////////////////////////
//获得收费规则
//	如果'Unit'的返回值为零, 表示无限长.
bool CSetting::CUnitRule::GetRule(const short UnitRulesId, short RequestTimes, long &Unit, double &Charge)
{
	if (!Valid(UnitRulesId)) 
		return false;
	short ID = UnitRulesId;
	ASSERT( (0 <= RequestTimes) && (100 > RequestTimes) );	//不能计算太多次
	if (100 < RequestTimes) return false;
	if (7 < RequestTimes) RequestTimes = 7;		//8次后均使用第八次规则

	if		(sp_None	== m_Map[ID]._Special[RequestTimes])	//普通
	{
		Unit = m_Map[ID]._Unit[RequestTimes];
		Charge = m_Map[ID]._Charge[RequestTimes];
	}
	else if (sp_Ditto	== m_Map[ID]._Special[RequestTimes])	//同上
	{
		if (0 == RequestTimes) return false;	//第零次没有同上
		return GetRule(UnitRulesId , RequestTimes - 1, Unit, Charge);
	}
	else if (sp_Add		== m_Map[ID]._Special[RequestTimes])	//加
	{
		Unit = m_Map[ID]._Unit[RequestTimes];
		Charge += m_Map[ID]._Charge[RequestTimes];
	}
	else // (sp_Subtract== m_Map[ID]._Special[RequestTimes])	//减
	{
		Unit = m_Map[ID]._Unit[RequestTimes];
		Charge -= m_Map[ID]._Charge[RequestTimes];
	}
	return true;
}

bool CSetting::CUnitRule::Valid(short ID)
{
	m_Iter = m_Map.find(ID);
	if (m_Iter != m_Map.end())
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////
void CSetting::CFixRule::Assign(const char * rhs)
{	//使用字符串形式的数据赋值
	struct String_Format
	{
		char		ID[2];
		char		InZoneStart[4];
		char		InZoneEnd[4];
		char		InDay[6];
		char		OutZoneStart[4];
		char		OutZoneEnd[4];
		char		OutDay[6];
		char		IODayDiff[3];
		char		DiscountRate[7];
	} fmt;

	ASSERT(strlen(rhs) >= sizeof(fmt));
	m_Map.clear();	//清除旧数据
	typedef map< USHORT, _Data >::value_type value_type;
	_Data data;

	int ipos = sizeof(fmt), ilen = strlen(rhs);
	while (ipos <= ilen)
	{
		memcpy(&fmt, rhs, sizeof(fmt));
		//类型转换
		data._InZoneStart	= mem2short( fmt.InZoneStart, 2) * 60 + mem2short( fmt.InZoneStart+2, 2);
		data._InZoneEnd		= mem2short( fmt.InZoneEnd, 2) * 60 + mem2short( fmt.InZoneEnd+2, 2);
		if ( 'W' == fmt.InDay[0] )
		{
			data._Indate.SetStatus(COleDateTime::invalid);
			data._InDayOfWeek = mem2short(fmt.InDay[1]) +1;
		}
		else
		{
			data._Indate = mem2date(fmt.InDay);
			data._InDayOfWeek = 0;	//invalid Day of week;
		}
		data._OutZoneStart	= mem2short( fmt.OutZoneStart, 2) * 60 + mem2short( fmt.OutZoneStart+2, 2);
		data._OutZoneEnd	= mem2short( fmt.OutZoneEnd, 2) * 60 + mem2short( fmt.OutZoneEnd+2, 2);
		if ( 'W' == fmt.OutDay[0] )
		{
			data._Outdate.SetStatus(COleDateTime::invalid);
			data._OutDayOfWeek = mem2short(fmt.OutDay[1]) +1;
		}
		else
		{
			data._Outdate = mem2date(fmt.OutDay);
			data._OutDayOfWeek = 0;	//invalid Day of week;
		}
		data._IODayDiff= mem2short( fmt.IODayDiff, sizeof(fmt.IODayDiff) );
		data._Discount = fmt.DiscountRate;

		m_Map.insert(value_type(mem2short( fmt.ID, sizeof(fmt.ID) ), data));
		rhs += sizeof(fmt);			//下一数据块指针.
		ipos += sizeof(fmt);		//已处理长度.
	}
}

CDiscount CSetting::CFixRule::GetFixDiscount(const COleDateTime &BegTime, const COleDateTime &EndTime)
{
	CDiscount discount;
	for (m_Iter = m_Map.begin(); m_Iter!=m_Map.end(); ++m_Iter)
	{
		//入场日期, 时间
		if (COleDateTime::invalid == m_Iter->second._Indate.GetStatus())
		{
			if ( BegTime.GetDayOfWeek() != m_Iter->second._InDayOfWeek )
				continue;
		}
		else
		{
			if ((BegTime.GetYear() != m_Iter->second._Indate.GetYear()) ||
				(BegTime.GetMonth() != m_Iter->second._Indate.GetMonth()) ||
				(BegTime.GetDay() != m_Iter->second._Indate.GetDay()) )
				continue;
		}

		if ( m_Iter->second._InZoneStart > BegTime.GetHour() * 60 + BegTime.GetMinute() )
			continue;
		if ( m_Iter->second._InZoneEnd < BegTime.GetHour() * 60 + BegTime.GetMinute() )
			continue;

		//出场日期, 时间
		if (COleDateTime::invalid == m_Iter->second._Outdate.GetStatus())
		{
			if ( EndTime.GetDayOfWeek() != m_Iter->second._OutDayOfWeek )
				continue;
		}
		else
		{
			if ((EndTime.GetYear() != m_Iter->second._Outdate.GetYear()) ||
				(EndTime.GetMonth() != m_Iter->second._Outdate.GetMonth()) ||
				(EndTime.GetDay() != m_Iter->second._Outdate.GetDay()) )
				continue;
		}

		if ( m_Iter->second._OutZoneStart > EndTime.GetHour() * 60 + EndTime.GetMinute() )
			continue;
		if ( m_Iter->second._OutZoneEnd < EndTime.GetHour() * 60 + EndTime.GetMinute() )
			continue;
		//停车天数
		if ( m_Iter->second._IODayDiff == (EndTime - BegTime).GetDays())
			break;		
	}
	if (m_Iter!=m_Map.end())
		discount = m_Iter->second._Discount;
	else
		discount.Clear();
	return discount;
}
/////////////////////////////////////////////////////////////////////////////
//八达通
CString CSetting::COTPRwlSetting::PathExchange()
{
	CCmdOtp::RWL_SETTINGS RWL_Settings;
	CCmdOtp::Instance()->OTP_Folders_Read(RWL_Settings);
	return RWL_Settings._Exchange;
}
CString CSetting::COTPRwlSetting::PathLib()
{
	CCmdOtp::RWL_SETTINGS RWL_Settings;
	CCmdOtp::Instance()->OTP_Folders_Read(RWL_Settings);
	return RWL_Settings._Blacklist;
}
bool CSetting::COTPRwlSetting::PathMeta(CString &MetaFileName)
{
		CString FileType;
/*	ASSERT(!(14 > MetaFileName.GetLength()));
	if (14 > MetaFileName.GetLength()) return false;

	const char TempFileFlag = '~';

	if (TempFileFlag == MetaFileName.Left(1))
		FileType = MetaFileName.Mid(1,4);
	else*/
		FileType = MetaFileName.Left(MetaFileName.Find('.'));

	CCmdOtp::RWL_SETTINGS RWL_Settings;
	CCmdOtp::Instance()->OTP_Folders_Read(RWL_Settings);

	if  (FileType.CompareNoCase("OTP") == 0)
		MetaFileName = RWL_Settings._Blacklist + "\\" + MetaFileName;
	if	(FileType.CompareNoCase("BLACKLIST") == 0)
		MetaFileName = RWL_Settings._Blacklist +"\\"+ MetaFileName;
	else if (FileType.Left(3).CompareNoCase("BLK") == 0)
		MetaFileName = RWL_Settings._Blacklist +"\\"+ MetaFileName;
	else if (FileType.CompareNoCase("IBKL") == 0)
		MetaFileName = RWL_Settings._Blacklist +"\\"+ MetaFileName;
	else if (FileType.CompareNoCase("EODF") == 0)
		MetaFileName = RWL_Settings._EOD +"\\"+ MetaFileName;
	else if (FileType.CompareNoCase("CCHS") == 0)
		MetaFileName = RWL_Settings._CCHS +"\\"+ MetaFileName;
	else if (FileType.CompareNoCase("FIRM") == 0)
		MetaFileName = RWL_Settings._Firmware +"\\"+ MetaFileName;
	else 
		return false;	//invalid filename

	return true;
}

void CSetting::CAccount::AfterShiftCloseAccount(double ShiftCashMaintain)
{
	_CurrentAmount = _CurrentCash =	_CurrentOctopus = _CurrentStoreValue = 0;
	_PayNum = 0;
	_DutyStart = COleDateTime::GetCurrentTime();
	_TotalCashMaintain = _TotalCashMaintain + ShiftCashMaintain;
	_CurrentCashMaintain = 0;
	//_ReceiptNoNumPart = 1;
	_HasAccount = false;
	Store(StrSetting());
}

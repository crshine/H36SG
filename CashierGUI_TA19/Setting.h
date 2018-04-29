// Setting.h: interface for the CSetting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTING_H__94047573_E3FB_4F3D_BBAF_B1A02750CC31__INCLUDED_)
#define AFX_SETTING_H__94047573_E3FB_4F3D_BBAF_B1A02750CC31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
class CSetting
{
public:
	static CSetting* Instance();
	virtual ~CSetting();

protected:
    CSetting();
	CSetting(const CSetting&);
	CSetting& operator=(const CSetting&);
    static CSetting* _instance;

public:
	class CBase
	{
	public:
		void StoreAndAssign(const char * strSetting, const short StrLen = 0);
		virtual void Assign(const char * strSetting/*, const short StrLen*/){};
		virtual ~CBase(){};
	protected:
		void Store(const char * strSetting);//保存设置
	private:
		virtual CString ClassID() const = 0;
	};

	class CBaseSystemSetting : public CBase				//基本系统设置
	{
	public: //func
		CString		SystemName(){return _SystemName;}
		short		SystemID(){return _SystemID;}
		CHourAndMin AutoFunctionTime(){return _AutoFunctionTime;}
		CString		CardCateAntiPassback(){return _CardCateAntiPassback;}
		short		OperatorLanguage(){return _OperatorLanguage;}
		short		CustomerLanguage(){return _CustomerLanguage;}
		short		EntryOrExit(){return _EntryOrExit;}
		short		LowestYN(){return _LowestYN;}			
		short		CashCardModeID(){return _CashCardModeID;}		// cashcard   -> Cash payment
		short		CashBackModeID(){return _CashBackModeID;}		// cashback   -> Octopus 
		short		StoreValueModeID(){return _StoreValueModeID;}	// StoreValue -> Store Value
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\BaseSystemSetting.dat";}
	private: //func
		

	private: //member
		CString		_SystemName;
		short		_SystemID;
		CHourAndMin _AutoFunctionTime;
		CString		_CardCateAntiPassback;
		short		_OperatorLanguage;
		short		_CustomerLanguage;
		short		_EntryOrExit;
		short		_LowestYN;
		short		_CashCardModeID;
		short		_CashBackModeID;
		short		_StoreValueModeID;
	} m_BaseSystemSetting;

	class CCardType : public CBase						//收费卡种类设定(4种)(允许扩展为0~9,十种)
	{
		struct _Data
		{
			bool		IsTimesWorkMode();		//是否使用有效次数模式
			bool		IsPeriodWorkMode();		//是否使用有效区间模式
			double		TimesFee(const short Times);	//计算相应次数所需要的费用
			double		PeriodFee(const COleDateTime Beg,const COleDateTime End);	//计算相应区间所需要的费用
			CString     showPrice();
			CString		_Name;
			short		_WorkMode;
			double		_JoiningFee;
			double		_CardFee;
			double		_UnitFee;
			CString		_Unit;
			short		_WarningLevel;
			CDiscount	_Discount;
			bool		_StoreValue;
		};
	public: //func
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString		Name(short ID){ASSERT(Valid(ID));return m_Map[ID]._Name;}
		short		WorkMode(short ID){ASSERT(Valid(ID));return m_Map[ID]._WorkMode;}
		double		JoiningFee(short ID){ASSERT(Valid(ID));return m_Map[ID]._JoiningFee;}
		double		CardFee(short ID){ASSERT(Valid(ID));return m_Map[ID]._CardFee;}
		double		UnitFee(short ID){ASSERT(Valid(ID));return m_Map[ID]._UnitFee;}
		CString		Unit(short ID){ASSERT(Valid(ID));return m_Map[ID]._Unit;}
		short		WarningLevel(short ID){ASSERT(Valid(ID));return m_Map[ID]._WarningLevel;}
		CDiscount	Discount(short ID){ASSERT(Valid(ID));return m_Map[ID]._Discount;}
		bool		StoreValue(short ID){ASSERT(Valid(ID));return m_Map[ID]._StoreValue;}
		bool		IsTimesWorkMode(short ID)		//是否使用有效次数模式
					{ASSERT(Valid(ID));return m_Map[ID].IsTimesWorkMode();}
		bool		IsPeriodWorkMode(short ID)		//是否使用有效区间模式
					{ASSERT(Valid(ID));return m_Map[ID].IsPeriodWorkMode();}
		CString		showWorkMode(short ID);
		CString		showPrice(short ID){ASSERT(Valid(ID));return m_Map[ID].showPrice();}
		double		TimesFee(short ID, const short Times)//计算相应次数所需要的费用
					{ASSERT(Valid(ID));return m_Map[ID].TimesFee(Times);}
		double		PeriodFee(short ID, const COleDateTime Beg,const COleDateTime End)//计算相应区间所需要的费用
					{ASSERT(Valid(ID));return m_Map[ID].PeriodFee(Beg, End);}

		CString ClassID() const{return "\\CardType.dat";}
	private: //func
	public: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_CardType;

	class CDiscountPlan : public CBase					//打折计划
	{
		struct _Data
		{
			CString		_DiscountName;
			CDiscount	_Discount;
		};
	public: //func
		bool		Valid(short ID);
		CDiscount	Discount(short ID){return m_Map[ID]._Discount;}
		CString		DiscountModeName(short ID) {return m_Map[ID]._DiscountName;}
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\DiscountPlan.dat";}
	private: //func

	public: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_DiscountPlan;

	class CGroupType : public CBase						//用户分组信息(4种)(允许扩展为0~9,十种)
	{
		struct _Data
		{
			short		_Lots;
			CString		_Description;
			short		_CtrlCategory;
			short		_CtrlLots;
			bool		_IgnoreFullSign;
		};
	public: //func
		CString		Name(short ID){ASSERT(Valid(ID));return m_Map[ID]._Description;}
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\GroupType.dat";}
	private: //func
		bool Valid(short ID);
		void decode(const char * strSetting);
		void fit();
	public: //member
		CGroupType();
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_GroupType;
	
	class CParkingFee : public CBase					//收费基本设置
	{
	public: //func
		COleDateTimeSpan EnterGrace(){return _EnterGrace;}
		COleDateTimeSpan PaidGrace(){return _PaidGrace;}
		COleDateTimeSpan TZoneGrace(){return _TZoneGrace;}
		double LostAmount(){return _LostAmount;}
		double CreditLimit(){return _CreditLimit;}
		double PerEntryAmt(){return _PerEntryAmt;}
		bool CutByTimeZone(){return _CutByTimeZone;}
		bool HandleLostTicket(){return _HandleLostTicket;}
		bool FixTimeRule(){return _FixTimeRule;}

		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\ParkingFee.dat";}
	private: //func
	private: //member
		COleDateTimeSpan _EnterGrace;
		COleDateTimeSpan _PaidGrace;
		COleDateTimeSpan _TZoneGrace;
		double _LostAmount;
		double _CreditLimit;
		double _PerEntryAmt;
		bool _CutByTimeZone;
		bool _HandleLostTicket;
		bool _FixTimeRule;
	} m_ParkingFee;

	class CPayModeDefinition : public CBase				//收款台收费模式定义
	{
		struct _Data
		{
			CString		_ModeName;
			bool		_NeedCashChanges;
		};
	public: //func
		CString		ModeName(short ID){return m_Map[ID]._ModeName;}
		bool		NeedCashChanges(short ID){return m_Map[ID]._NeedCashChanges;}
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\PayModeDefinition.dat";}
	private: //func
	public: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_PayModeDefinition;

	class CStationInformation : public CBase			//各个子站设置
	{
		struct _Data
		{
			short		_StationType;
			CString		_StationName;
			short		_GroupID;
			CString		_IPAddr;
			CString		_Brief;
		};
	public: //func
		void	Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool	Valid(short ID);
		short	GroupID(short ID){ASSERT(Valid(ID));return m_Map[ID]._GroupID;}    //???
		CString StationName(short ID){ASSERT(Valid(ID));return m_Map[ID]._StationName;}
		CString ClassID() const{return "\\StationInformation.dat";}
	private: //func

	public: //member
		bool IsEntryStation(short Type);
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_StationInformation;

	class CVehicleType : public CBase					//车辆种类设定(4种)
	{
		struct _Data
		{
			CString		_TypeName;
		};
	public: //func
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString		Name(short ID){ASSERT(Valid(ID));return m_Map[ID]._TypeName;}
		CString ClassID() const{return "\\VehicleType.dat";}
	private: //func
		void decode(const char * strSetting);
		void fit();		//用来检测及补全设定,设定保持合理.

	public: //member
		CVehicleType();
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	} m_VehicleType;



	class CAccount : public CBase						//有关部门帐目的一些统计结果
	{
	public: //func

		CAccount();
		CString		ReceiptNo();
		long		GetReceiptNo() {return _ReceiptNoNumPart;}
		void		LogPayAmount(double Amount, double Cash, double Octopus, double StoreValue, int TranType);
		void		GetCurrentAccount(double &Amount, double &Cash, double &Octopus, double &StoreValue, COleDateTime & DutyStart, long & PayNum, double &CashMaintain);
		//void		GetTotalAccount(double &Amount, double &Cash, double &Octopus, double &StoreValue);
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\Account.dat";}
		bool		GetHasAccount(){return _HasAccount;}
		void		Demolish();
		void CloseAcc();
		void GetTotalAccount(double &Amount, double &Cash, double &Octopus, double &StoreValue, long TransNum[], double &TotalCashMaintain);
		void GetOtherInfo(double &ADAmount, long &ADNum, double &SCAmount, long &SCNum);
		void AfterShiftCloseAccount(double ShiftCashMaintain);

	private: //func
		CString StrSetting();
	private: //member
		//从系统运行起的统计结果 // Calculation from system running
		double		_CurrentAmount;
		double		_CurrentCash;
		double		_CurrentOctopus;
		double		_CurrentStoreValue;
		double      _CurrentCashMaintain;
		//本次交接班内的情况     // Calculation from last shift
		double		_TotalAmount;
		double		_TotalCash;
		double		_TotalOctopus;
		double		_TotalStoreValue;
		double      _TotalCashMaintain;
		long		_ReceiptNoNumPart;		//发票号由两部分组成,StationId + 6位自增循环编号;
		COleDateTime _DutyStart;
		long		_PayNum;
		bool		_HasAccount;
		double		_ADAmount;
		long		_ADNum;
		double		_SCMgnAmount;
		long		_SCMgnNum;
		long		_TransNum[9];
	}m_Account;

	class CReceipt : public CBase				//票据格式设置
	{
	public: //func
		CString		Title1(){return _Title1;}
		CString		Title2(){return _Title2;}
		CString		Title3(){return _Title3;}
		CString		Ending1(){return _Ending1;}
		CString		Ending2(){return _Ending2;}
		double		TaxPercentageRate(){return _TaxPercentageRate;}
		CString		TaxName(){return _TaxName;}
		CString		TaxRegNo(){return _TaxRegNo;}
		short		LeftBlackSpaces(){return _LeftBlackSpaces;}
		short		LineSpaces(){return _LineSpaces;}
		short		FeedLines(){return _FeedLines;}
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\Receipt.dat";}

	private: //func
	private: //member
		CString		_Title1;
		CString		_Title2;
		CString		_Title3;
		CString		_Ending1;
		CString		_Ending2;
		double		_TaxPercentageRate;
		CString		_TaxName;
		CString		_TaxRegNo;
		short		_LeftBlackSpaces;
		short		_LineSpaces;
		short		_FeedLines;
	} m_Receipt;

	class CPeripheral : public CBase				//外设设置
	{
	public: //func
		CPeripheral();
		void GetKdeParameter(short &Port, short &ThreadStep, long &BaudRate);
		void GetLcdParameter(short &Port, short &ThreadStep, long &BaudRate);
		void GetOtpParameter(short &Port, short &ThreadStep, long &BaudRate);
		void GetPrinterParameter(short &Port, short &ThreadStep, long &BaudRate);
		void SetKdeParameter(const short Port, const short ThreadStep, const long BaudRate);
		void SetLcdParameter(const short Port, const short ThreadStep, const long BaudRate);
		void SetOtpParameter(const short Port, const short ThreadStep, const long BaudRate);
		void SetPrinterParameter(const short Port, const short ThreadStep, const long BaudRate);
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		//inline
		short	OtpPort()		{return _OtpPort;}
		short	OtpThreadStep()	{return _OtpThreadStep;}
		long	OtpBaudRate()	{return _OtpBaudRate;}
		short	KdePort()		{return _KdePort;}
		short	KdeThreadStep()	{return _KdeThreadStep;}
		long	KdeBaudRate()	{return _KdeBaudRate;}
		short	LcdPort()		{return _LcdPort;}
		short	LcdThreadStep()	{return _LcdThreadStep;}
		long	LcdBaudRate()	{return _LcdBaudRate;}
		CString ClassID() const{return "\\Peripheral.dat";}

	private: //func
		CString StrSetting();
	private: //member
		short	_KdePort;
		short	_KdeThreadStep;
		long	_KdeBaudRate;
		short	_LcdPort;
		short	_LcdThreadStep;
		long	_LcdBaudRate;
		short	_OtpPort;
		short	_OtpThreadStep;
		long	_OtpBaudRate;
		short	_PrinterPort;
		short	_PrinterThreadStep;
		long	_PrinterBaudRate;
	} m_Peripheral;

	class CCommunicate : public CBase				//与管理站的通讯设置
	{
	public: //func
		CCommunicate();
		void SetCommunicate( const short StationID, const short SendThreadStep,  
					 		 const short SendSocketPort, const short RecvSocketPort, 
					 		 const CString ManagementIP, const short ManagementID );
		CString		StationID(){return _StationID;}
		short		SendSocketPort(){return _SendSocketPort;}
		short		RecvSocketPort(){return _RecvSocketPort;}
		CString		ManagementIP(){return _ManagementIP;}
		CString		ManagementID(){return _ManagementID;}
		short		SendThreadStep(){return _SendThreadStep;}
		void Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		CString ClassID() const{return "\\Communicate.dat";}
	private: //func

		CString StrSetting();
	private: //member
		CString		_StationID;
		short		_SendSocketPort;
		short		_RecvSocketPort;
		CString		_ManagementIP;
		CString		_ManagementID;
		short		_SendThreadStep;
	} m_Communicate;

	class CPermission : public CBase			//各个功能的授权情况.
	{
		struct _Data
		{
			CString		_Caption;
			short		_StationType;
			bool		_ValidForGuest;
			bool		_ValidForOperator;
			bool		_ValidForSupervisor;
			bool		_ValidForManager;
			bool		_ValidForAdmin;
		};
	public: //func
		void	Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool	Valid(short ID);
//		short	GroupID(short ID){ASSERT(Valid(ID));return m_Map[ID]._GroupID;}
//		CString StationName(short ID){ASSERT(Valid(ID));return m_Map[ID]._StationName;}
		CString ClassID() const{return "\\Permission.dat";}
	private: //func
	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgSettingPermission;
	} m_Permission;

	class CDateRule : public CBase
	{
	friend class CDlgRateDay;
		struct _Data
		{
			COleDateTime	_date;
			short			_DayOfWeek;
			short			_GroupRulesId;
		};
	public: //func
		bool GetGroupRulesId(COleDateTime BegTime, short &GroupRulesId);
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\DateRule.dat";}
	private: //func
		void decode(const char * strSetting);

	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateDay;
	} m_DateRule;

	class CGroupRule : public CBase
	{
		struct _Data
		{
			short	_CRsIdOfGroupType0;		//	'CRsId' = Car Rules Id
			short	_CRsIdOfGroupType1;
			short	_CRsIdOfGroupType2;
			short	_CRsIdOfGroupType3;
		};
	public: //func
		bool GetCarRulesId(short GroupRulesId, short GroupTypeId, short &CarRulesId);
		short CarRulesIdOfGroupType(short GroupId, short GroupType);
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\GroupRule.dat";}
	private: //func
		void decode(const char * strSetting);
	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateGroup;
	} m_GroupRule;

	class CCarRule : public CBase
	{
		struct _Data
		{
			short	_TZRsIdOfCarType0;		//	'TZRsId' = Time Zone Rules Index
			short	_TZRsIdOfCarType1;
			short	_TZRsIdOfCarType2;
			short	_TZRsIdOfCarType3;
		};
	public: //func
		bool GetTimeZoneRulesId(short CarRulesId, short CarTypeId, short &TimeZoneRulesId);
		short TimeZoneRulesIDOfCarType(short CarRulesId, short CarType);
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\CarRule.dat";}
	private: //func
		void decode(const char * strSetting);
	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateCar;
	} m_CarRule;
	
	class CTimeZoneRule : public CBase
	{
		struct _Data
		{
			short	_BegTime1;		//记录了从当天早上起到本时间的分钟数
			short	_EndTime1;
			short	_UnitRulesId1;
			short	_BegTime2;
			short	_EndTime2;
			short	_UnitRulesId2;
			short	_BegTime3;
			short	_EndTime3;
			short	_UnitRulesId3;
			short	_BegTime4;
			short	_EndTime4;
			short	_UnitRulesId4;
		};
	public: //func
		bool GetUnitRulesId(const short TimeZoneRulesId, const COleDateTime BegTime, 
							short &UnitRulesId, COleDateTime &TimeZoneTerminal);
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\TimeZoneRule.dat";}
	private: //func
		void decode(const char * strSetting);
	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateTimezone;
	} m_TimeZoneRule;

	class CUnitRule : public CBase
	{
	public: //func
		bool GetRule( const short UnitRulesId, short RequestTimes, long &Unit, double &Charge );
		//特殊的规定
		enum special_Unit {sp_None, sp_Add, sp_Subtract, sp_Ditto};
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\UnitRule.dat";}
	private: //func
		void decode(const char * strSetting);
	private: //member
		struct _Data
		{
			long			_Unit[8];		//这个时间段包含秒数
			double			_Charge[8];
			special_Unit	_Special[8];
		public:
			CString Charge(short Id);
		private:
			CString Unit(short);
		friend class CDlgRateFee;
		};
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateFee;
	} m_UnitRule;

	class CFixRule : public CBase
	{
		struct _Data
		{
			short			_InZoneStart;//记录了从当天早上起到本时间的分钟数
			short			_InZoneEnd;
			COleDateTime	_Indate;
			short			_InDayOfWeek;
			short			_OutZoneStart;
			short			_OutZoneEnd;
			COleDateTime	_Outdate;
			short			_OutDayOfWeek;
			short			_IODayDiff;
			CDiscount		_Discount;
		};
	public: //func
		CDiscount	GetFixDiscount(const COleDateTime &BegTime, const COleDateTime &EndTime);
		void		Assign(const char * strSetting/*, const short StrLen*/);	//赋值
		bool		Valid(short ID);
		CString ClassID() const{return "\\FixRule.dat";}
	private: //func
		void decode(const char * strSetting);
	private: //member
		map< short , _Data >::iterator m_Iter;
		map< short , _Data > m_Map;
	friend class CDlgRateFix;
	} m_FixRule;

	void Load();
	BOOL LoadFile(CString FileName, CString & Item);
//	static const CString SettingFileName;

	class COTPRwlSetting
	{
	public:
		CString PathExchange();
		CString PathLib();
		bool	PathMeta(CString &MetaFileName);//根据名称返回相应的路径
	} m_OTPRwlSetting;
	
public:
	CFont& FontBig(){return _FontBig;}
	CFont& FontMid(){return _FontMid;}
	CFont& FontErrBig(){return _FontErrBig;}
	CFont& FontErrMid(){return _FontErrMid;}
	CBrush& BrushErrDlgBackGround(){return _BrushErrDlgBackGround;}
	CBrush&		AbnormityBrush(){return _AbnormityBrush;}//异常操作时的背景色
	COLORREF&	AbnormityColor(){return _AbnormityColor;}//异常操作时的文字颜色
private:
	CBrush		_BrushErrDlgBackGround;
	CBrush		_AbnormityBrush;	//异常操作时的背景色
	COLORREF	_AbnormityColor;	//异常操作时的文字颜色
	CFont		_FontBig;
	CFont		_FontMid;
	CFont		_FontErrBig;
	CFont		_FontErrMid;
};

#endif // !defined(AFX_SETTING_H__94047573_E3FB_4F3D_BBAF_B1A02750CC31__INCLUDED_)

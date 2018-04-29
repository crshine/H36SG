// CmdOtp.h: interface for the CCmdOtp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDOTP_H__3F34C630_79ED_4ED0_8ECB_2BBC85D21974__INCLUDED_)
#define AFX_CMDOTP_H__3F34C630_79ED_4ED0_8ECB_2BBC85D21974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "..\common\OTP\rwl_exp.h"
#include "..\common\OTP\rwl_TA18.h"
//#pragma comment(lib, "..\\common\\OTP\\rwl.lib")
//#include "..\rwl\rwl.h"
#pragma comment(lib, "..\\rwl_PC\\release\\rwl.lib")
#pragma message("Automatic link the rwl.lib")

class CCmdOtp  
{
public:
	#pragma pack (push, 1)
		typedef struct {
			unsigned int	_DevID; 	/* Device ID */
			unsigned int	_OperID;	/* Operator ID */
			unsigned int	_DevTime;	/* Device Time */
			unsigned int	_CompID;	/* Company ID */
			unsigned int	_KeyVer;	/* Key Version */
			unsigned int	_EODVer;	/* EOD Version */
			unsigned int	_BLVer;	    /* Blacklist Version */
			unsigned int	_FIRMVer;	/* Firmware Version */
			unsigned int	_CCHSVer;	/* CCHS MSG ID */
			unsigned int	_CSSer;		/* CS Serial #, Loc ID */
			unsigned char	_Reserved[8];
		public:
		} VER_TIME;
	#pragma pack (pop)
	enum DeviceStatus{DS_Stop = 1, DS_Normal = 2, DS_Busy = 3, DS_Error = 4};
	enum HouseKeepingOpportunity{AfterInitComm = 1,AfterXFile = 2,AfterBoth = 3};
	enum Color{None = 0, Green = 2, Yellow = 4, Red = 8, GreenRed = Green+Red};
	enum Sound{NoSound = 0, Successful = 1, Fail = 2};
	const double Display_Blank/* = -3000.0*/;	//for Function OTP_Display
	const double Diaplay_Dashes/* = -3000.1*/; //for Function OTP_Display

	typedef struct {
		CString		_CardNo;
		double		_Remain;
		CString		_AddValueDetail;
		CString		_LastAddValueDevice;
		short		_Class;	//1 : Adult 2 : Student 3 : Child 4 : Elder +8 for Personalized card. 
							//For example, a personalized student card is 8+2=10.
		short		_Language;	//0 : Chinese 1 : English
		double		_AvailableAmount;
//		CString     _Remark;
	}PATRON;

	typedef struct {
		CString			_SP_ID;
		double			_TransactionAmt;
		COleDateTime	_TransactionTime;
		CString			_MachineID;
		CString			_ServiceInfo;
	}LOG;
	typedef struct {
		CString		_CardNo;
		double		_Remain;
		CString		_AddValueDetail;
		CString		_LastAddValueDevice;
		short		_Class;	//1 : Adult 2 : Student 3 : Child 4 : Elder +8 for Personalized card. 
							//For example, a personalized student card is 8+2=10.
		short		_Language;	//0 : Chinese 1 : English
		double		_AvailableAmount;
		CString		_ManufactureID;
		LOG			_Log[10];
	}PATRON_LOG;
	typedef struct {
		CString _AR1;
		CString _AR2;
		CString _Exchange;
		CString _Blacklist;
		CString _Firmware;
		CString _EOD;
		CString _CCHS;
	}RWL_SETTINGS;

#pragma pack (push, 1)//TA19- for GetSysInfo
	typedef struct {
		unsigned int ActionListVer; // Action List Version
		unsigned int BlkUpToDate; // 0 – blacklist outdated
							    	// 1 – blacklist ok
		unsigned char ucRes[40]; // Reserved bytes
	}SYSINFO;
#pragma pack (pop)
	typedef void (CALLBACK* POLL_DETECT_CALLBACK)(const PATRON &CardInfo);

public:
	void OTP_StopRead(bool flag);
	bool Start();
	void Stop();

	static CCmdOtp* Instance(int SpID = 1);
	virtual ~CCmdOtp();
	static int GetLastError();
	static CString CCmdOtp::Translate(int Language=0, int ErrCode=-1); 
	static void Async_Poll(POLL_DETECT_CALLBACK PollDetectCallBack);	//	异步读卡
	static void Kill_Async_Poll();
	void WaitForOtpRemove(bool bNeedInitCheck=false);
	void WaitOtpRemove();
	//bool OTP_AddValue(const CString CardNo, const double Amount);//充值
	bool OTP_Deduct(const CString CardNo, const double Amount);//扣费
	bool OTP_Poll(); //TA11A 2009
	bool OTP_Poll(PATRON_LOG &Patron, short TimeOut = 1/* 0.1毫秒*/);
	bool OTP_Poll(PATRON &Patron, short TimeOut = 1/* 0.1毫秒*/);
	bool OTP_PollEx(PATRON &Patron, short TimeOut = 1/* 0.1毫秒*/); //TA19- 
	bool OTP_Poll_2(PATRON_LOG &Patron_Log, short TimeOut =1);
	bool OTP_TimeVer(VER_TIME &VerTime);//设置时间,返回版本号.
	long OTP_GetDevID();
	void OTP_Folders_Read(RWL_SETTINGS &RWL_Settings);
	void OTP_Folders_Write(RWL_SETTINGS &RWL_Settings);
	void OTP_Reset();//软件重置
	void SetPollDetectCallBack(POLL_DETECT_CALLBACK func = NULL);
	bool OTP_XFile(CString &XFileName);	//生成交换文件,并获取交换文件名称
	void ForceMarkTime();
	double GetMarkTime();
	bool OTP_HouseKeeping();
	bool OTP_AddValue(double Amount, double & Remain, CString CardNo="");
	bool OTP_Deduct(const double Amount, double &Remain, long ReceiptNo, int TransType, CString CardNo="");//扣费,并获取余额
	bool OTP_WriteID(const short ID=0);	//本地编号
	void OTP_DisplayBeforeDeduct(const double Amount);
	void OTP_DisplayEnquiry(const double Remain);
	void OTP_DisplayAfterEnquiry();
	static bool			IsConnection();
	void OTP_Display(double Amount, double Remain, Color c, Sound s); // [PY]: 06 Jum 2005 - changed to public
	static void AddOtpLog(CString Cmd, int Value, CString Remark);

	BOOL OtpGetExtraInfo(unsigned int uiCom, unsigned int uiParam, unsigned char *ucResult);//TA18-test

private:
	void Set_Display_Delay();
	bool In_Display_Delay();
	
	void OTP_DisplayBeforeAddValue(const double Amount);
	void OTP_DisplayNoInService();
	void OTP_DisplayIdle();
	void OTP_DisplayBeforePoll();
	void OTP_DisplayAfterPoll(const double Remain);
//	bool OTP_AddValue(const double Amount);//充值
//	bool OTP_AddValue(const double Amount, double &Remain);//充值,并获取余额
	bool OTP_Deduct(const double Amount);//扣费
	bool OTP_InitComm();//初始化
	void OTP_PortClose();//关闭设备
//	void OTP_Display(double Amount, double Remain, Color c, Sound s); // [PY]: 06 Jum 2005 - shifted to public
	
//	static void AddOtpLog(CString Cmd, int Value, CString Remark);
	void OTP_SetHouseKeepingOpportunity(HouseKeepingOpportunity);
	char AIInfo[65];

	static void CALLBACK PollDetect(const PATRON &CardInfo);
	

	static UINT THR_Start_Reader(LPVOID);		//	打开读卡器线程
	static UINT THR_Main_Poll(LPVOID);			//	反复检测读卡线程句柄
	static UINT THR_Async_Poll(LPVOID /* POLL_DETECT_CALLBACK */);	//	异步读卡线程

protected:
    CCmdOtp(int SpID);
	CCmdOtp(const CCmdOtp&);
	CCmdOtp& operator=(const CCmdOtp&);

private:
	static BYTE m_nLastMsgDate;
	static CFile m_fOtpLog;
	CString _RWL_FilePath;

	COleDateTime _Display_Delay_Time;	//	控制有效显示的延时.
	USHORT		 _Display_Delay_Times;	//	防止系统时间改变.

	static long	_LastError;
	int _Service_Provider_ID;
	POLL_DETECT_CALLBACK	_PollDetectCallBack;
	double _MarkTime;
	static DeviceStatus _DeviceStatus;

	static CWinThread* CW_Start_Reader;	//	打开读卡器线程句柄
	static CWinThread* CW_Main_Poll;	//	反复检测读卡线程句柄
	static CWinThread* CW_Async_Poll;	//	异步读卡句柄

	static bool Run_Start_Reader;		//	运行标记 打开读卡器线程
	static bool Run_Main_Poll;			//	运行标记 反复检测读卡线程
	static bool Run_Async_Poll;			//	运行标记 异步读卡线程

	static bool StopRead_Status;	

    static CCmdOtp* _instance;
};

#endif // !defined(AFX_CMDOTP_H__3F34C630_79ED_4ED0_8ECB_2BBC85D21974__INCLUDED_)

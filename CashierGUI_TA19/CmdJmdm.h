// CmdKde.h: interface for the CCmdJmdm class.
// 
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//	Normal Hourly Ticket (37 BYTES) for Track 2										 //	
//																					 //
// SYSID	CAN		VEH TYPE	DISCOUNT	ENTRY ID	ENTRYTIME		  PAY ID	 //
// -----	---		--------	--------	--------	----------		---------	 //
//	 3		8			1			2			2			6(*1)			2		 //
// PAYTIME		PAYNUM		PAYAMT		CHECKSUM									 //
// -------		------		------		--------									 //	
//   6			   1		  5				1										 //	
///////////////////////////////////////////////////////////////////////////////////////
//  Special Card(10 byte) for Track 2, Put Card Holder Name in Track 1				 //		
//																					 //	
// SYSID	CAN		CHECKSUM														 //
// -----	---		--------														 //
//	 3		 8			1															 //
///////////////////////////////////////////////////////////////////////////////////////
//  Discount Token(12 byte) for Track 2                                              //
//																					 //	
// SYSID	CAN		DISCOUNTPLAN	CHECKSUM										 //
// -----	---		------------	--------										 //
//	 3		 8			2				1											 //
///////////////////////////////////////////////////////////////////////////////////////
// NOTE:																			 //
//	1. TIME is encode as: = (((Month-1)*31+(Day-1))*24+Hour)*60+Minute				 //
//  2. ~ means the dec complementary number											 //
//	3. Checksum is the last digit of sum of the prior bytes.						 //
//	4. Track 3 is the duplicate copy of track 2										 //
//  5. Track 2 is got after translation:											 //	
//		a). Inverse all even digit													 //
//		b). reverse internal order for every 10 digits								 //		
//		c). reverse total order														 //	
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDJMDM_H__C18598C1_E7F5_45A8_9FC3_70D0BD855889__INCLUDED_)
#define AFX_CMDJMDM_H__C18598C1_E7F5_45A8_9FC3_70D0BD855889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define KDE_STATUS					unsigned char
#define KDE_STATUS_ERROR			'1'
#define KDE_STATUS_CARD_AT_MOUTH	'2'
#define KDE_STATUS_IDLE				'3'

#include "..\\Common\\KDE\\KDE.h"
#include "Jmdm.h"
#ifdef _DEBUG
	#pragma comment(lib, "..\\Common\\KDE\\debug\\KDE.lib") 
	#pragma message("Automatically linking KDE.lib(Debug Version)")
#else
	#pragma comment(lib,"..\\Common\\KDE\\release\\KDE.lib") 
	#pragma message("Automatically linking KDE.lib(Release Version)") 
#endif

class CCmdJmdm  //modify for barcode reader
{
public:
	typedef struct {
		short			_TicketTypeId;//0 : normal hourly 1 : special card
		CString			_CardNo;
		short			_VehicleId;			//车辆种类
		short			_DiscountId;
		short			_EntryId;
		COleDateTime	_EntryTime;
		short			_PayId;
		COleDateTime	_PayTime;
		short			_PaymentTimes;		//付费的次数
		double			_PayAmount;
		short			_ExitId;
		CString			_Remark;			//'UserName' if is special card
	}PATRON;
	
	typedef struct {
		char _SysId[3];
		char _CardNo[8];
		char _CheckSum;
	}SPECIAL_CARD;
	
	typedef struct {
		char _SysId[3];
		char _EntryId[2];
		char _CardNo[6];
		char _VehicleId;
		char _DiscountId[2];
		char _Spare;
		char _CardType;
		char _EntryTime[6];
		char _PayId[2];
		char _PayTime[6];
		char _PaymentTimes;			//付费的次数
		char _PayAmount[5];
		char _CheckSum;
	}HOURLY_CARD;

	typedef void (CALLBACK* POLL_DETECT_CALLBACK)();

	static CCmdJmdm* Instance();
	~CCmdJmdm();

	void Stop();//	停止与KDE通讯.
	bool Start();//	启动与KDE通讯.
	bool KDE_ReadTicket(PATRON &CardInfo);
	void KDE_EjectCard();//吐卡

protected:
    CCmdJmdm();
	CCmdJmdm(const CCmdJmdm&);
	CCmdJmdm& operator=(const CCmdJmdm&);

public:
	void CloseKDE();
	void OpenKDE();
	bool KDE_IsTicketValid();
	BYTE KDE_GetError(); // 
	enum DeviceStatus{DS_Stop = 1, DS_Normal = 2, DS_Busy = 3, DS_Error = 4};
	static bool			IsNormal();		// 是否正常
	static bool			IsStop();		// 是否工作
	void SetPollDetectCallBack(POLL_DETECT_CALLBACK func = NULL);
	bool KDE_IssueSpecialCard(const CString CardNo, const CString UserName);
	bool KDE_IssueHourlyCard(const CString CardNo, const COleDateTime PayTime, const double PayAmount);
	bool IssueManualTicket(const CString CardNo, const int Vehtype, const int ProcessType, const short EntryID, const COleDateTime EntryTime, const COleDateTime PayTime, const double PayAmount);

	bool KDE_IsTicketInside();		// 检测是否有卡
	BYTE KDE_TicketPos();
	bool KDE_NeedRead();			// 检测通讯,检测是否需要读卡
	bool KDE_MoveTicket(const short Orgin, const short Dest);

	const static short SPECIAL_TICKET;	//特殊票
	const static short HOURLY_TICKET;	//计时票
private:
	static void CALLBACK PollDetect( void );
	bool KDE_Decode(PATRON &CardInfo, char * TicketBuf); //解读卡内信息	//TicketBuf长度为39
	void KDE_Transform(LPSTR texts);//Encrypt the ticket info 加密
	void KDE_Restore(LPSTR texts);	//Decrypt the ticket info 解密
	void KDE_EncodeTime(const COleDateTime t, char * EncodeTime/*len = 6*/);
	void KDE_DecodeTime(COleDateTime &t, const char * DecodeTime/*len = 6*/);
	bool KDE_WriteTicket(const PATRON &CardInfo);//写票及打印

	static void			SetStopStatus();
	static void			SetNormalStatus();
	static void			SetBusyStatus();
	static void			SetErrorStatus();


	static UINT THR_Start_Reader(LPVOID);		//	打开读卡器线程
	static UINT THR_Kde_Main(LPVOID);			//	反复检测读卡线程


private:
	POLL_DETECT_CALLBACK	_PollDetectCallBack;

    static CCmdJmdm* _instance;
//	static CKDE * _RawKde;	//底层的KDE操作指针

	static CJmdm * _RawJmdm;	//底层的操作指针

	static CWinThread* CW_Start_Reader;	//	打开读卡器线程句柄
	static CWinThread* CW_Kde_Main;	//	反复检测读卡线程句柄

	static bool Run_Start_Reader;		//	运行标记 打开读卡器线程
	static bool Run_Kde_Main;			//	运行标记 反复检测读卡线程

	long	_LastError;

	static DeviceStatus _DeviceStatus;

};

#endif // !defined(AFX_CMDKDE_H__C18598C1_E7F5_45A8_9FC3_70D0BD855889__INCLUDED_)


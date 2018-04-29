// CmdMntRecv.h: interface for the CCmdMntRecv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_H__7486B064_7FD7_4523_AFAA_846C84FBE6EE__INCLUDED_)
#define AFX_CMD_H__7486B064_7FD7_4523_AFAA_846C84FBE6EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZZ\ZZSocket.h"	// Added by ClassView

#define MAX_COMMAND_LENGTH	4096	//最大命令长度

#define tttREPLYNEEDFUL	0x31	//需要回复
#define tttREPLYNEEDLESS	0x30	//不需要回复
#define tttDEFAULTPRIORITY 0x30	//默认安全级别
#define tttDDA				0x30
#define tttNODDA			0x31
#define tttISREPLAY		0x31	//是回复信息
#define tttNOREPLAY		0x30	//不是回复信息

#define ttt__STX			0x02	//开始位
#define ttt__ETX			0x03	//停止位

//#define CMDNULL				"000"
//#define CMDQUERYOPERATOR	"037"

class CCmdMntRecv
{
public:
	void Stop();
	bool Start();
	static CCmdMntRecv* Instance();
	virtual ~CCmdMntRecv();
	static void SendDDAReply(CZZSocket &wsk);
	static void SetDDAReply(char *CmdBuf, short CmdLen);
private:

	CCmdMntRecv();
    static CCmdMntRecv* _instance;
	static void ReceiveCmd(const char * CmdBuf, const short CmdLen);
	static void CALLBACK ReceiveCmd(SOCKET s, int ServerPort, const char *ClientIP);
	int PreDecodeData(const char * CmdBuf, const short CmdLen);

	////////////////////////////////////////////////////////////////////////////
	#define DECLARE_RECV_CMD(CMD_NAME) \
		void On_##CMD_NAME(const char * CmdBuf, const short CmdLen);

	DECLARE_RECV_CMD(GroupParkRate)
	DECLARE_RECV_CMD(VehicleParkRate)
	DECLARE_RECV_CMD(TimezoneParkRate)
	DECLARE_RECV_CMD(FeeParkRate)
	DECLARE_RECV_CMD(FixTimeRule)
	DECLARE_RECV_CMD(DateParkRate)
	DECLARE_RECV_CMD(CardType)
	DECLARE_RECV_CMD(TimeSynchronize)
	DECLARE_RECV_CMD(ReceiptSetting)
	DECLARE_RECV_CMD(StationInformation)
	DECLARE_RECV_CMD(Permission)
	DECLARE_RECV_CMD(PayModeDefinition)
	DECLARE_RECV_CMD(BaseSystemSetting)
	DECLARE_RECV_CMD(ParkingFee)
	DECLARE_RECV_CMD(GroupType)
	DECLARE_RECV_CMD(DiscountPlan)
	DECLARE_RECV_CMD(RequestOtpXFile)
	DECLARE_RECV_CMD(OtpMetaFile)
	DECLARE_RECV_CMD(CloseAccount)
	////////////////////////////////////////////////////////////////////////////

	struct _header	//命令包头
	{
		char	STX;
		char	DestAddr[2];
		char	SourceAddr[2];
		char	CommandID[3];
		char	Priority;
		char	DDAMode;
		char	NeedReply;
		char	IsReply;
		char	Time[12];
		char	Length[4];
		//Function
		CString GetTime(){
			ASSERT(12 == sizeof(Time));
			CString s;
			s.Format("%12.12s",Time);
			return s;
		};
		_header(){STX = 0x02;};
		void SetDestAddr(const char *cAddr){memcpy(DestAddr, cAddr, 2);};
		void SetSourceAddr(const char *cAddr){memcpy(SourceAddr, cAddr, 2);};
		void SetCommandID(const char *cCmdID){memcpy(CommandID, cCmdID, 3);};
		void SetCommandID(int CMDID){
			ASSERT(3 == sizeof(CommandID));
			CString s;
			s.Format("%03d", CMDID);
			memcpy(CommandID, s, 3);
		};
		int GetCommandID(){
			ASSERT(3 == sizeof(CommandID));
			CString s;
			s.Format("%3.3s", CommandID);
			return atoi(s);
		};
		int GetLength(){
			ASSERT(4 == sizeof(Length));
			CString s;
			s.Format("%4.4s", Length);
			return atoi(s);
		};
		void SetPriority(const int iPriority){Priority = tttDEFAULTPRIORITY + iPriority;};
		void SetDDAMode(){DDAMode=tttNODDA;};
		void ClrDDAMode(){DDAMode=tttDDA;};
		void SetNeedReply(){NeedReply=tttREPLYNEEDFUL;};
		void ClrNeedReply(){NeedReply=tttREPLYNEEDLESS;};
		BOOL ISNeedReply(){return (NeedReply==tttREPLYNEEDFUL);}
		void SetIsReply(){IsReply=tttISREPLAY;};
		void ClrIsReply(){IsReply=tttNOREPLAY;};
		void SetTime(const char *cTime){memcpy(Time, cTime, 12);};
		void SetLength(const char *cLength){memcpy(Length, cLength, 4);};
		void SetLength(int nLen){
			ASSERT(4 == sizeof(Length));
			CString s;
			s.Format("%04d", nLen);
			memcpy(Length, s, 4);
		};
		BOOL IsValidDateTime();
		void SetTime(){
			CString strTemp=CTime::GetCurrentTime().Format("%y%m%d%H%M%S");
			this->SetTime(strTemp);
};
	};

	struct _tial		//命令包尾
	{
	private:
		char	ETX;
	public:
		_tial(){ETX = 0x03;};
	};

/////////////////////////////////////////////////////
	struct _RecvBaseCmd
	{
	public:
		virtual void SendReply(short CmdId, CString Reason = "", bool IsSuccessful = true, char Priority='1', char DDAMode='0', char NeedReply='0', char IsReply='1');
	};
	struct _STRUCT_DateParkRate : public _RecvBaseCmd//收费标准,根据"日期"分别
	{
		virtual void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_GroupParkRate : public _RecvBaseCmd//收费标准,根据"分组"分别
	{
		virtual void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_VehicleParkRate : public _RecvBaseCmd//收费标准,根据"车辆"分别
	{
		virtual void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_TimezoneParkRate : public _RecvBaseCmd//收费标准,根据"时间段"分别
	{
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_FeeParkRate : public _RecvBaseCmd//收费标准,根据"收费"分别
	{
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_FixTimeRule : public _RecvBaseCmd//补充规定
	{
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_CardType	: public _RecvBaseCmd//收费卡种类设定
	{
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_TimeSynchronize : public _RecvBaseCmd//时间同步
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_ReceiptSetting : public _RecvBaseCmd//发票打印格式
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_StationInformation : public _RecvBaseCmd//改变cashier系统设置
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_Permission : public _RecvBaseCmd//功能开放程度
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_PayModeDefinition : public _RecvBaseCmd//收款台收费模式定义
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_BaseSystemSetting : public _RecvBaseCmd//基本系统设置
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_ParkingFee : public _RecvBaseCmd//收费基本设置
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_GroupType : public _RecvBaseCmd//用户分组
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_DiscountPlan : public _RecvBaseCmd//打折计划
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_RequestOtpXFile : public _RecvBaseCmd//请求发送八达通交换文件.
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	struct _STRUCT_OtpMetaFile : public _RecvBaseCmd	//收到八达通meta文件.
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	private:
	//	bool Decode(const char * Recv, const short RecvLen);
	};
	struct _STRUCT_CloseAccount: public _RecvBaseCmd
	{
	public:
		void Perform(const char *CmdBuf, const short CmdShort);
	};
	
private:
	CZZSocket		m_zzServer;
	_tial m_tial;
	_header m_header_SendReply;			//要发送的"响应"的报头格式: 

	static bool	  _DDAReplyFlag;
	static char   _DDAReplyBuf[MAX_COMMAND_LENGTH];
	static short  _DDAReplyLen;
};

#endif // !defined(AFX_CMD_H__7486B064_7FD7_4523_AFAA_846C84FBE6EE__INCLUDED_)

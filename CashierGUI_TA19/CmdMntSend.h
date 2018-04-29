// CmdMntSend.h: interface for the CCmdMntSend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_)
#define AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZZ\ZZSocket.h"

#define MAX_COMMAND_BUF_LENGTH	4096	//最大命令长度

//////////////////////////////////////////////////////////////////////////////////////////
class CCmdMntSend  
{
public:
	enum CommStatus{CS_Stop = 1, CS_Normal = 2, CS_Busy = 3, CS_Error = 4};
	static bool			IsNormal();		// 是否正常
	static bool			IsStop();		// 是否工作

	typedef struct _STRUCT_Header			//命令包头
	{
		char	m_STX;
		char	m_DestAddr[2];
		char	m_SourceAddr[2];
		char	m_CommandID[3];
		char	m_Priority;
		char	m_DDAMode;
		char	m_NeedReply;
		char	m_IsReply;
		char	m_Time[12];
		char	m_Length[4];
	public:
		USHORT GetLength();
		bool ValidRecvFormat();
	}HHEADER;
	typedef struct _STRUCT_Tial				//命令包尾
	{
		char	m_ETX;
	}HTIAL;
	typedef struct _STRUCT_Payment			//付款记录
	{
		_STRUCT_Payment()
		{::ZeroMemory(this, sizeof(_STRUCT_Payment));}
		char		CardNo[17];
		char		Category;
		char		CarType;
		char		StationID[2];
		char		Paytime[12];
		char		ReceiptNo[8];
		char		Amount[6];
		char		PayMode1;
		char		Amount1[6];
		char		PayMode2;
		char		Amount2[6];
		char		PayMode3;
		char		Amount3[6];
		char		TransactionNo[14];
		char        Remarks[20];
	}HPAYMENT;
	typedef struct _STRUCT_AddValue			//付款记录
	{
		_STRUCT_AddValue()
		{::ZeroMemory(this, sizeof(_STRUCT_AddValue));}
		char		CardNo[9];
		char		StationID[2];
		char		Optr[20];
		char		Paytime[12];
		char		ReceiptNo[8];
		char		Amount[6];
		char		PayMode;
		char		AVRemark[50];
	}HADDVALUE;


	typedef struct _STRUCT_CardStatus		//查询卡信息响应
	{
		CString GetDescription();
		bool		_IsSpecialCard;		//是否是特殊卡
		bool		_HaveHolder;		//是否有持有人信息
		bool		_IsVIPPass;			//是否是重要客人
		bool		_HaveTransaction;	//是否有入场记录
		struct struct_SpecialCardInfo{
			CString 		_CardNo;
			CString			_HolderID;
			COleDateTime	_RegTime;
			short			_CardType;
			bool			_Status;
			COleDateTime	_ValidForm;
			COleDateTime	_ValidTo;
			short			_ValidTimes;
			double			_StoreValue;
			CString			_Remark;
		}_SpecialCardInfo;
		struct struct_HolderInfo{
			CString			_HolderID;
			CString			_HolderName;
			CString			_Addr1;
			CString			_Addr2;
			CString			_Addr3;
			CString			_Zip;
			CString			_ContactNo;
			CString			_VehiclePlateNo;
			CString			_HolderIC;
			CString			_Portrait;
		}_HolderInfo;
		struct struct_TransactionInfo{
			CString			_CardNo;
			bool			_TransState;	//true 表示在停车场内
			short			_CardCate;
			short			_CarType;
			short			_EntryStation;
			COleDateTime	_EntryTime;
			short			_ExitStation;
			COleDateTime	_ExitTime;
			short			_PayStation;
			COleDateTime	_PayTime;
			double			_PaidAmount;
			short			_PaymentNum;
			short			_DiscountPlanID;
			CString			_Remark;
		}_TransactionInfo;
	}HCARDSTATUS;
	typedef struct _STRUCT_Operator			//查询操作员信息响应
	{
	public:
		short Level(){return _Level;}
		bool ValidFlag(){return _ValidFlag;}
		CString UserID(){return _UserID;}
		CString Name(){return _Name;}
		short	_Level;
		bool	_ValidFlag;
		bool	_Exist;
		CString _UserID;
		CString _Name;
		COleDateTime _ValidFrom;
		COleDateTime _ValidTo;
	}HOPERATOR;
	typedef struct _STRUCT_ErrorWarnNoticeLog	//操作日志
	{
	public:
		_STRUCT_ErrorWarnNoticeLog()
		{::ZeroMemory(this, sizeof(_STRUCT_ErrorWarnNoticeLog));}
		char		MessageType;
		char		Message[100];
	}HERRORWARNNOTICELOG;
	typedef struct _STRUCT_NonParkingPayment	//非停车收费
	{
	public:
		_STRUCT_NonParkingPayment()
		{::ZeroMemory(this, sizeof(_STRUCT_NonParkingPayment));}
			char		CardNo[17];
			char		Category;
			char		StationID[2];
			char		Paytime[12];
			char		PayAction;
			char		Operator[20];
			char		ReceiptNo[8];
			char		Amount[8];
			char		PayMode1;
			char		Amount1[6];
			char		PayMode2;
			char		Amount2[6];
			char		PayMode3;
			char		Amount3[6];
	}HNONPARKINGPAYMENT;
	typedef struct _STRUCT_FinancialMaintain	//结算操作
	{
	public:
		_STRUCT_FinancialMaintain()
		{::ZeroMemory(this, sizeof(_STRUCT_FinancialMaintain));}
		char		StationID[2];
		char		DutyStart[12];	
		char		DutyEnd[12];
		char		Operator[20];
		char		ReceiptNo[8];
		char		PayNum[6];
		char		CashAmt[8];
		char		OTPAmt[8];
		char		SVAmt[8];
		char        CashMaintain[8];
	}HFINANCIALMAINTAIN;
	typedef struct _STRUCT_OperatorActionLog	//重要操作日志
	{
	public:
		_STRUCT_OperatorActionLog()
		{::ZeroMemory(this, sizeof(_STRUCT_OperatorActionLog));}
		char		StationID[2];
		char		Time[12];
		char		SensitiveLvl;
		char		Operator[20];
		char		Operation[20];
		char		Description[100];
	}HOPERATORACTIONLOG;
	typedef struct _STRUCT_HolderInfo		//查询持卡人信息
	{
		bool	_HaveHolder;
		CString	_HolderID;
		CString	_HolderName;
		CString _Addr1;
		CString	_Addr2;
		CString	_Addr3;
		CString	_Zip;
		CString	_ContactNo;
		CString	_VehiclePlateNo;
		CString	_HolderIC;
		CString	_Portrait;
	}HHOLDERINFO;
	
	typedef struct _STRUCT_CREATEHOLDER		//查询持卡人信息
	{
		char	_HolderID[4];
		char	_HolderName[30];
		char	_Addr1[40];
		char	_Addr2[40];
		char	_Addr3[20];
		char 	_Zip[10];
		char	_ContactNo[15];
		char	_VehiclePlateNo[12];
		char	_HolderIC[16];
	}HCREATEHOLDER;

	typedef struct _STRUCT_CREATESPECCARD
	{
		char	_CardNo[9];
		char	_HolderID[4];
		char	_RegDate[6];
		char	_CateID;
		char	_Status;
		char	_ValidFrom[6]; 
		char	_ValidTo[6];
		char	_ValidTimes[4];
		char	_StoreValue[6];
		char	_Remark[20];
	}HCREATESPECCARD;


private:
	typedef struct _STRUCT_UploadOtpXFile_Buf
	{
		char		_Property[7];
		char		_FilePath[_MAX_PATH];
		char		_BlockId[4];
		char		_BlockLen[4];
	}HUPLOADOTPXFILEBUF;
public:
	static const char CONST_CHAR_TRUE;//用字符表示真='1'
	static const char CONST_CHAR_FALSE;//用字符表示假='0'
	static const SHORT SUCCESSFUL;//正确
	static const SHORT ERROR_RESPONSE;//错误
	static const SHORT TIME_OUT;//超时
	static const SHORT ERROR_HEADER;//错误报头
	static const SHORT ERROR_TIAL;//错误报尾
	static const SHORT ERROR_BODY;//错误报体
	static const char CONST_STX;//开始位
	static const char CONST_ETX;//停止位
	static bool		m_ThrRun;		//线程执行

public:
	void EncodeSendHeader(void * buf, const char * Property, const USHORT Length);
	void EncodeSendTial(void * buf);

	static CCmdMntSend* Instance();
	void Stop();
	bool Start();
	void SendBufCmd();
	
	virtual ~CCmdMntSend();

protected:
    CCmdMntSend();
	CCmdMntSend& operator=(const CCmdMntSend&);
	CCmdMntSend(const CCmdMntSend&);
	
private:
	static void			SetStopStatus();
	static void			SetNormalStatus();
	static void			SetBusyStatus();
	static void			SetErrorStatus();

	static ULONG _InvalidConnectionTimes;	//无效连接次数

	bool CheckHeaderTial(const char *Recv);
	void EncodePing(char *CmdBuf, short &CmdLen);
	int ErrorConfirm(LPCTSTR lpText);						//错误提示
	static UINT thrSendCmd(LPVOID);

public:
	void SendCurrentExistXFiles();
	UINT SendFile(LPCTSTR FileName);


	bool TimeSynchronize();					//时间同步请求

	void Reply(const char * Property, bool IsSuccessful = true, CString Reason = ""); //发送响应

	void Payment(HPAYMENT& Payment);
	void Payment(	CString CardNo, short CardType, short CarType, COleDateTime PayTime, CString ReceiptNo, 
					double Amount, double Amount1, double Amount2, double Amount3, CString TransactionNo, CString Remarks);
	void CreateSpecCard(HCREATESPECCARD & card);
	void CreateSpecCard(CString CardNo, short HolderID, COleDateTime RegDate, 
					char CateID, char Status, COleDateTime ValidFrom, COleDateTime ValidTo, 
					short ValidTimes, double StoreValue, CString Remark);
	bool DoesSpecialCardExist(CString CAN);
	//根据卡号查询卡信息.并将卡信息存入响应的结构中.
	bool QueryCardStatus(const CString &CardID, HCARDSTATUS &CardStatus);//查询卡信息
	bool QueryCardEntryLog(const CString &CardID, LPSTR Buf);
	bool QueryOperator(const CString& UserID, const CString& Password, HOPERATOR& Operator);

	enum MessageType{msg_Error = '0', msg_Warning = '1', msg_Notice = '2'};
	void ErrorWarnNoticeLog(HERRORWARNNOTICELOG& ErrorWarnNoticeLog);
	void ErrorWarnNoticeLog(const CString msg, MessageType = msg_Notice/*Informative notification*/);


	enum PayAction {act_Create = '1', act_Renew = '2', act_Replace = '3', act_RFU = '4'};
	void NonParkingPayment(HNONPARKINGPAYMENT& NonParkingPayment);
	void NonParkingPayment(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, 
							double Amount, double Amount1, double Amount2, double Amount3);
	void NonParkingPaymentCashCard(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount);
	void NonParkingPaymentCashBack(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount);
	void NonParkingPaymentStoreValue(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount);


	void FinancialMaintain(HFINANCIALMAINTAIN& FinancialMaintain);
	void FinancialMaintain(COleDateTime DutyStart, CString ReceiptNo, long PayNum, 
							double CashAmt, double OTPAmt, double	SVAmt, double CashMaintain);
							

	enum SensitiveLvl{lvl_Lower = '1', lvl_Warn = '2', lvl_Danger = '3'};
	void OperatorActionLog(HOPERATORACTIONLOG& OperatorActionLog);
	void OperatorActionLog(const CString Operation,const CString Description = "",SensitiveLvl Lvl = lvl_Lower/*Lower sesitivity*/);
	void OtpXFileReply(bool SuccessFlag, CString OtpXFileName);	//发送OtpXFile成功消息
	void AddValue(CString CardNo, CString Optr, COleDateTime PayTime, CString ReceiptNo, 
			double Amount, CString AVRemark);
	
	//根据卡号查询卡信息.并将卡信息存入响应的结构中.
	SYSRESULT QueryHolderInfo(const CString &HolderID, HHOLDERINFO &HolderInfo);//查询持卡人信息

	//发送所有OTP交换文件到管理站.
	SYSRESULT UploadOtpXFile();
	void UpdateTrans(CString CardNo, short Action, CString Remark, CString ExitTime, CString ExitStn); // [PY]: 07 Jun 2005 - added last 2 paras
private://func
	DWORD m_dwJustRestore;
	bool SendCmd(const char *CmdBuf, const short CmdLen);	//真正执行命令发送的地方.
	bool SendCmdSync(char *CmdBuf, short CmdLen);	//发送并接受.
	//解码数据
	void QueryOperatorDecode(const char * Recv, HOPERATOR &Operator);			//解码数据
	void QueryCardStatusDecode(const char * Recv, HCARDSTATUS &CardStatus);		//解码数据
	void QueryHolderInfoDecode(const char * Recv, HHOLDERINFO &HolderInfo);		//解码数据
	void AddValue(HADDVALUE & AddValue);
private:
	static CommStatus _CommStatus;

	bool InitBuf();
	bool UploadOtpXFile(HUPLOADOTPXFILEBUF &UploadOtpXFileBuf, char *CmdBuf, short CmdLen);
	HANDLE	m_SendCmdMutex;	//同步非缓冲与缓冲发送命令机制
	HANDLE	m_ThrHandle;			//线程句柄
	DWORD	m_ThrId;				//线程编号
    static CCmdMntSend* _instance;
	CZZSocket		m_zzClient;
	//buf
	void AddBufCmd(const char *CmdBuf, const int CmdLen);
	bool GetBufCmd(char *CmdBuf, short &CmdLen);
	void DelBufCmd();
	bool PatchBufCmd(char *CmdBuf, short CmdLen);

//	char m_SendBuf[MAX_COMMAND_BUF_LENGTH];	//发送命令存储
//	char m_RecvBuf[MAX_COMMAND_BUF_LENGTH];	//接受命令存储
};

#endif // !defined(AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_)

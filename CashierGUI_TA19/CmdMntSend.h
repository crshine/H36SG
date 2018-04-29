// CmdMntSend.h: interface for the CCmdMntSend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_)
#define AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZZ\ZZSocket.h"

#define MAX_COMMAND_BUF_LENGTH	4096	//��������

//////////////////////////////////////////////////////////////////////////////////////////
class CCmdMntSend  
{
public:
	enum CommStatus{CS_Stop = 1, CS_Normal = 2, CS_Busy = 3, CS_Error = 4};
	static bool			IsNormal();		// �Ƿ�����
	static bool			IsStop();		// �Ƿ���

	typedef struct _STRUCT_Header			//�����ͷ
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
	typedef struct _STRUCT_Tial				//�����β
	{
		char	m_ETX;
	}HTIAL;
	typedef struct _STRUCT_Payment			//�����¼
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
	typedef struct _STRUCT_AddValue			//�����¼
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


	typedef struct _STRUCT_CardStatus		//��ѯ����Ϣ��Ӧ
	{
		CString GetDescription();
		bool		_IsSpecialCard;		//�Ƿ������⿨
		bool		_HaveHolder;		//�Ƿ��г�������Ϣ
		bool		_IsVIPPass;			//�Ƿ�����Ҫ����
		bool		_HaveTransaction;	//�Ƿ����볡��¼
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
			bool			_TransState;	//true ��ʾ��ͣ������
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
	typedef struct _STRUCT_Operator			//��ѯ����Ա��Ϣ��Ӧ
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
	typedef struct _STRUCT_ErrorWarnNoticeLog	//������־
	{
	public:
		_STRUCT_ErrorWarnNoticeLog()
		{::ZeroMemory(this, sizeof(_STRUCT_ErrorWarnNoticeLog));}
		char		MessageType;
		char		Message[100];
	}HERRORWARNNOTICELOG;
	typedef struct _STRUCT_NonParkingPayment	//��ͣ���շ�
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
	typedef struct _STRUCT_FinancialMaintain	//�������
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
	typedef struct _STRUCT_OperatorActionLog	//��Ҫ������־
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
	typedef struct _STRUCT_HolderInfo		//��ѯ�ֿ�����Ϣ
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
	
	typedef struct _STRUCT_CREATEHOLDER		//��ѯ�ֿ�����Ϣ
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
	static const char CONST_CHAR_TRUE;//���ַ���ʾ��='1'
	static const char CONST_CHAR_FALSE;//���ַ���ʾ��='0'
	static const SHORT SUCCESSFUL;//��ȷ
	static const SHORT ERROR_RESPONSE;//����
	static const SHORT TIME_OUT;//��ʱ
	static const SHORT ERROR_HEADER;//����ͷ
	static const SHORT ERROR_TIAL;//����β
	static const SHORT ERROR_BODY;//������
	static const char CONST_STX;//��ʼλ
	static const char CONST_ETX;//ֹͣλ
	static bool		m_ThrRun;		//�߳�ִ��

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

	static ULONG _InvalidConnectionTimes;	//��Ч���Ӵ���

	bool CheckHeaderTial(const char *Recv);
	void EncodePing(char *CmdBuf, short &CmdLen);
	int ErrorConfirm(LPCTSTR lpText);						//������ʾ
	static UINT thrSendCmd(LPVOID);

public:
	void SendCurrentExistXFiles();
	UINT SendFile(LPCTSTR FileName);


	bool TimeSynchronize();					//ʱ��ͬ������

	void Reply(const char * Property, bool IsSuccessful = true, CString Reason = ""); //������Ӧ

	void Payment(HPAYMENT& Payment);
	void Payment(	CString CardNo, short CardType, short CarType, COleDateTime PayTime, CString ReceiptNo, 
					double Amount, double Amount1, double Amount2, double Amount3, CString TransactionNo, CString Remarks);
	void CreateSpecCard(HCREATESPECCARD & card);
	void CreateSpecCard(CString CardNo, short HolderID, COleDateTime RegDate, 
					char CateID, char Status, COleDateTime ValidFrom, COleDateTime ValidTo, 
					short ValidTimes, double StoreValue, CString Remark);
	bool DoesSpecialCardExist(CString CAN);
	//���ݿ��Ų�ѯ����Ϣ.��������Ϣ������Ӧ�Ľṹ��.
	bool QueryCardStatus(const CString &CardID, HCARDSTATUS &CardStatus);//��ѯ����Ϣ
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
	void OtpXFileReply(bool SuccessFlag, CString OtpXFileName);	//����OtpXFile�ɹ���Ϣ
	void AddValue(CString CardNo, CString Optr, COleDateTime PayTime, CString ReceiptNo, 
			double Amount, CString AVRemark);
	
	//���ݿ��Ų�ѯ����Ϣ.��������Ϣ������Ӧ�Ľṹ��.
	SYSRESULT QueryHolderInfo(const CString &HolderID, HHOLDERINFO &HolderInfo);//��ѯ�ֿ�����Ϣ

	//��������OTP�����ļ�������վ.
	SYSRESULT UploadOtpXFile();
	void UpdateTrans(CString CardNo, short Action, CString Remark, CString ExitTime, CString ExitStn); // [PY]: 07 Jun 2005 - added last 2 paras
private://func
	DWORD m_dwJustRestore;
	bool SendCmd(const char *CmdBuf, const short CmdLen);	//����ִ������͵ĵط�.
	bool SendCmdSync(char *CmdBuf, short CmdLen);	//���Ͳ�����.
	//��������
	void QueryOperatorDecode(const char * Recv, HOPERATOR &Operator);			//��������
	void QueryCardStatusDecode(const char * Recv, HCARDSTATUS &CardStatus);		//��������
	void QueryHolderInfoDecode(const char * Recv, HHOLDERINFO &HolderInfo);		//��������
	void AddValue(HADDVALUE & AddValue);
private:
	static CommStatus _CommStatus;

	bool InitBuf();
	bool UploadOtpXFile(HUPLOADOTPXFILEBUF &UploadOtpXFileBuf, char *CmdBuf, short CmdLen);
	HANDLE	m_SendCmdMutex;	//ͬ���ǻ����뻺�巢���������
	HANDLE	m_ThrHandle;			//�߳̾��
	DWORD	m_ThrId;				//�̱߳��
    static CCmdMntSend* _instance;
	CZZSocket		m_zzClient;
	//buf
	void AddBufCmd(const char *CmdBuf, const int CmdLen);
	bool GetBufCmd(char *CmdBuf, short &CmdLen);
	void DelBufCmd();
	bool PatchBufCmd(char *CmdBuf, short CmdLen);

//	char m_SendBuf[MAX_COMMAND_BUF_LENGTH];	//��������洢
//	char m_RecvBuf[MAX_COMMAND_BUF_LENGTH];	//��������洢
};

#endif // !defined(AFX_CMDMNT_H__7411022A_F51C_44EE_B618_3D2F6158149A__INCLUDED_)

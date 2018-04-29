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
		short			_VehicleId;			//��������
		short			_DiscountId;
		short			_EntryId;
		COleDateTime	_EntryTime;
		short			_PayId;
		COleDateTime	_PayTime;
		short			_PaymentTimes;		//���ѵĴ���
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
		char _PaymentTimes;			//���ѵĴ���
		char _PayAmount[5];
		char _CheckSum;
	}HOURLY_CARD;

	typedef void (CALLBACK* POLL_DETECT_CALLBACK)();

	static CCmdJmdm* Instance();
	~CCmdJmdm();

	void Stop();//	ֹͣ��KDEͨѶ.
	bool Start();//	������KDEͨѶ.
	bool KDE_ReadTicket(PATRON &CardInfo);
	void KDE_EjectCard();//�¿�

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
	static bool			IsNormal();		// �Ƿ�����
	static bool			IsStop();		// �Ƿ���
	void SetPollDetectCallBack(POLL_DETECT_CALLBACK func = NULL);
	bool KDE_IssueSpecialCard(const CString CardNo, const CString UserName);
	bool KDE_IssueHourlyCard(const CString CardNo, const COleDateTime PayTime, const double PayAmount);
	bool IssueManualTicket(const CString CardNo, const int Vehtype, const int ProcessType, const short EntryID, const COleDateTime EntryTime, const COleDateTime PayTime, const double PayAmount);

	bool KDE_IsTicketInside();		// ����Ƿ��п�
	BYTE KDE_TicketPos();
	bool KDE_NeedRead();			// ���ͨѶ,����Ƿ���Ҫ����
	bool KDE_MoveTicket(const short Orgin, const short Dest);

	const static short SPECIAL_TICKET;	//����Ʊ
	const static short HOURLY_TICKET;	//��ʱƱ
private:
	static void CALLBACK PollDetect( void );
	bool KDE_Decode(PATRON &CardInfo, char * TicketBuf); //���������Ϣ	//TicketBuf����Ϊ39
	void KDE_Transform(LPSTR texts);//Encrypt the ticket info ����
	void KDE_Restore(LPSTR texts);	//Decrypt the ticket info ����
	void KDE_EncodeTime(const COleDateTime t, char * EncodeTime/*len = 6*/);
	void KDE_DecodeTime(COleDateTime &t, const char * DecodeTime/*len = 6*/);
	bool KDE_WriteTicket(const PATRON &CardInfo);//дƱ����ӡ

	static void			SetStopStatus();
	static void			SetNormalStatus();
	static void			SetBusyStatus();
	static void			SetErrorStatus();


	static UINT THR_Start_Reader(LPVOID);		//	�򿪶������߳�
	static UINT THR_Kde_Main(LPVOID);			//	�����������߳�


private:
	POLL_DETECT_CALLBACK	_PollDetectCallBack;

    static CCmdJmdm* _instance;
//	static CKDE * _RawKde;	//�ײ��KDE����ָ��

	static CJmdm * _RawJmdm;	//�ײ�Ĳ���ָ��

	static CWinThread* CW_Start_Reader;	//	�򿪶������߳̾��
	static CWinThread* CW_Kde_Main;	//	�����������߳̾��

	static bool Run_Start_Reader;		//	���б�� �򿪶������߳�
	static bool Run_Kde_Main;			//	���б�� �����������߳�

	long	_LastError;

	static DeviceStatus _DeviceStatus;

};

#endif // !defined(AFX_CMDKDE_H__C18598C1_E7F5_45A8_9FC3_70D0BD855889__INCLUDED_)


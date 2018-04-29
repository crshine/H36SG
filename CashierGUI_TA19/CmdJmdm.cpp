// CmdKde.cpp: implementation of the CCmdJmdm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Customer.h"
#include "Setting.h"
#include "CmdJmdm.h"

#include "Jmdm.h"

extern int _TicketProcessCate;
extern _System		g_System;	//ϵͳȫ�ֱ���
extern CSetting * g_Setting;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define ERR_NOERR			0	//No error 
#define ERR_COM_ERR			1	//Communication error, R/W not connected
#define ERR_INVPARAM		2	//Invalid parameter 
#define ERR_NO_TICKET		3	//No ticket detect.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const short CCmdJmdm::HOURLY_TICKET  = 0;	//��ʱƱ
const short CCmdJmdm::SPECIAL_TICKET = 1;	//����Ʊ

//CKDE *   CCmdKde::_RawKde = NULL;	//�ײ��KDE����ָ��

CJmdm *   CCmdJmdm::_RawJmdm = NULL;	//�ײ�Ĳ���ָ��

CCmdJmdm* CCmdJmdm::_instance = 0;

CWinThread* CCmdJmdm::CW_Start_Reader = NULL;	//	�򿪶������߳̾��
CWinThread* CCmdJmdm::CW_Kde_Main = NULL;	//	�����������߳̾��

bool CCmdJmdm::Run_Start_Reader;		//	���б�� �򿪶������߳�
bool CCmdJmdm::Run_Kde_Main;			//	���б�� �����������߳�
CCmdJmdm::DeviceStatus CCmdJmdm::_DeviceStatus = CCmdJmdm::DS_Stop;

CCmdJmdm* CCmdJmdm::Instance()
{
    if (_instance == 0) {
        _instance = new CCmdJmdm;
    }
    return _instance;
}

CCmdJmdm::CCmdJmdm()
{
	_RawJmdm = NULL;
	SetPollDetectCallBack(PollDetect);
}

CCmdJmdm::~CCmdJmdm()
{
	Stop();
}

/////////////////////////////////////////////////////////////////////////////
//                            ��⵽����Ļص�����                         //
/////////////////////////////////////////////////////////////////////////////
void CCmdJmdm::SetPollDetectCallBack(POLL_DETECT_CALLBACK func/* = NULL*/)
{
	if (func != NULL)
		_PollDetectCallBack = func;
	else
		_PollDetectCallBack = PollDetect;
}
void CALLBACK CCmdJmdm::PollDetect( void )
{
	_TicketProcessCate = 2;
	//��⵽��, Ĭ��Ϊ�û������¼�����.
	//����һ��"�ͻ�"(ʹ��KDE����ͣ�����Ŀͻ�)
	CCustomer::CKdeUserExitCarPark Exit;
	Exit.Trade();
}
/////////////////////////////////////////////////////////////////////////////
//                          ���ֻ��⵱ǰ״̬��Ϣ                         //
/////////////////////////////////////////////////////////////////////////////
void CCmdJmdm::SetStopStatus()
{
	_DeviceStatus = DS_Stop;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)551);//ֹͣ
}
void CCmdJmdm::SetNormalStatus()
{
	_DeviceStatus = DS_Normal;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)552);//����
}
void CCmdJmdm::SetBusyStatus()
{
	_DeviceStatus = DS_Busy;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)553);//æ
}
void CCmdJmdm::SetErrorStatus()
{
	_DeviceStatus = DS_Error;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)554);//����
}
bool CCmdJmdm::IsNormal()
{
	return (DS_Normal == _DeviceStatus);
}
bool CCmdJmdm::IsStop()
{
	return (DS_Stop == _DeviceStatus);
}
/////////////////////////////////////////////////////////////////////////////
//	ֹͣ��KDEͨѶ.
void CCmdJmdm::Stop()
{
	if (!IsStop())
	{	
		SetBusyStatus();

		Run_Start_Reader = false;	//�߳�ͨѶ����
		Run_Kde_Main = false;		//�߳�ͨѶ����

		if (NULL != CW_Start_Reader)
			WaitForSingleObject(CW_Start_Reader->m_hThread,INFINITE);//�ȴ��߳̽���
		if (NULL != CW_Kde_Main)
			WaitForSingleObject(CW_Kde_Main->m_hThread,INFINITE);//�ȴ��߳̽���
		
		delete _RawJmdm;
		_RawJmdm = NULL;
		SetStopStatus();
	}
}
///////////////////////////////////////////////////////////////////////////////////
//	������KDEͨѶ.
bool CCmdJmdm::Start()
{
	Stop();				//Stop first;
	Run_Start_Reader = true;	//�߳�ͨѶ����
	Run_Kde_Main = true;		//�߳�ͨѶ����
//	this->KDE_EjectCard();
//	this->KDE_EjectCard();
	CW_Start_Reader = AfxBeginThread( &THR_Start_Reader, 0 );	//�򿪶������߳�
	ASSERT(NULL != CW_Start_Reader );
	CW_Kde_Main = AfxBeginThread( &THR_Kde_Main, 0 );		//�����������߳�
	ASSERT(NULL != CW_Kde_Main );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//��KDE�ӿڲ���ʼ���������߳�
UINT CCmdJmdm::THR_Start_Reader(LPVOID)
{
	if (!IsStop()) return 0;
	if (NULL != _RawJmdm) return 0;
	TRACE(_T("����KDE: ��ʼ\n"));

	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;

//	_RawKde= new CKDE(Peripheral.KdePort());

	_RawJmdm = new CJmdm(Peripheral.KdePort());

	if (!_RawJmdm->OpenDev())
//		if (!_RawKde->KDE_Init())
	{
		SetErrorStatus();		//����
	}
	else
	{
		SetNormalStatus();		//����
	}

	TRACE(_T("����KDE: ����\n"));
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//	KDEͨѶ�߳�.
UINT CCmdJmdm::THR_Kde_Main(LPVOID)
{
	TRACE(_T("���KDE: ��ʼ\n"));
	Sleep(10);//Give time to initcomm
	
	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;
	
	PATRON CardInfo;//������������.

	while (Run_Kde_Main)
	{
//		Sleep(1000);
		Sleep(Peripheral.KdeThreadStep() );
		if (!Run_Kde_Main) return 1;			//	������б��

		if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 0)) 
		{
			Sleep(300);
			continue;	//	����Աæ
		}
	//	int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	����Ա��
	//	ASSERT (TRUE == b);
		//���KDE������״̬
		if (CCmdJmdm::Instance()->KDE_NeedRead())
		{
			SetBusyStatus();
			CCmdJmdm::Instance()->_PollDetectCallBack();
			while(CCmdJmdm::Instance()->KDE_NeedRead())
			{
				Sleep(500);	//�ȴ�����Աȡ��.
			}
			Sleep(500);	//��һ����Ч�Ľ��׹�����ɺ�ģ��ȴ�0.5�������´�ͬ���Ľ���
		}
		else
			Sleep(500);	//UCH -wait a while
	
		int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	����Ա��
		ASSERT (TRUE == b);
	}

	TRACE(_T("���KDE:����\n"));
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//                            ������KDE�������ķ�װ                              //
///////////////////////////////////////////////////////////////////////////////////
//Ʊ��ǰλ��
BYTE CCmdJmdm::KDE_TicketPos()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
//	int ret = _RawKde->KDE_GetStatus(loc);
	loc = loc & 0xFA;
	return loc;
}
//�ƶ�Ʊ
bool CCmdJmdm::KDE_MoveTicket(const short Orgin, const short Dest)
{
		return true;
}

//�Ƿ���Ʊ�ڻ�����
bool CCmdJmdm::KDE_IsTicketInside()
{
	return FALSE;
}

//���ͨѶ,����Ƿ���Ҫ����
bool CCmdJmdm::KDE_NeedRead()
{
	if ( IsStop() ) return false;

	if(_RawJmdm->IsValidTicket()) return TRUE;
		else return FALSE;
}

bool CCmdJmdm::KDE_ReadTicket(PATRON &CardInfo)
{
	if ( IsStop() ) return false;
	//�ƶ�������λ��
//	if ( FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 6, 0, 0, 0, 0) )
	{
//		if ( FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 6, 0, 0, 0, 0) )
//			return false;
	}

	char TicketBuf[40];
	char DupTicketBuf[40];
	char Remark[100];
	memset(Remark, 0, 100);
	memset(TicketBuf, 0, 40);
	memset(DupTicketBuf, 0, 40);

	//��ͼ����
	CardInfo._Remark = mem2str(Remark, sizeof(Remark));

	_RawJmdm->ReadTicket(TicketBuf);
	CardInfo._CardNo=TicketBuf;

	return TRUE;
}
//�¿�
void CCmdJmdm::KDE_EjectCard()
{
//	if ( IsStop() ) return ;
//	if ( !KDE_IsTicketInside() ) return;
//	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
//	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
}
//���������Ϣ
bool CCmdJmdm::KDE_Decode(PATRON &CardInfo, char * TicketBuf)	//TicketBuf����Ϊ39
{
	SPECIAL_CARD * Sfmt;	//���⿨
	HOURLY_CARD * Hfmt;		//��ͨ��

	TicketBuf[38] = 0;
	int SysIdInTicket = 0;
	char CheckSum;

	// Special Card
	if		( sizeof(SPECIAL_CARD) == strlen(TicketBuf) )	
	{
		CardInfo._TicketTypeId = SPECIAL_TICKET ; 
		Sfmt = static_cast<SPECIAL_CARD * >((void *)TicketBuf);

		CheckSum = Sfmt->_CheckSum;
		Sfmt->_CheckSum = 0;
		if (CheckSum != CalculateCSum(TicketBuf)) return false;	//�ۼӺ�
		SysIdInTicket = mem2short(Sfmt->_SysId, sizeof(Sfmt->_SysId));//ϵͳ��
	
		CardInfo._CardNo = "P";
		CardInfo._CardNo += mem2str(Sfmt->_CardNo, sizeof(Sfmt->_CardNo));
	}
	// Hourly / Damage / Lost
	else if ( sizeof(HOURLY_CARD)  == strlen(TicketBuf) )
	{
//		CardInfo._TicketTypeId = HOURLY_TICKET ; // normal hourly

		Hfmt = static_cast<HOURLY_CARD * >((void *)TicketBuf);
		CheckSum = Hfmt->_CheckSum;
		Hfmt->_CheckSum = 0;
		if (CheckSum != CalculateCSum(TicketBuf)) return false;	//�ۼӺ�
		SysIdInTicket = mem2short(Hfmt->_SysId, sizeof(Hfmt->_SysId));//ϵͳ��

		CardInfo._EntryId		= mem2short( Hfmt->_EntryId,		sizeof(Hfmt->_EntryId));		
	
		CardInfo._TicketTypeId  = mem2short( Hfmt->_CardType        );
		if ( CardInfo._TicketTypeId == 7)   CardInfo._CardNo		= "D";
		else if ( CardInfo._TicketTypeId == 8)   CardInfo._CardNo		= "L";
		else  CardInfo._CardNo		= "P";

		CardInfo._CardNo	   += mem2str(   Hfmt->_EntryId,		sizeof(Hfmt->_EntryId));
		CardInfo._CardNo	   += mem2str(   Hfmt->_CardNo,			sizeof(Hfmt->_CardNo));

		CardInfo._VehicleId		= mem2short( Hfmt->_VehicleId		);
		CardInfo._DiscountId	= mem2short( Hfmt->_DiscountId,		sizeof(Hfmt->_DiscountId));

		CardInfo._PayId			= mem2short( Hfmt->_PayId,			sizeof(Hfmt->_PayId));
		CardInfo._PaymentTimes	= mem2short( Hfmt->_PaymentTimes	);	
		CardInfo._PayAmount		= mem2dbl(   Hfmt->_PayAmount,		sizeof(Hfmt->_PayAmount)  );
		KDE_DecodeTime( CardInfo._EntryTime, Hfmt->_EntryTime );
		KDE_DecodeTime( CardInfo._PayTime, Hfmt->_PayTime );
	}
	else
		return false;
	
	if ( SysIdInTicket != CSetting::Instance()->m_BaseSystemSetting.SystemID())
		return false;
	return true;
}
//����һ�����⿨.
bool CCmdJmdm::KDE_IssueSpecialCard(const CString CardNo, const CString UserName)
{
	ASSERT(1 < CardNo.GetLength());
	PATRON CardInfo;
	CardInfo._TicketTypeId	= SPECIAL_TICKET; // special card
	CardInfo._CardNo		= CardNo;
	CardInfo._Remark		= UserName;
	return KDE_WriteTicket(CardInfo);
}
bool CCmdJmdm::IssueManualTicket(const CString CardNo, const int VehType, const int ProcessType, const short EntryID, const COleDateTime EntryTime, const COleDateTime PayTime, const double PayAmount)
{
	showTip("�д��J�ťպϱ���!", true);

	// read blank ticket
	if ( KDE_IsTicketValid() == true)
	{
		PATRON CardInfo;
		if (ProcessType == 0) // Damage Ticket 
			CardInfo._TicketTypeId = 7;
		else if (ProcessType == 1) // Lost Ticket
			CardInfo._TicketTypeId = 8;
		else if (ProcessType == 3) // Change VehType
			CardInfo._TicketTypeId = 0;
		else return false;
		CardInfo._CardNo = CardNo;
		CardInfo._DiscountId = 0;
		CardInfo._VehicleId = VehType;
		CardInfo._EntryId = EntryID;
		CardInfo._EntryTime = EntryTime;
		CardInfo._PayId = Str2Int(g_Setting->m_Communicate.StationID(), 3);
		CardInfo._PayTime = PayTime;
		CardInfo._PayAmount = PayAmount;
		CardInfo._PaymentTimes=1;
		CardInfo._PayId = _ttol(CSetting::Instance()->m_Communicate.StationID());
		bool res = KDE_WriteTicket(CardInfo);

		showTip("�Ш��X�ϱ���!", true);
		while(CCmdJmdm::Instance()->KDE_NeedRead())
		{
			Sleep(500);	//�ȴ�����Աȡ��.
		}
		return res;

	}else return false;

}
//����һ����ͨ��
bool CCmdJmdm::KDE_IssueHourlyCard(const CString CardNo, const COleDateTime PayTime, const double PayAmount)
{
	ASSERT(1 < CardNo.GetLength());
	PATRON CardInfo;
	if ( !KDE_ReadTicket(CardInfo) )
	{	//��������
		return false;
	}
	else
	{
		//������ȷ���ͱȽ��Ƿ���ͬһ����. //???
		if ( (SPECIAL_TICKET == CardInfo._TicketTypeId) && (CardNo != CardInfo._CardNo) )
			return false;
	}
	CardInfo._PayTime = PayTime;
	CardInfo._PayAmount = PayAmount;
	CardInfo._PaymentTimes++;
	CardInfo._PayId = _ttol(CSetting::Instance()->m_Communicate.StationID());
	
	return KDE_WriteTicket(CardInfo);
	
}

//������
bool CCmdJmdm::KDE_WriteTicket(const PATRON &CardInfo)//дƱ����ӡ
{

	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//                               �����Ǹ�������                                  //
///////////////////////////////////////////////////////////////////////////////////
//Encrypt the ticket info ����
void CCmdJmdm::KDE_Transform(LPSTR texts)
{
	Reverse(texts);
	LPSTR pos;
	int TLen = strlen(texts);
	int j, i=0; 
	do{
		j = i + 9;
		if (j >= TLen) j = TLen-1;
		pos = texts + i;
		Reverse(pos, j - i + 1);
		i+=10;
	}while (j < TLen-1);
	for (i=0; i<TLen; i++)
	{
		if (i%2 == 0) texts[i] = 0x30 + 0x39 - texts[i];
	}
}

//Decrypt the ticket info ����
void CCmdJmdm::KDE_Restore(LPSTR texts)
{
	LPSTR pos;
	int TLen = strlen(texts);
	int i, j;
	
	for (i=0; i<TLen; i++)
	{
		if (i%2 == 0) texts[i] = 0x30 + 0x39 - texts[i];
	}
	i=0; 
	do{
		j = i + 9;
		if (j >= TLen) j = TLen-1;
		pos = texts + i;
		Reverse(pos, j - i + 1);
		i+=10;
	}while (j < TLen-1);
	Reverse(texts);	
}

void CCmdJmdm::KDE_EncodeTime(const COleDateTime t, char * EncodeTime/*len = 6*/)
{	//��ʱ���Ϊ�ɵ�ǰ�������ڵķ�����
	long Code = 0;
//	CString tmp;
	if ( COleDateTime::valid == t.GetStatus() )
	{
		Code = (t.GetMonth() - 1) * 31;
		Code = (Code + t.GetDay() - 1) * 24;
		Code = (Code + t.GetHour()) * 60;
		Code = Code + t.GetMinute();
	}

//	tmp.Format("%06d", Code);
//	str2mem(tmp,EncodeTime, 6);

	long2mem(Code, EncodeTime, 6);	//Encode length = 6
}

void CCmdJmdm::KDE_DecodeTime(COleDateTime &t, const char * DecodeTime/*len = 6*/)
{	//����������Ϊʱ��
	if (strncmp(DecodeTime, "000000", 6) == 0)
	{
		t.SetStatus(COleDateTime::null);
		return;
	}
	long Code = mem2long(DecodeTime, 6);
	int m = ((Code / 1440) / 31) + 1;
	int d = ((Code / 1440) % 31) + 1;
	int H = (Code % 1440) / 60;
	int M = (Code % 1440) % 60;

	COleDateTime thisyeardate(COleDateTime::GetCurrentTime().GetYear(), m, d, H, M, 0);
	COleDateTime lastyeardate(COleDateTime::GetCurrentTime().GetYear() - 1, m, d, H, M, 0);
	double thisyeardated = (double)thisyeardate;
	double lastyeardated = (double)lastyeardate;
	double todayd = (double)(COleDateTime::GetCurrentTime());
	double diff = todayd - thisyeardate;
	if ((diff > 0) || ((diff < 0) && (diff > -0.007))) 
		t = thisyeardate;
	else 
		t = lastyeardate;
}

BYTE CCmdJmdm::KDE_GetError()
{
	return false;
}

bool CCmdJmdm::KDE_IsTicketValid()
{

	return true;
}

void CCmdJmdm::OpenKDE()  //[JC]20060309  SOLVE the logout could pay problem 003
{
//	_RawKde->OpenKDE();
}

void CCmdJmdm::CloseKDE()  //[JC]20060309  SOLVE the logout could pay problem 004
{
//	_RawKde->CloseKDE();

}

// CmdKde.cpp: implementation of the CCmdKde class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Customer.h"
#include "Setting.h"
#include "CmdKde.h"
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
const short CCmdKde::HOURLY_TICKET  = 0;	//��ʱƱ
const short CCmdKde::SPECIAL_TICKET = 1;	//����Ʊ

CKDE *   CCmdKde::_RawKde = NULL;	//�ײ��KDE����ָ��
CCmdKde* CCmdKde::_instance = 0;

CWinThread* CCmdKde::CW_Start_Reader = NULL;	//	�򿪶������߳̾��
CWinThread* CCmdKde::CW_Kde_Main = NULL;	//	�����������߳̾��

bool CCmdKde::Run_Start_Reader;		//	���б�� �򿪶������߳�
bool CCmdKde::Run_Kde_Main;			//	���б�� �����������߳�
CCmdKde::DeviceStatus CCmdKde::_DeviceStatus = CCmdKde::DS_Stop;

CCmdKde* CCmdKde::Instance()
{
    if (_instance == 0) {
        _instance = new CCmdKde;
    }
    return _instance;
}

CCmdKde::CCmdKde()
{
	_RawKde = NULL;
	SetPollDetectCallBack(PollDetect);
}

CCmdKde::~CCmdKde()
{
	Stop();
}

/////////////////////////////////////////////////////////////////////////////
//                            ��⵽����Ļص�����                         //
/////////////////////////////////////////////////////////////////////////////
void CCmdKde::SetPollDetectCallBack(POLL_DETECT_CALLBACK func/* = NULL*/)
{
	if (func != NULL)
		_PollDetectCallBack = func;
	else
		_PollDetectCallBack = PollDetect;
}
void CALLBACK CCmdKde::PollDetect( void )
{
	//��⵽��, Ĭ��Ϊ�û������¼�����.
	//����һ��"�ͻ�"(ʹ��KDE����ͣ�����Ŀͻ�)
	CCustomer::CKdeUserExitCarPark Exit;
	Exit.Trade();
}
/////////////////////////////////////////////////////////////////////////////
//                          ���ֻ��⵱ǰ״̬��Ϣ                         //
/////////////////////////////////////////////////////////////////////////////
void CCmdKde::SetStopStatus()
{
	_DeviceStatus = DS_Stop;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)551);//ֹͣ
}
void CCmdKde::SetNormalStatus()
{
	_DeviceStatus = DS_Normal;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)552);//����
}
void CCmdKde::SetBusyStatus()
{
	_DeviceStatus = DS_Busy;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)553);//æ
}
void CCmdKde::SetErrorStatus()
{
	_DeviceStatus = DS_Error;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)554);//����
}
bool CCmdKde::IsNormal()
{
	return (DS_Normal == _DeviceStatus);
}
bool CCmdKde::IsStop()
{
	return (DS_Stop == _DeviceStatus);
}
/////////////////////////////////////////////////////////////////////////////
//	ֹͣ��KDEͨѶ.
void CCmdKde::Stop()
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
		
		delete _RawKde;
		_RawKde = NULL;
		SetStopStatus();
	}
}
///////////////////////////////////////////////////////////////////////////////////
//	������KDEͨѶ.
bool CCmdKde::Start()
{
	Stop();				//Stop first;
	Run_Start_Reader = true;	//�߳�ͨѶ����
	Run_Kde_Main = true;		//�߳�ͨѶ����
	this->KDE_EjectCard();
	this->KDE_EjectCard();
	CW_Start_Reader = AfxBeginThread( &THR_Start_Reader, 0 );	//�򿪶������߳�
	ASSERT(NULL != CW_Start_Reader );
	CW_Kde_Main = AfxBeginThread( &THR_Kde_Main, 0 );		//�����������߳�
	ASSERT(NULL != CW_Kde_Main );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//��KDE�ӿڲ���ʼ���������߳�
UINT CCmdKde::THR_Start_Reader(LPVOID)
{
	if (!IsStop()) return 0;
	if (NULL != _RawKde) return 0;
	TRACE(_T("����KDE: ��ʼ\n"));

	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;

	_RawKde= new CKDE(Peripheral.KdePort());
	
	if (!_RawKde->KDE_Init())
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
UINT CCmdKde::THR_Kde_Main(LPVOID)
{
	TRACE(_T("���KDE: ��ʼ\n"));
	Sleep(10);//Give time to initcomm
	
	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;
	
	PATRON CardInfo;//������������.
	while (Run_Kde_Main)
	{
		Sleep(Peripheral.KdeThreadStep() );
		if (!Run_Kde_Main) return 1;			//	������б��

		if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 0)) continue;	//	����Աæ
	//	int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	����Ա��
	//	ASSERT (TRUE == b);
		//���KDE������״̬
		if (CCmdKde::Instance()->KDE_NeedRead())
		{
			SetBusyStatus();
			CCmdKde::Instance()->_PollDetectCallBack();
			while(CCmdKde::Instance()->KDE_NeedRead())
			{
				Sleep(500);	//�ȴ�����Աȡ��.
			}
			Sleep(500);	//��һ����Ч�Ľ��׹�����ɺ�ģ��ȴ�0.5�������´�ͬ���Ľ���
		}
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
BYTE CCmdKde::KDE_TicketPos()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
	int ret = _RawKde->KDE_GetStatus(loc);
	loc = loc & 0xFA;
	return loc;
}
//�ƶ�Ʊ
bool CCmdKde::KDE_MoveTicket(const short Orgin, const short Dest)
{
	if (TRUE == _RawKde->KDE_Operate(Orgin, Dest, 0, 0, 0, 0, 0) )
		return true;
	else
		return false;
}

//�Ƿ���Ʊ�ڻ�����
bool CCmdKde::KDE_IsTicketInside()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
	int ret = _RawKde->KDE_GetStatus(loc);
	loc = loc & 0xFA;
	return ( 0 != loc );
}

//���ͨѶ,����Ƿ���Ҫ����
bool CCmdKde::KDE_NeedRead()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
	int ret = _RawKde->KDE_GetStatus(loc);
	if (TRUE==GetBitFlag(loc, 0))
		return true;
	if (254 == ret)	
	{
		SetErrorStatus();
	}
	else
	{
		SetNormalStatus();
	}
	return false;
}

bool CCmdKde::KDE_ReadTicket(PATRON &CardInfo)
{
	if ( IsStop() ) return false;
	//�ƶ�������λ��
	if ( FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 6, 0, 0, 0, 0) )
	{
		if ( FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 6, 0, 0, 0, 0) )
			return false;
	}

	char TicketBuf[40];
	char DupTicketBuf[40];
	char Remark[100];
	memset(Remark, 0, 100);
	memset(TicketBuf, 0, 40);
	memset(DupTicketBuf, 0, 40);

	//��ͼ����
	if (FALSE == _RawKde->KDE_ReadTicket(Remark, TicketBuf, DupTicketBuf))
	{
		if (FALSE == _RawKde->KDE_ReadTicket(Remark, TicketBuf, DupTicketBuf))
			return false;
	}
	CardInfo._Remark = mem2str(Remark, sizeof(Remark));

	if (KDE_Decode(CardInfo, TicketBuf)) return true;	//����ɹ�
	if (KDE_Decode(CardInfo, DupTicketBuf)) return true;//����ɹ�

	return false;
}
//�¿�
void CCmdKde::KDE_EjectCard()
{
	if ( IsStop() ) return ;
	if ( !KDE_IsTicketInside() ) return;
	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
}
//���������Ϣ
bool CCmdKde::KDE_Decode(PATRON &CardInfo, char * TicketBuf)	//TicketBuf����Ϊ39
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
bool CCmdKde::KDE_IssueSpecialCard(const CString CardNo, const CString UserName)
{
	ASSERT(1 < CardNo.GetLength());
	PATRON CardInfo;
	CardInfo._TicketTypeId	= SPECIAL_TICKET; // special card
	CardInfo._CardNo		= CardNo;
	CardInfo._Remark		= UserName;
	return KDE_WriteTicket(CardInfo);
}
bool CCmdKde::IssueManualTicket(const CString CardNo, const int VehType, const int ProcessType, const short EntryID, const COleDateTime EntryTime, const COleDateTime PayTime, const double PayAmount)
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
		while(CCmdKde::Instance()->KDE_NeedRead())
		{
			Sleep(500);	//�ȴ�����Աȡ��.
		}
		return res;

	}else return false;

}
//����һ����ͨ��
bool CCmdKde::KDE_IssueHourlyCard(const CString CardNo, const COleDateTime PayTime, const double PayAmount)
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
bool CCmdKde::KDE_WriteTicket(const PATRON &CardInfo)//дƱ����ӡ
{
	char TicketBuf[40];
	char ReadTicketBuf[40];
	char ReadTicketBuf2[40];

	char Remark[100];
	char PrintBuf[40];

	int i;
	
	memset(TicketBuf, 0, sizeof(TicketBuf));
	memset(ReadTicketBuf, 0, sizeof(ReadTicketBuf));
	memset(ReadTicketBuf2, 0, sizeof(ReadTicketBuf2));
	memset(Remark, 0, sizeof(Remark));
	memset(PrintBuf, 0, sizeof(PrintBuf));
	short SysId = CSetting::Instance()->m_BaseSystemSetting.SystemID();
	ASSERT(1 < CardInfo._CardNo.GetLength());

	CString TicketNo = CardInfo._CardNo;			// ɾ��Ʊ��ǰ׺ maybe 'P'.
	TicketNo.Delete(0);

	CString ttktno;
/*
	if (CardInfo._TicketTypeId == 7 ||CardInfo._TicketTypeId == 8) // damage/lost hourly
		ttktno.Format("%02d%s", CardInfo._TicketTypeId, TicketNo);
*/

	ttktno.Format("%s", TicketNo);
																												////// //??? Temp for hourly ticket //////////////							
	if	(HOURLY_TICKET == CardInfo._TicketTypeId ||CardInfo._TicketTypeId == 7 ||CardInfo._TicketTypeId == 8 || CardInfo._TicketTypeId == 1) // normal hourly
	{
		HOURLY_CARD * Hfmt = static_cast<HOURLY_CARD * >((void *)TicketBuf);		//��ͨ��
		CString tmp;
		
		tmp.Format("%03d", SysId);
		str2mem(tmp,Hfmt->_SysId, sizeof(Hfmt->_SysId) );
		
		if ( (CardInfo._TicketTypeId == 7) || (CardInfo._TicketTypeId == 8) )
		{
			tmp.Format("%02d", CardInfo._PayId);
		}
		else tmp.Format("%02d", CardInfo._EntryId);
		str2mem(tmp,Hfmt->_EntryId, sizeof(Hfmt->_EntryId) );

		str2mem(TicketNo.Mid(2,6),Hfmt->_CardNo, sizeof(Hfmt->_CardNo) );

		short2mem(CardInfo._VehicleId,Hfmt->_VehicleId);
		
		tmp.Format("%02d", CardInfo._DiscountId);
		str2mem(tmp,Hfmt->_DiscountId,sizeof(Hfmt->_DiscountId));

		short2mem(0,Hfmt->_Spare);
		
		short2mem(CardInfo._TicketTypeId,Hfmt->_CardType);
		
		KDE_EncodeTime(CardInfo._EntryTime,	Hfmt->_EntryTime);
		
		tmp.Format("%02d", CardInfo._PayId);
		str2mem(tmp,Hfmt->_PayId,sizeof(Hfmt->_PayId));
		
		KDE_EncodeTime(CardInfo._PayTime,	Hfmt->_PayTime);
		
		short2mem( CardInfo._PaymentTimes%10,	Hfmt->_PaymentTimes);

		tmp.Format("%05d", (long)(CardInfo._PayAmount*10));
		str2mem(tmp,Hfmt->_PayAmount,sizeof(Hfmt->_PayAmount));

		// [BW] 20051203 
		// Check for all the information != ' ', if any char == ' ' change it to '0'
		for (i=0; i<37; i++)
		{
			//                   ' '                    '0'
			if (TicketBuf[i] == 0x20 ) TicketBuf[i]  = 0x30;
		}

		Hfmt->_CheckSum = CalculateCSum(TicketBuf);

		//��ӡ����	"CSH00 TKT00000000 2004.01.01 01:01"
		CString PrintStr;
		CString TicketType;
		if (CardInfo._TicketTypeId == 0)
		{
			if (CardInfo._PaymentTimes == 1)
				PrintStr.Format("%02d$%.0f@%s",
					CardInfo._PayId, CardInfo._PayAmount, 
					CardInfo._PayTime.Format("%m.%d %H:%M")	);
			else
				PrintStr.Format("                    %02d$%.0f@%s",
					CardInfo._PayId, CardInfo._PayAmount, 
					CardInfo._PayTime.Format("%H:%M")	);
		}
		////////////////////////////////////////////////////////////////////////////////
		if (CardInfo._TicketTypeId == 1) //???   temp for hourly ticket 
		{
			if (CardInfo._PaymentTimes == 1)
				PrintStr.Format("%02d$%.0f@%s",
					CardInfo._PayId, CardInfo._PayAmount, 
					CardInfo._PayTime.Format("%m.%d %H:%M")	);
			else
				PrintStr.Format("                    %02d$%.0f@%s",
					CardInfo._PayId, CardInfo._PayAmount, 
					CardInfo._PayTime.Format("%H:%M")	);
		}
		//////////////////////////////////////////////////////////////////////////////////
		if (CardInfo._TicketTypeId == 7) 
		{TicketType = "D";
			PrintStr.Format("CS%02dTP%01d %s%s $%-4.0f@%s",
		         CardInfo._PayId, CardInfo._VehicleId, TicketType, TicketNo, CardInfo._PayAmount, 
                 CardInfo._PayTime.Format("%m.%d %H:%M"));
		}
		if (CardInfo._TicketTypeId == 8) 
		{TicketType = "L";
			PrintStr.Format("CS%02dTP%01d %s%s $%-4.0f@%s",
		         CardInfo._PayId, CardInfo._VehicleId, TicketType, TicketNo,CardInfo._PayAmount, 
                 CardInfo._PayTime.Format("%m.%d %H:%M"));
		}
		
		str2mem( PrintStr, PrintBuf, min(sizeof(PrintBuf), PrintStr.GetLength()) );
	}
	else if ( CardInfo._TicketTypeId>0 && CardInfo._TicketTypeId<6)// special card
	{
		SPECIAL_CARD * Sfmt = static_cast<SPECIAL_CARD * >((void *)TicketBuf);	//���⿨
		CString tmpstr;
		tmpstr.Format("%03d", SysId);
		str2mem( tmpstr,			Sfmt->_SysId,	sizeof(Sfmt->_SysId) );
		str2mem(   TicketNo,		Sfmt->_CardNo,	sizeof(Sfmt->_CardNo) );
		Sfmt->_CheckSum = CalculateCSum(TicketBuf);
		
		str2mem( CardInfo._Remark, Remark, min(sizeof(Remark), CardInfo._Remark.GetLength()) );
	}
	else
	{
		return false;
	}

	for (i=0; i<3; i++)
	{
		if ( i > 0 ) 
		{
			while (1) 
			{
				if (KDE_NeedRead()) break;
				Sleep(500);
			}
		} 
/* ORG
		if (FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 0, Remark, TicketBuf, TicketBuf, PrintBuf))  
		{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 0, Remark, TicketBuf, TicketBuf, PrintBuf); 
		}

		if (_RawKde->KDE_GetResult() == -1) return true; // -1 mean 0xFFFFFFFFFFFFFFFF No error condition
		else
		{
			if (i == 2) 
			{
				showTip("�Ш��X�ϲ�! �ϱa�w�l�a, �вM�~���Y��A����!", true);	
				return false;
			}
			else 
			{
				showTip("�Ш��X�ϲ�! �ϱa�w�l�a, �д��J�s�ϲ�!", true);
				while(CCmdKde::Instance()->KDE_NeedRead())
				{
					Sleep(500);	//�ȴ�����Աȡ��.
				}
			}
		}
ORG*/
////////////////////////////////////////////////////
		if (FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_FRONT, 0, Remark, TicketBuf, TicketBuf, 0))  
		{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_FRONT, 0, Remark, TicketBuf, TicketBuf, 0); 
		}
		_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 6, 0, 0, 0, PrintBuf);
		_RawKde->KDE_ReadTicket(ReadTicketBuf2, ReadTicketBuf, ReadTicketBuf2);
		if ( ReadTicketBuf[36] == TicketBuf[36]) 
		{
           	//_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 6, 0, 0, 0, PrintBuf);
			return true;
		}
		else
		{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 6, 0, 0, 0, "                                X");
			if (i == 2) 
			{
				showTip("�Ш��X�ϲ�! �ϱa�w�l�a, �вM�~���Y��A����!", true);	
				return false;
			}
			else 
			{
				showTip("�Ш��X�ϲ�! �ϱa�w�l�a, �д��J�s�ϲ�!", true);
				while(CCmdKde::Instance()->KDE_NeedRead())
				{
					Sleep(500);	//�ȴ�����Աȡ��.
				}
			}
		}
///////////////////////////////////////////////////////
	} 
	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//                               �����Ǹ�������                                  //
///////////////////////////////////////////////////////////////////////////////////
//Encrypt the ticket info ����
void CCmdKde::KDE_Transform(LPSTR texts)
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
void CCmdKde::KDE_Restore(LPSTR texts)
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

void CCmdKde::KDE_EncodeTime(const COleDateTime t, char * EncodeTime/*len = 6*/)
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

void CCmdKde::KDE_DecodeTime(COleDateTime &t, const char * DecodeTime/*len = 6*/)
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

BYTE CCmdKde::KDE_GetError()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
	int ret = _RawKde->KDE_GetResult();
	loc = loc & 0xFC;
	return loc;
}

bool CCmdKde::KDE_IsTicketValid()
{
	int i;

	char TicketBuf[40];
	char ReadTicketBuf[40];
	char ReadTicketBuf2[40];
	
	memset(TicketBuf, 0, sizeof(TicketBuf));
	memset(ReadTicketBuf, 0, sizeof(ReadTicketBuf));
	memset(ReadTicketBuf2, 0, sizeof(ReadTicketBuf2));

	// Check for all the information != ' ', if any char == ' ' change it to '0'
	for (i=0; i<37; i++)
	{
		TicketBuf[i]  = 0x30;
	}

	for (i=0; i<3; i++)
	{
		while (1) 
		{
			if (KDE_NeedRead()) break;
			Sleep(500);
		} 
/* ORG
		// Read Ticket from FRONT to Back
		_RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 7, 0, 0, 0, 0);

		if (_RawKde->KDE_GetResult() == -1) // -1 mean 0xFFFFFFFFFFFFFFFF no error condition
		{
			return true;
		}else{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 7, 0, 0, 0, 0);
			if (i < 2) showTip("�Ш��X�ϲ�! ������V���~ �� �ϱa�w�l�a, �Э���!", true);
			else showTip("�Ш��X�ϲ�! ������V���~ �� �ϱa�w�l�a, �вM�~���Y��A����!", true);
			while(CCmdKde::Instance()->KDE_NeedRead())
			{
				Sleep(500);	//�ȴ�����Աȡ��.
			}
			if (i == 2) return false;
		}
ORG */
		// Write Ticket From Front to Back
		if (FALSE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 0, 0, TicketBuf, TicketBuf, 0))  
		{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 0, 0, TicketBuf, TicketBuf, 0);
		}
		_RawKde->KDE_Operate(POS_ANYWHERE, POS_BACK, 6, 0, 0, 0, 0);
		_RawKde->KDE_ReadTicket(ReadTicketBuf2, ReadTicketBuf, ReadTicketBuf2);
		if ( ReadTicketBuf[36] == 0x30) return true;
		else
		{
			_RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 6, 0, 0, 0, 0);
			if (i < 2) showTip("�Ш��X�ϲ�! ������V���~ �� �ϱa�w�l�a, �Э���!", true);
			else showTip("�Ш��X�ϲ�! ������V���~ �� �ϱa�w�l�a, �вM�~���Y��A����!", true);
			while(CCmdKde::Instance()->KDE_NeedRead())
			{
				Sleep(500);	//�ȴ�����Աȡ��.
			}
			if (i == 2) return false;
		}
    } 
	return true;
}

void CCmdKde::OpenKDE()  //[JC]20060309  SOLVE the logout could pay problem 003
{
	_RawKde->OpenKDE();
}

void CCmdKde::CloseKDE()  //[JC]20060309  SOLVE the logout could pay problem 004
{
	_RawKde->CloseKDE();

}

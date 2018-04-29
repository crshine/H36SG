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
extern _System		g_System;	//系统全局变量
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
const short CCmdJmdm::HOURLY_TICKET  = 0;	//计时票
const short CCmdJmdm::SPECIAL_TICKET = 1;	//特殊票

//CKDE *   CCmdKde::_RawKde = NULL;	//底层的KDE操作指针

CJmdm *   CCmdJmdm::_RawJmdm = NULL;	//底层的操作指针

CCmdJmdm* CCmdJmdm::_instance = 0;

CWinThread* CCmdJmdm::CW_Start_Reader = NULL;	//	打开读卡器线程句柄
CWinThread* CCmdJmdm::CW_Kde_Main = NULL;	//	反复检测读卡线程句柄

bool CCmdJmdm::Run_Start_Reader;		//	运行标记 打开读卡器线程
bool CCmdJmdm::Run_Kde_Main;			//	运行标记 反复检测读卡线程
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
//                            检测到卡后的回调函数                         //
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
	//检测到卡, 默认为用户出场事件发生.
	//创建一个"客户"(使用KDE卡出停车场的客户)
	CCustomer::CKdeUserExitCarPark Exit;
	Exit.Trade();
}
/////////////////////////////////////////////////////////////////////////////
//                          保持或检测当前状态信息                         //
/////////////////////////////////////////////////////////////////////////////
void CCmdJmdm::SetStopStatus()
{
	_DeviceStatus = DS_Stop;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)551);//停止
}
void CCmdJmdm::SetNormalStatus()
{
	_DeviceStatus = DS_Normal;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)552);//空闲
}
void CCmdJmdm::SetBusyStatus()
{
	_DeviceStatus = DS_Busy;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)553);//忙
}
void CCmdJmdm::SetErrorStatus()
{
	_DeviceStatus = DS_Error;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)554);//错误
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
//	停止与KDE通讯.
void CCmdJmdm::Stop()
{
	if (!IsStop())
	{	
		SetBusyStatus();

		Run_Start_Reader = false;	//线程通讯变量
		Run_Kde_Main = false;		//线程通讯变量

		if (NULL != CW_Start_Reader)
			WaitForSingleObject(CW_Start_Reader->m_hThread,INFINITE);//等待线程结束
		if (NULL != CW_Kde_Main)
			WaitForSingleObject(CW_Kde_Main->m_hThread,INFINITE);//等待线程结束
		
		delete _RawJmdm;
		_RawJmdm = NULL;
		SetStopStatus();
	}
}
///////////////////////////////////////////////////////////////////////////////////
//	启动与KDE通讯.
bool CCmdJmdm::Start()
{
	Stop();				//Stop first;
	Run_Start_Reader = true;	//线程通讯变量
	Run_Kde_Main = true;		//线程通讯变量
//	this->KDE_EjectCard();
//	this->KDE_EjectCard();
	CW_Start_Reader = AfxBeginThread( &THR_Start_Reader, 0 );	//打开读卡器线程
	ASSERT(NULL != CW_Start_Reader );
	CW_Kde_Main = AfxBeginThread( &THR_Kde_Main, 0 );		//反复检测读卡线程
	ASSERT(NULL != CW_Kde_Main );
	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//打开KDE接口并初始化读卡器线程
UINT CCmdJmdm::THR_Start_Reader(LPVOID)
{
	if (!IsStop()) return 0;
	if (NULL != _RawJmdm) return 0;
	TRACE(_T("启动KDE: 开始\n"));

	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;

//	_RawKde= new CKDE(Peripheral.KdePort());

	_RawJmdm = new CJmdm(Peripheral.KdePort());

	if (!_RawJmdm->OpenDev())
//		if (!_RawKde->KDE_Init())
	{
		SetErrorStatus();		//错误
	}
	else
	{
		SetNormalStatus();		//正常
	}

	TRACE(_T("启动KDE: 结束\n"));
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//	KDE通讯线程.
UINT CCmdJmdm::THR_Kde_Main(LPVOID)
{
	TRACE(_T("检测KDE: 开始\n"));
	Sleep(10);//Give time to initcomm
	
	CSetting::CPeripheral Peripheral = CSetting::Instance()->m_Peripheral;
	
	PATRON CardInfo;//创建读卡缓存.

	while (Run_Kde_Main)
	{
//		Sleep(1000);
		Sleep(Peripheral.KdeThreadStep() );
		if (!Run_Kde_Main) return 1;			//	检测运行标记

		if (WAIT_TIMEOUT == WaitForSingleObject(g_System.m_OprBusyMutex, 0)) 
		{
			Sleep(300);
			continue;	//	操作员忙
		}
	//	int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	操作员闲
	//	ASSERT (TRUE == b);
		//检测KDE读卡器状态
		if (CCmdJmdm::Instance()->KDE_NeedRead())
		{
			SetBusyStatus();
			CCmdJmdm::Instance()->_PollDetectCallBack();
			while(CCmdJmdm::Instance()->KDE_NeedRead())
			{
				Sleep(500);	//等待操作员取卡.
			}
			Sleep(500);	//当一个有效的交易过程完成后的，等待0.5秒后进行下次同样的交易
		}
		else
			Sleep(500);	//UCH -wait a while
	
		int b = ReleaseMutex(g_System.m_OprBusyMutex);			//	操作员闲
		ASSERT (TRUE == b);
	}

	TRACE(_T("检测KDE:结束\n"));
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//                            以下是KDE卡操作的封装                              //
///////////////////////////////////////////////////////////////////////////////////
//票当前位置
BYTE CCmdJmdm::KDE_TicketPos()
{
	if ( IsStop() ) return false;
	BYTE loc = 0;
//	int ret = _RawKde->KDE_GetStatus(loc);
	loc = loc & 0xFA;
	return loc;
}
//移动票
bool CCmdJmdm::KDE_MoveTicket(const short Orgin, const short Dest)
{
		return true;
}

//是否有票在机器内
bool CCmdJmdm::KDE_IsTicketInside()
{
	return FALSE;
}

//检测通讯,检测是否需要读卡
bool CCmdJmdm::KDE_NeedRead()
{
	if ( IsStop() ) return false;

	if(_RawJmdm->IsValidTicket()) return TRUE;
		else return FALSE;
}

bool CCmdJmdm::KDE_ReadTicket(PATRON &CardInfo)
{
	if ( IsStop() ) return false;
	//移动到读卡位置
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

	//试图读卡
	CardInfo._Remark = mem2str(Remark, sizeof(Remark));

	_RawJmdm->ReadTicket(TicketBuf);
	CardInfo._CardNo=TicketBuf;

	return TRUE;
}
//吐卡
void CCmdJmdm::KDE_EjectCard()
{
//	if ( IsStop() ) return ;
//	if ( !KDE_IsTicketInside() ) return;
//	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
//	if ( TRUE == _RawKde->KDE_Operate(POS_ANYWHERE, POS_REJECT, 1, 0, 0, 0 ,0) ) return;
}
//解读卡内信息
bool CCmdJmdm::KDE_Decode(PATRON &CardInfo, char * TicketBuf)	//TicketBuf长度为39
{
	SPECIAL_CARD * Sfmt;	//特殊卡
	HOURLY_CARD * Hfmt;		//普通卡

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
		if (CheckSum != CalculateCSum(TicketBuf)) return false;	//累加和
		SysIdInTicket = mem2short(Sfmt->_SysId, sizeof(Sfmt->_SysId));//系统号
	
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
		if (CheckSum != CalculateCSum(TicketBuf)) return false;	//累加和
		SysIdInTicket = mem2short(Hfmt->_SysId, sizeof(Hfmt->_SysId));//系统号

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
//发布一个特殊卡.
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
	showTip("叫础フ合兵布!", true);

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

		showTip("叫合兵布!", true);
		while(CCmdJmdm::Instance()->KDE_NeedRead())
		{
			Sleep(500);	//等待操作员取卡.
		}
		return res;

	}else return false;

}
//发布一个普通卡
bool CCmdJmdm::KDE_IssueHourlyCard(const CString CardNo, const COleDateTime PayTime, const double PayAmount)
{
	ASSERT(1 < CardNo.GetLength());
	PATRON CardInfo;
	if ( !KDE_ReadTicket(CardInfo) )
	{	//读卡错误
		return false;
	}
	else
	{
		//读卡正确，就比较是否是同一个卡. //???
		if ( (SPECIAL_TICKET == CardInfo._TicketTypeId) && (CardNo != CardInfo._CardNo) )
			return false;
	}
	CardInfo._PayTime = PayTime;
	CardInfo._PayAmount = PayAmount;
	CardInfo._PaymentTimes++;
	CardInfo._PayId = _ttol(CSetting::Instance()->m_Communicate.StationID());
	
	return KDE_WriteTicket(CardInfo);
	
}

//发布卡
bool CCmdJmdm::KDE_WriteTicket(const PATRON &CardInfo)//写票及打印
{

	return true;
}
///////////////////////////////////////////////////////////////////////////////////
//                               以下是辅助功能                                  //
///////////////////////////////////////////////////////////////////////////////////
//Encrypt the ticket info 加密
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

//Decrypt the ticket info 解密
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
{	//将时间改为由当前年起到现在的分钟数
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
{	//将分钟数改为时间
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

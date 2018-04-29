// CmdMntRecv.cpp: implementation of the CCmdMntRecv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Setting.h"
#include "CmdMntSend.h"
#include "CmdMntRecv.h"
#include "CmdOtp.h"
#include "afxsock.h"
#include ".\\dlg\\dlgpayment.h"
extern _System		g_System;
extern CSetting *	g_Setting;
extern CLog *		g_pLog;

#define ID_CMD_TimeSynchronize		19
#define ID_CMD_BaseSystemSetting	23
#define ID_CMD_ReceiptSetting		24
#define ID_CMD_ParkingFee			25
#define ID_CMD_DateParkRate			26
#define ID_CMD_GroupParkRate		27
#define ID_CMD_VehicleParkRate		28
#define ID_CMD_TimezoneParkRate		29
#define ID_CMD_FeeParkRate			30
#define ID_CMD_FixTimeRule			31
#define ID_CMD_PayModeDefinition	32
#define ID_CMD_CardType				33
#define ID_CMD_StationInformation	34
#define ID_CMD_Permission			35
#define ID_CMD_GroupType			39
#define ID_CMD_DiscountPlan			40
#define ID_CMD_RequestOtpXFile		49
#define ID_CMD_OtpMetaFile			50
#define ID_CMD_CloseAccount			52
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool	CCmdMntRecv::_DDAReplyFlag = false;
char 	CCmdMntRecv::_DDAReplyBuf[MAX_COMMAND_LENGTH];
short	CCmdMntRecv::_DDAReplyLen = 0;

CCmdMntRecv* CCmdMntRecv::_instance = 0;

CCmdMntRecv* CCmdMntRecv::Instance()
{
    if (_instance == 0) {
        _instance = new CCmdMntRecv;
    }
    return _instance;
}

CCmdMntRecv::CCmdMntRecv()
{
}

CCmdMntRecv::~CCmdMntRecv()
{
}

UINT RecvFile(LPVOID axx)
{
	//LPCTSTR m_lpFilePath = (LPCTSTR)TempMetaFileName;
	CString dsp;
	CSocket sockRecv;
	CCmdMntSend * pCmdMntSend = CCmdMntSend::Instance();
	if (!sockRecv.Create(6778))
	{
		dsp.Format("Recv File Fail - Create Socket Error!");
		//pCmdMntSend->ErrorWarnNoticeLog(dsp, CCmdMntSend::msg_Error);
		showTip(dsp, true);
		return 0;
	}
	if (!sockRecv.Listen())
	{
		dsp.Format("Recv File Fail - Listen Socket Error!");
		showTip(dsp, true);
		sockRecv.Close();
		return 0;
	}
	int a = 0;
	while (1)//WaitForSingleObject(StopRecvFileEvent.m_hObject, 1)==WAIT_TIMEOUT)
	{
		if (a==0) a ++;
		CSocket sockRecv1;
		if (!sockRecv.Accept(sockRecv1))
		{
			dsp.Format("Recv File Fail - Accept Socket Error!");
			showTip(dsp, true);
			sockRecv1.Close();
			continue;
		}
		CSocketFile socketfile(&sockRecv1);
		CArchive arIn(&socketfile, CArchive::load);
		CFile ff;
		CString strFileName;
		char buf[1024];
		UINT len;
		int counter = 0;
		while (1)
		{
			if (counter == 0) 
			{
				len = arIn.Read(buf, 255);
				if (len < 1)
				{
					dsp.Format("Recv File Fail - File Name Error/Cannot Read!");
					showTip(dsp, true);
					break;
				}
				CString TempMetaFileName = CString(buf);
				CSetting::Instance()->m_OTPRwlSetting.PathMeta(TempMetaFileName);
				strFileName = TempMetaFileName;
				//strFileName = CString(m_lpFilePath) + CString(buf);
				if (!ff.Open(strFileName, CFile::modeWrite | CFile::modeCreate))
				{
					dsp.Format("Recv File Fail - %s File Open Error!", strFileName);
					showTip(dsp, true);
					break;
				}
				counter ++;
				continue;
			}
			len = arIn.Read(buf, 1024);
			if (len > 0) ff.Write(buf, len);
			if (len < 1024)
			{
				ff.Flush();
				ff.Close();
				dsp.Format("Receive File Success - %s ", (LPCTSTR)strFileName);
				showTip(dsp, true);
				break;
			}
		}
		socketfile.Close();
		arIn.Close();
		sockRecv1.Close();
	}
	dsp.Format("Stop receiving any files!");
	showTip(dsp, true);
	sockRecv.Close();
	return 1;
}


///////////////////////////////////////////////////////////////////////////////////
//	试图启动与管理站通讯(接收部分)
bool CCmdMntRecv::Start()
{	//开始监听
	AfxGetApp()->BeginWaitCursor();
	TRACE(_T("Comm With Management Receive: Start \n"));
	CString info;
	bool status = false;
	if(m_zzServer.CreateServer(CSetting::Instance()->m_Communicate.RecvSocketPort(), SOMAXCONN))
	{
		status = (TRUE == m_zzServer.StartServer(ReceiveCmd)) ? true : false;
	}
	if(status)
	{	//success
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), _T("Socket Listen start Successful."));
	}
	else
	{	//error
		info.Format("Socket Listen start Error: %d", m_zzServer.err);
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_SYSTEM), info);
	}
	TRACE(_T("Comm With Management Receive: Exit \n"));

	TRACE(_T("Setup the file receiving channel"));

	AfxBeginThread( &RecvFile, 0 );
	AfxGetApp()->EndWaitCursor();
	return status;
}
///////////////////////////////////////////////////////////////////////////////////
//	试图停止与管理站通讯
void CCmdMntRecv::Stop()
{
	m_zzServer.CloseServer();
}
///////////////////////////////////////////////////////////////////////////////////
//	接收回调函数
void CALLBACK CCmdMntRecv::ReceiveCmd(SOCKET s, int ServerPort, const char *ClientIP)
{
	CString info;
	char CmdBuf[MAX_COMMAND_LENGTH];
	CZZSocket wsk;
	wsk = s;
	TRACE("R read\n\n");
	int Ret = wsk.ReadData(CmdBuf, MAX_COMMAND_LENGTH, 0);
	if(0 >= Ret)
	{
		info.Format("recv error: %d", Ret);
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), info);
	}
	else
	{
		#ifdef _DEBUG
			info.Format("recv successful: %d", Ret);
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), info);
		#endif
		CmdBuf[Ret] = '\0';
		ReceiveCmd(CmdBuf, static_cast<short>(Ret));	//调用命令分派函数
		SendDDAReply(wsk);//
	}
	wsk.Close();
}
///////////////////////////////////////////////////////////////////////////////////
#define RECV_CMD(CMD_NAME)	\
	void CCmdMntRecv::On_##CMD_NAME(const char * CmdBuf, const short CmdLen){	\
	_STRUCT_##CMD_NAME cmd; cmd.Perform(CmdBuf, CmdLen);}

RECV_CMD(GroupParkRate)
RECV_CMD(VehicleParkRate)
RECV_CMD(TimezoneParkRate)
RECV_CMD(FeeParkRate)
RECV_CMD(FixTimeRule)
RECV_CMD(DateParkRate)
RECV_CMD(CardType)
RECV_CMD(TimeSynchronize)
RECV_CMD(ReceiptSetting)
RECV_CMD(StationInformation)
RECV_CMD(Permission)
RECV_CMD(PayModeDefinition)
RECV_CMD(BaseSystemSetting)
RECV_CMD(ParkingFee)
RECV_CMD(GroupType)
RECV_CMD(DiscountPlan)
RECV_CMD(RequestOtpXFile)
RECV_CMD(OtpMetaFile)
RECV_CMD(CloseAccount)

///////////////////////////////////////////////////////////////////////////////////
void CCmdMntRecv::ReceiveCmd(const char * CmdBuf, const short CmdLen)
{
	CCmdMntRecv * cmd;
	CString info;
	info.Empty();
	//获取命令编码
	cmd = new(CCmdMntRecv);
	int icmdID = cmd->PreDecodeData(CmdBuf, CmdLen);
	delete cmd;

#define CASE(CMD) \
	case ID_CMD_##CMD: cmd->On_##CMD(CmdBuf, CmdLen);\
	break;

	switch(icmdID)
	{
	case  0://空命令
		break;
	CASE(TimeSynchronize)		//时间同步命令
	CASE(BaseSystemSetting)		//基本系统设置
	CASE(ReceiptSetting)		//接受打印设置
	CASE(ParkingFee)			//收费基本设置
	CASE(DateParkRate)			//收费标准,根据"日期"分别
	CASE(GroupParkRate)			//收费标准,根据"分组"分别
	CASE(VehicleParkRate)		//收费标准,根据"车辆"分别
	CASE(TimezoneParkRate)		//收费标准,根据"时间段"分别
	CASE(FeeParkRate)			//收费标准
	CASE(FixTimeRule)			//补充规定
	CASE(PayModeDefinition)		//收款台收费模式
	CASE(CardType)				//收费卡种类设定
	CASE(StationInformation)	//改变cashier系统设置
	CASE(Permission)			//功能开放程度
	CASE(GroupType)				//用户分组
	CASE(DiscountPlan)			//打折计划
	CASE(RequestOtpXFile)		//请求发送八达通交换文件
	CASE(OtpMetaFile)			//八达通meta文件
	CASE(CloseAccount)//CLOSE ACCOUNT
	default://错误
		info.Format("Recv data format error.");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), info);
	}	
}

///////////////////////////////////////////////////////////////////////////////////
BOOL CCmdMntRecv::_header::IsValidDateTime()
{
	FILETIME ft;
	SYSTEMTIME st;
	char szTemp[3];
	LPTSTR lpszBuf = Time;

	ZeroMemory(&st,sizeof(st));

	lstrcpyn(szTemp,lpszBuf+6,3);//hour
	if(atoi(szTemp)>23)return FALSE;

	lstrcpyn(szTemp,lpszBuf+8,3);//minute
	if(atoi(szTemp)>59)return FALSE;

	lstrcpyn(szTemp,lpszBuf+10,3);//second
	if(atoi(szTemp)>59)return FALSE;

	lstrcpyn(szTemp,lpszBuf,3);
	st.wYear=2000+atoi(szTemp);	//year

	lstrcpyn(szTemp,lpszBuf+2,3);
	st.wMonth=atoi(szTemp);		//month

	lstrcpyn(szTemp,lpszBuf+4,3);
	st.wDay=atoi(szTemp);		//day

	return SystemTimeToFileTime(&st,&ft);
}

/////////////////////////////////////////////////////////////////////////////
int CCmdMntRecv::PreDecodeData(const char * CmdBuf, const short CmdLen)
{
	_header header;
	memcpy(&header, CmdBuf, sizeof(header));

	CSetting * pSetting = CSetting::Instance();
	if (0 != memcmp(header.DestAddr, pSetting->m_Communicate.StationID(), sizeof(header.DestAddr))) return -1;
	if (0 != memcmp(header.SourceAddr, pSetting->m_Communicate.ManagementID(), sizeof(header.SourceAddr))) return -1;
	if (!header.IsValidDateTime()) return -1;	//报头时间格式错误
	if (header.GetLength() + sizeof(_header) + sizeof(_tial) != CmdLen) return -1; //检验包长度
	if (ttt__ETX != CmdBuf[CmdLen-1]) return -1;			//报尾错误
	return header.GetCommandID();
}
/////////////////////////////////////////////////////////////////////////////////////

void CCmdMntRecv::_RecvBaseCmd::SendReply(short CmdId, CString Reason/* = ""*/, bool IsSuccessful/* = true*/, char Priority/*=1*/, char DDAMode/*=0*/, char NeedReply/*=0*/, char IsReply/*=1*/)
{
	//generate property string
	struct Property_Format
	{
		char _CmdId[3];
		char _Priority;
		char _DDAMode;
		char _NeedReply;
		char _IsReply;
	} fmt;
	short2mem(CmdId, fmt._CmdId, sizeof(fmt._CmdId));
	if (' ' == fmt._CmdId[0]) fmt._CmdId[0] = '0';
	if (' ' == fmt._CmdId[1]) fmt._CmdId[1] = '0';
//	if (' ' == fmt._CmdId[2]) fmt._CmdId[2] = '0'; no need

	fmt._Priority	= Priority;
	fmt._DDAMode	= DDAMode;
	fmt._NeedReply	= NeedReply;
	fmt._IsReply	= IsReply;

	CCmdMntSend * pCmdSend = CCmdMntSend::Instance();
	if ('0' == fmt._DDAMode)
	{
		pCmdSend->Reply((char *)&fmt, IsSuccessful, Reason);//failure
	}
	else
	{
		char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
		short BodyLen;
		if (CmdId == ID_CMD_CloseAccount)
		{//no successful indicator
			BodyLen = Reason.GetLength();
			//header
			pCmdSend->EncodeSendHeader(CmdBuf, (char *)&fmt, BodyLen);
			memcpy(CmdBuf+sizeof(CCmdMntSend::HHEADER), Reason, Reason.GetLength());
			//tial
			pCmdSend->EncodeSendTial(CmdBuf + sizeof(CCmdMntSend::HHEADER) + BodyLen);
			SetDDAReply(CmdBuf, sizeof(CCmdMntSend::HHEADER) + BodyLen + sizeof(CCmdMntSend::HTIAL));
			return;
		}
		BodyLen = Reason.GetLength() + 1;//IsSuccessful + Reason
		//header
		pCmdSend->EncodeSendHeader(CmdBuf, (char *)&fmt, BodyLen);
		//body
		bool2mem(IsSuccessful, *(CmdBuf+sizeof(CCmdMntSend::HHEADER)));
		memcpy(CmdBuf+sizeof(CCmdMntSend::HHEADER)+1, Reason, Reason.GetLength());
		//tial
		pCmdSend->EncodeSendTial(CmdBuf + sizeof(CCmdMntSend::HHEADER) + BodyLen);
		SetDDAReply(CmdBuf, sizeof(CCmdMntSend::HHEADER) + BodyLen + sizeof(CCmdMntSend::HTIAL));
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//"日期"收费标准
void CCmdMntRecv::_STRUCT_DateParkRate::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Date park rate>."));
	//添加数据
	g_Setting->m_DateRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_DateParkRate);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Date park rate success reply>."));
}
/////////////////////////////////////////////////////////////////////////////////////
//"分组"收费标准
void CCmdMntRecv::_STRUCT_GroupParkRate::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Group park rate>."));
	//添加数据
	g_Setting->m_GroupRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_GroupParkRate);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Group park rate success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//"车辆"收费标准
void CCmdMntRecv::_STRUCT_VehicleParkRate::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Vehicle park rate>."));
	//添加数据
	g_Setting->m_CarRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_VehicleParkRate);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Vehicle park rate success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//收费标准,根据"时间段"分别
void CCmdMntRecv::_STRUCT_TimezoneParkRate::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Timezone park rate>."));
	//添加数据
	g_Setting->m_TimeZoneRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_TimezoneParkRate);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Timezone park rate success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//收费标准
void CCmdMntRecv::_STRUCT_FeeParkRate::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Fee park rate>."));
	//添加数据
	g_Setting->m_UnitRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_FeeParkRate);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Fee park rate success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//补充规定
void CCmdMntRecv::_STRUCT_FixTimeRule::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <FixTime park rate>."));
	//添加数据
	g_Setting->m_FixRule.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_FixTimeRule);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <FixTime park rate success reply>."));
};
////////////////////////////////////////////////////////////////////////////
//时间同步
void CCmdMntRecv::_STRUCT_TimeSynchronize::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Time Synchronize>."));
	_header header;
	memcpy(&header, CmdBuf, sizeof(header));
	//执行这个命令
	char buf[3];
		buf[3] = '\0';
	SYSTEMTIME ST;
		memcpy(buf, header.Time, 2);
		ST.wYear = atoi(buf)+2000;		//can use in 2000~2099;
		memcpy(buf, header.Time+2, 2);
		ST.wMonth = atoi(buf);
		memcpy(buf, header.Time+4, 2);
		ST.wDay = atoi(buf);
		memcpy(buf, header.Time+6, 2);
		int nHour = atoi(buf);
	//	if (nHour > 8) {nHour -= 8; }
//		else {nHour += 16; ST.wDay --;}
		ST.wHour = nHour;//(nHour>8? nHour-8: nHour+16);
		memcpy(buf, header.Time+8, 2);
		ST.wMinute = atoi(buf);
		memcpy(buf, header.Time+10, 2);
		ST.wSecond = atoi(buf);
		ST.wMilliseconds = 0;
	CString info, sTimeBefore = CTime::GetCurrentTime().Format("%y%m%d%H%M%S");
	if (SetLocalTime(&ST)){//SystemTime(&ST)){//改变时钟
		SendReply(ID_CMD_TimeSynchronize);
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Time Synchronize success reply>."));
	}
	else
	{
		SendReply(ID_CMD_TimeSynchronize, "Try Synchronize Time Failure.");
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Time Synchronize failure reply>."));
	};
}
/////////////////////////////////////////////////////////////////////////////////////
//收费卡种类设定
void CCmdMntRecv::_STRUCT_CardType::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Card Category Setting>."));
	//添加数据
	g_Setting->m_CardType.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_CardType);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Card Category Setting success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//发票格式设定
void CCmdMntRecv::_STRUCT_ReceiptSetting::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Receipt Setting>."));
	//添加数据
	g_Setting->m_Receipt.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_ReceiptSetting);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Receipt Setting success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//改变cashier系统设置
void CCmdMntRecv::_STRUCT_StationInformation::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Station Information>."));
	//添加数据
	g_Setting->m_StationInformation.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_StationInformation);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Station Information success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//功能开放程度
void CCmdMntRecv::_STRUCT_Permission::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Function Permission>."));
	//添加数据
	g_Setting->m_Permission.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_Permission);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Function Permission success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//收款台收费模式
void CCmdMntRecv::_STRUCT_PayModeDefinition::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Pay Mode Definition>."));
	//添加数据
	g_Setting->m_PayModeDefinition.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_PayModeDefinition);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Pay Mode Definition success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//  收款台收费模式
void CCmdMntRecv::_STRUCT_BaseSystemSetting::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Base System Setting>."));
	//添加数据
	g_Setting->m_BaseSystemSetting.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_BaseSystemSetting);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Base System Setting success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//  收费基本设置
void CCmdMntRecv::_STRUCT_ParkingFee::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Parking Fee Setting>."));
	//添加数据
	g_Setting->m_ParkingFee.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_ParkingFee);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Parking Fee Setting success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//  用户分组
void CCmdMntRecv::_STRUCT_GroupType::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Group Setting>."));
	//	保存数据
	g_Setting->m_GroupType.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//	响应
	SendReply(ID_CMD_GroupType);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Group Setting success reply>."));
};
/////////////////////////////////////////////////////////////////////////////////////
//  打折计划
void CCmdMntRecv::_STRUCT_DiscountPlan::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Discount Plan Setting>."));
	//添加数据
	g_Setting->m_DiscountPlan.StoreAndAssign(CmdBuf + sizeof(_header), CmdLen);
	//响应
	SendReply(ID_CMD_DiscountPlan);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Discount Plan Setting success reply>."));
};

/////////////////////////////////////////////////////////////////////////////////////
//  请求发送八达通交换文件.
void CCmdMntRecv::_STRUCT_RequestOtpXFile::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Request Octopus exchange files>."));
	//响应
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Request Octopus exchange files success reply>."));
	//执行请求
	CCmdMntSend * pCmdMntSend = CCmdMntSend::Instance();
	pCmdMntSend->ErrorWarnNoticeLog("OTPXFile Process Begin.", CCmdMntSend::msg_Notice);
	pCmdMntSend->UploadOtpXFile();

//	SendReply(ID_CMD_RequestOtpXFile, "OTPXFile Process Begin.");
};
/////////////////////////////////////////////////////////////////////////////////////
//  收到八达通meta文件.
void CCmdMntRecv::_STRUCT_OtpMetaFile::Perform(const char *CmdBuf, const short CmdLen)
{
	ASSERT(CmdBuf != NULL);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Otp Meta File>."));
	//检测是否有同名文件存在
	CString dsp;
	if (!CCmdOtp::Instance()->OTP_HouseKeeping())
	{
		dsp.Format("ERR: OTP Housekeeping Error! - (%s)", CCmdOtp::Instance()->Translate());
		CCmdMntSend::Instance()->ErrorWarnNoticeLog(dsp, CCmdMntSend::msg_Error);
		showTip(dsp, true);
//		OtpErrProcess();
	}
	else
	{
/*		WIN32_FIND_DATA FindFileData;
		CString path = CSetting::Instance()->m_OTPRwlSetting.PathLib();
		CString xfilename = path + "\\*.*";
		CString FileName;
		HANDLE hFind = FindFirstFile((LPCTSTR)xfilename, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE) {
			do{
				FileName = path +"\\" + FindFileData.cFileName;
				DeleteFile(FileName);
			} while (FindNextFile(hFind, &FindFileData));
		}*/
		showTip("House Keeping Succeed!", true);
		CCmdMntSend::Instance()->ErrorWarnNoticeLog("House Keeping Succeed!", CCmdMntSend::msg_Notice);
	}
	//执行请求 + 响应
/*	if ( Decode(CmdBuf + sizeof(_header), CmdLen - sizeof(_header) - sizeof(_tial)) )
	{
		SendReply(ID_CMD_OtpMetaFile, "", true, '1', '1');		//成功
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Otp Meta File success reply>."));
	}
	else
	{
		SendReply(ID_CMD_OtpMetaFile, "", false, '1', '1');		//失败
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Otp Meta File failure reply>."));
	}
*/
};
/*
bool CCmdMntRecv::_STRUCT_OtpMetaFile::Decode(const char * Recv, const short RecvLen)
{
	const short MaxBlockLength = 3800;

	struct String_Format
	{
		char		_FileName[24];
		char		_BlockId[4];
		char		_TotalBlockId[4];
	} fmt;
	memcpy(&fmt, Recv, sizeof(fmt));
	CString MetaFileName= mem2str(	fmt._FileName,		sizeof(fmt._FileName) );
	MetaFileName.TrimLeft(' ');
	MetaFileName.TrimRight(' ');
	short BlockId		= mem2short(fmt._BlockId,		sizeof(fmt._BlockId) );
	short TotalBlockId	= mem2short(fmt._TotalBlockId,	sizeof(fmt._TotalBlockId) );
	short BlockLen		= RecvLen - sizeof(fmt);

	CString TempMetaFileName = '~' + MetaFileName;

	CFileException e;
	CFile TempMetaFile;

	//获得相应路径
	if (!CSetting::Instance()->m_OTPRwlSetting.PathMeta(TempMetaFileName))
		return false;

	if (0 == BlockId)
	{
		if (!TempMetaFile.Open(TempMetaFileName, CFile::modeReadWrite| CFile::modeCreate, &e))
		{//尝试创建文件
			return false;
		}
	}
	else
	{
		if (!TempMetaFile.Open(TempMetaFileName, CFile::modeReadWrite| CFile::shareDenyWrite, &e))
		{//尝试打开文件
			return false;
		}
	}

	UINT Pos = TempMetaFile.Seek(BlockId * MaxBlockLength, CFile::begin);
	if (Pos != BlockId * MaxBlockLength)
		return false;

	TempMetaFile.Write(Recv + sizeof(fmt), BlockLen);
	TempMetaFile.Flush();
	TempMetaFile.Close();

	
	if (BlockId == TotalBlockId)
	{
		//获得相应路径
		if (!CSetting::Instance()->m_OTPRwlSetting.PathMeta(MetaFileName))
			return false;
		TRY
		{
			CFile::Remove( MetaFileName );
		}
		CATCH( CFileException, e )
		{
			;
		}
		END_CATCH

		TRY
		{
			CFile::Rename( TempMetaFileName, MetaFileName );
		}
		CATCH( CFileException, e )
		{
			return false;
		}
		END_CATCH
	}
	return true;
}
*/

void CCmdMntRecv::_STRUCT_CloseAccount::Perform(const char *CmdBuf, const short CmdLen)
{
	CString x;
	CSetting * pSetting = CSetting::Instance();
	long a[9]; 
	long b, c;
	double cash, otp, sv, ad, sc, tot, tcm;
	::SendMessage( g_System.RunTime.hOtpPaymentDlg,IDC_CLOSEACCOUNT1,0,0);
	Sleep(1000);
	pSetting->m_Account.GetTotalAccount(tot, cash, otp, sv, a, tcm);
	pSetting->m_Account.GetOtherInfo(ad, b, sc, c);
	x.Format("%08.0f%08.0f%08.0f%06d%06d%06d%06d%06d%06d%06d%06d%08.0f%08.0f%06d%06d",
			  cash*100, otp*100, sv*100, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], ad*100, sc*100, b, c);
	SendReply(ID_CMD_CloseAccount, x, true, '1', '1');
	pSetting->m_Account.CloseAcc();
//	CDlgPayment::AddAccountLog();
}

void CCmdMntRecv::SendDDAReply(CZZSocket &wsk)
{
	if ((false!=_DDAReplyFlag)	&& (0 < _DDAReplyLen))
	{
		wsk.SendData(_DDAReplyBuf, _DDAReplyLen, 3);
		_DDAReplyFlag = false;
		_DDAReplyLen = 0;
	}
}

void CCmdMntRecv::SetDDAReply(char *CmdBuf, short CmdLen)
{
	ASSERT(NULL != CmdBuf);
	_DDAReplyFlag = true;
	memcpy(_DDAReplyBuf, CmdBuf, CmdLen);
	_DDAReplyLen = CmdLen;
}
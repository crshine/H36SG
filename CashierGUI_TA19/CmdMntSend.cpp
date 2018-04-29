// CmdMntSend.cpp: implementation of the CCmdMntSend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "Setting.h"
#include "CmdOtp.h"
#include "CmdBuffer.h"
#include "CmdMntSend.h"
#include "afxsock.h"
extern _System		g_System;
extern CLog *		g_pLog;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 
/*	命令属性串
 *	command property string
 *      CMDID Priority DDAMode NeedReply IsReply
 *        3       1	      1        1        1     (char)
 */

#define PROPERTY_CMD_Ping				"0001000"
#define PROPERTY_CMD_Payment			"0131000"
#define PROPERTY_CMD_FinancialMaintain	"0141000"
#define PROPERTY_CMD_OperatorActionLog	"0161000"
#define PROPERTY_CMD_ErrorWarnNoticeLog	"0171000"
#define PROPERTY_CMD_TimeSynchronize	"0181000"
#define PROPERTY_CMD_NonParkingPayment	"0201000"
#define PROPERTY_CMD_OperatorQuery		"0374110"
#define PROPERTY_CMD_CardStatusQuery	"0385110"

#define PROPERTY_CMD_UploadOtpXFile		"0501110"
#define PROPERTY_CMD_OtpXFileReply		"0491001"
#define PROPERTY_CMD_TransQuery			"0535110"
#define PROPERTY_CMD_UpdateTrans		"0541000"
#define PROPERTY_CMD_AddValue			"0551000"
#define	PROPERTY_CMD_CreateHolder		"0571000"
#define	PROPERTY_CMD_CreateSpecCard		"0561000"
#define PROPERTY_CMD_HolderInfoQuery	"0585110"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char	CCmdMntSend::CONST_CHAR_TRUE	= '1'; //用字符表示真   real
const char	CCmdMntSend::CONST_CHAR_FALSE	= '0'; //用字符表示假   virtural

const SHORT CCmdMntSend::SUCCESSFUL		= -1000;//	if (result < CCmdMntSend::SUCCESSFUL) there have some error!
const SHORT CCmdMntSend::ERROR_RESPONSE	= -1001;
const SHORT CCmdMntSend::TIME_OUT		= -1002;
const SHORT CCmdMntSend::ERROR_HEADER	= -1003;
const SHORT CCmdMntSend::ERROR_TIAL		= -1004;
const SHORT CCmdMntSend::ERROR_BODY		= -1005;

const char	CCmdMntSend::CONST_STX		= 0x02;	//开始位	start bit
const char	CCmdMntSend::CONST_ETX		= 0x03;	//停止位	stop bit

bool		CCmdMntSend::m_ThrRun		= false;		//线程执行	Thread run

CCmdMntSend::CommStatus CCmdMntSend::_CommStatus = CCmdMntSend::CS_Normal;

ULONG CCmdMntSend::_InvalidConnectionTimes = 0;	//无效连接次数	Times of failure connection

CCmdMntSend* CCmdMntSend::_instance = 0;

CCmdMntSend* CCmdMntSend::Instance()
{
    if (_instance == 0) {
        _instance = new CCmdMntSend;
    }
    return _instance;
}

CCmdMntSend::CCmdMntSend()
{
	m_ThrHandle = NULL;
	m_dwJustRestore = 0;
	m_SendCmdMutex = CreateMutex(NULL, FALSE, NULL);
}

CCmdMntSend::~CCmdMntSend()
{
	Stop();
	CCmdBuffer * _pCmdBuffer = CCmdBuffer::Instance();
	delete _pCmdBuffer;
}

////////////////////////////////////////
// Send a file to the management station via the CArchive and CScoket channel
// can be used to send x file
UINT CCmdMntSend::SendFile(LPCTSTR FileName)
{
	CString dsp;
	CSocket sockSend;
	CCmdMntSend * pCmdMntSend = CCmdMntSend::Instance();
	if (!sockSend.Create())
	{
		dsp.Format("Send File Fail - %s Create Socket Error!", FileName);
		showTip(dsp, true);
		return 0;
	}
	if (!sockSend.Connect(CSetting::Instance()->m_Communicate.ManagementIP(), 6779))
	{
		dsp.Format("Send File Fail - %s Socket Connect Error!", FileName);
		showTip(dsp, true);
		sockSend.Close();
		return 0;
	}
	CSocketFile file(&sockSend);
	CArchive arOut(&file, CArchive::store);
	CFile ff;
	DWORD len;
	char buf[1024];
	CString FileNamea = FileName;
	CString FileNameOnly = FileNamea.Mid(FileNamea.ReverseFind(TCHAR('\\'))+1);
	if (!ff.Open(FileName, CFile::modeRead)) 
	{
		arOut.Close();
		sockSend.Close();
		file.Close();
		dsp.Format("Send File Fail - %s File Open Error!", FileName);
		showTip(dsp, true);
		return 0;
	}

	int icount  =0;
	do {
		if (icount==0)
		{
			memset(buf, 0, 1024);
			memcpy(buf, FileNameOnly.GetBuffer(255), FileNameOnly.GetLength());
			arOut.Write(buf, 255);
			arOut.Flush();
			icount ++;
			continue;
		}
		len = ff.Read(buf, 1024);
		if (len > 0) 
		{
			arOut.Write(buf, len);
			arOut.Flush();
		}
		if (len < 1024)
		{
			ff.Close();
			dsp.Format("Send File Successful - %s!", FileName);
			showTip(dsp, true);
			break;
		}
	} while (1);
	arOut.Close();
	file.Close();
	sockSend.Close();
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
//                          保持或检测当前状态信息                         //
// Keep or Check the existing status signal
/////////////////////////////////////////////////////////////////////////////
void CCmdMntSend::SetStopStatus()
{
	_CommStatus = CS_Stop;
	_InvalidConnectionTimes = 0;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)155);//停止
}
void CCmdMntSend::SetNormalStatus()
{
	_CommStatus = CS_Normal;
	_InvalidConnectionTimes = 0;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)255);//空闲
}
void CCmdMntSend::SetBusyStatus()
{
	_CommStatus = CS_Busy;
	::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)355);//忙
}
void CCmdMntSend::SetErrorStatus()
{
	const short ConfirmInvalid = 5;	//错误小于五次就算连接上了.   Error < 5 times = connection success
	_InvalidConnectionTimes++;
	if (ConfirmInvalid < _InvalidConnectionTimes)
	{
		_CommStatus = CS_Error;
		::PostMessage(g_System.RunTime.hMainFrame, WM_USER_SETCOMMSTATUS, (WPARAM)NULL, (LPARAM)455);//错误 error
	}
}
bool CCmdMntSend::IsNormal()
{
	return (CS_Normal == _CommStatus);
}
bool CCmdMntSend::IsStop()
{
	return (CS_Stop == _CommStatus);
}
///////////////////////////////////////////////////////////////////////////////////
//	启动与管理站通讯(发送部分), 用于缓充机制和状态检测.
//
//    币笆籔恨瞶硄癟(祇癳场だ), ノ絯诀㎝篈浪代.
bool CCmdMntSend::Start()
{
	AfxGetApp()->BeginWaitCursor();
//	Stop();		//Stop first;
	m_ThrRun = true;
	CWinThread* cw = AfxBeginThread( &thrSendCmd, 0 );
	if (cw == NULL)
	{
		m_ThrHandle = NULL;
		m_ThrId = 0;
		m_ThrRun = false;
	}
	else
	{
		m_ThrHandle = cw->m_hThread;
		m_ThrId = cw->m_nThreadID;
		m_ThrRun = true;
	}
	AfxGetApp()->EndWaitCursor();
	return m_ThrRun;
}
///////////////////////////////////////////////////////////////////////////////////
//	停止与管理站通讯(发送部分)
//
//  Stop communication with management(Sending)
void CCmdMntSend::Stop()
{
	AfxGetApp()->BeginWaitCursor();
	if (!IsStop())
	{
		SetBusyStatus();
		m_ThrRun = false;	//线程通讯变量
		if (NULL != m_ThrHandle)
			WaitForSingleObject(m_ThrHandle, INFINITE);
		m_ThrHandle = NULL;
		SetStopStatus();
	}
	AfxGetApp()->EndWaitCursor();
}

///////////////////////////////////////////////////////////////////////////////////
//	发送命令线程
//
//  Command Send Thread
UINT CCmdMntSend::thrSendCmd(LPVOID)
{
	TRACE(_T("Comm With Management Receive Send: Start \n"));
	DWORD LastTick = GetTickCount();
	// Main loop
	CCmdMntSend* pCmd = CCmdMntSend::Instance();
	while (pCmd->m_ThrRun)
	{
		Sleep(CSetting::Instance()->m_Communicate.SendThreadStep());
		pCmd->SendBufCmd();
		if (GetTickCount() - LastTick > 6000000)
		{
			pCmd->SendCurrentExistXFiles();
			LastTick = GetTickCount();
		}
		Sleep(1);


	} // while
	TRACE(_T("Comm With Management Receive Send: Exit \n"));
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//  缓冲机制
//	当命令不可丢失时, 使用本缓冲机制
//
//  絯侥诀
//	讽㏑ぃメア, ㄏノセ絯侥诀
////////////////////////////////////////////////////////////////////////////////
void CCmdMntSend::SendBufCmd()
{
	short CmdLen = 0;
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];//发送命令存储	  save command sending

	WaitForSingleObject(m_SendCmdMutex, INFINITE);	//与非缓冲同步   籔獶絯侥˙
	bool orgstate = IsNormal();
	//if ( !IsNormal() )	//通讯出现问题就发送ping测试	//硄癟瞷拜肈碞祇癳ping代刚
	{
		EncodePing(CmdBuf, CmdLen);//发送空命令		Send a null command
		SendCmd(CmdBuf, CmdLen);
	}

	if (!orgstate && IsNormal())//just restore the communication
		m_dwJustRestore = GetTickCount();
	
	if (!GetBufCmd(CmdBuf, CmdLen))	//获取命令	get the command
	{
		EncodePing(CmdBuf, CmdLen); //发送空命令	send a null command
		SendCmd(CmdBuf, CmdLen);
		ReleaseMutex(m_SendCmdMutex);
		return;
	}
	DWORD x = GetTickCount();
	if ((m_dwJustRestore > 100) && (x - m_dwJustRestore < 120000))//all the unsend msg will not be sent till 40 secs later
	{
		if (CmdBuf[5] == '0' && CmdBuf[6] == '1' && CmdBuf[7] == '3') 
		{
			DelBufCmd();
			AddBufCmd(CmdBuf, CmdLen);
			Sleep(500);
			ReleaseMutex(m_SendCmdMutex);
			return;
		}
	}
	else m_dwJustRestore = 0;


	if (PatchBufCmd(CmdBuf, CmdLen))	//将需要修改的命令补全.//盢惠璶э㏑干.
	{//发送成功                      //祇癳Θ
		DelBufCmd();//删除命令.      //埃㏑.
	}
	else
	{
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), _T("Send buffer command error! Auto retry."));
		EncodePing(CmdBuf, CmdLen);//发送空命令    send a null command
		SendCmd(CmdBuf, CmdLen);
	}
	ReleaseMutex(m_SendCmdMutex);
}
void CCmdMntSend::AddBufCmd(const char *CmdBuf, const int CmdLen)
{
	CCmdBuffer * _pCmdBuffer = CCmdBuffer::Instance();
	_pCmdBuffer->AddCmd(CmdBuf, CmdLen);
}
bool CCmdMntSend::GetBufCmd(char *CmdBuf, short &CmdLen)
{
	CCmdBuffer * _pCmdBuffer = CCmdBuffer::Instance();
	return _pCmdBuffer->GetCmd(CmdBuf, CmdLen);
}
bool CCmdMntSend::PatchBufCmd(char *CmdBuf, short CmdLen)
{
	ASSERT( (NULL != CmdBuf) && (0 < CmdLen));
	ASSERT( !(MAX_COMMAND_BUF_LENGTH < CmdLen) );

/*	if (0 == memcmp(CmdBuf, PROPERTY_CMD_UploadOtpXFile, 7))
	{
		HUPLOADOTPXFILEBUF UploadOtpXFileBuf;
		memcpy(&UploadOtpXFileBuf, CmdBuf, sizeof(UploadOtpXFileBuf));
		return UploadOtpXFile( UploadOtpXFileBuf, CmdBuf, CmdLen );
	}*/
	bool ret = SendCmd(CmdBuf, CmdLen);
	return ret;
}
void CCmdMntSend::DelBufCmd()
{
	CCmdBuffer * _pCmdBuffer = CCmdBuffer::Instance();
	_pCmdBuffer->DelCmd();
}
////////////////////////////////////////////////////////////////////////////////////////
//	发送同步命令(不使用缓冲机制,直接发送)
//
//  祇癳˙㏑(ぃㄏノ絯侥诀,钡祇癳)
//
bool CCmdMntSend::SendCmd(const char *CmdBuf, const short CmdLen)
{
	ASSERT( (NULL != CmdBuf) && (0 < CmdLen));
	ASSERT( !(MAX_COMMAND_BUF_LENGTH < CmdLen) );

	if ( MAX_COMMAND_BUF_LENGTH < CmdLen ) return false;//检测缓冲长度
														//浪代絯侥
	if ( !m_ThrRun )
	{
		SetStopStatus();
		return false;//如果缓冲线程不执行,那么就都不执行
				   	 //  狦絯侥絬祘ぃ磅︽,ê或碞常ぃ磅︽
	}

	CString info;
	_InvalidConnectionTimes++;	//假设这次发送不成功
								//安砞硂Ω祇癳ぃΘ
	//连接
	//硈钡
					 // CZZSocket
	BOOL m_bConnected = m_zzClient.Connection( CSetting::Instance()->m_Communicate.ManagementIP(), 
											   CSetting::Instance()->m_Communicate.SendSocketPort() );
	if( !m_bConnected )
	{
		SetErrorStatus();
		return false;
	}
	
	//发送
    //祇癳
	int nRet = m_zzClient.SendData(CmdBuf, CmdLen, 3);
	if( nRet!=CmdLen )
	{	//失败
		//ア毖
		SetErrorStatus();
		return false;
	}

	//成功
	//Θ
	SetNormalStatus();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////
//	发送同步命令(不使用缓冲机制,直接发送)
//		
//		使用输入参数DataLen,来发送CmdBuf中的数据.
//		将返回结果传回CmdBuf;
//
//	祇癳˙㏑(ぃㄏノ絯侥诀,钡祇癳)
//		
//		ㄏノ块把计DataLen,ㄓ祇癳CmdBufい戈.
//		盢挡狦肚CmdBuf;
//

bool CCmdMntSend::SendCmdSync(char *CmdBuf, short CmdLen)
{
	ASSERT( (NULL != CmdBuf) && (0 < CmdLen));
	ASSERT( !(MAX_COMMAND_BUF_LENGTH < CmdLen) );
	if (MAX_COMMAND_BUF_LENGTH < CmdLen) return false;  //检测缓冲长度
														//浪代絯侥

	//发送数据
	//祇癳计沮
    //       
	//      _||_
	//      \  /
	//       \/
	if ( !SendCmd(CmdBuf,CmdLen) ) return false;
	CString Temp;
	Temp.Format("TickCount: %d", GetTickCount());
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), "SendOk " + Temp);
	//接受数据
	//钡计沮
	memset( CmdBuf, '\0', sizeof(HHEADER));			//清空缓冲	//睲絯侥
    
	//            _||_
	//            \  /
	//             \/
	int nRet = m_zzClient.ReadData(CmdBuf, MAX_COMMAND_BUF_LENGTH, 5);
		
	ASSERT( !(MAX_COMMAND_BUF_LENGTH < nRet) );
	if (MAX_COMMAND_BUF_LENGTH < nRet) return false;//检测缓冲长度	浪代絯侥

	if(0 >= nRet)
	{	//失败	//ア毖
		Temp.Format("TickCount: %d", GetTickCount());
		g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), "RecvError " + Temp);

		#ifdef _DEBUG
			CString info;
			info.Format("Debug: Recv from MNT Err: %d", m_zzClient.err);
			g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_ERROR), info);
		#endif
		SetErrorStatus();
		return false;
	}
	Temp.Format("TickCount: %d", GetTickCount());
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_DETAIL), "RecvOK " + Temp);

	//成功
	//Θ
	CmdBuf[nRet] = '\0';			//接受到的数据改为相应的字符串,如果有'\0'在中间就会为非法的数据。
									//钡戈э莱﹃,狦Τ'\0'い丁碞穦獶猭计沮
	SetNormalStatus();
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
//	通讯故障提示
int CCmdMntSend::ErrorConfirm(LPCTSTR lpText)
{
	return MessageBox(g_System.RunTime.hMainFrame,
					lpText,
					(CString)(LPCTSTR)SYS_MSG_MNT_COMMUNICATE, 
					MB_RETRYCANCEL| MB_ICONQUESTION );
}
///////////////////////////////////////////////////////////////////////////////////
//在指定地址添加报头
void CCmdMntSend::EncodeSendHeader(void * buf, const char * Property, const USHORT Length)
{
	ASSERT( NULL != buf );
	CString strTemp;
	HHEADER* ph = static_cast< HHEADER* >( buf );
	ph->m_STX = CCmdMntSend::CONST_STX;
	CSetting * pSetting = CSetting::Instance();
	memcpy( ph->m_DestAddr, pSetting->m_Communicate.ManagementID(), sizeof(ph->m_DestAddr));
	memcpy( ph->m_SourceAddr, pSetting->m_Communicate.StationID(), sizeof(ph->m_SourceAddr));
	memcpy( ph->m_CommandID, Property, 7);  //change character '7' if change 'Property' format;
	ASSERT( 12==sizeof(ph->m_Time) );		//change next line if change 'Time' format;
	strTemp=COleDateTime::GetCurrentTime().Format("%y%m%d%H%M%S");
	memcpy(ph->m_Time, strTemp, sizeof(ph->m_Time));
	ASSERT( 4==sizeof(ph->m_Length) );	//change character '4' if change 'Length' format;
	strTemp.Format("%04d", Length);	//change character '4' if change 'Length' format;
	memcpy(ph->m_Length, strTemp, sizeof(ph->m_Length));

}
///////////////////////////////////////////////////////////////////////////////////
//在指定地址添加报尾
void CCmdMntSend::EncodeSendTial(void* buf)
{
	ASSERT( NULL != buf );
	_STRUCT_Tial * pTial = (_STRUCT_Tial *)buf;
	pTial->m_ETX = CCmdMntSend::CONST_ETX;
}
/////////////////////////////////////////////////////////////////////////////////
//检验报
bool CCmdMntSend::CheckHeaderTial(const char *Recv)
{ 
	

	HHEADER header;
	int iLen = strlen(Recv);
	if (iLen < sizeof(header)) return false;		//检验报头长度
	if(iLen>=392) return TRUE; //HA- attetion: offen find check error
	memcpy(&header, Recv, sizeof(header));
//	if (header.GetLength() + sizeof(header) + sizeof(_STRUCT_Tial) != iLen) 
//	if (header.GetLength() + sizeof(header) + sizeof(_STRUCT_Tial)+10!= iLen) //HA- cmd38 add LPN length
//	if (header.GetLength() + sizeof(header) + sizeof(_STRUCT_Tial)+10!= iLen && iLen!=400) //HA- cmd38 add LPN length , Confirm Exit iLen=400?
	if (header.GetLength() + sizeof(header) + sizeof(_STRUCT_Tial)+10!= iLen && iLen!=400 && iLen>100) //HA- cmd38 add LPN length , Confirm Exit iLen=400? (except iLen<=100 for login checking)
		return false;	//检验包长度
//	if (CONST_ETX != Recv[iLen-1]) 
	if (CONST_ETX != Recv[iLen-1] && Recv[402]!=3) 
		return false;		//报尾错误
	return header.ValidRecvFormat();	//检验报头
}
/////////////////////////////////////////////////////////////////////////////////
//检验报头
bool CCmdMntSend::HHEADER::ValidRecvFormat()
{
	CSetting * pSetting = CSetting::Instance();
	if (0 != memcmp(m_DestAddr, pSetting->m_Communicate.StationID(), sizeof(m_DestAddr)) )
		return false;
	if (0 != memcmp(m_SourceAddr, pSetting->m_Communicate.ManagementID(), sizeof(m_SourceAddr)) )
		return false;
	//报头时间格式
	FILETIME ft;
	SYSTEMTIME st;
	char szTemp[3];
	LPTSTR lpszBuf = m_Time;

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

	if (SystemTimeToFileTime(&st,&ft))
		return true; 
	else
		return false;
}

USHORT CCmdMntSend::HHEADER::GetLength()
{
	ASSERT(4 == sizeof(m_Length));
	CString s;
	s.Format("%4.4s", m_Length);
	return atoi(s);
}

////////////////////////////////////////////////////////////////////////////////
//  检测当前服务器状态
void CCmdMntSend::EncodePing(char *CmdBuf, short &CmdLen)
{
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_Ping, 0);
	EncodeSendTial(CmdBuf + sizeof(HHEADER));
	CmdLen = sizeof(HHEADER) + sizeof(HTIAL);
}
////////////////////////////////////////////////////////////////////////////////
//	文字描述卡信息
CString CCmdMntSend::_STRUCT_CardStatus::GetDescription()
{
	const CString CONST_SEPARATE = "----------------------------------------------------------------------------------------------";
	CString Tmp, s, sDiscount;

	//特殊卡信息
	s = "Description :";
	s += "\r\n\t" + CONST_SEPARATE;
	if ( !_IsSpecialCard )
	{
		s += "\r\nNot Have Special Card Message.";
	}
	else
	{
		s += "\r\nSpecial Card :";
		s += "\r\n\tRegTime :\t\t"		+ show(_SpecialCardInfo._RegTime);
		s += "\r\n\tCard Category :\t"	+ showSpecialCardTypeName(_SpecialCardInfo._CardType);
		s += "\r\n\tValid :\t\t"		+ show(_SpecialCardInfo._Status);
		s += "\r\n\tValid Date :\t"		+ show(_SpecialCardInfo._ValidForm) + " -> " + show(_SpecialCardInfo._ValidTo);
		s += "\r\n\tValid Times :\t"	+ show(_SpecialCardInfo._ValidTimes);
		s += "\r\n\tStore Value :\t"	+ show(_SpecialCardInfo._StoreValue);
		s += "\r\n\tRemark :\t\t"		+ show(_SpecialCardInfo._Remark);
	}
	//持有者信息
	s += "\r\n\t" + CONST_SEPARATE;
	if ( !_HaveHolder )
	{
		s += "\r\nNot Have Holder Infomation.";
	}
	else
	{
		s += "\r\nHolder Info:";
		s += "\r\n\tHolder ID:\t\t"		+ _HolderInfo._HolderID;
		s += "\r\n\tHolder Name:\t"		+ _HolderInfo._HolderName;
		s += "\r\n\tHolder IC:\t\t"		+ _HolderInfo._HolderIC;
		s += "\r\n\tVehicle Plate No:\t"+ _HolderInfo._VehiclePlateNo;
		s += "\r\n\tContact No:\t"	+ _HolderInfo._ContactNo;
		s += "\r\n\tAddr1:\t\t"			+ _HolderInfo._Addr1;
		s += "\r\n\tAddr2:\t\t"			+ _HolderInfo._Addr2;
		s += "\r\n\tAddr3:\t\t"			+ _HolderInfo._Addr3;
		s += "\r\n\tZip:\t\t"				+ _HolderInfo._Zip;
	}
	//上次入场信息
	s += "\r\n\t" + CONST_SEPARATE;
	if ( !_HaveTransaction )
	{
		s += "\r\nNot Have Transaction.";
	}
	else
	{
		s += "\r\nTransaction:";
		s += "\r\n\tIs Parking:\t\t"	+ show( _TransactionInfo._TransState );
		s += "\r\n\tCard Category:\t"	+ showSpecialCardTypeName( _TransactionInfo._CardCate );
		s += "\r\n\tEntry Station:\t"	+ showStationName( _TransactionInfo._EntryStation );
		s += "\r\n\tEntry Time:\t"		+ show( _TransactionInfo._EntryTime );
		s += "\r\n\tExit Station:\t"	+ showStationName( _TransactionInfo._ExitStation );
		s += "\r\n\tExit Time:\t\t"		+ show( _TransactionInfo._ExitTime );
		s += "\r\n\tPay Station:\t"		+ showStationName( _TransactionInfo._PayStation );
		s += "\r\n\tPay Time:\t\t"		+ show( _TransactionInfo._PayTime );
		s += "\r\n\tPaidAmount:\t"		+ show( _TransactionInfo._PaidAmount );
		s += "\r\n\tPaymentNum:\t"		+ show( _TransactionInfo._PaymentNum );
		s += "\r\n\tDiscount :\t\t"		+ show( _TransactionInfo._DiscountPlanID);
		s += "\r\n\tRemark:\t\t"		+ show( _TransactionInfo._Remark );
	}

	return s;
}
////////////////////////////////////////////////////////////////////////////////////////////
//查询卡信息
//琩高戈癟
//
bool CCmdMntSend::QueryCardStatus(const CString &CardID, HCARDSTATUS &CardStatus) //payment check point (Query Card Status)
{
	if ( !IsNormal() ) return false;

						//琩高戈癟﹚Α
	struct Query_Struct	//查询卡信息协议格式
	{
		char			CardID[17];
		char			CheckSpecialCard;
		char			RetrieveHolder;
		char			CheckVIPPass;
		char			RetrieveTrans;
	} *Body;

//1. 构造请求命令			
//   篶硑叫―㏑

	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	//                       CMD = "0385110"
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_CardStatusQuery, sizeof(Query_Struct)); //start OTP Μ禣╃001
	//body
	Body  = static_cast< Query_Struct* >( (void *)(CmdBuf+sizeof(HHEADER)) );
	{
		str2mem(CardID, Body->CardID, sizeof(Body->CardID));
		Body->CheckSpecialCard= '1';
		Body->RetrieveHolder= '1';
		Body->CheckVIPPass= '1';
		Body->RetrieveTrans= '1';
	}
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(Query_Struct));

//2. 发送命令
//   祇癳㏑

	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <QueryCardStatus>."));
	WaitForSingleObject(m_SendCmdMutex, INFINITE);	//与非缓冲同步		籔獶絯侥˙
	if (!SendCmdSync(CmdBuf, sizeof(HHEADER)+sizeof(Query_Struct)+sizeof(HTIAL))) return false;

//3. 处理结果
//	 矪瞶挡狦	 

	if (!CheckHeaderTial(CmdBuf)) return false;
	ReleaseMutex(m_SendCmdMutex);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <CardStatus>."));
	QueryCardStatusDecode(CmdBuf + sizeof(HHEADER), CardStatus);
	return true;
}

//字符串解码到卡信息结构中
//﹃秆絏戈癟挡篶い
void CCmdMntSend::QueryCardStatusDecode(const char * Recv, HCARDSTATUS &CardStatus) // payment check point (Query Card Status Decode)
{
	struct String_Format		//	卡信息字符串格式
	{
		char			IsSpecialCard;
		struct struct_SpecialCardInfo{
			char		CardNo[17];
			char		HolderID[4];
			char		RegTime[12];
			char		CardCate;
			char		Status;
			char		ValidForm[6];
			char		ValidTo[6];
			char		ValidTimes[4];
			char		StoreValue[8];
			char		Remark[20];
		}_S_Info;
		char			HaveHolderInfo;
		struct struct_HolderInfo{
			char		HolderID[4];
			char		HolderName[30];
			char		Addr1[40];
			char		Addr2[40];
			char		Addr3[20];
			char		Zip[10];
			char		ContactNo[15];
			char		VehiclePlateNo[12];
			char		HolderIC[16];
			char		Portrait[5];
		}_H_Info;
		char			IsVIPPass;
		char			HaveTransactionInfo;
		struct struct_TransactionInfo{
			char		CardNo[17];
			char		TransState;
			char		CardCate;
			char		CarType;
			char		EntryStation[2];
			char		EntryTime[12];
			char		ExitStation[2];
			char		ExitTime[12];
			char		PayStation[2];
			char		PayTime[12];
			char		PaidAmount[6];
			char		PaymentNum;
			char		DiscountPlanID[3];
			char		Remark[17];
		}_T_Info;
	}fmt;
	memcpy(&fmt, Recv, sizeof(fmt));
	
	CardStatus._IsSpecialCard	= mem2bool(fmt.IsSpecialCard);
	CardStatus._HaveHolder		= mem2bool(fmt.HaveHolderInfo);
	CardStatus._IsVIPPass		= mem2bool(fmt.IsVIPPass);
	CardStatus._HaveTransaction	= mem2bool(fmt.HaveTransactionInfo);

	if (CardStatus._IsSpecialCard)
	{
		CardStatus._SpecialCardInfo._CardNo		= mem2str(		fmt._S_Info.CardNo,		sizeof(fmt._S_Info.CardNo));
		CardStatus._SpecialCardInfo._HolderID	= mem2str(		fmt._S_Info.HolderID,	sizeof(fmt._S_Info.HolderID));
		CardStatus._SpecialCardInfo._RegTime	= mem2datetime(	fmt._S_Info.RegTime		);
		CardStatus._SpecialCardInfo._CardType	= mem2short(	fmt._S_Info.CardCate	);
		CardStatus._SpecialCardInfo._Status		= mem2bool(		fmt._S_Info.Status		);
		CardStatus._SpecialCardInfo._ValidForm	= mem2date(		fmt._S_Info.ValidForm	);
		CardStatus._SpecialCardInfo._ValidTo	= mem2date(		fmt._S_Info.ValidTo		);
		CardStatus._SpecialCardInfo._ValidTimes	= mem2short(	fmt._S_Info.ValidTimes, sizeof(fmt._S_Info.ValidTimes));
		CardStatus._SpecialCardInfo._StoreValue	= mem2dbl(		fmt._S_Info.StoreValue, sizeof(fmt._S_Info.StoreValue));
		CardStatus._SpecialCardInfo._Remark		= mem2str(		fmt._S_Info.Remark,		sizeof(fmt._S_Info.Remark));
	}
	if (CardStatus._HaveHolder)
	{
		CardStatus._HolderInfo._HolderID		= mem2str( fmt._H_Info.HolderID,		sizeof(fmt._H_Info.HolderID) );
		CardStatus._HolderInfo._HolderName		= mem2str( fmt._H_Info.HolderName,		sizeof(fmt._H_Info.HolderName) );
		CardStatus._HolderInfo._Addr1			= mem2str( fmt._H_Info.Addr1,			sizeof(fmt._H_Info.Addr1) );
		CardStatus._HolderInfo._Addr2			= mem2str( fmt._H_Info.Addr2,			sizeof(fmt._H_Info.Addr2) );
		CardStatus._HolderInfo._Addr3			= mem2str( fmt._H_Info.Addr3,			sizeof(fmt._H_Info.Addr3) );
		CardStatus._HolderInfo._Zip				= mem2str( fmt._H_Info.Zip,				sizeof(fmt._H_Info.Zip) );
		CardStatus._HolderInfo._ContactNo		= mem2str( fmt._H_Info.ContactNo,		sizeof(fmt._H_Info.ContactNo) );
		CardStatus._HolderInfo._VehiclePlateNo	= mem2str( fmt._H_Info.VehiclePlateNo,	sizeof(fmt._H_Info.VehiclePlateNo) );
		CardStatus._HolderInfo._HolderIC		= mem2str( fmt._H_Info.HolderIC,		sizeof(fmt._H_Info.HolderIC) );
		CardStatus._HolderInfo._Portrait		= mem2str( fmt._H_Info.Portrait,		sizeof(fmt._H_Info.Portrait) );
	}
	if (CardStatus._HaveTransaction)
	{
		CardStatus._TransactionInfo._CardNo			= mem2str(		fmt._T_Info.CardNo,		sizeof(fmt._T_Info.CardNo) );
		CardStatus._TransactionInfo._TransState		= mem2bool(	fmt._T_Info.TransState		);
		CardStatus._TransactionInfo._CardCate		= mem2short(	fmt._T_Info.CardCate		);
		CardStatus._TransactionInfo._CarType		= mem2short(	fmt._T_Info.CarType			);
		CardStatus._TransactionInfo._EntryStation	= mem2short(	fmt._T_Info.EntryStation,	sizeof(fmt._T_Info.EntryStation) );
		CardStatus._TransactionInfo._EntryTime		= mem2datetime(	fmt._T_Info.EntryTime		);
		CardStatus._TransactionInfo._ExitStation	= mem2short(	fmt._T_Info.ExitStation,	sizeof(fmt._T_Info.ExitStation)	);
		CardStatus._TransactionInfo._ExitTime		= mem2datetime(	fmt._T_Info.ExitTime		);
		CardStatus._TransactionInfo._PayStation		= mem2short(	fmt._T_Info.PayStation,		sizeof(fmt._T_Info.PayStation) );
		CardStatus._TransactionInfo._PayTime		= mem2datetime(	fmt._T_Info.PayTime			);
		CardStatus._TransactionInfo._PaidAmount		= mem2dbl(		fmt._T_Info.PaidAmount		);
		CardStatus._TransactionInfo._PaymentNum		= mem2short(	fmt._T_Info.PaymentNum		);
		CardStatus._TransactionInfo._DiscountPlanID = mem2short(	fmt._T_Info.DiscountPlanID,	sizeof(fmt._T_Info.DiscountPlanID));
		CardStatus._TransactionInfo._Remark			= mem2str(		fmt._T_Info.Remark,			sizeof(fmt._T_Info.Remark) );
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//查询持卡人信息
SYSRESULT CCmdMntSend::QueryHolderInfo(const CString &HolderID, HHOLDERINFO &HolderInfo)
{
	if ( !IsNormal() ) return false;
	struct Query_Struct	//查询持卡人信息协议格式
	{
		char			HolderID[4];
	} *Body;

//1. 构造请求命令
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_HolderInfoQuery, sizeof(Query_Struct));
	//body
	Body  = static_cast< Query_Struct* >( (void *)(CmdBuf+sizeof(HHEADER)) );
	{
		str2mem(HolderID, Body->HolderID, sizeof(Body->HolderID));
	}
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(Query_Struct));
//2. 发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Query Holder Info>."));
	WaitForSingleObject(m_SendCmdMutex, INFINITE);	//与缓冲同步
	if (!SendCmdSync(CmdBuf, sizeof(HHEADER)+sizeof(Query_Struct)+sizeof(HTIAL))) return false;
//3. 处理结果
	if (!CheckHeaderTial(CmdBuf)) return false;
	ReleaseMutex(m_SendCmdMutex);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Holder Info>."));
	QueryHolderInfoDecode(CmdBuf + sizeof(HHEADER), HolderInfo);
	return true;
}

void CCmdMntSend::QueryHolderInfoDecode(const char * Recv, HHOLDERINFO &HolderInfo)
{
	struct String_Format		//	卡信息字符串格式
	{
		char	HaveHolderInfo;
		char	HolderID[4];
		char	HolderName[30];
		char	Addr1[40];
		char	Addr2[40];
		char	Addr3[20];
		char	Zip[10];
		char	ContactNo[15];
		char	VehiclePlateNo[12];
		char	HolderIC[16];
		char	Portrait[5];
	}fmt;
	memcpy(&fmt, Recv, sizeof(fmt));
	HolderInfo._HaveHolder = mem2bool(fmt.HaveHolderInfo);
	if (HolderInfo._HaveHolder)
	{
		HolderInfo._HolderID		= mem2str( fmt.HolderID,		sizeof(fmt.HolderID) );
		HolderInfo._HolderName		= mem2str( fmt.HolderName,		sizeof(fmt.HolderName) );
		HolderInfo._Addr1			= mem2str( fmt.Addr1,			sizeof(fmt.Addr1) );
		HolderInfo._Addr2			= mem2str( fmt.Addr2,			sizeof(fmt.Addr2) );
		HolderInfo._Addr3			= mem2str( fmt.Addr3,			sizeof(fmt.Addr3) );
		HolderInfo._Zip				= mem2str( fmt.Zip,				sizeof(fmt.Zip) );
		HolderInfo._ContactNo		= mem2str( fmt.ContactNo,		sizeof(fmt.ContactNo) );
		HolderInfo._VehiclePlateNo	= mem2str( fmt.VehiclePlateNo,	sizeof(fmt.VehiclePlateNo) );
		HolderInfo._HolderIC		= mem2str( fmt.HolderIC,		sizeof(fmt.HolderIC) );
		HolderInfo._Portrait		= mem2str( fmt.Portrait,		sizeof(fmt.Portrait) );
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//查询入场记录
bool CCmdMntSend::QueryCardEntryLog(const CString &CardID, LPSTR Buf)
{

	if ( !IsNormal() ) return false;
	struct Query_Struct	//查询持卡人信息协议格式
	{
		char	CardNo[9];//ta19- check
	} *Body;

//1. 构造请求命令
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_TransQuery, sizeof(Query_Struct));
	//body
	Body  = static_cast< Query_Struct* >( (void *)(CmdBuf+sizeof(HHEADER)) );
	{
		str2mem(CardID, Body->CardNo, sizeof(Body->CardNo));
	}
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(Query_Struct));
	WaitForSingleObject(m_SendCmdMutex, INFINITE);	//与缓冲同步
	if (!SendCmdSync(CmdBuf, sizeof(HHEADER)+sizeof(Query_Struct)+sizeof(HTIAL))) return false;
//3. 处理结果
	if (!CheckHeaderTial(CmdBuf)) return false;
	ReleaseMutex(m_SendCmdMutex);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////
//操作员认证
bool CCmdMntSend::QueryOperator(const CString& UserID, const CString& Password, HOPERATOR& Operator)
{
	if ( !IsNormal() ) return false;
	struct Query_Struct	//查询持卡人信息协议格式
	{
		char		UserID[12];
		char		Password[8];
	} *Body;

//1. 构造请求命令
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_OperatorQuery, sizeof(Query_Struct));
	//body
	Body  = static_cast< Query_Struct* >( (void *)(CmdBuf+sizeof(HHEADER)) );
	{
		str2mem(UserID, Body->UserID, sizeof(Body->UserID));
		str2mem(Password, Body->Password, sizeof(Body->Password));
	}
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(Query_Struct));
//2. 发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <QueryOperator>."));
	WaitForSingleObject(m_SendCmdMutex, INFINITE);	//与非缓冲同步
	if (!SendCmdSync(CmdBuf, sizeof(HHEADER)+sizeof(Query_Struct)+sizeof(HTIAL))) return false;
//3. 处理结果
	if (!CheckHeaderTial(CmdBuf)) return false;
	ReleaseMutex(m_SendCmdMutex);
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Recv Command: <Operator>."));
	QueryOperatorDecode(CmdBuf + sizeof(HHEADER), Operator);
	return true;
}
//解码
void CCmdMntSend::QueryOperatorDecode(const char * Recv, HOPERATOR& Operator)
{
	struct String_Format		//	卡信息字符串格式
	{
		char		havethisOperator;
		char		UserID[12];
		char		Name[30];
		char		Level;
		char		ValidFlag;
		char		ValidFrom[6];
		char		ValidTo[6];
	}fmt;
	memcpy(&fmt, Recv, sizeof(fmt));

	Operator._Exist		= mem2bool( fmt.havethisOperator );
	Operator._Level		= mem2short( fmt.Level );
	Operator._ValidFlag = mem2bool( fmt.ValidFlag );
	Operator._UserID	= mem2str( fmt.UserID,		sizeof(fmt.UserID) );
	Operator._Name		= mem2str( fmt.Name,		sizeof(fmt.Name) );
	Operator._ValidFrom	= mem2date( fmt.ValidFrom );
	Operator._ValidTo	= mem2date( fmt.ValidTo );
}

////////////////////////////////////////////////////////////////////////////////////
//时间同步请求
bool CCmdMntSend::TimeSynchronize()
{
	if ( !IsNormal() ) return false;
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_TimeSynchronize, 0);
	EncodeSendTial(CmdBuf + sizeof(HHEADER));
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <Time Synchronize>."));
	return SendCmd(CmdBuf, sizeof(HHEADER) + sizeof(HTIAL));
}
////////////////////////////////////////////////////////////////////////////////////
//发送响应
void CCmdMntSend::Reply(const char * Property, bool IsSuccessful/* = true*/, CString Reason/* = ""*/) //发送响应
{
	if ( !IsNormal() ) return;
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	short BodyLen = Reason.GetLength() + 1;//IsSuccessful + Reason
	//header
	EncodeSendHeader(CmdBuf, Property, BodyLen);
	//body
	bool2mem(IsSuccessful, *(CmdBuf+sizeof(HHEADER)));
	memcpy(CmdBuf+sizeof(HHEADER)+1, Reason, Reason.GetLength());
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + BodyLen);
	//发送命令
	SendCmd(CmdBuf, sizeof(HHEADER) + BodyLen + sizeof(HTIAL));
}
////////////////////////////////////////////////////////////////////////////////////
//  Update a trans CMD 54
// [PY]: 07 Jun 2005 - added the 'ExitTime' and 'ExitStn' parameters
// Confirm Exit Check Point 002
void CCmdMntSend::UpdateTrans(CString CardNo, short Action, CString Remark, CString ExitTime, CString ExitStn)
{
	typedef struct _STRUCT_UpdateTrans			//付款记录
	{
		_STRUCT_UpdateTrans()
		{::ZeroMemory(this, sizeof(_STRUCT_UpdateTrans));}
		char		CardNo[11];// TA19- this size will influence the data package of communication
		char		Action;
		char		OperatorID[10];
		char		ActTime[12];
		char		ExitTime[12]; // [PY]: 07 Jun 2005 - added additional fields for updating; namely 'Exit Time'
		char		ExitStn[3];   // 'Exit Stn' and
		char		Remark[21];   // 'Remark' (eg. CE - Confirm Exit)
	}HUPDATETRANS;

	HUPDATETRANS data;

	str2mem(CardNo,	data.CardNo, sizeof(data.CardNo));
	short2mem(Action, data.Action);
	str2mem(g_System.Operator.CurUserID, data.OperatorID, sizeof(data.OperatorID));
	datetime2mem(COleDateTime::GetCurrentTime(), data.ActTime);
//	str2mem(ExitTime, data.ExitTime, sizeof(ExitTime));	// [PY]: 07 Jun 2005 - additional fields
	str2mem(ExitTime, data.ExitTime, 12);
	str2mem(ExitStn, data.ExitStn, 3);	// [PY]: to be updated to the database
	str2mem("CE", data.Remark, 2);						// [PY]: CE = Confirm Exit
	
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_UpdateTrans, sizeof(_STRUCT_UpdateTrans));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &data, sizeof(HUPDATETRANS));
	//tail
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(_STRUCT_UpdateTrans));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <UpdateTrans>.")); // write to YYYY-MM-DD.log file
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(_STRUCT_UpdateTrans)+sizeof(HTIAL));
	OperatorActionLog("Trans-Update", Remark, lvl_Warn); // write to YYYY-MM-DD.log file

	// [PY]: 07 Jun 2005 - apparently no call to mgmt stn to write record to the database, NOT DIRECTLY
	// but how to send message to mgmt?????
	// how does the command buffer work?????
}



// Regsiter a Special Card
void CCmdMntSend::CreateSpecCard(HCREATESPECCARD & card)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_CreateSpecCard, sizeof(_STRUCT_CREATESPECCARD));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &card, sizeof(HCREATESPECCARD));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(_STRUCT_CREATESPECCARD));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <Create Special Card>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(_STRUCT_CREATESPECCARD)+sizeof(HTIAL));

}
void CCmdMntSend::CreateSpecCard(CString CardNo, short HolderID, COleDateTime RegDate, 
								 char CateID, char Status, COleDateTime ValidFrom, COleDateTime ValidTo, 
								 short ValidTimes, double StoreValue, CString Remark)
{
	HCREATESPECCARD data;

	str2mem(	CardNo,			data._CardNo,		sizeof(data._CardNo));
	short2mem(	HolderID,		data._HolderID,		sizeof(data._HolderID));
	date2mem(	RegDate,		data._RegDate);
	short2mem(	CateID,			data._CateID);
	short2mem(	Status,			data._Status);
	date2mem(	ValidFrom,		data._ValidFrom);
	date2mem(	ValidTo,		data._ValidTo);
	short2mem(	ValidTimes,		data._ValidTimes,	sizeof(data._ValidTimes));
	dbl2mem(	StoreValue, 	data._StoreValue,	sizeof(data._StoreValue) );
	str2mem(	Remark, 		data._Remark,		sizeof(data._Remark) );
	CreateSpecCard(data);
}


bool CCmdMntSend::DoesSpecialCardExist(CString CAN)
{
	HCARDSTATUS CardStatus;
	if (!QueryCardStatus(CAN, CardStatus)) return true;
	return CardStatus._IsSpecialCard;
}

////////////////////////////////////////////////////////////////////////////////////
//	付款操作
void CCmdMntSend::Payment(HPAYMENT& Payment)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_Payment, sizeof(_STRUCT_Payment));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &Payment, sizeof(HPAYMENT));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(_STRUCT_Payment));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <Payment>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(_STRUCT_Payment)+sizeof(HTIAL));
}
// Send Cmd to Management Check Point
void CCmdMntSend::Payment(CString CardNo, short CardType, short CarType, COleDateTime PayTime, CString ReceiptNo, 
			double Amount, double Amount1, double Amount2, double Amount3, CString TransactionNo, CString Remarks)
{
	HPAYMENT data;

	str2mem(	CardNo,		data.CardNo,		sizeof(data.CardNo) );
	str2mem(	ReceiptNo, 	data.ReceiptNo,		sizeof(data.ReceiptNo) );
	str2mem(	TransactionNo, 	data.TransactionNo,	sizeof(data.TransactionNo) );
	str2mem(	Remarks,		data.Remarks,		sizeof(data.Remarks) );

	datetime2mem(	PayTime, 	data.Paytime );
	
	dbl2mem(	Amount,		data.Amount, sizeof(data.Amount));
	dbl2mem(	Amount1,	data.Amount1, sizeof(data.Amount1));
	dbl2mem(	Amount2,	data.Amount2, sizeof(data.Amount2));
	dbl2mem(	Amount3,	data.Amount3, sizeof(data.Amount3));

	short2mem(	CardType,	data.Category);
	short2mem(	CarType,	data.CarType);

	CSetting * pSetting = CSetting::Instance();
	str2mem(	pSetting->m_Communicate.StationID(),
							data.StationID,		sizeof(data.StationID) );
	// cashcard   -> Cash payment
	// cashback   -> Octopus 
	// StoreValue -> Store Value
	short2mem(		pSetting->m_BaseSystemSetting.CashCardModeID(),
							data.PayMode1);
	short2mem(		pSetting->m_BaseSystemSetting.CashBackModeID(),
							data.PayMode2);
	short2mem(		pSetting->m_BaseSystemSetting.StoreValueModeID(),
							data.PayMode3);
	Payment(data);
}


////////////////////////////////////////////////////////////////////////////////////
//	付款操作
void CCmdMntSend::AddValue(HADDVALUE & AddValue)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_AddValue, sizeof(_STRUCT_AddValue));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &AddValue, sizeof(HADDVALUE));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(_STRUCT_AddValue));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <Add Value>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(_STRUCT_AddValue)+sizeof(HTIAL));
}

void CCmdMntSend::AddValue(CString CardNo, CString Optr, COleDateTime PayTime, CString ReceiptNo, 
			double Amount, CString AVRemark)
{
 	HADDVALUE data;

	str2mem(	CardNo,		data.CardNo,		sizeof(data.CardNo) );
	CSetting * pSetting = CSetting::Instance();
	str2mem(	pSetting->m_Communicate.StationID(),
							data.StationID,		sizeof(data.StationID) );
	str2mem(	Optr,		data.Optr,			sizeof(data.Optr));
	datetime2mem(	PayTime, 	data.Paytime );
	str2mem(	ReceiptNo, 	data.ReceiptNo,		sizeof(data.ReceiptNo) );
	dbl2mem(	Amount,		data.Amount, sizeof(data.Amount));
	// cashcard   -> Cash payment
	// cashback   -> Octopus 
	// StoreValue -> Store Value
	short2mem(	pSetting->m_BaseSystemSetting.CashCardModeID(),	
							data.PayMode);
	str2mem(	AVRemark,	data.AVRemark,		sizeof(data.AVRemark) );
	AddValue(data);
}



	

////////////////////////////////////////////////////////////////////////////////////
//	//操作日志
void CCmdMntSend::ErrorWarnNoticeLog(HERRORWARNNOTICELOG& data)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_ErrorWarnNoticeLog, sizeof(data));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &data, sizeof(data));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(data));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <ErrorWarnNoticeLog>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(data)+sizeof(HTIAL));
}
void CCmdMntSend::ErrorWarnNoticeLog(const CString msg, MessageType type/*= msg_Notice*/)
{
	HERRORWARNNOTICELOG data;
	data.MessageType = type;
	str2mem(msg, data.Message, sizeof(data.Message));
	ErrorWarnNoticeLog(data);
}
////////////////////////////////////////////////////////////////////////////////////
//	//非停车收费
void CCmdMntSend::NonParkingPayment(HNONPARKINGPAYMENT& data)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_NonParkingPayment, sizeof(data));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &data, sizeof(data));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(data));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <NonParkingPayment>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(data)+sizeof(HTIAL));
}
void CCmdMntSend::NonParkingPayment(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, 
		double Amount, double Amount1, double Amount2, double Amount3)
{
	HNONPARKINGPAYMENT data;

	str2mem(	CardNo,		data.CardNo,		sizeof(data.CardNo) );
	str2mem(	PayTime, 	data.Paytime,		sizeof(data.Paytime) );
	str2mem(	ReceiptNo, 	data.ReceiptNo,		sizeof(data.ReceiptNo) );

	data.PayAction = pa;

	dbl2mem(	Amount,		data.Amount, sizeof(data.Amount));
	dbl2mem(	Amount1,	data.Amount1, sizeof(data.Amount1));
	dbl2mem(	Amount2,	data.Amount2, sizeof(data.Amount2));
	dbl2mem(	Amount3,	data.Amount3, sizeof(data.Amount3));

	short2mem(	CardType,	data.Category);

	CSetting * pSetting = CSetting::Instance();
	str2mem(	g_System.Operator.CurUserName ,
							data.Operator,		sizeof(data.Operator) );
	str2mem(	pSetting->m_Communicate.StationID(),
							data.StationID,		sizeof(data.StationID) );
	// cashcard   -> Cash payment
	// cashback   -> Octopus 
	// StoreValue -> Store Value
	short2mem(		pSetting->m_BaseSystemSetting.CashCardModeID(),
							data.PayMode1);
	short2mem(		pSetting->m_BaseSystemSetting.CashBackModeID(),
							data.PayMode2);
	short2mem(		pSetting->m_BaseSystemSetting.StoreValueModeID(),
							data.PayMode3);
	NonParkingPayment(data);

}
void CCmdMntSend::NonParkingPaymentCashCard(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount)
{
	NonParkingPayment(CardNo,CardType,PayTime,pa,ReceiptNo,Amount,Amount,0,0);
}
void CCmdMntSend::NonParkingPaymentCashBack(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount)
{
	NonParkingPayment(CardNo,CardType,PayTime,pa,ReceiptNo,Amount,0,Amount,0);
}
void CCmdMntSend::NonParkingPaymentStoreValue(CString CardNo, short CardType, CString PayTime, PayAction pa, CString ReceiptNo, double Amount)
{
	NonParkingPayment(CardNo,CardType,PayTime,pa,ReceiptNo,Amount,0,0,Amount);
}

////////////////////////////////////////////////////////////////////////////////////
//	//结算操作
void CCmdMntSend::FinancialMaintain(HFINANCIALMAINTAIN& data)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_FinancialMaintain, sizeof(data));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &data, sizeof(data));
	//tial
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(data));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Send Command: <FinancialMaintain>."));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(data)+sizeof(HTIAL));
}
void CCmdMntSend::FinancialMaintain(COleDateTime DutyStart, CString ReceiptNo, long PayNum, 
							double CashAmt, double OTPAmt, double SVAmt, double CashMaintain)
// shift close account check point (Financial Maintain)							
{	
		
	HFINANCIALMAINTAIN data;
	CSetting * pSetting = CSetting::Instance();

	str2mem(pSetting->m_Communicate.StationID(),data.StationID,		sizeof(data.StationID));
	datetime2mem(DutyStart,data.DutyStart);
	datetime2mem(COleDateTime::GetCurrentTime(), data.DutyEnd);
	str2mem(g_System.Operator.CurUserName, data.Operator, 20);
	str2mem(ReceiptNo,	data.ReceiptNo,	8);
	long2mem(PayNum, data.PayNum, 6);
	dbl2mem(CashAmt,data.CashAmt, 8);
	dbl2mem(OTPAmt,	data.OTPAmt, 8);
	dbl2mem(SVAmt,	data.SVAmt, 8);
	dbl2mem(CashMaintain, data.CashMaintain, 8);
	FinancialMaintain(data);
}

////////////////////////////////////////////////////////////////////////////////////
//	//重要操作日志
void CCmdMntSend::OperatorActionLog(const CString Operation,const CString Description/*=""*/,SensitiveLvl lvl/*= lvl_Lower*/)
{
	HOPERATORACTIONLOG data;

	data.SensitiveLvl = lvl;
	str2mem(	CTime::GetCurrentTime().Format("%y%m%d%H%M%S"),
								data.Time,			sizeof(data.Time) );
	str2mem(	Operation,		data.Operation,		sizeof(data.Operation) );
	str2mem(	Description,	data.Description,	sizeof(data.Description) );
	str2mem(	g_System.Operator.CurUserName ,
								data.Operator,		sizeof(data.Operator) );

	CSetting * pSetting = CSetting::Instance();
	str2mem(	pSetting->m_Communicate.StationID(),
								data.StationID,		sizeof(data.StationID) );

	OperatorActionLog(data);
}
void CCmdMntSend::OperatorActionLog(HOPERATORACTIONLOG& data)
{
	char  CmdBuf[MAX_COMMAND_BUF_LENGTH];
	//header
	EncodeSendHeader(CmdBuf, PROPERTY_CMD_OperatorActionLog, sizeof(data));
	//body
	memcpy(CmdBuf+sizeof(HHEADER), &data, sizeof(data));
	//tail
	EncodeSendTial(CmdBuf + sizeof(HHEADER) + sizeof(data));
	//发送命令
	g_pLog->WriteLog(LoadS(IDS_MSG_TYPE_OPERATOR), _T("Buffer Command: <OperatorActionLog>."));
//	SendCmd(sizeof(HHEADER)+sizeof(data)+sizeof(HTIAL));
	AddBufCmd(CmdBuf, sizeof(HHEADER)+sizeof(data)+sizeof(HTIAL));
}
////////////////////////////////////////////////////////////////////////////////////
//	发送所有交换文件. (添加到缓冲)
SYSRESULT CCmdMntSend::UploadOtpXFile()
{
	const short PreTranLength = 3800;
//	HUPLOADOTPXFILEBUF fmt;

	CFile f;
	CFileException e;
	CString dsp;
	//生成交换文件, 取得路径
	CString XFilePath = "some";
	bool XFileRet;

	WaitForSingleObject(g_System.m_OprBusyMutex, INFINITE);
	XFileRet = CCmdOtp::Instance()->OTP_XFile(XFilePath);
	ReleaseMutex(g_System.m_OprBusyMutex);			//	操作员闲
	
	if (!XFileRet)
	{
		dsp.Format("ERR: OTP Generate XFile Fail! - (%s)", CCmdOtp::Instance()->Translate());
		ErrorWarnNoticeLog(dsp, CCmdMntSend::msg_Error);
		showTip(dsp);
		//OtpErrProcess();
	}else{
		dsp.Format("OTP Exchange File Generated");
		ErrorWarnNoticeLog(dsp, CCmdMntSend::msg_Notice);
	}
	Sleep(1000);
	SendCurrentExistXFiles();
	
	return SUCCESS;
}

//send all current existing x files
//search all x files in this station, and try to send it.
void CCmdMntSend::SendCurrentExistXFiles()
{
//	showTip("Octopus X-Files Process, please wait ...", true);
	CString filename, tmpstr, fpath, name1;
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	int curday=CTime::GetCurrentTime().GetMonth()*30+CTime::GetCurrentTime().GetDay();
	int curye=CTime::GetCurrentTime().GetYear();

	fpath = CSetting::Instance()->m_OTPRwlSetting.PathExchange() + "\\";
	filename = fpath + "MPS.*";
	hFind = FindFirstFile((LPCTSTR)filename, &wfd);
	if (hFind == INVALID_HANDLE_VALUE) {
	//	ErrorWarnNoticeLog("0Cannot Find Generated Exchange Files!", CCmdMntSend::msg_Error);
	}else{
		do{
			tmpstr = wfd.cFileName;
			tmpstr.TrimRight();
			filename= tmpstr;
			tmpstr = fpath + tmpstr;
			if (SendFile(tmpstr) ==1)
			{
				MoveFile(tmpstr,fpath+"XFILEBK\\"+filename);
				DeleteFile(tmpstr);
			}
		}while (FindNextFile(hFind, &wfd));
	}


	filename = fpath+"XFILEBK\\MPS.*";
	hFind = FindFirstFile((LPCTSTR)filename, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do{
			tmpstr = wfd.cFileName;
			tmpstr.TrimRight();
			if (tmpstr.Find(".") < 0) continue;
			name1=tmpstr;
			tmpstr=name1.Right(14);
			if(tmpstr.Left(1)!='2') continue;
			int m=(tmpstr.GetAt(4)-'0')*10+(tmpstr.GetAt(5)-'0');
			int n=(tmpstr.GetAt(6)-'0')*10+(tmpstr.GetAt(7)-'0');
			if(m*30+n<curday-7)//backup recent 7 days 
			{
				tmpstr = fpath+"XFILEBK\\" + name1;
				DeleteFile(tmpstr);
			}
		}while (FindNextFile(hFind, &wfd));
	}

}

//	发送所有交换文件. (实际执行)
bool CCmdMntSend::UploadOtpXFile(HUPLOADOTPXFILEBUF &UploadOtpXFileBuf, char *CmdBuf, short CmdLen)
{
	return true;
}


////////////////////////////////////////////////////////////////////////////////
//  //发送OtpXFile成功消息
void CCmdMntSend::OtpXFileReply(bool SuccessFlag, CString OtpXFileName)
{

}


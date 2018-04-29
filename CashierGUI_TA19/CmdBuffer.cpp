// CmdBuffer.cpp: implementation of the CCmdBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashierGUI.h"
#include "CmdBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const short		CCmdBuffer::SEPARATE_FLAG_LEN	= 5;
const char		CCmdBuffer::SEPARATE_FLAG[]
									={'\n','\004','\003','\002','\001'};
const char		CCmdBuffer::DELETE_FLAG[]
									={'\n','\055','\055','\055','\004'};
const short		CCmdBuffer::CMD_LEN_FLAG_LEN	= 4;
const short		CCmdBuffer::BUF_CMD_MAX_LEN		= 4096 + CMD_LEN_FLAG_LEN + SEPARATE_FLAG_LEN;
const ULONG		CCmdBuffer::BUF_FILE_LENGTH		= BUF_CMD_MAX_LEN * 1000;//当每个命令都是最长时可允许1000命令
const ULONG		CCmdBuffer::LAST_VALID_WRITE_POS= BUF_FILE_LENGTH - BUF_CMD_MAX_LEN;
const ULONG		CCmdBuffer::INVALID_POS			= BUF_FILE_LENGTH + 1;
const CString	CCmdBuffer::BUF_FILE_NAME		= "CommBufFile.dat";

CCmdBuffer *	CCmdBuffer::_Instance = NULL;

CCmdBuffer* CCmdBuffer::Instance()
{
    if (_Instance == 0) {
        _Instance = new CCmdBuffer;
    }
    return _Instance;
}

CCmdBuffer::CCmdBuffer()
{
	_BufMutex = CreateMutex(NULL, FALSE, NULL);
	CFileException e;
	if (!_BufferFile.Open(BUF_FILE_NAME, CFile::modeReadWrite| CFile::shareDenyWrite, &e))
	{//尝试打开文件
		if (!_BufferFile.Open(BUF_FILE_NAME, CFile::modeReadWrite| CFile::modeCreate, &e))
		{//尝试创建文件
			AfxMessageBox("Fatal error!\nOpen buffer file error!\nPlease restart program!");
		}
		//添充缓冲文件.
		_BufferFile.SeekToBegin();
		for (int i = 0; i < BUF_FILE_LENGTH; i += 10)
			_BufferFile.Write(".....NORVA", 10);
		_BufferFile.Flush();
		_BufferFile.Close();
		if (!_BufferFile.Open(BUF_FILE_NAME, CFile::modeReadWrite| CFile::shareDenyWrite, &e))
			AfxMessageBox("Read Buffer File Error.");

	}

	//初始化命令指针
	SetPosRead();
	SetPosWrite();
}

CCmdBuffer::~CCmdBuffer()
{

}

bool CCmdBuffer::GetCmd(char *CmdData, short &CmdLen)
{
	if ( INVALID_POS<=_PosRead) return false;
	if (_PosRead == _PosWrite) return false;
	_BufferFile.AssertValid();
	char buf[SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN];
	WaitForSingleObject(_BufMutex, INFINITE);	//读写互斥信号
	_BufferFile.Seek(_PosRead, CFile::begin);
	_BufferFile.Read(buf, sizeof(buf));		//读分割标记,和命令长标记.
	if (!IsSepatateFlag(buf))
	{	//出错,从新获取PosRead.
		SetPosRead();
		ReleaseMutex(_BufMutex);					//读写互斥信号
		return false;
	}
	else
	{
		CmdLen = GetCmdLen(buf);
		//读命令
		_BufferFile.Seek(_PosRead + SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN, CFile::begin);
		ULONG dwRead = _BufferFile.Read(CmdData, CmdLen);
		ASSERT(dwRead == (ULONG)CmdLen);
		ReleaseMutex(_BufMutex);					//读写互斥信号
		return true;
	}
}

void CCmdBuffer::AddCmd(const char *CmdData, const short CmdLen)
{
	// [PY]: 07 Jun 2005 - Note: writes data to "CommBufFile.dat" (text) file

	WaitForSingleObject(_BufMutex, INFINITE);	//读写互斥信号
	_BufferFile.AssertValid();
	if (_PosWrite > LAST_VALID_WRITE_POS) _PosWrite = 0;	//指向文件头
	_BufferFile.Seek(_PosWrite, CFile::begin);
	_BufferFile.Write(SEPARATE_FLAG, SEPARATE_FLAG_LEN);	//写入分割标记
	_BufferFile.Write(GenCmdLen(CmdLen), CMD_LEN_FLAG_LEN);	//写入命令长
	_BufferFile.Write(CmdData, CmdLen);						//写入命令
	_BufferFile.Flush();
	//有必要就修改_PosRead指针
	if ( INVALID_POS <= _PosRead ) _PosRead = _PosWrite;
	_PosWrite = _PosWrite + SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN + CmdLen;
	ReleaseMutex(_BufMutex);					//读写互斥信号
}

void CCmdBuffer::DelCmd()
{
	if ( INVALID_POS<=_PosRead ) return ;
	if (_PosRead == _PosWrite) return ;
	_BufferFile.AssertValid();
	WaitForSingleObject(_BufMutex, INFINITE);	//读写互斥信号
	char buf[SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN];
	_BufferFile.Seek(_PosRead, CFile::begin);
	_BufferFile.Read(buf, sizeof(buf));		//读分割标记,和命令长标记.
	ASSERT(IsSepatateFlag(buf));			//一定是分割标记.		
	if (IsSepatateFlag(buf))
	{
		short CmdLen = GetCmdLen(buf);
		_BufferFile.Seek(_PosRead, CFile::begin);
		_BufferFile.Write(DELETE_FLAG, SEPARATE_FLAG_LEN);	//写入分割标记
		_PosRead = _PosRead + SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN + CmdLen;
		if (_PosRead > LAST_VALID_WRITE_POS) _PosRead = 0;
	}
	ReleaseMutex(_BufMutex);					//读写互斥信号
}

//设置分割标记
//检索不到则标记为无效
void CCmdBuffer::SetPosRead()
{
	//检索第一个分割标记.
	_PosRead = INVALID_POS;
	short CmdLen = 0;
	if (!FindSepatateFlag(0, LAST_VALID_WRITE_POS, _PosRead, CmdLen)) return;
	//以下处理过程主要是考虑当第一个分割标记不是第一个应当发送的命令请况.
	//检索第一个删除标记.
	ULONG TempPos = _PosRead;
	if (!FindDeleteFlag(TempPos, LAST_VALID_WRITE_POS, TempPos, CmdLen)) return;
	//检索下一个分割标记.
	FindSepatateFlag(TempPos, LAST_VALID_WRITE_POS, _PosRead, CmdLen);
}
//设置写入位置.
void CCmdBuffer::SetPosWrite()
{
	_PosWrite = 0;
	//空文件
	if (INVALID_POS<=_PosRead) return;
	//找[0, _PosRead)之间的最后一个SepatateFlag
	//如过存在那就是相应的_PosWrite
	short CmdLen = 0;
	if (0 != _PosRead)
	{
		while( FindSepatateFlag(_PosWrite, _PosRead - 1, _PosWrite, CmdLen) )
		{
			_PosWrite = _PosWrite + CmdLen + SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN;
		}
		if ( (_PosWrite!=0) && (_PosWrite<_PosRead) ) return;	//找到
	}
	//找[_PosRead, LAST_VALID_WRITE_POS]之间的最后一个SepatateFlag
	_PosWrite = _PosRead;
	while( FindSepatateFlag(_PosWrite, LAST_VALID_WRITE_POS, _PosWrite, CmdLen) )
	{
		_PosWrite = _PosWrite + CmdLen + SEPARATE_FLAG_LEN + CMD_LEN_FLAG_LEN;
	}
}

CString CCmdBuffer::GenCmdLen(const short CmdLen)
{
	CString s;
	ASSERT(4 == CMD_LEN_FLAG_LEN);
	s.Format("%4d", CmdLen);
	return s;
}

short CCmdBuffer::GetCmdLen(const char *FlagPos)
{
	short CmdLen;
	char CmdLenBuf[5];
	CmdLenBuf[4] = '\0';
	memcpy(CmdLenBuf, FlagPos + SEPARATE_FLAG_LEN, 4);
	sscanf(CmdLenBuf,"%ld",&CmdLen);
	return CmdLen;
}

bool CCmdBuffer::IsSepatateFlag(const char *buf)
{
	if ( (buf[0] == SEPARATE_FLAG[0]) &&
		 (buf[1] == SEPARATE_FLAG[1]) &&
		 (buf[2] == SEPARATE_FLAG[2]) &&
		 (buf[3] == SEPARATE_FLAG[3]) &&
		 (buf[4] == SEPARATE_FLAG[4]) )
	return true;
	return false;
}

bool CCmdBuffer::IsDeleteFlag(const char *buf)
{
	if ( (buf[0] == DELETE_FLAG[0]) &&
		 (buf[1] == DELETE_FLAG[1]) &&
		 (buf[2] == DELETE_FLAG[2]) &&
		 (buf[3] == DELETE_FLAG[3]) &&
		 (buf[4] == DELETE_FLAG[4]) )
	return true;
	return false;
}
//在[SeekBeg, SeekEnd]之间寻找SepatateFlag,并将位置写入到Pos内
bool CCmdBuffer::FindSepatateFlag(const ULONG SeekBeg, const ULONG SeekEnd, ULONG &Pos, short &CmdLen)
{
	if (SeekBeg > SeekEnd) return false;
	//当SeekEnd < SeekBeg时,将分为两段收索
	char Buf[BUF_CMD_MAX_LEN];
	//[SeekBeg, SeekEnd]
	_BufferFile.Seek(SeekBeg, CFile::begin);
	while( _BufferFile.GetPosition() <= SeekEnd )
	{
		_BufferFile.Read(Buf, sizeof(Buf));//读一部分文件
		for ( UINT FlagPos = 0; 
			  FlagPos < (sizeof(Buf) - SEPARATE_FLAG_LEN - CMD_LEN_FLAG_LEN);
			  FlagPos++)
		{
			if ( IsSepatateFlag(&Buf[FlagPos]) )
			{
				Pos = _BufferFile.GetPosition() - sizeof(Buf) + FlagPos;
				CmdLen = GetCmdLen( &Buf[FlagPos] );
				return true;
			}
		}
	}
	return false;
}
//在[SeekBeg, SeekEnd]之间寻找FindDeleteFlag,并将位置写入到Pos内
bool CCmdBuffer::FindDeleteFlag(const ULONG SeekBeg, const ULONG SeekEnd, ULONG &Pos, short &CmdLen)
{
	if (SeekBeg > SeekEnd) return false;
	_BufferFile.Seek(SeekBeg, CFile::begin);
	char Buf[BUF_CMD_MAX_LEN];
	while( _BufferFile.GetPosition() <= SeekEnd )
	{
		_BufferFile.Read(Buf, sizeof(Buf));//读一部分文件
		for ( UINT FlagPos = 0; 
			  FlagPos < (sizeof(Buf) - SEPARATE_FLAG_LEN - CMD_LEN_FLAG_LEN);
			  FlagPos++)
		{
			if ( IsDeleteFlag(&Buf[FlagPos]) )
			{
				Pos = _BufferFile.GetPosition() - sizeof(Buf) + FlagPos;
				CmdLen = GetCmdLen( &Buf[FlagPos] );
				return true;
			}
		}
	}
	return false;
}


// CmdBuffer.h: interface for the CCmdBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDBUFFER_H__88953385_51AD_4904_B3F9_9C9651B91D77__INCLUDED_)
#define AFX_CMDBUFFER_H__88953385_51AD_4904_B3F9_9C9651B91D77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCmdBuffer  
{
public:
	void DelCmd();
	virtual ~CCmdBuffer();
	void AddCmd(const char * CmdData,const short CmdLen);
	bool GetCmd(char * CmdData, short &CmdLen);
	static CCmdBuffer* Instance();
private:
	CCmdBuffer();
private:
	bool FindSepatateFlag(const ULONG SeekBeg,const ULONG SeekEnd, ULONG &Pos, short &CmdLen);
	bool FindDeleteFlag(const ULONG SeekBeg,const ULONG SeekEnd, ULONG &Pos, short &CmdLen);
	bool IsDeleteFlag(const char *buf);
	bool IsSepatateFlag(const char * buf);
	CString GenCmdLen(const short CmdLen);
	short GetCmdLen(const char * CmdLen);
	bool FindNextCmd(ULONG &CmdPos, short &CmdLen);	//找到下一命令长度和位置
	void SetPosRead();
	void SetPosWrite();
	
	static const short		SEPARATE_FLAG_LEN;	//分割标记长度
	static const char		SEPARATE_FLAG[];	//分割标记
	static const char		DELETE_FLAG[];	//删除标记
	static const short		CMD_LEN_FLAG_LEN;	//命令长度标记长
	static const short		BUF_CMD_MAX_LEN;	//缓冲命令最大长度
	static const ULONG		BUF_FILE_LENGTH;	//缓冲文件长度
	static const ULONG		LAST_VALID_WRITE_POS;//最后可写命令的有效位置
	static const ULONG		INVALID_POS;		//无效位置
	static const CString	BUF_FILE_NAME;		//缓冲文件名
	
	static CCmdBuffer *		_Instance;
	CFile 		_BufferFile;	//缓冲文件指针
	ULONG		_PosRead;	//读命令指针
	ULONG		_PosWrite;	//写命令指针
	HANDLE		_BufMutex;	//读写互斥信号
};

#endif // !defined(AFX_CMDBUFFER_H__88953385_51AD_4904_B3F9_9C9651B91D77__INCLUDED_)

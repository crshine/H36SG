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
	bool FindNextCmd(ULONG &CmdPos, short &CmdLen);	//�ҵ���һ����Ⱥ�λ��
	void SetPosRead();
	void SetPosWrite();
	
	static const short		SEPARATE_FLAG_LEN;	//�ָ��ǳ���
	static const char		SEPARATE_FLAG[];	//�ָ���
	static const char		DELETE_FLAG[];	//ɾ�����
	static const short		CMD_LEN_FLAG_LEN;	//����ȱ�ǳ�
	static const short		BUF_CMD_MAX_LEN;	//����������󳤶�
	static const ULONG		BUF_FILE_LENGTH;	//�����ļ�����
	static const ULONG		LAST_VALID_WRITE_POS;//����д�������Чλ��
	static const ULONG		INVALID_POS;		//��Чλ��
	static const CString	BUF_FILE_NAME;		//�����ļ���
	
	static CCmdBuffer *		_Instance;
	CFile 		_BufferFile;	//�����ļ�ָ��
	ULONG		_PosRead;	//������ָ��
	ULONG		_PosWrite;	//д����ָ��
	HANDLE		_BufMutex;	//��д�����ź�
};

#endif // !defined(AFX_CMDBUFFER_H__88953385_51AD_4904_B3F9_9C9651B91D77__INCLUDED_)

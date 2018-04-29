#if !defined(AFX_CJMDM_H__D4BB750F_A782_492F_8DEA_9D2C6DD1BFEE__INCLUDED_)
#define AFX_CJMDM_H__D4BB750F_A782_492F_8DEA_9D2C6DD1BFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Eltra.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJmdm document

class CJmdm 
{

public:
	CJmdm(int Comport);
	virtual ~CJmdm();
private:
	int m_nPortNo;
	HANDLE m_Handle;

	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	DWORD dwBytesWrite;
	
	char m_TicketNO[9];
	char m_ReadData[32];

public:
	BOOL OpenDev();
	BOOL CloseDev();
	BOOL Send_RMPM_Cmd(int port,BOOL IsON);
	BOOL ReadTicket(char *) ;
	BOOL IsValidTicket();

private:


	// Generated message map functions
protected:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELTRA_H__D4BB750F_A782_492F_8DEA_9D2C6DD1BFEE__INCLUDED_)

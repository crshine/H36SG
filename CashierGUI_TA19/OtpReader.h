// OtpReader.h: interface for the COtpReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTPREADER_H__20EF8D68_EC97_4D90_85A6_634B5F35B4D1__INCLUDED_)
#define AFX_OTPREADER_H__20EF8D68_EC97_4D90_85A6_634B5F35B4D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\OTP\rwl_exp.h"
#pragma comment(lib, "..\\common\\OTP\\rwl.lib")
#pragma message("Automatic link the rwl.lib")

typedef struct {
	BYTE SPID;
	double Amount;
	COleDateTime TransTime;
	DWORD Mid;
}HOTPTRAN, * LPOTPTRAN;


class COtpReader  
{
public:
	COtpReader(BYTE SPID);
	virtual ~COtpReader();
private:
	CString m_szRWLPath;
	int m_nSPID;
private:
	
			
private://reader settings
	//under main section
	BOOL	m_bUseNegVal;  
	BYTE	m_nHouseKeepType; //0..3
	//under exchange section
	CString m_szXFileFolder;
	CString m_szBListFolder;
	CString m_szFWareFolder;
	CString m_szEODFolder;
	CString m_szCCHSFolder;
	CString m_szARFolder1;
	CString m_szARFolder2;
	BYTE	m_nDayKept;
	BYTE	m_nPortNum;
	DWORD	m_dwBaudRate;
	BYTE	m_nTimeOut;
	stDevVer * m_lpVersion;
private:
	DWORD m_dwErrCode;
public:
	void SetComPort(int nPort = 1, DWORD dwBaudRate = 115200);
	void LoadSettings();
	void SaveSettings();
	BOOL SetTimeVerID(DWORD ID = 0);
	BOOL OpenReader();
	void CloseReader();
	BOOL OtpDetect(LPSTR CAN, double & RmnBal, LPOTPTRAN pTran = NULL, BYTE * pClass = NULL,
			WORD * pAvDetail = NULL, DWORD * pAvMach = NULL, BYTE * pLang = NULL, BYTE * pApsUnit = NULL);
	BOOL OtpDeduct(double Amt, double & RmtVal);
	BOOL GenerateXFile(LPSTR XName);
	BOOL Topup(double Amt, BYTE Type, double & RmtVal, int Receipt4DID);
	BOOL OtpHouseKeeping();
	void OtpReset();
	//BOOL CheckPin(int Pin, int szNewPin = 0);
	void RefreshDisplay(double Line1Val, double Line2Val, BYTE Color, BYTE Sound);
	DWORD GetLastError(LPTSTR ErrMsg = NULL);
	void AccessReaderSetting(LPCTSTR lpszTag, LPVOID pValue, BOOL isLoad = TRUE);
	DWORD GetVersion(LPCTSTR lpszTag);
private:
	BOOL AnalysisPollData(LPSTR PollData, LPSTR CAN, LPOTPTRAN * ppTran, BYTE * pClass, 
								  WORD * pAvDetail, DWORD * pAvMach, BYTE * pLang, BYTE * pApsUnit);
	LPSTR GetToken(LPSTR * ppBuf, char Token);
	void CreatePathMap();
};

#endif // !defined(AFX_OTPREADER_H__20EF8D68_EC97_4D90_85A6_634B5F35B4D1__INCLUDED_)

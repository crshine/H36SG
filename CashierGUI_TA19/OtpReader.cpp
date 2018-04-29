// OtpReader.cpp: implementation of the COtpReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OtpReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define _ADD_UTILITIES_DLL_
#include "..\loaddll.h"

#include "..\common\OTP\rwl_exp.h"
#pragma comment(lib, "..\\common\\OTP\\rwl.lib")
#pragma message("Automatic link the rwl.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COtpReader::COtpReader(BYTE SPID)
{
	if (GetWindowsDirectory(m_szRWLPath.GetBuffer(_MAX_PATH), _MAX_PATH) != 0)
	{
		m_szRWLPath.ReleaseBuffer();
		m_szRWLPath += _T("\\RWL.INI");
	}else m_szRWLPath = _T("c:\\windows\\rwl.ini");
	m_lpVersion = new stDevVer;
	m_nSPID = SPID;
	LoadSettings();
	CreatePathMap();

}

COtpReader::~COtpReader()
{
	delete m_lpVersion;
	PortClose();
}
//according to the reader settings, create the path
void COtpReader::CreatePathMap()
{
	CreateDirectory((LPCTSTR)m_szXFileFolder, NULL);
	CreateDirectory((LPCTSTR)m_szEODFolder, NULL);
	CreateDirectory((LPCTSTR)m_szCCHSFolder, NULL);
	CreateDirectory((LPCTSTR)m_szBListFolder, NULL);
	CreateDirectory((LPCTSTR)m_szFWareFolder, NULL);
	CreateDirectory((LPCTSTR)m_szARFolder1, NULL);
	CreateDirectory((LPCTSTR)m_szARFolder2, NULL);
}
//load the settings from the rwl.ini file
void COtpReader::LoadSettings()
{
	//use negative value
	m_bUseNegVal = GetPrivateProfileInt(_T("Main"), _T("NEGVAL"), 0, (LPCTSTR)m_szRWLPath);
	//house keep type
	m_nHouseKeepType = (BYTE)GetPrivateProfileInt(_T("Main"), _T("INITHOUSE"), 1, (LPCTSTR)m_szRWLPath);
	//baud rate
	m_dwBaudRate = (DWORD)GetPrivateProfileInt(_T("COMM"), _T("BAUD"), 115200, (LPCTSTR)m_szRWLPath);
	//port
	m_nPortNum = (BYTE)GetPrivateProfileInt(_T("COMM"), _T("PORT"), 1, (LPCTSTR)m_szRWLPath);
	//time out
	m_nTimeOut = (BYTE)GetPrivateProfileInt(_T("COMM"), _T("TIMEOUT"), 10, (LPCTSTR)m_szRWLPath);
	//get xfile folder
	GetPrivateProfileString(_T("EXCHANGE"), _T("FILEDIR"), _T("C:\\RWL\\UPLOAD"), m_szXFileFolder.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szXFileFolder.ReleaseBuffer();
	//get blacklist folder
	GetPrivateProfileString(_T("BLACKLIST"), _T("FILEDIR"), _T("C:\\RWL\\DOWNLOAD"), m_szBListFolder.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szBListFolder.ReleaseBuffer();
	//get firware folder
	GetPrivateProfileString(_T("FIRMWARE"), _T("FILEDIR"), _T("C:\\RWL\\DOWNLOAD"), m_szFWareFolder.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szFWareFolder.ReleaseBuffer();
	//get eod file folder
	GetPrivateProfileString(_T("EOD"), _T("FILEDIR"), _T("C:\\RWL\\DOWNLOAD"), m_szEODFolder.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szEODFolder.ReleaseBuffer();
	//get cchs file folder
	GetPrivateProfileString(_T("CCHS"), _T("FILEDIR"), _T("C:\\RWL\\DOWNLOAD"), m_szCCHSFolder.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szCCHSFolder.ReleaseBuffer();
	//get ar1 file folder
	GetPrivateProfileString(_T("AR"), _T("DIR1"), _T("C:\\RWL\\AR"), m_szARFolder1.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szARFolder1.ReleaseBuffer();
	//get ar2 file folder
	GetPrivateProfileString(_T("AR"), _T("DIR2"), _T("C:\\RWL\\AR"), m_szARFolder2.GetBuffer(_MAX_PATH), _MAX_PATH, (LPCTSTR)m_szRWLPath);
	m_szARFolder2.ReleaseBuffer();
	//get date keep
	m_nDayKept = (BYTE)GetPrivateProfileInt(_T("AR"), _T("DAYKEEP"), 7, (LPCTSTR)m_szRWLPath);

}
//save the settings into the rwl.ini file
void COtpReader::SaveSettings()
{
	//use negative value
	CString tmpstr;
	tmpstr.Format("%d", m_bUseNegVal);
	WritePrivateProfileString(_T("Main"), _T("NEGVAL"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
	//house keep type
	tmpstr.Format("%d", m_nHouseKeepType);
	WritePrivateProfileString(_T("Main"), _T("INITHOUSE"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
	//baud rate
	tmpstr.Format("%d", m_dwBaudRate);
	WritePrivateProfileString(_T("COMM"), _T("BAUD"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
	//port
	tmpstr.Format("%d", m_nPortNum);
	WritePrivateProfileString(_T("COMM"), _T("PORT"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
	//time out
	tmpstr.Format("%d", m_nTimeOut);
	WritePrivateProfileString(_T("COMM"), _T("TIMEOUT"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
	//Write xfile folder
	WritePrivateProfileString(_T("EXCHANGE"), _T("FILEDIR"), (LPCTSTR)m_szXFileFolder, (LPCTSTR)m_szRWLPath);
	//Write blacklist folder
	WritePrivateProfileString(_T("BLACKLIST"), _T("FILEDIR"), (LPCTSTR)m_szBListFolder, (LPCTSTR)m_szRWLPath);
	//Write firware folder
	WritePrivateProfileString(_T("FIRMWARE"), _T("FILEDIR"), (LPCTSTR)m_szFWareFolder, (LPCTSTR)m_szRWLPath);
	//Write eod file folder
	WritePrivateProfileString(_T("EOD"), _T("FILEDIR"), (LPCTSTR)m_szEODFolder, (LPCTSTR)m_szRWLPath);
	//Write cchs file folder
	WritePrivateProfileString(_T("CCHS"), _T("FILEDIR"), (LPCTSTR)m_szCCHSFolder, (LPCTSTR)m_szRWLPath);
	//Write ar1 file folder
	WritePrivateProfileString(_T("AR"), _T("DIR1"), (LPCTSTR)m_szARFolder1, (LPCTSTR)m_szRWLPath);
	//Write ar2 file folder
	WritePrivateProfileString(_T("AR"), _T("DIR2"), (LPCTSTR)m_szARFolder2, (LPCTSTR)m_szRWLPath);
	//Write date keep
	tmpstr.Format("%d", m_nDayKept);
	WritePrivateProfileString(_T("AR"), _T("DAYKEEP"), (LPCTSTR)tmpstr, (LPCTSTR)m_szRWLPath);
}
//set time, get version and set location id
BOOL COtpReader::SetTimeVerID(DWORD ID)
{
	int ret = TimeVer((BYTE *)m_lpVersion);
	showOtpErr(ret);
	if (ret != 0) 
	{
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	if (ID == 0) return TRUE;
	ret = WriteID(ID);
	if (ret == 0) return TRUE;
	else {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
}
//open the reader
BOOL COtpReader::OpenReader()
{
	int ret = InitComm(m_nPortNum, m_dwBaudRate);
	showOtpErr(ret);
	if (ret == 0) 
	{
		RefreshDisplay(-3000.1, -3000.1, 8, 4);
		Sleep(100);
		RefreshDisplay(-3000.1, -3000.1, 8, 1);
		Sleep(100);
		RefreshDisplay(-3000.1, -3000.1, 8, 3);
		Sleep(100);
		RefreshDisplay(-3000.1, -3000.1, 8, 2);
		Sleep(100);
		RefreshDisplay(-3000.1, -3000.1, 8, 4);
		Sleep(100);
		RefreshDisplay(-3000, -3000, 2, 1);
		return TRUE;
	}
	else {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
}
//close the reader
void COtpReader::CloseReader()
{
	PortClose();
}
//polling
BOOL COtpReader::OtpDetect(LPSTR CAN, double & RmnBal, LPOTPTRAN pTran, BYTE * pClass, WORD * pAvDetail, DWORD * pAvMach, BYTE * pLang, BYTE * pApsUnit)
{
	int ret;
	char PollData[512];
	memset(PollData, 0, 512);
	BYTE subcomm;
	if (!pTran) subcomm = 0;
	else subcomm = 2;
	
	ret = Poll(subcomm, m_nTimeOut, PollData);
	
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	RmnBal = (double)ret * 0.1;
	if (!AnalysisPollData(PollData, CAN, &pTran, pClass, pAvDetail, pAvMach, pLang, pApsUnit))
		return FALSE;
	else
		return TRUE;
}

BOOL COtpReader::OtpDeduct(double Amt, double & RmtVal)
{	
	int Amt10Cents = (int)(Amt * 10);
	char AIInfo[65];
	int ret = Deduct(Amt10Cents, (LPBYTE)AIInfo);
	showOtpErr(ret);
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	RmtVal = (double)ret * 0.1;
	return TRUE;
}
//generate the xfile and with the file naem output
BOOL COtpReader::GenerateXFile(LPSTR XName)
{
	int ret = XFile(XName);
	showOtpErr(ret);
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	return TRUE;
}
//top up a octopus card
BOOL COtpReader::Topup(double Amt, BYTE Type, double & RmtVal, int Receipt4DID)
{
	int Amt10Cents = (int)(Amt * 10);
	char AIInfo[65];
	int ret = AddValue(Amt10Cents, Type, (LPBYTE)AIInfo);
	showOtpErr(ret);
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	RmtVal = (double)ret * 0.1;
	return TRUE;
}
BOOL COtpReader::OtpHouseKeeping()
{
	int ret = HouseKeeping();
	showOtpErr(ret);
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	return TRUE;
}
//reset
void COtpReader::OtpReset()
{
	Reset();
}
/*//check the correctness of the pin.
BOOL COtpReader::CheckPin(int Pin, int NewPin)
{
	int ret = PIN(Pin, NewPin);
	if (ret > 100000) {
		m_dwErrCode = ret - 100000;
		return FALSE;
	}
	return TRUE;
}*/
void COtpReader::RefreshDisplay(double Line1Val, double Line2Val, BYTE Color, BYTE Sound)
{
	int Line1 = (int)(Line1Val * 10);
	int Line2 = (int)(Line2Val * 10);
	TxnAmt(Line1, Line2, Color, Sound);
}
DWORD COtpReader::GetLastError(LPTSTR ErrMsg)
{
	return m_dwErrCode;
}
BOOL COtpReader::AnalysisPollData(LPSTR PollData, LPSTR CAN, LPOTPTRAN * ppTran, BYTE * pClass, 
								  WORD * pAvDetail, DWORD * pAvMach, BYTE * pLang, BYTE * pApsUnit)
{
	int mylen, Len = strlen(PollData);
	LPSTR pos = PollData;
	int ipos = 0;
	mylen = 0;
	
	LPSTR lpstr;
	
	lpstr = GetToken(&pos, ',');
	if (strlen(lpstr) < 1) return FALSE;
	if (CAN) strcpy(CAN, lpstr);

	if (pAvDetail) 
	{
		*pAvDetail = Str2Int(GetToken(&pos, '-'), -1);
		if (*pAvDetail < 0) return FALSE;
	}

	if (pAvMach) {
		*pAvMach = Str2Long(GetToken(&pos, '-'), -1);
		if (*pAvMach < 0) return FALSE;
	}

	if (pClass) {
		*pClass = Str2Int(GetToken(&pos, '-'), -1);
		if (*pClass < 0) return FALSE;
	}

	if (pLang) {
		*pLang = Str2Int(GetToken(&pos, '-'), -1);
		if (*pLang < 0) return FALSE;
	}

	if (pApsUnit) {
		*pApsUnit = Str2Int(GetToken(&pos, ','), -1);
		if (* pApsUnit < 0) return FALSE;
	}

	if (strlen(pos) < 1) return TRUE;//for subcomm = 0; only can, and patron info
	//for subcomm = 1 or 2, have manufactury id and transaction log
	
	lpstr = GetToken(&pos, ',');
	if (strlen(lpstr) < 1) return FALSE;
//	if (pManuID) strcpy(pManuID, lpstr);

	if (!(*ppTran)) return TRUE;
	
	int SPID, Amt, sTime, Mid;
	LPSTR SInfo;
	COleDateTime xtime(2000, 1, 1, 0, 0, 0);
	while (TRUE)
	{
		SPID = Str2Int(GetToken(&pos, ','), -1);
		Amt = Str2Int(GetToken(&pos, ','), -1);
		sTime = Str2Long(GetToken(&pos, ','), -1);
		Mid = Str2Int(GetToken(&pos, ','), -1);
		SInfo = GetToken(&pos, ',');
		if (SPID == m_nSPID)
		{
			//assign the value into the structure.
			(*ppTran)->SPID = SPID;
			(*ppTran)->Amount = (double)Amt * 0.1;
			(*ppTran)->TransTime = COleDateTime((double)(DATE)xtime + (double)sTime / 86400);
			(*ppTran)->Mid = Mid;
			break;
		}
		if (strlen(pos) < 1) 
		{ *ppTran = NULL;	break;}
	}
	return TRUE;
}

LPSTR COtpReader::GetToken(LPSTR * ppBuf, char Token)
{
	LPSTR ret = *ppBuf;
	int len = strlen(*ppBuf);
	for (int i=0; i<len; i++)
	{
		if ((*ppBuf)[i] == Token){
			(*ppBuf)[i] = 0;
			(*ppBuf) = (*ppBuf) + i + 1;
			return ret;
		}
	}
	(*ppBuf) = (*ppBuf) + i;
	return ret;
}

void COtpReader::AccessReaderSetting(LPCTSTR lpszTag, LPVOID pValue, BOOL isLoad)
{
	if (isLoad){
		if (_tcscmp(lpszTag, _T("USENEGVAL")) == 0) {
			memcpy(pValue, &m_bUseNegVal, sizeof(m_bUseNegVal));
		} else if (_tcscmp(lpszTag, _T("HOUSEKEEPTYPE")) == 0){
			memcpy(pValue, &m_nHouseKeepType, sizeof(m_nHouseKeepType));
		} else if (_tcscmp(lpszTag, _T("PORTNUM")) == 0) {		
			memcpy(pValue, &m_nPortNum, sizeof(m_nPortNum));
		} else if (_tcscmp(lpszTag, _T("BAUDRATE")) == 0) {	
			memcpy(pValue, &m_dwBaudRate, sizeof(m_dwBaudRate));
		} else if (_tcscmp(lpszTag, _T("TIMEOUT")) == 0) {
			memcpy(pValue, &m_nTimeOut, sizeof(m_nTimeOut));
		} else if (_tcscmp(lpszTag, _T("KEEPDAYS")) == 0) {
			memcpy(pValue, &m_nDayKept, sizeof(m_nDayKept));
		} else if (_tcscmp(lpszTag, _T("XPATH")) == 0) {
			memcpy(pValue, m_szXFileFolder.GetBuffer(0), (m_szXFileFolder.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("EODPATH")) == 0) {
			memcpy(pValue, m_szXFileFolder.GetBuffer(0), (m_szXFileFolder.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("CCHSPATH")) == 0) {	
			memcpy(pValue, m_szCCHSFolder.GetBuffer(0), (m_szCCHSFolder.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("AR1PATH")) == 0) {
			memcpy(pValue, m_szARFolder1.GetBuffer(0), (m_szARFolder1.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("AR2PATH")) == 0) {		
			memcpy(pValue, m_szARFolder2.GetBuffer(0), (m_szARFolder2.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("BLPATH")) == 0) {		
			memcpy(pValue, m_szBListFolder.GetBuffer(0), (m_szBListFolder.GetLength() + 1) * sizeof(TCHAR));
		} else if (_tcscmp(lpszTag, _T("FWPATH")) == 0) {
			memcpy(pValue, m_szFWareFolder.GetBuffer(0), (m_szFWareFolder.GetLength() + 1) * sizeof(TCHAR));
		}
	}else{
		if (_tcscmp(lpszTag, _T("USENEGVAL")) == 0) {
			memcpy(&m_bUseNegVal, pValue, sizeof(m_bUseNegVal));
		} else if (_tcscmp(lpszTag, _T("HOUSEKEEPTYPE")) == 0){
			memcpy(&m_nHouseKeepType, pValue, sizeof(m_nHouseKeepType));
		} else if (_tcscmp(lpszTag, _T("PORTNUM")) == 0) {		
			memcpy(&m_nPortNum, pValue, sizeof(m_nPortNum));
		} else if (_tcscmp(lpszTag, _T("BAUDRATE")) == 0) {	
			memcpy(&m_dwBaudRate, pValue, sizeof(m_dwBaudRate));
		} else if (_tcscmp(lpszTag, _T("TIMEOUT")) == 0) {
			memcpy(&m_nTimeOut, pValue, sizeof(m_nTimeOut));
		} else if (_tcscmp(lpszTag, _T("KEEPDAYS")) == 0) {
			memcpy(&m_nDayKept, pValue, sizeof(m_nDayKept));
		} else if (_tcscmp(lpszTag, _T("XPATH")) == 0) {
			memcpy(m_szXFileFolder.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1)* sizeof(TCHAR));
			m_szXFileFolder.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("EODPATH")) == 0) {
			memcpy(m_szEODFolder.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szEODFolder.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("CCHSPATH")) == 0) {	
			memcpy(m_szCCHSFolder.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szCCHSFolder.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("AR1PATH")) == 0) {
			memcpy(m_szARFolder1.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szARFolder1.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("AR2PATH")) == 0) {		
			memcpy(m_szARFolder2.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szARFolder2.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("BLPATH")) == 0) {		
			memcpy(m_szBListFolder.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szBListFolder.ReleaseBuffer();
		} else if (_tcscmp(lpszTag, _T("FWPATH")) == 0) {
			memcpy(m_szFWareFolder.GetBuffer(_MAX_PATH), pValue, (_tcslen((LPTSTR)pValue) + 1) * sizeof(TCHAR));
			m_szFWareFolder.ReleaseBuffer();
		}
	}
}

DWORD COtpReader::GetVersion(LPCTSTR lpszTag)
{
	if (_tcscmp(lpszTag, _T("DEVID")) == 0) {
		return (m_lpVersion->DevID);
	}else if (_tcscmp(lpszTag, _T("OPTRID")) == 0) {
		return (m_lpVersion->OperID);
	}else if (_tcscmp(lpszTag, _T("COMPID")) == 0) {
		return (m_lpVersion->CompID);
	}else if (_tcscmp(lpszTag, _T("KEYVER")) == 0) {
		return (m_lpVersion->KeyVer);
	}else if (_tcscmp(lpszTag, _T("EODVER")) == 0) {
		return (m_lpVersion->EODVer);
	}else if (_tcscmp(lpszTag, _T("BLVER")) == 0) {
		return (m_lpVersion->BLVer);
	}else if (_tcscmp(lpszTag, _T("FIRMVER")) == 0) {
		return (m_lpVersion->FIRMVer);
	}else if (_tcscmp(lpszTag, _T("CCHSVER")) == 0) {
		return (m_lpVersion->CCHSVer);
	}else if (_tcscmp(lpszTag, _T("CSSER")) == 0) {
		return (m_lpVersion->CSSer);
	}else if (_tcscmp(lpszTag, _T("DEVTIME")) == 0) {
		return (m_lpVersion->DevTime);
	}
	return 0;
}


void COtpReader::SetComPort(int nPort, DWORD dwBaudRate)
{
	m_nPortNum = nPort;
	m_dwBaudRate = dwBaudRate;
}

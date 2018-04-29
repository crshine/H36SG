#ifndef _RECEIPTPRN_H_
#define _RECEIPTPRN_H_
 
class AFX_EXT_CLASS CReceiptPrn : public CObject
{
public:
	CReceiptPrn(
		CString PortName, CString Starter[], CString Ending[], 
		int leftspc, int linespc, int cutline,
		CString TaxName, CString TaxNo, int TaxPerc, int StationID, long DevID);
	virtual ~CReceiptPrn();
public:
	BOOL PrintAddValueReceipt(
				LONG         av_ReceiptNo, 
				CString      av_ReceiptOtpNo, 
				COleDateTime av_ReceiptPayTime,
				double       av_ReceiptAmt, 
		        double       av_ReceiptOtpOldBal,
				double       av_ReceiptOtpNewBal,
				double       av_ReceiptCash,
				double       av_ReceiptChange
				);
	BOOL PrintSeasonCreate(
				LONG         sc_ReceiptNo, 
				CString      sc_ReceiptCardNo, 
				COleDateTime sc_ReceiptPayTime,
				COleDateTime sc_ReceiptValidFrom,
				COleDateTime sc_ReceiptValidTo,
				double       sc_ReceiptAmt, 
				double       sc_ReceiptCash,
				double       sc_ReceiptChange
				);
	BOOL PrintSeasonExtend(
				LONG         se_ReceiptNo, 
				CString      se_ReceiptCardNo, 
				COleDateTime se_ReceiptPayTime,
				COleDateTime se_ReceiptExtendFrom,
				COleDateTime se_ReceiptExtendTo,
				double       se_ReceiptAmt, 
				double       se_ReceiptCash,
				double       se_ReceiptChange
				);
	BOOL PrintShiftCloseReceipt(
				CString Operator, 
				LONG ReceiptNo, 
				COleDateTime DutyStart, 
				int PayNum, 
				double CashAmt, 
				double CCAmt, 
				double SVAmt,
				double ShiftCashMaintain);
	DWORD GetErrCode();
	BOOL PrintParkingReceipt(
		        LONG ReceiptNo, 
		        LPSTR CAN, 
				LPSTR PayCAN, 
				BOOL IsReply,
				LPSTR Cate, 
				double EnterTime,
				double LastPayTime,
				double PayTime,
				LPSTR DiscountStr,
				double fFareCardAmt, 
				double fFareCardBal,
				double fStoreValueAmt, 
				double fStoreValueBal,
				double ReceiptCash, 
				double ReceiptChange,
				short  VehicleType,
				CString Remark
				);

	BOOL CReceiptPrn::OpenDrawer() 
	{
		/*	char abuf[] = {27, 112,0}; return SendtoPrn(abuf, 3); */
		return TRUE;
	}

//	void PrintAccountInfo(CString Operator, CTime Time, CString Category[], int TransNum[], double CCAmt, double SVAmt);
	BOOL PrintBarrierReceipt(CString Operator, CTime Time, CString Reason);
	BOOL InitPrinter();
	BOOL PrintHeader();
	BOOL PrintEnding();
	BOOL PrintTax();
	BOOL PrintLine(LPSTR datamsg, BOOL isCentre);
	void LoadChineseFontLib();
	BOOL AuxReset();
	BOOL SendtoPrn(LPCVOID pbuf, DWORD MsgLen);
	BOOL SetLineSpace(BYTE dotNo);//default is 16 dots
	BOOL SetCharSpace(BYTE dotNo); //default is 4 dots
	BOOL CharsReverse(BOOL isActive);
private:
	long m_DevID;
	DWORD m_dwErrCode;
	BOOL m_isDeviceOK;
	int m_nStationID;
	CString m_lpStarter[3];
	CString m_lpEnding[2];
	CString m_lpTaxName, m_lpTaxNo;
	int m_nLeftSpc, m_nLineSpc, m_nCutLine, m_nTaxPerc;
	HANDLE m_RPrn;
	CFile * pfile;//chinese font lib
	BOOL bChineseAvailable;
protected:
	BOOL CharSize(int H, int W);
	void ConvertDotMatrix(BYTE * ByteBuf);
	BOOL PrintLSpc();
	// This class is exported from the Rprn.dll
	void WritePrint(LPCVOID pbuf, DWORD MsgLen);
	BOOL SetOutOfPaperInstruction(BOOL bEnabled);
	HANDLE OpenRPrn(LPCTSTR PortName);
	void CloseRPrn();
	BOOL PrintLine(CString datamsg, BOOL isCentre);
	
	BOOL LineFeed();
	BOOL PrintFeed(BYTE dotLine);
	BOOL PrintFeedBack(BYTE dotLine);

	BOOL LineInverse(BOOL isActive);//turn on/off(default) inverse print by line
	BOOL CharRotate(BYTE Rotate);//rotate the char; 0: Non-rotate; 1: 90' right; 2; 90'left; 3: ignoral
	//Character Shape modification
	BOOL CharsUnderLine(BYTE LineWidth);
	BOOL CharsDblWidth(BOOL isActive);
	BOOL CharsDblHeight(BOOL isActive);
	
	BOOL CharsBold(BOOL isActive);//composed by 2 cmds(Esc+E; Esc+F);
	//BarCode
	BOOL BCodeSelect(BYTE Mode, CString Data);//mode =4 barcode 39.
	BOOL BCodeWidth(BYTE NWidth, BYTE WWidth);//narrow width= 1(3 dots); wide 2(9 dots)
	BOOL BCodePos(BYTE Pos);//pos = 0-left; 1-centre; 2-right;
	BOOL BCodeHeight(BYTE Height);
	BOOL BCodeCharPos(BYTE Pos);//pos= 0-No print; 1-top; 2-bottom; 3-top and bottom.
	BOOL BCodeCharSize(BYTE Size);//size = 0-24*12; 1-16*8
	//Auxiliary functions
	BOOL AuxMarkDetect(BYTE DetectCon, int DotsLen);
	BOOL AuxNoPaperAct(BOOL act);
	BOOL AuxCancel();
	
	BOOL AuxFullCut();
	BOOL AuxPartialCut();
	BOOL PrintChineseChar(int ID);
	BOOL GetFontMatrix(int ID, BYTE * Buf);
};

#endif
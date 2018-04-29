// DlgCardRenew.cpp : implementation file
//

#include "stdafx.h"
#include "cashiergui.h"
#include "DlgCardRenew.h"
#include "cmdotp.h"
#include "cmdkde.h"
#include "setting.h"
#include "cmdmntsend.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCardRenew dialog


CDlgCardRenew::CDlgCardRenew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCardRenew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCardRenew)
	m_CardNum = _T("");
	m_CardType = _T("");
	m_NewPeriod = _T("");
	m_OrgPeriod = _T("");
	m_OrgTransNum = 0;
	m_AmountPeriod = _T("");
	m_PricePeriod = _T("");
	m_ValidFrom = COleDateTime::GetCurrentTime();
	m_ValidTo = COleDateTime::GetCurrentTime();
	m_AmountSV = _T("");
	m_AmountTotal = _T("");
	m_AmountTransNum = _T("");
	m_PriceTransNum = _T("");
	m_NewSV = _T("");
	m_OrgSV = _T("");
	m_NewTransNum = 0;
	m_AddSV = _T("");
	m_AddTransNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgCardRenew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCardRenew)
	DDX_Text(pDX, IDC_CARDNUM, m_CardNum);
	DDX_Text(pDX, IDC_CARDTYPE, m_CardType);
	DDX_Text(pDX, IDC_CURPERIOD, m_NewPeriod);
	DDX_Text(pDX, IDC_ORGPERIOD, m_OrgPeriod);
	DDX_Text(pDX, ORGTRANSTIMES, m_OrgTransNum);
	DDX_Text(pDX, PERIOD_AMOUNT, m_AmountPeriod);
	DDX_Text(pDX, PERIOD_PRICE, m_PricePeriod);
	DDX_DateTimeCtrl(pDX, PERIODFROM, m_ValidFrom);
	DDX_DateTimeCtrl(pDX, PERIODTO, m_ValidTo);
	DDX_Text(pDX, STOREVALUE_AMOUNT, m_AmountSV);
	DDX_Text(pDX, TOTAL, m_AmountTotal);
	DDX_Text(pDX, TRANSACTION_AMOUNT, m_AmountTransNum);
	DDX_Text(pDX, TRANSACTION_PRICE, m_PriceTransNum);
	DDX_Text(pDX, NEWSTOREVALUE, m_NewSV);
	DDX_Text(pDX, ORGSTOREVALUE, m_OrgSV);
	DDX_Text(pDX, NEWTRANSTIMES, m_NewTransNum);
	DDX_Text(pDX, ADDSTOREVALUE, m_AddSV);
	DDX_Text(pDX, ADDTRANSTIMES, m_AddTransNum);
	DDV_MinMaxInt(pDX, m_AddTransNum, 0, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCardRenew, CDialog)
	//{{AFX_MSG_MAP(CDlgCardRenew)
	ON_WM_TIMER()
	ON_BN_CLICKED(RADIO_1M, On1m)
	ON_BN_CLICKED(RADIO_2M, On2m)
	ON_BN_CLICKED(RADIO_3M, On3m)
	ON_BN_CLICKED(RADIO_6M, On6m)
	ON_BN_CLICKED(RADIO_12M, On12m)
	ON_BN_CLICKED(RADIO_24M, On24m)
	ON_EN_CHANGE(ADDSTOREVALUE, OnChangeADDSTOREVALUE)
	ON_NOTIFY(DTN_CLOSEUP, PERIODFROM, OnCloseupPERIODFROM)
	ON_NOTIFY(DTN_CLOSEUP, PERIODTO, OnCloseupPERIODTO)
	ON_EN_CHANGE(ADDTRANSTIMES, OnChangeADDTRANSTIMES)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCardRenew message handlers

BOOL CDlgCardRenew::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSetting * pSetting = CSetting::Instance();
	GetDlgItem(PERIOD_AMOUNT)->SetFont(&pSetting->FontMid());
	GetDlgItem(TRANSACTION_AMOUNT)->SetFont(&pSetting->FontMid());
	GetDlgItem(TOTAL)->SetFont(&pSetting->FontMid());
	//GetDlgItem(STORE_VALUE)->SetFont(&pSetting->FontMid());
	showTip("請拍所需續期的八達通卡或插入磁卡...", true);
	m_AddTransNum = 0;
	m_AddSV = "";
	m_AmountPeriod = "";
	m_AmountSV = "";
	m_AmountTotal = "";
	m_AmountTransNum = "";
	m_PricePeriod = "";
	hasotpcard = false;
	haskdecard = false;
	m_PriceTransNum = "";
	_Amount = _PeriodFee = _TransactionFee = _StoreValueFee = 0.0;
	UpdateData(FALSE);
	if (CCmdOtp::Instance()->IsConnection()) SetTimer(1, 1600, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCardRenew::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	//Auto Read KDE or Otp
	// TODO: Add your message handler code here and/or call default
	CCmdOtp * pCmdOtp = CCmdOtp::Instance();
	CCmdOtp::PATRON CardInfo;
	CCmdKde * pCmdKde = CCmdKde::Instance();
	CCmdKde::PATRON CardInfo1;
	
	if (!haskdecard && pCmdKde->KDE_NeedRead()){
		if (pCmdKde->KDE_ReadTicket(CardInfo1))
		{
			m_CardType = "磁條卡";
			haskdecard = true;
			m_CardNum = CardInfo1._CardNo.Mid(1);
			UpdateData(FALSE);
		}
		else
		{
			pCmdKde->KDE_EjectCard();
			haskdecard = false;
			showTip("請取出磁條卡!", true);
			while (pCmdKde->KDE_NeedRead()) Sleep(1000);
			showTip("請拍所需續期的八達通卡或插入磁卡...", true);
		}
	}
	if (!haskdecard)
	{
		if (pCmdOtp->OTP_Poll(CardInfo))
		{
			m_CardType = "八達通卡";
			hasotpcard = true;
			m_CardNum = CardInfo._CardNo.Mid(1);
			UpdateData(FALSE);
		}else {
			hasotpcard = false;
			m_CardType = "";
			m_CardNum = "";
			UpdateData(FALSE);
		}
	}
	if (haskdecard || hasotpcard)
	{//retreive information from internet.
		
		if (_CardNo == (m_CardType == "八達通卡"?"O":"P") + m_CardNum) 
		{
			SetTimer(1, 1600, 0);
			return;
		}
		_CardNo = (m_CardType == "八達通卡"?"O":"P") + m_CardNum;
		CCmdMntSend * pSend = CCmdMntSend::Instance();
		CCmdMntSend::HCARDSTATUS CardStatus;
		if (pSend->QueryCardStatus(_CardNo, CardStatus))
		{//if found from server
			if (!CardStatus._IsSpecialCard)
			{
				GetDlgItem(IDOK)->EnableWindow(FALSE);
//				::AfxMessageBox("This Card is not a special card!", MB_ICONSTOP);
				::AfxMessageBox("這不是季票, 無法續期!", MB_ICONSTOP|MB_SYSTEMMODAL);
				_CardNo = "";
				if (haskdecard)
				{
					pCmdKde->KDE_EjectCard();
					haskdecard = false;
					showTip("請取出磁條卡!", true);
					while (pCmdKde->KDE_NeedRead()) Sleep(1000);
					showTip("請拍所需續期的八達通卡或插入磁卡...", true);
				}
				if (hasotpcard)
				{
					pCmdOtp->WaitForOtpRemove();
				}
			}else{
				_CardTypeId = CardStatus._SpecialCardInfo._CardType;
				_Status		= CardStatus._SpecialCardInfo._Status;
				_RegTime	= CardStatus._SpecialCardInfo._RegTime;
				_HolderID	= _ttol(CardStatus._SpecialCardInfo._HolderID);
				_ValidFrom  = CardStatus._SpecialCardInfo._ValidForm;
				_ValidTo	= CardStatus._SpecialCardInfo._ValidTo;
				_ValidTranTimes = CardStatus._SpecialCardInfo._ValidTimes;
				_StoreValue = CardStatus._SpecialCardInfo._StoreValue;
				m_ValidFrom = _ValidFrom;
				m_ValidTo = _ValidTo;
				m_OrgSV = show(_StoreValue);
				m_NewSV = show(_StoreValue);
				m_OrgTransNum = _ValidTranTimes;
				m_NewTransNum = _ValidTranTimes;
				m_OrgPeriod.Format("%s - %s", _ValidFrom.Format("%b %d %Y"),  _ValidTo.Format("%b %d %Y"));
				m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"),  m_ValidTo.Format("%b %d %Y"));
				
				if (CSetting::Instance()->m_CardType.WorkMode(_CardTypeId) == 0)
				{
					m_PricePeriod = CSetting::Instance()->m_CardType.showPrice(_CardTypeId);
					m_PriceTransNum = "";
					((CEdit *)GetDlgItem(ADDTRANSTIMES))->SetReadOnly(TRUE);
					GetDlgItem(PERIODFROM)->EnableWindow(TRUE);
					GetDlgItem(PERIODTO)->EnableWindow(TRUE);
					GetDlgItem(RADIO_1M)->EnableWindow(TRUE);
					GetDlgItem(RADIO_2M)->EnableWindow(TRUE);
					GetDlgItem(RADIO_3M)->EnableWindow(TRUE);
					GetDlgItem(RADIO_6M)->EnableWindow(TRUE);
					GetDlgItem(RADIO_12M)->EnableWindow(TRUE);
					GetDlgItem(RADIO_24M)->EnableWindow(TRUE);
				}else{
					m_PriceTransNum = CSetting::Instance()->m_CardType.showPrice(_CardTypeId);
					m_PricePeriod = "";
					((CEdit *)GetDlgItem(ADDTRANSTIMES))->SetReadOnly(FALSE);
					GetDlgItem(PERIODFROM)->EnableWindow(FALSE);
					GetDlgItem(PERIODTO)->EnableWindow(FALSE);
					GetDlgItem(RADIO_1M)->EnableWindow(FALSE);
					GetDlgItem(RADIO_2M)->EnableWindow(FALSE);
					GetDlgItem(RADIO_3M)->EnableWindow(FALSE);
					GetDlgItem(RADIO_6M)->EnableWindow(FALSE);
					GetDlgItem(RADIO_12M)->EnableWindow(FALSE);
					GetDlgItem(RADIO_24M)->EnableWindow(FALSE);
				}
				if (CSetting::Instance()->m_CardType.StoreValue(_CardTypeId))
				{
					GetDlgItem(ORGSTOREVALUE)->ShowWindow(SW_SHOW);
					GetDlgItem(ADDSTOREVALUE)->ShowWindow(SW_SHOW);
					GetDlgItem(NEWSTOREVALUE)->ShowWindow(SW_SHOW);
					GetDlgItem(STOREVALUE_AMOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_SHOW);
				}else{
					GetDlgItem(ORGSTOREVALUE)->ShowWindow(SW_HIDE);
					GetDlgItem(ADDSTOREVALUE)->ShowWindow(SW_HIDE);
					GetDlgItem(NEWSTOREVALUE)->ShowWindow(SW_HIDE);
					GetDlgItem(STOREVALUE_AMOUNT)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_3)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_4)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
				}
				GetDlgItem(IDOK)->EnableWindow(TRUE);
				UpdateData(FALSE);
			}

		}else{//cannot found from server
			//showTip("Cannot proceed without communication!", true);
			showTip("通訊中斷，操作無法完成！", true);
			GetDlgItem(IDOK)->EnableWindow(FALSE);
			_CardNo = "";
		}
	}
	SetTimer(1, 1000, 0);
	CDialog::OnTimer(nIDEvent);
}

void CDlgCardRenew::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if (!haskdecard && !hasotpcard)
	{	
//		::AfxMessageBox("Please place your special card first!");
		::AfxMessageBox("請拍季票八達通卡 / 插入磁季票!",MB_SYSTEMMODAL);
		return;
	}
	if ((_ValidFrom == m_ValidFrom) && (_ValidTo == m_ValidTo) && (_ValidTranTimes == m_AddTransNum))
	{
//		::AfxMessageBox("No Changes At All! Abort!");
		::AfxMessageBox("未完成續期操作! 請繼續...",MB_SYSTEMMODAL);
		return;
	}
	_ValidFrom = m_ValidFrom;
	_ValidTo = m_ValidTo;
	_ValidTranTimes = m_NewTransNum;

	CDialog::OnOK();
}

//add month to the end of the validity period
void CDlgCardRenew::AddMonth(short Month)
{
	UpdateData(true);
	COleDateTime x = _ValidTo;
	short Year = x.GetYear();
	Month += x.GetMonth();
	
	while (Month > 12)
	{
		Month -= 12;
		++Year;
	}
	short day = x.GetDay();
	if ((day >= 29) && (Month == 2)) {day =1; Month = 3;}
	if (day == 31)
	{
		if ((Month == 2) || (Month == 4) ||(Month == 6) ||(Month == 9) ||(Month == 11)) 
		{
			day = 1; Month ++;
		}
	}
	x.SetDateTime(Year, Month, day, 0, 0, 0);
	m_ValidTo = x;
	UpdateData(false);
}


void CDlgCardRenew::On1m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(1);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
	
}

void CDlgCardRenew::On2m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(2);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}

void CDlgCardRenew::On3m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(3);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}

void CDlgCardRenew::On6m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(6);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}

void CDlgCardRenew::On12m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(12);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}

void CDlgCardRenew::On24m() 
{
	// TODO: Add your control notification handler code here
	AddMonth(24);
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}



BOOL CDlgCardRenew::Calculate(COleDateTime ValidFrom, COleDateTime ValidTo, 
							  int CardCate, COleDateTime StartTime, COleDateTime EndTime, double & Fee)
{
	if (StartTime > EndTime) 
	{
//		::AfxMessageBox(_T("Err: Start time must smaller than End time!"), MB_OK|MB_ICONSTOP);
		::AfxMessageBox(_T("錯誤 : 有效日期不正確!"), MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		return FALSE;

	}
	COleDateTime today = COleDateTime::GetCurrentTime ();
	if (EndTime < today)
	{
//		::AfxMessageBox(_T("Err: End time small than today!"), MB_OK|MB_ICONSTOP);
		::AfxMessageBox(_T("錯誤 : 有效日期不正確!"), MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
		return FALSE;
	}
	if (StartTime < today) StartTime = today;
	COleDateTime Zone1Start, Zone1End, Zone2Start, Zone2End;
	COleDateTimeSpan leftzone, rightzone;
	if (StartTime < ValidFrom )
	{
		Zone1Start = StartTime;
		if (EndTime > ValidFrom ) Zone1End = ValidFrom;
		else Zone1End = EndTime;
		leftzone = Zone1End - Zone1Start;
	} else 
	{	
		Zone1Start = StartTime;
		Zone1End = StartTime;
	}

	if (EndTime > ValidTo)
	{
		Zone2End = EndTime;
		if (StartTime > ValidTo ) Zone2Start = StartTime;
		else Zone2Start = ValidTo ;
	}
	else
	{
		Zone2Start = EndTime;
		Zone2End = EndTime;
	}
	double fee1, fee2;
	if (!CalculateZone(CardCate, Zone1Start, Zone1End, fee1))
	{
		return FALSE;
	}
	if (!CalculateZone(CardCate, Zone2Start, Zone2End, fee2))
	{
		return FALSE;
	}
	Fee = fee1 + fee2;
	return TRUE;

}

BOOL CDlgCardRenew::CalculateZone(int Cate, COleDateTime StartTime, COleDateTime EndTime, double & Fee)
{
	if (EndTime < StartTime) return FALSE;
	int syear, smon, sday, eyear, emon, eday;
	syear = StartTime.GetYear();
	smon = StartTime.GetMonth ();
	sday = StartTime.GetDay ();
	eyear = EndTime.GetYear();
	emon = EndTime.GetMonth();
	eday = EndTime.GetDay();
	COleDateTimeSpan x = EndTime - StartTime;
	CString Unit = CSetting::Instance()->m_CardType.Unit(Cate); Unit.TrimLeft(); Unit.TrimRight();
	double UnitFee = CSetting::Instance()->m_CardType.UnitFee(Cate);
	if (Unit.IsEmpty ()) Unit = _T("1D");
	CString Type = Unit.Right (1);
	int Value = _ttoi(Unit.Left (Unit.GetLength()-1));
	if (Value <= 0)
	{
		::AfxMessageBox (_T("Err: Unit can not be zero or negative!"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	LONG tl;
	if (Type == _T("D"))
	{
		tl = x.GetDays();
		Fee =  UnitFee * tl / Value;
		return TRUE;
	}
	else if (Type == _T("W"))
	{
		tl = x.GetDays();
		Fee = UnitFee * tl / (7 * Value);
		return TRUE;
	}
	else if (Type == _T("M"))
	{
		tl = (eyear - syear)*12 + (emon- smon);
		Fee = UnitFee * (tl + (eday - sday)/30) / Value;
		return TRUE;
	}
	else if (Type == _T("Y"))
	{
		Fee = UnitFee * (eyear - syear) / Value;
		Fee += UnitFee * (emon - smon)/ (12 * Value);
		Fee += UnitFee * (eday - sday) / (365 * Value);
		return TRUE;
	}
	else 
	{
		Fee = 0.0;
		return TRUE;
	}
}


void CDlgCardRenew::OnChangeADDSTOREVALUE() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	CString s = m_AddSV;
	s.Replace('$',' ');
	_StoreValueFee = atof( s );
	m_AmountSV = show(_StoreValueFee);
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}
void CDlgCardRenew::OnCloseupPERIODFROM(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
	*pResult = 0;
}

void CDlgCardRenew::OnCloseupPERIODTO(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_NewPeriod.Format("%s - %s", m_ValidFrom.Format("%b %d %Y"), m_ValidTo.Format("%b %d %Y"));
	double fee;
	Calculate(_ValidFrom, _ValidTo, _CardTypeId, m_ValidFrom, m_ValidTo, fee); m_AmountPeriod = show(fee);
	_PeriodFee = fee;
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
	*pResult = 0;
}

void CDlgCardRenew::OnChangeADDTRANSTIMES() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString Unit = CSetting::Instance()->m_CardType.Unit(_CardTypeId); Unit.TrimLeft(); Unit.TrimRight();
	double UnitFee = CSetting::Instance()->m_CardType.UnitFee(_CardTypeId);
	if (Unit.IsEmpty ()) Unit = _T("1T");
	CString Type = Unit.Right (1);
	int Value = _ttoi(Unit.Left (Unit.GetLength()-1));
	if (Value <= 0)
	{
		::AfxMessageBox (_T("Err: Unit can not be zero or negative!"), MB_OK|MB_ICONSTOP);
		return;
	}
	if (Type != _T("T"))
	{
		::AfxMessageBox (_T("Err: Unit must count by Transaction!"), MB_OK|MB_ICONSTOP);
		return;
	}
	_TransactionFee = m_AddTransNum * UnitFee / Value;
	m_AmountTransNum = show(_TransactionFee);
	_Amount = _PeriodFee + _TransactionFee + _StoreValueFee;
	m_AmountTotal = show(_Amount);
	UpdateData(false);
}

void CDlgCardRenew::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (hasotpcard)
		CCmdOtp::Instance()->WaitForOtpRemove(true);
	else if (haskdecard){
		showTip("請取出磁條票!", true);
		CCmdKde * pkde = CCmdKde::Instance();
		pkde->KDE_EjectCard();
		DWORD x = GetTickCount();
		while(pkde->KDE_NeedRead()) 
		{
			Sleep(500);	//脹渾紱釬埜�▼�.
			if (GetTickCount() - x > 5000) 
			{pkde->KDE_EjectCard(); x = GetTickCount();}
		}
	}

	CDialog::OnCancel();
}

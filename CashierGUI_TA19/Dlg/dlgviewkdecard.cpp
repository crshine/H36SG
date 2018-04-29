// dlgviewkdecard.cpp : implementation file
//

#include "stdafx.h"
#include "..\cashiergui.h"
#include "..\cmdkde.h"
#include "dlgviewkdecard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewKdeCard dialog


CDlgViewKdeCard::CDlgViewKdeCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewKdeCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewKdeCard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgViewKdeCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewKdeCard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewKdeCard, CDialog)
	//{{AFX_MSG_MAP(CDlgViewKdeCard)
	ON_BN_CLICKED(ID_READ_TICKET, OnReadTicket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewKdeCard message handlers

void CDlgViewKdeCard::OnReadTicket() 
{
	GetDlgItem(ID_READ_TICKET)->EnableWindow(false);
	ClearAll();
	CCmdKde * pCmdKde = CCmdKde::Instance();

	if ( pCmdKde->IsStop() )		//	¼ì²âÉè×´Ì¬
	{
		showTip( (LPCTSTR)TIP_KDE_STOP );
		GetDlgItem(ID_READ_TICKET)->EnableWindow(true);
		return;
	}
	if ( !pCmdKde->KDE_NeedRead() )	//	¼ì²âÆ±Î»ÖÃ
	{
		showTip( (LPCTSTR)TIP_KDE_NO_TICKET );
		GetDlgItem(ID_READ_TICKET)->EnableWindow(true);
		return;
	}

	CCmdKde::PATRON CardInfo;
	if ( !pCmdKde->KDE_ReadTicket(CardInfo) )	//¶ÁÆ±
	{
		showTip( (LPCTSTR)TIP_KDE_EMPTY_TICKET );
	}
	else
	{
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_SPECIAL))->SetCheck((CCmdKde::SPECIAL_TICKET == CardInfo._TicketTypeId) ? 1 : 0);
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_HOURLY))->SetCheck((CCmdKde::HOURLY_TICKET == CardInfo._TicketTypeId) ? 1 : 0);
		
		SetDlgItemText(IDC_CARD_NO,			CardInfo._CardNo			);
		SetDlgItemText(IDC_REMARK,			show(CardInfo._Remark)		);

		if (CCmdKde::HOURLY_TICKET == CardInfo._TicketTypeId)
		{
			SetDlgItemText(IDC_VEHICLE_TYPE,	show(CardInfo._VehicleId)	);
			SetDlgItemText(IDC_DISCOUNT,		show(CardInfo._DiscountId)	);
			SetDlgItemText(IDC_ENTRY_STATION,	show(CardInfo._EntryId)		);
			SetDlgItemText(IDC_ENTRY_TIME,		show(CardInfo._EntryTime)	);
			SetDlgItemText(IDC_PAYMENT_TIMES,	show(CardInfo._PaymentTimes));
			SetDlgItemText(IDC_AMOUNT,			show(CardInfo._PayAmount)	);
			SetDlgItemText(IDC_PAY_STATION,		show(CardInfo._PayId)		);
			SetDlgItemText(IDC_PAY_TIME,		show(CardInfo._PayTime)		);
		}
		
	}

	pCmdKde->KDE_EjectCard();
	GetDlgItem(ID_READ_TICKET)->EnableWindow(true);

	return;
}

void CDlgViewKdeCard::ClearAll()
{
	static_cast<CButton *>(GetDlgItem(IDC_RADIO_SPECIAL))->SetCheck(0);
	static_cast<CButton *>(GetDlgItem(IDC_RADIO_HOURLY))->SetCheck(0);
	SetDlgItemText(IDC_CARD_NO,			"");
	SetDlgItemText(IDC_VEHICLE_TYPE,	"");
	SetDlgItemText(IDC_DISCOUNT,		"");
	SetDlgItemText(IDC_ENTRY_STATION,	"");
	SetDlgItemText(IDC_ENTRY_TIME,		"");
	SetDlgItemText(IDC_PAYMENT_TIMES,	"");
	SetDlgItemText(IDC_AMOUNT,			"");
	SetDlgItemText(IDC_PAY_STATION,		"");
	SetDlgItemText(IDC_PAY_TIME,		"");
	SetDlgItemText(IDC_REMARK,			"");
}

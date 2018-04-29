// CmdLcd.cpp: implementation of the CCmdLcd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cashiergui.h"
#include "Setting.h"
#include "..\common\LCD\LCD.h"
#include "CmdLcd.h"

#ifdef _DEBUG
	#pragma comment(lib, "..\\common\\LCD\\debug\\LCD.lib")
	#pragma message("linking LCD.lib(Debug Version)")
#else
	#pragma comment(lib, "..\\common\\LCD\\release\\LCD.lib")
	#pragma message("linking LCD.lib(Release Version)")
#endif 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCmdLcd* CCmdLcd::_instance				= NULL;
bool CCmdLcd::_ThrTimeDisplayFlag = false;
CWinThread* CCmdLcd::_CW_Time_Display = NULL;	//	��ʾʱ���߳̾��

CCmdLcd::CCmdLcd()
{
	_RawLcd = new CLCD;
}

CCmdLcd::~CCmdLcd()
{
	if ( NULL != _RawLcd ) delete _RawLcd;
}

CCmdLcd* CCmdLcd::Instance()
{
    if (NULL == _instance) {
        _instance = new CCmdLcd;
    }
    return _instance;
}
////////////////////////////////////////////////////////////////////////////////
bool CCmdLcd::Start()	//��LCD
{
	if (!_RawLcd->Start(CSetting::Instance()->m_Peripheral.LcdPort(),
						CSetting::Instance()->m_Peripheral.LcdBaudRate() ) )
	{
		return false;
	}
	else
	{	
		_CW_Time_Display = AfxBeginThread( &thrTimeDisplay, 0L);
		return true;
	}
}

bool CCmdLcd::Stop()	//�ر�LCD
{
	_ThrTimeDisplayFlag = false;
	if (NULL != _CW_Time_Display)
		WaitForSingleObject(_CW_Time_Display->m_hThread, INFINITE);//�ȴ��߳̽���
	return _RawLcd->Stop();
}

////////////////////////////////////////////////////////////////////////////////
//                        ��ʾ��ʱ
////////////////////////////////////////////////////////////////////////////////
void CCmdLcd::Set_Display_Delay()
{
	COleDateTimeSpan ts;
	ts.SetDateTimeSpan(0, 0, 0, 20);

	_Display_Delay_Times = 30;	//10����ǿ��Ҫ�����ʾ��������ʾ.
	_Display_Delay_Time = COleDateTime::GetCurrentTime();
	_Display_Delay_Time += ts;
}

bool CCmdLcd::In_Display_Delay()
{
	if (0 == _Display_Delay_Times) return false;
	_Display_Delay_Times--;
	if (COleDateTime::GetCurrentTime() > _Display_Delay_Time) return false;
	return true;
}

//raw ��ʾ����
void  CCmdLcd::LCD_Display(CString LineUpper, CString LineDown, DisplayAlign DA/* = DA_Left*/)
{
	Set_Display_Delay();
	CLCD::DisplayAlign RDA;
	if		(DA == DA_Left)
		RDA = CLCD::DA_Left;
	else if (DA == DA_Center)
		RDA = CLCD::DA_Center;
	else if (DA == DA_Right)
		RDA = CLCD::DA_Right;

	_RawLcd->DisplayUpper(LineUpper, LineUpper.GetLength(), RDA);
	_RawLcd->DisplayLower(LineDown, LineDown.GetLength(), RDA);
}
//������ʾ
void CCmdLcd::LCD_DisplayIdle()
{
	if (In_Display_Delay()) return;
	const CString Title = "* SMARON CARPARK *";
	CString StrTime = COleDateTime::GetCurrentTime().Format("%b-%d %a  %H:%M:%S");
	_RawLcd->DisplayUpper(Title, Title.GetLength(), CLCD::DA_Center);
	_RawLcd->DisplayLower(StrTime, StrTime.GetLength());
}
//��������ʾ
void CCmdLcd::LCD_DisplayNoInService()
{
	const CString Line1 = "SORRY";
	const CString Line2 = "Not in service";
	_RawLcd->DisplayUpper(Line1, Line1.GetLength(), CLCD::DA_Center);
	_RawLcd->DisplayLower(Line2, Line2.GetLength(), CLCD::DA_Center);
}
//��ͼ����ǰ����ʾ.
void CCmdLcd::LCD_DisplayBeforePay(const double Amount, const COleDateTime EntryTime)
{
	CString Line1, Line2;
    Line1.Format("Amount: $ %6.2f", Amount);
	Line2 = EntryTime.Format("Enter : %d/%m %H:%M");
	LCD_Display(Line1, Line2);
}
//��ͼ����ǰ����ʾ.
void CCmdLcd::LCD_DisplayBeforePay(const double Amount, LPCTSTR Description)
{
	CString Line1, Line2;
    Line1.Format("Amount: $ %6.2f", Amount);
	Line2 = Description;
	LCD_Display(Line1, Line2);
}
//��ͼ��������ʾ.
void CCmdLcd::LCD_DisplayAfterPay(const double Paid, const double Amount, bool isOtp /*=false*/)
{
	CString Line1, Line2;
	if (!isOtp)
	{
		Line1.Format("Paid   : $ %6.1f", Paid);
		Line2.Format("Change : $ %6.1f", Amount);
	}else{
		Line1.Format("Octopus Paid: $%5.1f", Paid);
		Line2.Format("Remain Value: $%5.1f", Amount);
	}
	LCD_Display(Line1, Line2);
}
///////////////////////////////////////////////////////////////////////////////////////////
UINT CCmdLcd::thrTimeDisplay(LPVOID)
{
	TRACE("lcdʱ����ʾ��ʼ\n");
	_ThrTimeDisplayFlag = true;
	CCmdLcd * pCmdLcd = CCmdLcd::Instance();
	while(_ThrTimeDisplayFlag)
	{
		pCmdLcd->LCD_DisplayIdle();
		Sleep( max(1000, CSetting::Instance()->m_Peripheral.LcdThreadStep()) );
	}
	pCmdLcd->LCD_DisplayNoInService();
	TRACE("lcdʱ����ʾ����\n");
	return 0;
}
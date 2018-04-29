// CmdLcd.h: interface for the CCmdLcd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDLCD_H__439FBC72_D627_48F7_A926_99DB192FA88E__INCLUDED_)
#define AFX_CMDLCD_H__439FBC72_D627_48F7_A926_99DB192FA88E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLCD;
class CCmdLcd
{
public:
	enum DisplayAlign {DA_Left = 0, DA_Center = 1, DA_Right = 2};

public:
	CCmdLcd();
	virtual ~CCmdLcd();
	static CCmdLcd* Instance();
public:
	bool In_Display_Delay();
	void Set_Display_Delay();
	void LCD_DisplayBeforePay(const double Amount, const COleDateTime EntryTime);
	void LCD_DisplayAfterPay(const double Paid, const double Amount, bool isOtp=false);
	void LCD_DisplayNoInService();
	void LCD_DisplayIdle();
	void LCD_Display(CString LineUpper, CString LineDown, DisplayAlign = DA_Left);
	void LCD_DisplayBeforePay(const double Amount, LPCTSTR Description);
	bool Start();	//��LCD
	bool Stop();	//�ر�LCD

	static UINT thrTimeDisplay(LPVOID);
private:
	CLCD * _RawLcd;
	COleDateTime _Display_Delay_Time;	//	������Ч��ʾ����ʱ.
	USHORT		 _Display_Delay_Times;	//	��ֹϵͳʱ��ı�.

	static CWinThread* _CW_Time_Display;	//	��ʾʱ���߳̾��
	static bool  _ThrTimeDisplayFlag;
 	static CCmdLcd* _instance;
};

#endif // !defined(AFX_CMDLCD_H__439FBC72_D627_48F7_A926_99DB192FA88E__INCLUDED_)

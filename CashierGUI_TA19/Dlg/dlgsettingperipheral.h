#if !defined(AFX_DLGSETTINGPERIPHERAL_H__DB2407E8_6788_49CC_8844_EF265CA3B097__INCLUDED_)
#define AFX_DLGSETTINGPERIPHERAL_H__DB2407E8_6788_49CC_8844_EF265CA3B097__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgsettingperipheral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingPeripheral dialog
#include "DlgInput.h"
class CDlgSettingPeripheral : public CDlgInput
{
// Construction
public:
	CDlgSettingPeripheral(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettingPeripheral)
	enum { IDD = IDD_SETTING_PERIPHERAL };
private:
	CComboBox	PrinterBaudRateBox;
	CComboBox	OtpBaudRateBox;
	CComboBox	LcdBaudRateBox;
	CComboBox	KdeBaudRateBox;
	CComboBox	PrinterPortBox;
	CComboBox	OtpPortBox;
	CComboBox	LcdPortBox;
	CComboBox	KdePortBox;
	short	m_KdeThreadStep;
	short	m_LcdThreadStep;
	short	m_OtpThreadStep;
	short	m_PrinterThreadStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingPeripheral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingPeripheral)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeOtpPort();
	afx_msg void OnSelchangeLcdPort();
	afx_msg void OnSelchangeKdePort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetLastValidValue();
	void SyncComboBox();
	void InitControl();
	const short NULL_PORT;
	short	m_KdePort, m_KdePort_Tmp;
	short	m_LcdPort, m_LcdPort_Tmp;
	short	m_OtpPort, m_OtpPort_Tmp;
	short	m_PrinterPort;
	long	m_KdeBaudRate;
	long	m_LcdBaudRate;
	long	m_OtpBaudRate;
	long	m_PrinterBaudRate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGPERIPHERAL_H__DB2407E8_6788_49CC_8844_EF265CA3B097__INCLUDED_)

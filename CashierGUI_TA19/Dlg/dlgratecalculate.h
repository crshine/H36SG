#if !defined(AFX_DLGRATECALCULATE_H__3DACE5D5_1968_4202_86F0_976E15564402__INCLUDED_)
#define AFX_DLGRATECALCULATE_H__3DACE5D5_1968_4202_86F0_976E15564402__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgratecalculate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRateCalculate dialog

class CDlgRateCalculate : public CDialog
{
// Construction
public:
	static void CALLBACK ShowDetail(CString Detail);
	CDlgRateCalculate(CWnd* pParent = NULL);   // standard constructor
	static CDlgRateCalculate * pThis;

// Dialog Data
	//{{AFX_DATA(CDlgRateCalculate)
	enum { IDD = IDD_RATE_CALCULATE };
	CComboBox	m_VehicleType;
	CDateTimeCtrl	m_ExitTime;
	CDateTimeCtrl	m_ExitDate;
	CDateTimeCtrl	m_EntryTime;
	CComboBox	m_GroupType;
	CDateTimeCtrl	m_EntryDate;
	CListCtrl	m_DetailList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRateCalculate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRateCalculate)
	virtual BOOL OnInitDialog();
	afx_msg void OnCalculate();
	virtual void OnOK();
	afx_msg void OnChangelistwidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitControl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRATECALCULATE_H__3DACE5D5_1968_4202_86F0_976E15564402__INCLUDED_)

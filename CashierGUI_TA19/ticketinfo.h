#ifndef _TICKETINFO_H
#define _TICKETINFO_H

typedef struct {
	int m_nVehType;      //1
	double m_fEnterTime;   //7
	int m_nEnterStn;     //2
	double m_fLastPayTime; //7
	int m_nPayStn;       //2
	double m_fTotalPayAmt;  //5
	int m_nPayNum;       //1
	int m_nDiscountPlan; //2
} HPARKINGINFO, * LPPARKINGINFO;


typedef struct {
	double m_fCreditAmt;
} HTICKETCREDITINFO, *LPCREDITINFO;

typedef struct {
	CString lpszCAN;
	BOOL bAps;
	CString lpszRemark;
	LPPARKINGINFO lpParkingInfo;
	LPCREDITINFO  lpCreditInfo;
	BOOL bRedemption;
} HTICKETINFO, *LPTICKETINFO;

#endif
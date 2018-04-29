// Card.h: interface for the CCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARD_H__C8BEC95D_AF17_46E8_939C_686BC2C7BC27__INCLUDED_)
#define AFX_CARD_H__C8BEC95D_AF17_46E8_939C_686BC2C7BC27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GetCString(NAME)						\
		CString Get##NAME(){					\
			CString s;							\
			for(int i=0;sizeof(NAME)>i;i++)		\
				s.Insert(i, NAME[i]);			\
			s.TrimRight();						\
			return s;							\
		}

#define GetDouble(NAME)							\
		double Get##NAME(){						\
			CString s;							\
			for(int i=0;sizeof(NAME)>i;i++)		\
				s.Insert(i, NAME[i]);			\
			double d=(double)_ttol(s)*0.01;		\
			return d;							\
		}


class CCard  
{
public:
	CCard();
	virtual ~CCard();
	////////////////////////////////////////////////收费卡种类设定
	typedef struct __structCardCategory
	{
		char		CategoryID;
		char		CategoryName[20];
		char		WorkMode;
		char		JoiningFee[6];
		char		CardFee[6];
		char		UnitFee[8];
		char		Unit[2];
		char		WarningLevel[4];
		char		Discount[7];
		char		IsStoreValue;
		char	GetCategoryID(){return CategoryID;};
	public:
		CString GetDescription();
		GetCString(Discount);
		GetCString(CategoryName);
		GetCString(WarningLevel);
		GetCString(UnitFee);
		GetDouble(JoiningFee);
		GetDouble(CardFee);
	};
//	map< char, __structCardCategory >::iterator iterCardCategory;
//	map< char, __structCardCategory > mapCardCategory;
	BOOL AddCardCategory(const char* sRule);
};

#endif // !defined(AFX_CARD_H__C8BEC95D_AF17_46E8_939C_686BC2C7BC27__INCLUDED_)

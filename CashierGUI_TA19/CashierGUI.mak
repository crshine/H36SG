# Microsoft Developer Studio Generated NMAKE File, Based on CashierGUI.dsp
!IF "$(CFG)" == ""
CFG=CashierGUI - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CashierGUI - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CashierGUI - Win32 Release" && "$(CFG)" != "CashierGUI - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CashierGUI.mak" CFG="CashierGUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CashierGUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CashierGUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CashierGUI.exe"


CLEAN :
	-@erase "$(INTDIR)\Card.obj"
	-@erase "$(INTDIR)\CashierGUI.obj"
	-@erase "$(INTDIR)\CashierGUI.pch"
	-@erase "$(INTDIR)\CashierGUI.res"
	-@erase "$(INTDIR)\ChildView.obj"
	-@erase "$(INTDIR)\CmdKde.obj"
	-@erase "$(INTDIR)\CmdMntRecv.obj"
	-@erase "$(INTDIR)\CmdMntSend.obj"
	-@erase "$(INTDIR)\CmdOtp.obj"
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\dlgcardcategory.obj"
	-@erase "$(INTDIR)\dlgcardsearch.obj"
	-@erase "$(INTDIR)\dlgcreatecard.obj"
	-@erase "$(INTDIR)\dlgcreatecard1.obj"
	-@erase "$(INTDIR)\dlgcreatecard2.obj"
	-@erase "$(INTDIR)\dlgcreatecard3.obj"
	-@erase "$(INTDIR)\dlgcreatecard4.obj"
	-@erase "$(INTDIR)\dlgeventlog.obj"
	-@erase "$(INTDIR)\dlginput.obj"
	-@erase "$(INTDIR)\dlglogin.obj"
	-@erase "$(INTDIR)\dlgmessage.obj"
	-@erase "$(INTDIR)\DLGOtpTest.obj"
	-@erase "$(INTDIR)\dlgpayment.obj"
	-@erase "$(INTDIR)\dlgpaymentcash.obj"
	-@erase "$(INTDIR)\dlgpaymentkde.obj"
	-@erase "$(INTDIR)\dlgpaymentKDEcard.obj"
	-@erase "$(INTDIR)\dlgpaymentkdeentry.obj"
	-@erase "$(INTDIR)\dlgpaymentkdeticketno.obj"
	-@erase "$(INTDIR)\DlgPaymentOtp.obj"
	-@erase "$(INTDIR)\dlgpaymentotpaddvalue.obj"
	-@erase "$(INTDIR)\DlgPaymentOTPCard.obj"
	-@erase "$(INTDIR)\dlgpaymentotpentry.obj"
	-@erase "$(INTDIR)\dlgpaymentotpticketno.obj"
	-@erase "$(INTDIR)\dlgpaymentreceipt.obj"
	-@erase "$(INTDIR)\dlgpaymentreceiptcloseaccount.obj"
	-@erase "$(INTDIR)\dlgpaymentreceiptshiftaccount.obj"
	-@erase "$(INTDIR)\dlgpaymentshiftaccount.obj"
	-@erase "$(INTDIR)\DlgRate.obj"
	-@erase "$(INTDIR)\dlgratecalculate.obj"
	-@erase "$(INTDIR)\dlgratecar.obj"
	-@erase "$(INTDIR)\dlgrateday.obj"
	-@erase "$(INTDIR)\dlgratefee.obj"
	-@erase "$(INTDIR)\dlgratefix.obj"
	-@erase "$(INTDIR)\dlgrategroup.obj"
	-@erase "$(INTDIR)\dlgratetimezone.obj"
	-@erase "$(INTDIR)\DlgSetting.obj"
	-@erase "$(INTDIR)\dlgsettingcalculaterrule.obj"
	-@erase "$(INTDIR)\dlgsettingcardtype.obj"
	-@erase "$(INTDIR)\dlgsettingcartype.obj"
	-@erase "$(INTDIR)\DlgSettingDiscountPlan.obj"
	-@erase "$(INTDIR)\dlgsettinggrouptype.obj"
	-@erase "$(INTDIR)\dlgsettingotpreader.obj"
	-@erase "$(INTDIR)\DlgSettingPaymode.obj"
	-@erase "$(INTDIR)\dlgsettingpaymodetype.obj"
	-@erase "$(INTDIR)\dlgsettingperipheral.obj"
	-@erase "$(INTDIR)\dlgsettingreceipt.obj"
	-@erase "$(INTDIR)\dlgsettingstation.obj"
	-@erase "$(INTDIR)\dlgsettingsystem.obj"
	-@erase "$(INTDIR)\dlgsplash.obj"
	-@erase "$(INTDIR)\dlgtrymnt.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\OtpReader.obj"
	-@erase "$(INTDIR)\Rate.obj"
	-@erase "$(INTDIR)\Setting.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Sxbutton.obj"
	-@erase "$(INTDIR)\trypckdeimpdlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\ZZClocktext.obj"
	-@erase "$(INTDIR)\ZZColorButton.obj"
	-@erase "$(INTDIR)\ZZCtrltoolbar.obj"
	-@erase "$(INTDIR)\ZZMoveTabCtrl.obj"
	-@erase "$(INTDIR)\ZZSocket.obj"
	-@erase "$(INTDIR)\ZZTitleStatic.obj"
	-@erase "$(OUTDIR)\CashierGUI.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CashierGUI.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CashierGUI.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\CashierGUI.pdb" /machine:I386 /out:"$(OUTDIR)\CashierGUI.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Card.obj" \
	"$(INTDIR)\CashierGUI.obj" \
	"$(INTDIR)\ChildView.obj" \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\dlgcreatecard.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OtpReader.obj" \
	"$(INTDIR)\Rate.obj" \
	"$(INTDIR)\Setting.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Sxbutton.obj" \
	"$(INTDIR)\trypckdeimpdlg.obj" \
	"$(INTDIR)\DlgRate.obj" \
	"$(INTDIR)\dlgratecalculate.obj" \
	"$(INTDIR)\dlgratecar.obj" \
	"$(INTDIR)\dlgrateday.obj" \
	"$(INTDIR)\dlgratefee.obj" \
	"$(INTDIR)\dlgratefix.obj" \
	"$(INTDIR)\dlgrategroup.obj" \
	"$(INTDIR)\dlgratetimezone.obj" \
	"$(INTDIR)\DlgSetting.obj" \
	"$(INTDIR)\dlgsettingcalculaterrule.obj" \
	"$(INTDIR)\dlgsettingcardtype.obj" \
	"$(INTDIR)\dlgsettingcartype.obj" \
	"$(INTDIR)\DlgSettingDiscountPlan.obj" \
	"$(INTDIR)\dlgsettinggrouptype.obj" \
	"$(INTDIR)\dlgsettingotpreader.obj" \
	"$(INTDIR)\DlgSettingPaymode.obj" \
	"$(INTDIR)\dlgsettingpaymodetype.obj" \
	"$(INTDIR)\dlgsettingperipheral.obj" \
	"$(INTDIR)\dlgsettingreceipt.obj" \
	"$(INTDIR)\dlgsettingstation.obj" \
	"$(INTDIR)\dlgsettingsystem.obj" \
	"$(INTDIR)\dlgpayment.obj" \
	"$(INTDIR)\dlgpaymentcash.obj" \
	"$(INTDIR)\dlgpaymentkde.obj" \
	"$(INTDIR)\dlgpaymentKDEcard.obj" \
	"$(INTDIR)\dlgpaymentkdeentry.obj" \
	"$(INTDIR)\dlgpaymentkdeticketno.obj" \
	"$(INTDIR)\DlgPaymentOtp.obj" \
	"$(INTDIR)\dlgpaymentotpaddvalue.obj" \
	"$(INTDIR)\DlgPaymentOTPCard.obj" \
	"$(INTDIR)\dlgpaymentotpentry.obj" \
	"$(INTDIR)\dlgpaymentotpticketno.obj" \
	"$(INTDIR)\dlgpaymentreceipt.obj" \
	"$(INTDIR)\dlgpaymentreceiptcloseaccount.obj" \
	"$(INTDIR)\dlgpaymentreceiptshiftaccount.obj" \
	"$(INTDIR)\dlgpaymentshiftaccount.obj" \
	"$(INTDIR)\dlgcardcategory.obj" \
	"$(INTDIR)\dlgcardsearch.obj" \
	"$(INTDIR)\dlgcreatecard1.obj" \
	"$(INTDIR)\dlgcreatecard2.obj" \
	"$(INTDIR)\dlgcreatecard3.obj" \
	"$(INTDIR)\dlgcreatecard4.obj" \
	"$(INTDIR)\dlgtrymnt.obj" \
	"$(INTDIR)\dlgeventlog.obj" \
	"$(INTDIR)\dlginput.obj" \
	"$(INTDIR)\dlglogin.obj" \
	"$(INTDIR)\dlgmessage.obj" \
	"$(INTDIR)\DLGOtpTest.obj" \
	"$(INTDIR)\dlgsplash.obj" \
	"$(INTDIR)\ZZClocktext.obj" \
	"$(INTDIR)\ZZColorButton.obj" \
	"$(INTDIR)\ZZCtrltoolbar.obj" \
	"$(INTDIR)\ZZMoveTabCtrl.obj" \
	"$(INTDIR)\ZZSocket.obj" \
	"$(INTDIR)\ZZTitleStatic.obj" \
	"$(INTDIR)\CmdKde.obj" \
	"$(INTDIR)\CmdMntRecv.obj" \
	"$(INTDIR)\CmdMntSend.obj" \
	"$(INTDIR)\CmdOtp.obj" \
	"$(INTDIR)\CashierGUI.res"

"$(OUTDIR)\CashierGUI.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CashierGUI.exe" "$(OUTDIR)\CashierGUI.bsc"


CLEAN :
	-@erase "$(INTDIR)\Card.obj"
	-@erase "$(INTDIR)\Card.sbr"
	-@erase "$(INTDIR)\CashierGUI.obj"
	-@erase "$(INTDIR)\CashierGUI.pch"
	-@erase "$(INTDIR)\CashierGUI.res"
	-@erase "$(INTDIR)\CashierGUI.sbr"
	-@erase "$(INTDIR)\ChildView.obj"
	-@erase "$(INTDIR)\ChildView.sbr"
	-@erase "$(INTDIR)\CmdKde.obj"
	-@erase "$(INTDIR)\CmdKde.sbr"
	-@erase "$(INTDIR)\CmdMntRecv.obj"
	-@erase "$(INTDIR)\CmdMntRecv.sbr"
	-@erase "$(INTDIR)\CmdMntSend.obj"
	-@erase "$(INTDIR)\CmdMntSend.sbr"
	-@erase "$(INTDIR)\CmdOtp.obj"
	-@erase "$(INTDIR)\CmdOtp.sbr"
	-@erase "$(INTDIR)\Customer.obj"
	-@erase "$(INTDIR)\Customer.sbr"
	-@erase "$(INTDIR)\dlgcardcategory.obj"
	-@erase "$(INTDIR)\dlgcardcategory.sbr"
	-@erase "$(INTDIR)\dlgcardsearch.obj"
	-@erase "$(INTDIR)\dlgcardsearch.sbr"
	-@erase "$(INTDIR)\dlgcreatecard.obj"
	-@erase "$(INTDIR)\dlgcreatecard.sbr"
	-@erase "$(INTDIR)\dlgcreatecard1.obj"
	-@erase "$(INTDIR)\dlgcreatecard1.sbr"
	-@erase "$(INTDIR)\dlgcreatecard2.obj"
	-@erase "$(INTDIR)\dlgcreatecard2.sbr"
	-@erase "$(INTDIR)\dlgcreatecard3.obj"
	-@erase "$(INTDIR)\dlgcreatecard3.sbr"
	-@erase "$(INTDIR)\dlgcreatecard4.obj"
	-@erase "$(INTDIR)\dlgcreatecard4.sbr"
	-@erase "$(INTDIR)\dlgeventlog.obj"
	-@erase "$(INTDIR)\dlgeventlog.sbr"
	-@erase "$(INTDIR)\dlginput.obj"
	-@erase "$(INTDIR)\dlginput.sbr"
	-@erase "$(INTDIR)\dlglogin.obj"
	-@erase "$(INTDIR)\dlglogin.sbr"
	-@erase "$(INTDIR)\dlgmessage.obj"
	-@erase "$(INTDIR)\dlgmessage.sbr"
	-@erase "$(INTDIR)\DLGOtpTest.obj"
	-@erase "$(INTDIR)\DLGOtpTest.sbr"
	-@erase "$(INTDIR)\dlgpayment.obj"
	-@erase "$(INTDIR)\dlgpayment.sbr"
	-@erase "$(INTDIR)\dlgpaymentcash.obj"
	-@erase "$(INTDIR)\dlgpaymentcash.sbr"
	-@erase "$(INTDIR)\dlgpaymentkde.obj"
	-@erase "$(INTDIR)\dlgpaymentkde.sbr"
	-@erase "$(INTDIR)\dlgpaymentKDEcard.obj"
	-@erase "$(INTDIR)\dlgpaymentKDEcard.sbr"
	-@erase "$(INTDIR)\dlgpaymentkdeentry.obj"
	-@erase "$(INTDIR)\dlgpaymentkdeentry.sbr"
	-@erase "$(INTDIR)\dlgpaymentkdeticketno.obj"
	-@erase "$(INTDIR)\dlgpaymentkdeticketno.sbr"
	-@erase "$(INTDIR)\DlgPaymentOtp.obj"
	-@erase "$(INTDIR)\DlgPaymentOtp.sbr"
	-@erase "$(INTDIR)\dlgpaymentotpaddvalue.obj"
	-@erase "$(INTDIR)\dlgpaymentotpaddvalue.sbr"
	-@erase "$(INTDIR)\DlgPaymentOTPCard.obj"
	-@erase "$(INTDIR)\DlgPaymentOTPCard.sbr"
	-@erase "$(INTDIR)\dlgpaymentotpentry.obj"
	-@erase "$(INTDIR)\dlgpaymentotpentry.sbr"
	-@erase "$(INTDIR)\dlgpaymentotpticketno.obj"
	-@erase "$(INTDIR)\dlgpaymentotpticketno.sbr"
	-@erase "$(INTDIR)\dlgpaymentreceipt.obj"
	-@erase "$(INTDIR)\dlgpaymentreceipt.sbr"
	-@erase "$(INTDIR)\dlgpaymentreceiptcloseaccount.obj"
	-@erase "$(INTDIR)\dlgpaymentreceiptcloseaccount.sbr"
	-@erase "$(INTDIR)\dlgpaymentreceiptshiftaccount.obj"
	-@erase "$(INTDIR)\dlgpaymentreceiptshiftaccount.sbr"
	-@erase "$(INTDIR)\dlgpaymentshiftaccount.obj"
	-@erase "$(INTDIR)\dlgpaymentshiftaccount.sbr"
	-@erase "$(INTDIR)\DlgRate.obj"
	-@erase "$(INTDIR)\DlgRate.sbr"
	-@erase "$(INTDIR)\dlgratecalculate.obj"
	-@erase "$(INTDIR)\dlgratecalculate.sbr"
	-@erase "$(INTDIR)\dlgratecar.obj"
	-@erase "$(INTDIR)\dlgratecar.sbr"
	-@erase "$(INTDIR)\dlgrateday.obj"
	-@erase "$(INTDIR)\dlgrateday.sbr"
	-@erase "$(INTDIR)\dlgratefee.obj"
	-@erase "$(INTDIR)\dlgratefee.sbr"
	-@erase "$(INTDIR)\dlgratefix.obj"
	-@erase "$(INTDIR)\dlgratefix.sbr"
	-@erase "$(INTDIR)\dlgrategroup.obj"
	-@erase "$(INTDIR)\dlgrategroup.sbr"
	-@erase "$(INTDIR)\dlgratetimezone.obj"
	-@erase "$(INTDIR)\dlgratetimezone.sbr"
	-@erase "$(INTDIR)\DlgSetting.obj"
	-@erase "$(INTDIR)\DlgSetting.sbr"
	-@erase "$(INTDIR)\dlgsettingcalculaterrule.obj"
	-@erase "$(INTDIR)\dlgsettingcalculaterrule.sbr"
	-@erase "$(INTDIR)\dlgsettingcardtype.obj"
	-@erase "$(INTDIR)\dlgsettingcardtype.sbr"
	-@erase "$(INTDIR)\dlgsettingcartype.obj"
	-@erase "$(INTDIR)\dlgsettingcartype.sbr"
	-@erase "$(INTDIR)\DlgSettingDiscountPlan.obj"
	-@erase "$(INTDIR)\DlgSettingDiscountPlan.sbr"
	-@erase "$(INTDIR)\dlgsettinggrouptype.obj"
	-@erase "$(INTDIR)\dlgsettinggrouptype.sbr"
	-@erase "$(INTDIR)\dlgsettingotpreader.obj"
	-@erase "$(INTDIR)\dlgsettingotpreader.sbr"
	-@erase "$(INTDIR)\DlgSettingPaymode.obj"
	-@erase "$(INTDIR)\DlgSettingPaymode.sbr"
	-@erase "$(INTDIR)\dlgsettingpaymodetype.obj"
	-@erase "$(INTDIR)\dlgsettingpaymodetype.sbr"
	-@erase "$(INTDIR)\dlgsettingperipheral.obj"
	-@erase "$(INTDIR)\dlgsettingperipheral.sbr"
	-@erase "$(INTDIR)\dlgsettingreceipt.obj"
	-@erase "$(INTDIR)\dlgsettingreceipt.sbr"
	-@erase "$(INTDIR)\dlgsettingstation.obj"
	-@erase "$(INTDIR)\dlgsettingstation.sbr"
	-@erase "$(INTDIR)\dlgsettingsystem.obj"
	-@erase "$(INTDIR)\dlgsettingsystem.sbr"
	-@erase "$(INTDIR)\dlgsplash.obj"
	-@erase "$(INTDIR)\dlgsplash.sbr"
	-@erase "$(INTDIR)\dlgtrymnt.obj"
	-@erase "$(INTDIR)\dlgtrymnt.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\OtpReader.obj"
	-@erase "$(INTDIR)\OtpReader.sbr"
	-@erase "$(INTDIR)\Rate.obj"
	-@erase "$(INTDIR)\Rate.sbr"
	-@erase "$(INTDIR)\Setting.obj"
	-@erase "$(INTDIR)\Setting.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Sxbutton.obj"
	-@erase "$(INTDIR)\Sxbutton.sbr"
	-@erase "$(INTDIR)\trypckdeimpdlg.obj"
	-@erase "$(INTDIR)\trypckdeimpdlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\ZZClocktext.obj"
	-@erase "$(INTDIR)\ZZClocktext.sbr"
	-@erase "$(INTDIR)\ZZColorButton.obj"
	-@erase "$(INTDIR)\ZZColorButton.sbr"
	-@erase "$(INTDIR)\ZZCtrltoolbar.obj"
	-@erase "$(INTDIR)\ZZCtrltoolbar.sbr"
	-@erase "$(INTDIR)\ZZMoveTabCtrl.obj"
	-@erase "$(INTDIR)\ZZMoveTabCtrl.sbr"
	-@erase "$(INTDIR)\ZZSocket.obj"
	-@erase "$(INTDIR)\ZZSocket.sbr"
	-@erase "$(INTDIR)\ZZTitleStatic.obj"
	-@erase "$(INTDIR)\ZZTitleStatic.sbr"
	-@erase "$(OUTDIR)\CashierGUI.bsc"
	-@erase "$(OUTDIR)\CashierGUI.exe"
	-@erase "$(OUTDIR)\CashierGUI.ilk"
	-@erase "$(OUTDIR)\CashierGUI.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\CashierGUI.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CashierGUI.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Card.sbr" \
	"$(INTDIR)\CashierGUI.sbr" \
	"$(INTDIR)\ChildView.sbr" \
	"$(INTDIR)\Customer.sbr" \
	"$(INTDIR)\dlgcreatecard.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\OtpReader.sbr" \
	"$(INTDIR)\Rate.sbr" \
	"$(INTDIR)\Setting.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Sxbutton.sbr" \
	"$(INTDIR)\trypckdeimpdlg.sbr" \
	"$(INTDIR)\DlgRate.sbr" \
	"$(INTDIR)\dlgratecalculate.sbr" \
	"$(INTDIR)\dlgratecar.sbr" \
	"$(INTDIR)\dlgrateday.sbr" \
	"$(INTDIR)\dlgratefee.sbr" \
	"$(INTDIR)\dlgratefix.sbr" \
	"$(INTDIR)\dlgrategroup.sbr" \
	"$(INTDIR)\dlgratetimezone.sbr" \
	"$(INTDIR)\DlgSetting.sbr" \
	"$(INTDIR)\dlgsettingcalculaterrule.sbr" \
	"$(INTDIR)\dlgsettingcardtype.sbr" \
	"$(INTDIR)\dlgsettingcartype.sbr" \
	"$(INTDIR)\DlgSettingDiscountPlan.sbr" \
	"$(INTDIR)\dlgsettinggrouptype.sbr" \
	"$(INTDIR)\dlgsettingotpreader.sbr" \
	"$(INTDIR)\DlgSettingPaymode.sbr" \
	"$(INTDIR)\dlgsettingpaymodetype.sbr" \
	"$(INTDIR)\dlgsettingperipheral.sbr" \
	"$(INTDIR)\dlgsettingreceipt.sbr" \
	"$(INTDIR)\dlgsettingstation.sbr" \
	"$(INTDIR)\dlgsettingsystem.sbr" \
	"$(INTDIR)\dlgpayment.sbr" \
	"$(INTDIR)\dlgpaymentcash.sbr" \
	"$(INTDIR)\dlgpaymentkde.sbr" \
	"$(INTDIR)\dlgpaymentKDEcard.sbr" \
	"$(INTDIR)\dlgpaymentkdeentry.sbr" \
	"$(INTDIR)\dlgpaymentkdeticketno.sbr" \
	"$(INTDIR)\DlgPaymentOtp.sbr" \
	"$(INTDIR)\dlgpaymentotpaddvalue.sbr" \
	"$(INTDIR)\DlgPaymentOTPCard.sbr" \
	"$(INTDIR)\dlgpaymentotpentry.sbr" \
	"$(INTDIR)\dlgpaymentotpticketno.sbr" \
	"$(INTDIR)\dlgpaymentreceipt.sbr" \
	"$(INTDIR)\dlgpaymentreceiptcloseaccount.sbr" \
	"$(INTDIR)\dlgpaymentreceiptshiftaccount.sbr" \
	"$(INTDIR)\dlgpaymentshiftaccount.sbr" \
	"$(INTDIR)\dlgcardcategory.sbr" \
	"$(INTDIR)\dlgcardsearch.sbr" \
	"$(INTDIR)\dlgcreatecard1.sbr" \
	"$(INTDIR)\dlgcreatecard2.sbr" \
	"$(INTDIR)\dlgcreatecard3.sbr" \
	"$(INTDIR)\dlgcreatecard4.sbr" \
	"$(INTDIR)\dlgtrymnt.sbr" \
	"$(INTDIR)\dlgeventlog.sbr" \
	"$(INTDIR)\dlginput.sbr" \
	"$(INTDIR)\dlglogin.sbr" \
	"$(INTDIR)\dlgmessage.sbr" \
	"$(INTDIR)\DLGOtpTest.sbr" \
	"$(INTDIR)\dlgsplash.sbr" \
	"$(INTDIR)\ZZClocktext.sbr" \
	"$(INTDIR)\ZZColorButton.sbr" \
	"$(INTDIR)\ZZCtrltoolbar.sbr" \
	"$(INTDIR)\ZZMoveTabCtrl.sbr" \
	"$(INTDIR)\ZZSocket.sbr" \
	"$(INTDIR)\ZZTitleStatic.sbr" \
	"$(INTDIR)\CmdKde.sbr" \
	"$(INTDIR)\CmdMntRecv.sbr" \
	"$(INTDIR)\CmdMntSend.sbr" \
	"$(INTDIR)\CmdOtp.sbr"

"$(OUTDIR)\CashierGUI.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\CashierGUI.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CashierGUI.exe" /pdbtype:sept /libpath:"..\helpCashier" 
LINK32_OBJS= \
	"$(INTDIR)\Card.obj" \
	"$(INTDIR)\CashierGUI.obj" \
	"$(INTDIR)\ChildView.obj" \
	"$(INTDIR)\Customer.obj" \
	"$(INTDIR)\dlgcreatecard.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OtpReader.obj" \
	"$(INTDIR)\Rate.obj" \
	"$(INTDIR)\Setting.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Sxbutton.obj" \
	"$(INTDIR)\trypckdeimpdlg.obj" \
	"$(INTDIR)\DlgRate.obj" \
	"$(INTDIR)\dlgratecalculate.obj" \
	"$(INTDIR)\dlgratecar.obj" \
	"$(INTDIR)\dlgrateday.obj" \
	"$(INTDIR)\dlgratefee.obj" \
	"$(INTDIR)\dlgratefix.obj" \
	"$(INTDIR)\dlgrategroup.obj" \
	"$(INTDIR)\dlgratetimezone.obj" \
	"$(INTDIR)\DlgSetting.obj" \
	"$(INTDIR)\dlgsettingcalculaterrule.obj" \
	"$(INTDIR)\dlgsettingcardtype.obj" \
	"$(INTDIR)\dlgsettingcartype.obj" \
	"$(INTDIR)\DlgSettingDiscountPlan.obj" \
	"$(INTDIR)\dlgsettinggrouptype.obj" \
	"$(INTDIR)\dlgsettingotpreader.obj" \
	"$(INTDIR)\DlgSettingPaymode.obj" \
	"$(INTDIR)\dlgsettingpaymodetype.obj" \
	"$(INTDIR)\dlgsettingperipheral.obj" \
	"$(INTDIR)\dlgsettingreceipt.obj" \
	"$(INTDIR)\dlgsettingstation.obj" \
	"$(INTDIR)\dlgsettingsystem.obj" \
	"$(INTDIR)\dlgpayment.obj" \
	"$(INTDIR)\dlgpaymentcash.obj" \
	"$(INTDIR)\dlgpaymentkde.obj" \
	"$(INTDIR)\dlgpaymentKDEcard.obj" \
	"$(INTDIR)\dlgpaymentkdeentry.obj" \
	"$(INTDIR)\dlgpaymentkdeticketno.obj" \
	"$(INTDIR)\DlgPaymentOtp.obj" \
	"$(INTDIR)\dlgpaymentotpaddvalue.obj" \
	"$(INTDIR)\DlgPaymentOTPCard.obj" \
	"$(INTDIR)\dlgpaymentotpentry.obj" \
	"$(INTDIR)\dlgpaymentotpticketno.obj" \
	"$(INTDIR)\dlgpaymentreceipt.obj" \
	"$(INTDIR)\dlgpaymentreceiptcloseaccount.obj" \
	"$(INTDIR)\dlgpaymentreceiptshiftaccount.obj" \
	"$(INTDIR)\dlgpaymentshiftaccount.obj" \
	"$(INTDIR)\dlgcardcategory.obj" \
	"$(INTDIR)\dlgcardsearch.obj" \
	"$(INTDIR)\dlgcreatecard1.obj" \
	"$(INTDIR)\dlgcreatecard2.obj" \
	"$(INTDIR)\dlgcreatecard3.obj" \
	"$(INTDIR)\dlgcreatecard4.obj" \
	"$(INTDIR)\dlgtrymnt.obj" \
	"$(INTDIR)\dlgeventlog.obj" \
	"$(INTDIR)\dlginput.obj" \
	"$(INTDIR)\dlglogin.obj" \
	"$(INTDIR)\dlgmessage.obj" \
	"$(INTDIR)\DLGOtpTest.obj" \
	"$(INTDIR)\dlgsplash.obj" \
	"$(INTDIR)\ZZClocktext.obj" \
	"$(INTDIR)\ZZColorButton.obj" \
	"$(INTDIR)\ZZCtrltoolbar.obj" \
	"$(INTDIR)\ZZMoveTabCtrl.obj" \
	"$(INTDIR)\ZZSocket.obj" \
	"$(INTDIR)\ZZTitleStatic.obj" \
	"$(INTDIR)\CmdKde.obj" \
	"$(INTDIR)\CmdMntRecv.obj" \
	"$(INTDIR)\CmdMntSend.obj" \
	"$(INTDIR)\CmdOtp.obj" \
	"$(INTDIR)\CashierGUI.res"

"$(OUTDIR)\CashierGUI.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CashierGUI.dep")
!INCLUDE "CashierGUI.dep"
!ELSE 
!MESSAGE Warning: cannot find "CashierGUI.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CashierGUI - Win32 Release" || "$(CFG)" == "CashierGUI - Win32 Debug"
SOURCE=.\Card.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\Card.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\Card.obj"	"$(INTDIR)\Card.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\CashierGUI.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\CashierGUI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\CashierGUI.obj"	"$(INTDIR)\CashierGUI.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\CashierGUI.rc

"$(INTDIR)\CashierGUI.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ChildView.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ChildView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ChildView.obj"	"$(INTDIR)\ChildView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\Customer.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\Customer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\Customer.obj"	"$(INTDIR)\Customer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\OtpReader.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\OtpReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\OtpReader.obj"	"$(INTDIR)\OtpReader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\Rate.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\Rate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\Rate.obj"	"$(INTDIR)\Rate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\Setting.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\Setting.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\Setting.obj"	"$(INTDIR)\Setting.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CashierGUI.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\CashierGUI.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Include\Sxbutton.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\Sxbutton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\Sxbutton.obj"	"$(INTDIR)\Sxbutton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\trypckdeimpdlg.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\trypckdeimpdlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\trypckdeimpdlg.obj"	"$(INTDIR)\trypckdeimpdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\DlgRate.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\DlgRate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\DlgRate.obj"	"$(INTDIR)\DlgRate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgratecalculate.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgratecalculate.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgratecalculate.obj"	"$(INTDIR)\dlgratecalculate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgratecar.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgratecar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgratecar.obj"	"$(INTDIR)\dlgratecar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgrateday.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgrateday.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgrateday.obj"	"$(INTDIR)\dlgrateday.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgratefee.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgratefee.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgratefee.obj"	"$(INTDIR)\dlgratefee.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgratefix.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgratefix.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgratefix.obj"	"$(INTDIR)\dlgratefix.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgrategroup.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgrategroup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgrategroup.obj"	"$(INTDIR)\dlgrategroup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgratetimezone.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgratetimezone.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgratetimezone.obj"	"$(INTDIR)\dlgratetimezone.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DlgSetting.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DlgSetting.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DlgSetting.obj"	"$(INTDIR)\DlgSetting.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgsettingcalculaterrule.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingcalculaterrule.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingcalculaterrule.obj"	"$(INTDIR)\dlgsettingcalculaterrule.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingcardtype.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingcardtype.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingcardtype.obj"	"$(INTDIR)\dlgsettingcardtype.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingcartype.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingcartype.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingcartype.obj"	"$(INTDIR)\dlgsettingcartype.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DlgSettingDiscountPlan.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DlgSettingDiscountPlan.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DlgSettingDiscountPlan.obj"	"$(INTDIR)\DlgSettingDiscountPlan.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgsettinggrouptype.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettinggrouptype.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettinggrouptype.obj"	"$(INTDIR)\dlgsettinggrouptype.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingotpreader.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingotpreader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingotpreader.obj"	"$(INTDIR)\dlgsettingotpreader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DlgSettingPaymode.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DlgSettingPaymode.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DlgSettingPaymode.obj"	"$(INTDIR)\DlgSettingPaymode.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgsettingpaymodetype.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingpaymodetype.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingpaymodetype.obj"	"$(INTDIR)\dlgsettingpaymodetype.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingperipheral.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingperipheral.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingperipheral.obj"	"$(INTDIR)\dlgsettingperipheral.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingreceipt.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingreceipt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingreceipt.obj"	"$(INTDIR)\dlgsettingreceipt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingstation.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingstation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingstation.obj"	"$(INTDIR)\dlgsettingstation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgsettingsystem.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsettingsystem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsettingsystem.obj"	"$(INTDIR)\dlgsettingsystem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpayment.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpayment.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpayment.obj"	"$(INTDIR)\dlgpayment.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentcash.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentcash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentcash.obj"	"$(INTDIR)\dlgpaymentcash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentkde.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentkde.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentkde.obj"	"$(INTDIR)\dlgpaymentkde.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentKDEcard.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentKDEcard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentKDEcard.obj"	"$(INTDIR)\dlgpaymentKDEcard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentkdeentry.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentkdeentry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentkdeentry.obj"	"$(INTDIR)\dlgpaymentkdeentry.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentkdeticketno.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentkdeticketno.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentkdeticketno.obj"	"$(INTDIR)\dlgpaymentkdeticketno.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DlgPaymentOtp.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DlgPaymentOtp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DlgPaymentOtp.obj"	"$(INTDIR)\DlgPaymentOtp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgpaymentotpaddvalue.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentotpaddvalue.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentotpaddvalue.obj"	"$(INTDIR)\dlgpaymentotpaddvalue.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DlgPaymentOTPCard.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DlgPaymentOTPCard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DlgPaymentOTPCard.obj"	"$(INTDIR)\DlgPaymentOTPCard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgpaymentotpentry.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentotpentry.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentotpentry.obj"	"$(INTDIR)\dlgpaymentotpentry.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentotpticketno.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentotpticketno.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentotpticketno.obj"	"$(INTDIR)\dlgpaymentotpticketno.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentreceipt.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentreceipt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentreceipt.obj"	"$(INTDIR)\dlgpaymentreceipt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentreceiptcloseaccount.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentreceiptcloseaccount.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentreceiptcloseaccount.obj"	"$(INTDIR)\dlgpaymentreceiptcloseaccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentreceiptshiftaccount.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentreceiptshiftaccount.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentreceiptshiftaccount.obj"	"$(INTDIR)\dlgpaymentreceiptshiftaccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgpaymentshiftaccount.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgpaymentshiftaccount.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgpaymentshiftaccount.obj"	"$(INTDIR)\dlgpaymentshiftaccount.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgcardcategory.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\dlgcardcategory.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\dlgcardcategory.obj"	"$(INTDIR)\dlgcardcategory.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgcardsearch.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgcardsearch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgcardsearch.obj"	"$(INTDIR)\dlgcardsearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgcreatecard.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgcreatecard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgcreatecard.obj"	"$(INTDIR)\dlgcreatecard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgcreatecard1.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\dlgcreatecard1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\dlgcreatecard1.obj"	"$(INTDIR)\dlgcreatecard1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgcreatecard2.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\dlgcreatecard2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\dlgcreatecard2.obj"	"$(INTDIR)\dlgcreatecard2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgcreatecard3.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\dlgcreatecard3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\dlgcreatecard3.obj"	"$(INTDIR)\dlgcreatecard3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgcreatecard4.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\dlgcreatecard4.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\dlgcreatecard4.obj"	"$(INTDIR)\dlgcreatecard4.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgtrymnt.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgtrymnt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgtrymnt.obj"	"$(INTDIR)\dlgtrymnt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgeventlog.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgeventlog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgeventlog.obj"	"$(INTDIR)\dlgeventlog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlginput.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlginput.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlginput.obj"	"$(INTDIR)\dlginput.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlglogin.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlglogin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlglogin.obj"	"$(INTDIR)\dlglogin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\dlgmessage.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgmessage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgmessage.obj"	"$(INTDIR)\dlgmessage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Dlg\DLGOtpTest.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\DLGOtpTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\DLGOtpTest.obj"	"$(INTDIR)\DLGOtpTest.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Dlg\dlgsplash.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\dlgsplash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CashierGUI.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\dlgsplash.obj"	"$(INTDIR)\dlgsplash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ZZ\ZZClocktext.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZClocktext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZClocktext.obj"	"$(INTDIR)\ZZClocktext.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ZZ\ZZColorButton.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZColorButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZColorButton.obj"	"$(INTDIR)\ZZColorButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ZZ\ZZCtrltoolbar.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZCtrltoolbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZCtrltoolbar.obj"	"$(INTDIR)\ZZCtrltoolbar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ZZ\ZZMoveTabCtrl.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZMoveTabCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZMoveTabCtrl.obj"	"$(INTDIR)\ZZMoveTabCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ZZ\ZZSocket.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZSocket.obj"	"$(INTDIR)\ZZSocket.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\ZZ\ZZTitleStatic.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\ZZTitleStatic.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\ZZTitleStatic.obj"	"$(INTDIR)\ZZTitleStatic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CmdKde.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\CmdKde.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\CmdKde.obj"	"$(INTDIR)\CmdKde.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\CmdMntRecv.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\CmdMntRecv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\CmdMntRecv.obj"	"$(INTDIR)\CmdMntRecv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\CmdMntSend.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\CmdMntSend.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\CmdMntSend.obj"	"$(INTDIR)\CmdMntSend.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 

SOURCE=.\CmdOtp.cpp

!IF  "$(CFG)" == "CashierGUI - Win32 Release"


"$(INTDIR)\CmdOtp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"


"$(INTDIR)\CmdOtp.obj"	"$(INTDIR)\CmdOtp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\CashierGUI.pch"


!ENDIF 


!ENDIF 


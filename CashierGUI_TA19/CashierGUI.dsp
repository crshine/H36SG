# Microsoft Developer Studio Project File - Name="CashierGUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CashierGUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CashierGUI.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CashierGUI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /ZI /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/CashierGUI_SG.exe"

!ELSEIF  "$(CFG)" == "CashierGUI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL" /d "AFX_TARG_NEU" /d "AFX_TARG_CHT" /d "AFX_RESOURCE_DLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/CashierGUI_UCH.exe" /pdbtype:sept /libpath:"..\helpCashier"

!ENDIF 

# Begin Target

# Name "CashierGUI - Win32 Release"
# Name "CashierGUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CashierGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\CashierGUI.rc
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdJmdm.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdJmdm.h
# End Source File
# Begin Source File

SOURCE=.\CmdLcd.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\Customer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCardRenew.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCheckCard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEntCreate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExitConfirm.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgOTP4Record.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentAccount.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentOperate.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentOperate.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentParkFee11.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentParkFee11.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgreceiptparkingfee.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgviewkdecard.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgviewotpcard.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Eltra.cpp
# End Source File
# Begin Source File

SOURCE=.\Eltra.h
# End Source File
# Begin Source File

SOURCE=.\FeeCalculate.cpp
# End Source File
# Begin Source File

SOURCE=.\Jmdm.cpp
# End Source File
# Begin Source File

SOURCE=.\Jmdm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxWait.cpp
# End Source File
# Begin Source File

SOURCE=.\PayMode.cpp
# End Source File
# Begin Source File

SOURCE=.\Setting.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Include\Sxbutton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CashierGUI.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\CmdBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CmdLcd.h
# End Source File
# Begin Source File

SOURCE=.\CmdPrint.h
# End Source File
# Begin Source File

SOURCE=.\Customer.h
# End Source File
# Begin Source File

SOURCE=.\DlgCardRenew.h
# End Source File
# Begin Source File

SOURCE=.\DlgCheckCard.h
# End Source File
# Begin Source File

SOURCE=.\DlgEntCreate.h
# End Source File
# Begin Source File

SOURCE=.\DlgExitConfirm.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgOTP4Record.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgPaymentAccount.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgProgress.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgreceiptparkingfee.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgviewkdecard.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgviewotpcard.h
# End Source File
# Begin Source File

SOURCE=.\FeeCalculate.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxWait.h
# End Source File
# Begin Source File

SOURCE=.\PayMode.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Setting.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Include\Sxbutton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3D.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Book04.ico
# End Source File
# Begin Source File

SOURCE=.\res\cash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CashierGUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\CashierGUI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cexit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\confirmexit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Contactl.ico
# End Source File
# Begin Source File

SOURCE=.\res\discount.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_sla.ico
# End Source File
# Begin Source File

SOURCE=.\res\KDECard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\KDEErrorCard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key.ico
# End Source File
# Begin Source File

SOURCE=.\res\operator.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OTPCard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OTPCard2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OTPErrorCard.bmp
# End Source File
# Begin Source File

SOURCE=".\res\PaymentLabel(Taiwan).bmp"
# End Source File
# Begin Source File

SOURCE=.\res\process.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ship.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\status.bmp
# End Source File
# Begin Source File

SOURCE=.\res\status1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\status2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Group "Dlg"

# PROP Default_Filter ""
# Begin Group "rate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg\DlgRate.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgrate.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratecalculate.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratecalculate.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratecar.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratecar.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgrateday.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgrateday.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratefee.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratefee.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratefix.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratefix.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgrategroup.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgrategroup.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratetimezone.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgratetimezone.h
# End Source File
# End Group
# Begin Group "setting"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg\DlgSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgSetting.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcalculaterrule.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcalculaterrule.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcardtype.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcardtype.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcartype.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcartype.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcommunicate.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingcommunicate.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgSettingDiscountPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgSettingDiscountPlan.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettinggrouptype.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettinggrouptype.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingotpreader.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingotpreader.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgSettingPaymode.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\DlgSettingPaymode.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingpaymodetype.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingpaymodetype.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingperipheral.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingperipheral.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingpermission.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingpermission.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingreceiptformat.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingreceiptformat.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingstation.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingstation.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingsysparameters.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsettingsysparameters.h
# End Source File
# End Group
# Begin Group "Payment"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg\dlgpayment.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpayment.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentkde.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentkde.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentkdeticketno.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentkdeticketno.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpentry.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpentry.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotppreaddvalue.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotppreaddvalue.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpsubaddvalue.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpsubaddvalue.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpticketno.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentotpticketno.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentparkfee.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentparkfee.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceipt.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceipt.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceiptcloseaccount.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceiptcloseaccount.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceiptshiftaccount.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentreceiptshiftaccount.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentselectdiscount.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentselectdiscount.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentshiftaccount.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgpaymentshiftaccount.h
# End Source File
# End Group
# Begin Group "card"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg\dlgcardcategory.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcardcategory.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcardsearch.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcardsearch.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard1.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard1.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard2.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard2.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard3.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard4.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgcreatecard4.h
# End Source File
# End Group
# Begin Group "try"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg\dlgtrymnt.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgtrymnt.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Dlg\dlgeventlog.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgeventlog.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlginput.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlginput.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlglogin.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlglogin.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgmessage.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgmessage.h
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsplash.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Dlg\dlgsplash.h
# End Source File
# End Group
# Begin Group "ZZ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ZZ\ZZClocktext.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZClocktext.h
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZcolorbutton.h
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZCtrltoolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZCtrltoolbar.h
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZMoveTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZMovetabctrl.h
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZSocket.h
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZTitleStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\ZZ\ZZTitleStatic.h
# End Source File
# End Group
# Begin Group "Cmd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CmdKde.cpp
# End Source File
# Begin Source File

SOURCE=.\CMDKDE.h
# End Source File
# Begin Source File

SOURCE=.\CmdMntRecv.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdMntRecv.h
# End Source File
# Begin Source File

SOURCE=.\CmdMntSend.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdMntSend.h
# End Source File
# Begin Source File

SOURCE=.\CmdOtp.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdOtp.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\DEFINE.H
# End Source File
# Begin Source File

SOURCE=..\loaddll.h
# End Source File
# End Target
# End Project

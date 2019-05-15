# Microsoft Developer Studio Project File - Name="YimaEncViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=YimaEncViewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "YimaEncViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "YimaEncViewer.mak" CFG="YimaEncViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "YimaEncViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "YimaEncViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "YimaEncViewer - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 MSIMG32.LIB /nologo /subsystem:windows /machine:I386 /out:"Release/YimaEncNavigator.exe"

!ELSEIF  "$(CFG)" == "YimaEncViewer - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 MSIMG32.LIB /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/YimaEncNavigator.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "YimaEncViewer - Win32 Release"
# Name "YimaEncViewer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CenterRotateMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeDepthLineValDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmulateParamSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoCalculateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoObjectInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\HighlightDepthAreaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerManDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LibFaceStylesViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LibLineStylesViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LibPointStylesViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLayerShowDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLibInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\NavigationDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintTitleSetingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RouteEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\S63FileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectedGeoObjectsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetS63DeviceIDDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSafeContourDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetScaleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipNavEmulator.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UserDefineMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserMapLayersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\YimaEnc.cpp
# End Source File
# Begin Source File

SOURCE=.\YIMAENCHEAD.cpp
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewer.rc
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewerView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlarmSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\CenterRotateMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeDepthLineValDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmulateParamSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\GeoCalculateDlg.h
# End Source File
# Begin Source File

SOURCE=.\GeoObjectInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\HighlightDepthAreaDlg.h
# End Source File
# Begin Source File

SOURCE=.\LayerManDlg.h
# End Source File
# Begin Source File

SOURCE=.\LibFaceStylesViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\LibLineStylesViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\LibPointStylesViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapLayerShowDlg.h
# End Source File
# Begin Source File

SOURCE=.\MapLibInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\NavigationDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\PrintTitleSetingDlg.h
# End Source File
# Begin Source File

SOURCE=.\QueryDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RouteEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\S63FileDialog.h
# End Source File
# Begin Source File

SOURCE=.\SelectedGeoObjectsDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetS63DeviceIDDialog.h
# End Source File
# Begin Source File

SOURCE=.\SetSafeContourDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetScaleDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShipNavEmulator.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UserDefineMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserMapLayersDlg.h
# End Source File
# Begin Source File

SOURCE=.\YimaEnc.h
# End Source File
# Begin Source File

SOURCE=.\YIMAENCHEAD.H
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewer.h
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewerDoc.h
# End Source File
# Begin Source File

SOURCE=.\YimaEncViewerView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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

SOURCE=.\res\emulate_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\YimaEncViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\YimaEncViewer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\YimaEncViewerDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section YimaEncViewer : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section YimaEncViewer : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section YimaEncViewer : {13C204AD-1B1E-470F-A5F6-674C55126D4F}
# 	2:5:Class:CYimaEnc
# 	2:10:HeaderFile:yimaenc.h
# 	2:8:ImplFile:yimaenc.cpp
# End Section
# Section YimaEncViewer : {18468C02-CE97-4311-B4ED-9776C8AA5FA1}
# 	2:21:DefaultSinkHeaderFile:yimaenc.h
# 	2:16:DefaultSinkClass:CYimaEnc
# End Section

; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHowToPlayDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NetChess.h"
LastPage=0

ClassCount=16
Class1=CNetChessApp
Class2=CNetChessDoc
Class3=CNetChessView
Class4=CMainFrame

ResourceCount=11
Resource1=IDD_DIALOG_GAME_TYPE
Class5=CAboutDlg
Class6=CServerSocket
Class7=CClientSocket
Resource2=IDR_MAINFRAME
Class8=COptions
Resource3=IDD_DIALOG_SERVER_INFO
Class9=CServerInfoDlg
Resource4=IDR_SHELL_MENU
Class10=CMessageSend
Resource5=IDD_ABOUTBOX
Class11=CHistoryDlg
Class12=CMyColorDialog
Resource6=IDD_DIALOG_PICK_PIECE
Class13=CPickPieceDlg
Resource7=IDD_DIALOG_MESSAGE
Resource8=IDD_DIALOG_HISTORY
Class14=CPropertiesDlg
Resource9=IDD_DIALOG_PROPERTIES
Class15=CGameTypeDlg
Resource10=IDD_DIALOG_OPTIONS
Class16=CHowToPlayDlg
Resource11=IDD_DIALOG_HOWTOPLAY

[CLS:CNetChessApp]
Type=0
HeaderFile=NetChess.h
ImplementationFile=NetChess.cpp
Filter=N

[CLS:CNetChessDoc]
Type=0
HeaderFile=NetChessDoc.h
ImplementationFile=NetChessDoc.cpp
Filter=N

[CLS:CNetChessView]
Type=0
HeaderFile=NetChessView.h
ImplementationFile=NetChessView.cpp
Filter=C
LastObject=ID_TOOLS_SENDMESSAGE
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=NetChess.cpp
ImplementationFile=NetChess.cpp
Filter=D
LastObject=AFX_ID_PREVIEW_CLOSE

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVEHISTORY
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_REDO
Command8=ID_EDIT_MOVEFIRST
Command9=ID_EDIT_MOVELAST
Command10=ID_EDIT_OPTIONS
Command11=ID_EDIT_PROPERTIES
Command12=ID_TOOLS_CLIENT
Command13=ID_TOOLS_SERVER
Command14=ID_TOOLS_DISCONNECT
Command15=ID_TOOLS_SENDMESSAGE
Command16=ID_VIEW_LETTER
Command17=ID_VIEW_NUMBER
Command18=ID_VIEW_HISTORY
Command19=ID_VIEW_HIDE
Command20=ID_APP_ABOUT
Command21=ID_HELP_HOWTOPLAY
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_SAVEHISTORY
Command2=ID_TOOLS_CLIENT
Command3=ID_TOOLS_DISCONNECT
Command4=ID_TOOLS_SERVER
Command5=ID_EDIT_MOVEFIRST
Command6=ID_VIEW_HIDE
Command7=ID_VIEW_HISTORY
Command8=ID_TOOLS_SENDMESSAGE
Command9=ID_FILE_NEW
Command10=ID_FILE_OPEN
Command11=ID_EDIT_OPTIONS
Command12=D_EDIT_PROPERTIES
Command13=ID_FILE_SAVE
Command14=ID_EDIT_MOVELAST
Command15=ID_EDIT_UNDO
Command16=ID_EDIT_CUT
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
Command19=ID_EDIT_COPY
Command20=ID_EDIT_PASTE
Command21=ID_EDIT_CUT
Command22=ID_EDIT_REDO
Command23=ID_EDIT_UNDO
CommandCount=23

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_MOVEFIRST
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_REDO
Command7=ID_EDIT_MOVELAST
Command8=ID_TOOLS_SENDMESSAGE
Command9=ID_EDIT_OPTIONS
Command10=ID_VIEW_HIDE
Command11=ID_TOOLS_SERVER
Command12=ID_TOOLS_CLIENT
Command13=ID_VIEW_HISTORY
Command14=ID_TOOLS_DISCONNECT
Command15=ID_APP_ABOUT
Command16=AFX_ID_PREVIEW_CLOSE
Command17=AFX_ID_PREVIEW_CLOSE
Command18=AFX_ID_PREVIEW_CLOSE
Command19=AFX_ID_PREVIEW_CLOSE
CommandCount=19

[CLS:CServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CServerSocket
VirtualFilter=q

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=ID_EDIT_UNDO
VirtualFilter=q

[DLG:IDD_DIALOG_OPTIONS]
Type=1
Class=COptions
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_CHECK_WHITE_ON_TOP,button,1073807363
Control3=IDC_BUTTON_WHITE_COLOR,button,1342242816
Control4=IDC_BUTTON_BLACK_COLOR,button,1342242816
Control5=IDC_STATIC_WHITE,static,1342308352
Control6=IDC_STATIC_BLACK,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_BUTTON_WHITE_PIECE_COLOR,button,1342242816
Control10=IDC_BUTTON_BLACK_PIECE_COLOR,button,1342242816
Control11=IDC_STATIC_WHITE_PIECE_COLOR,static,1342308352
Control12=IDC_STATIC_BLACK_PIECE_COLOR,static,1342308352

[CLS:COptions]
Type=0
HeaderFile=Options.h
ImplementationFile=Options.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_BLACK_PIECE_COLOR
VirtualFilter=dWC

[DLG:IDD_DIALOG_SERVER_INFO]
Type=1
Class=CServerInfoDlg
ControlCount=6
Control1=IDC_IPADDRESS,SysIPAddress32,1073807360
Control2=IDC_EDIT_PORT_NUMBER,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC_IP_ADDRESS,static,1073872896
Control6=IDC_STATIC,static,1342308352

[CLS:CServerInfoDlg]
Type=0
HeaderFile=ServerInfoDlg.h
ImplementationFile=ServerInfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CServerInfoDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_MESSAGE]
Type=1
Class=CMessageSend
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_MESSAGE,edit,1352728580
Control4=IDC_EDIT_RECEIVE_MESSAGE,edit,1352730756

[CLS:CMessageSend]
Type=0
HeaderFile=MessageSend.h
ImplementationFile=MessageSend.cpp
BaseClass=CDialog
Filter=D
LastObject=CMessageSend
VirtualFilter=dWC

[DLG:IDD_DIALOG_HISTORY]
Type=1
Class=CHistoryDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_HISTORY,edit,1352730692

[CLS:CHistoryDlg]
Type=0
HeaderFile=HistoryDlg.h
ImplementationFile=HistoryDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHistoryDlg

[CLS:CMyColorDialog]
Type=0
HeaderFile=MyColorDialog.h
ImplementationFile=MyColorDialog.cpp
BaseClass=CColorDialog
Filter=D
VirtualFilter=dWC
LastObject=CMyColorDialog

[DLG:IDD_DIALOG_PICK_PIECE]
Type=1
Class=CPickPieceDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_BITMAP_BLACK,static,1350570247
Control4=IDC_STATIC_BITMAP_BLACK_KING,static,1350570247
Control5=IDC_STATIC_BITMAP_WHITE,static,1350570247
Control6=IDC_STATIC_BITMAP_WHITE_KING,static,1350570247
Control7=IDC_STATIC_STATUS,static,1342308352
Control8=IDC_STATIC_EMPTY,static,1342181639

[CLS:CPickPieceDlg]
Type=0
HeaderFile=PickPieceDlg.h
ImplementationFile=PickPieceDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=AFX_ID_PREVIEW_CLOSE
VirtualFilter=dWC

[MNU:IDR_SHELL_MENU]
Type=1
Class=?
Command1=ID_SHELL_CLOSE
Command2=ID_SHELL_VIEW
CommandCount=2

[DLG:IDD_DIALOG_PROPERTIES]
Type=1
Class=CPropertiesDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_STATUS,static,1342308352
Control3=IDC_STATIC_CLIENT_STATUS,static,1342308352

[CLS:CPropertiesDlg]
Type=0
HeaderFile=PropertiesDlg.h
ImplementationFile=PropertiesDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_PREVIEW_CLOSE

[DLG:IDD_DIALOG_GAME_TYPE]
Type=1
Class=CGameTypeDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_AMERICAN,button,1342177289
Control4=IDC_RADIO_SPARSE,button,1342177289
Control5=IDC_RADIO_CROWDED,button,1342177289
Control6=IDC_RADIO_CHINESE8x8,button,1342177289
Control7=IDC_RADIO_CHINESE10x10,button,1342177289
Control8=IDC_RADIO_INTERNATIONAL,button,1342177289
Control9=IDC_RADIO_ITALIAN,button,1342177289
Control10=IDC_RADIO_POLISH,button,1342177289
Control11=IDC_RADIO_RUSSIAN,button,1342177289
Control12=IDC_STATIC,button,1342177287

[CLS:CGameTypeDlg]
Type=0
HeaderFile=GameTypeDlg1.h
ImplementationFile=GameTypeDlg1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO_SPARSE

[CLS:CHowToPlayDlg]
Type=0
HeaderFile=HowToPlayDlg.h
ImplementationFile=HowToPlayDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHowToPlayDlg

[DLG:IDD_DIALOG_HOWTOPLAY]
Type=1
Class=CHowToPlayDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_HOWTOPLAY,edit,1352730628


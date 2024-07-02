// HowToPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetChess.h"
#include "HowToPlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHowToPlayDlg dialog


CHowToPlayDlg::CHowToPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHowToPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHowToPlayDlg)
	m_edit_howtoplay = _T("");
	//}}AFX_DATA_INIT
}


void CHowToPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHowToPlayDlg)
	DDX_Text(pDX, IDC_EDIT_HOWTOPLAY, m_edit_howtoplay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHowToPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CHowToPlayDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHowToPlayDlg message handlers

BOOL CHowToPlayDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edit_howtoplay = "NetCheckers is an American Checkers game which can be played over lan, intranet using TCP/IP between two players.\r\n\r\n"
		"This software can be used for playing checkers as server, client or single board.\r\n"
		"To play as server, enter the Server port number by clicking Tools->Server menu option.\r\n"
		"To connect to the server, enter server ip and port number by clicking Tools->Client menu option.\r\n"
		"Two players can play in the same board also.\r\n\r\n"
		"Once the connection is established, mouse can be used to move the checkers.\r\n"
		"Same action will be reflected to the client/server side also. Features like undo, redo, move first, move last "
		"are also provided. The current game can be saved with history. History alone also can be saved. "
		"The saved game can be opened, the board will be placed with opened game with history. "
		"The actions New, Open, Undo, Redo, Move First, Move Last, Send Message, Moving a piece, selecting/promoting a piece "
		" will be reflected to client/server.\r\n"
		"\r\nOther features are:-----\r\n"
		"\"Edit->Option\" can be used to to change the color of the board squares.\r\n"
		"\"Edit->Propertis\" will display the current status of the game.\r\n"		
		"\"Tools->SendMessage\" can be used to send instant message to the other player.\r\n"
		"\"Tools->Disconnect\" disconnects from the network.\r\n"
		"\"View->Letter\", \"View->Number\" displays letters or numbers on the board.\r\n"
		"\"View->History\" will display the history of the game.\r\n"
		"\"View->Hide\" will hide the current board and an icon will be placed in the system tray. "
		"On clicking on icon, the hidden board will be displayed\r\n\r\n"
		"To change an existing piece or to place new piece or to promote "
		"a piece, click on mouse right button and select the required piece.\r\n"
		"Whenever there is a move, a message or any other action, an icon will be toggled in the system tray. "
		"On clicking on icon in system tray, the hidden game will be displayed.\r\n\r\n"
		"This software is aimed at for playing checkers game between two players over network.\r\n"
		"No inteligence is implemented with this software.\r\n\r\n"
		"Enjoy the game!!!";  
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// NetChessView.cpp : implementation of the CNetChessView class
//

#include "stdafx.h"
#include "NetChess.h"
#include "Options.h"
#include "ChessBoard.h"
#include "ServerInfoDlg.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "MessageSend.h"
#include "History.h"
#include "HistoryDlg.h"
#include "PickPieceDlg.h"
#include "PropertiesDlg.h"
#include "GameTypeDlg1.h"
#include "HowToPlayDlg.h"

#include "NetChessDoc.h"
#include "NetChessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetChessView

IMPLEMENT_DYNCREATE(CNetChessView, CView)

BEGIN_MESSAGE_MAP(CNetChessView, CView)
	//{{AFX_MSG_MAP(CNetChessView)
	ON_COMMAND(ID_EDIT_OPTIONS, OnEditOptions)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOOLS_CLIENT, OnToolsClient)
	ON_COMMAND(ID_TOOLS_SERVER, OnToolsServer)
	ON_COMMAND(ID_TOOLS_SENDMESSAGE, OnToolsSendmessage)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_VIEW_LETTER, OnViewLetter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LETTER, OnUpdateViewLetter)
	ON_COMMAND(ID_VIEW_NUMBER, OnViewNumber)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NUMBER, OnUpdateViewNumber)
	ON_COMMAND(ID_FILE_SAVEHISTORY, OnFileSavehistory)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SERVER, OnUpdateToolsServer)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CLIENT, OnUpdateToolsClient)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_VIEW_HISTORY, OnViewHistory)
	ON_COMMAND(ID_TOOLS_WHITEONTOP, OnToolsWhiteontop)
	ON_COMMAND(ID_EDIT_MOVEFIRST, OnEditMovefirst)
	ON_COMMAND(ID_EDIT_MOVELAST, OnEditMovelast)
	ON_COMMAND(ID_HELP_HOWTOPLAY, OnHelpHowtoplay)
	ON_COMMAND(ID_TOOLS_DISCONNECT, OnToolsDisconnect)
	ON_COMMAND(D_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_MESSAGE(ID_MY_MESSAGE_COLORDATA,OnMessageColorData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetChessView construction/destruction

CNetChessView::CNetChessView()
{
	// TODO: add construction code here
	m_mouseMoveFlag = false;
	m_moveRect =0;
	m_pClientSocket = NULL;
	m_pServerSocket = NULL;
	m_iHistory = -1;
	m_LetterFlag = true;
	m_NumberFlag = true;
	m_white_on_top = false;
	m_player_turn = WHITE;
	m_topHistory = -1;
	m_timerFlag = false;
	m_squareWidth = 40;
	m_level = 8;
	m_GameType = AMERICAN; 
	m_ChatDlg = NULL;
}

CNetChessView::~CNetChessView()
{
}

BOOL CNetChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNetChessView drawing

void CNetChessView::OnDraw(CDC* pDC)
{
	CNetChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	DrawBoard();
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CNetChessView printing

BOOL CNetChessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNetChessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNetChessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNetChessView diagnostics

#ifdef _DEBUG
void CNetChessView::AssertValid() const
{
	CView::AssertValid();
}

void CNetChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNetChessDoc* CNetChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetChessDoc)));
	return (CNetChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNetChessView message handlers

void CNetChessView::OnEditOptions() 
{
	m_optDlg.DoModal();	 
	DrawBoard();
}

void CNetChessView::DrawBoard()
{
	CClientDC dc(this);	
 
	CBitmap localbmp;
	localbmp.LoadBitmap(IDB_BITMAP_BASE);
	//BITMAP bp={0,1000,490,3000,1,24,0x00000000};
	//localbmp.CreateBitmapIndirect(&bp);

	CDC ldc;
	ldc.CreateCompatibleDC(&dc);
	ldc.SelectObject(&localbmp); 
	COLORREF cr(RGB(20,140,17));	 
	//ldc.SetBkColor(cr);
	CBrush brush(cr);
	ldc.SelectObject(brush);
	CRect crect;
	GetClientRect(&crect);
	 
 
	ldc.FillRect(&crect,&brush);
	COLORREF bkcrRef;
	 
	//CRect crect = cb[3][3].GetRect();
	COLORREF redcr(RGB(255,0,0));

	CBrush redbrush;
	redbrush.CreateSolidBrush(redcr);
	
	COLORREF redbluecr(RGB(255,0,255));
	CBrush redbluebrush;
	redbluebrush.CreateSolidBrush(redbluecr);

	CBrush* pbrush = ldc.SelectObject(&redbluebrush);

	ldc.Rectangle(crect.left + 4, crect.top + 4,
		crect.right - 4, crect.bottom - 4);

	 
	COLORREF bluecr(RGB(0,255,255));//ball color
	CBrush bluebrush;
	bluebrush.CreateSolidBrush(bluecr);

	COLORREF greencr(RGB(0,255,0));
	CBrush greenbrush;
	greenbrush.CreateSolidBrush(greencr);

	ldc.SelectObject(bluebrush);

	ldc.Rectangle(crect.left +21, crect.top +21,
		crect.right - 21, crect.bottom -21);

	pbrush =  ldc.SelectObject(&redbluebrush);
	
	if(m_white_on_top == (int)false && m_optDlg.m_check_white_on_top == (int)true) 
	//if(m_optDlg.m_check_white_on_top == (int)true) 
	{		
		m_white_on_top = true;
		for(int i=0;i<=m_level/4;i++)
		{
			for(int j=0;j<m_level;j++)
			{
				int from_piece_id;
				COLOR_TYPE from_piece_color;
				PIECE_TYPE from_piece_type;
				STATE from_piece_state;
				cb[i][m_level-1 -j].GetPieceData(from_piece_id,from_piece_color,from_piece_type,from_piece_state);
				int to_piece_id;
				COLOR_TYPE to_piece_color;
				PIECE_TYPE to_piece_type;
				STATE to_piece_state;
				cb[m_level-1-i][j].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);
				cb[m_level-1-i][j].SetPieceData(from_piece_id,from_piece_color,from_piece_type,from_piece_state);
				cb[i][m_level-1 - j].SetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);
			}
		}
	}
	else if(m_white_on_top == true && m_optDlg.m_check_white_on_top == false)
	//else if( m_optDlg.m_check_white_on_top == false)
	{
		m_white_on_top = false;
		for(int i=0;i<m_level/2;i++)
		{
			for(int j=0;j<m_level;j++)
			{
				int from_piece_id;
				COLOR_TYPE from_piece_color;
				PIECE_TYPE from_piece_type;
				STATE from_piece_state; 
				cb[i][m_level-1 -j].GetPieceData(from_piece_id,from_piece_color,from_piece_type,from_piece_state);
				int to_piece_id;
				COLOR_TYPE to_piece_color;
				PIECE_TYPE to_piece_type;
				STATE to_piece_state;
				cb[m_level-1-i][j].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);
				cb[m_level-1-i][j].SetPieceData(from_piece_id,from_piece_color,from_piece_type,from_piece_state);
				cb[i][m_level-1 - j].SetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);

			}
		}
	}
	 

	for(int i = 0; i < m_level; i++)
	{
		for( int j = 0; j < m_level; j++)
		{
			CRect rect = cb[i][j].GetRect();
			
			//ldc.SelectObject(&greenbrush);
			//ldc.Rectangle(rect);
			  
			if(cb[i][j].GetColorType() == BLACK)
			{
				CPoint pt(m_moveRect.left+25,m_moveRect.top+25);
				if(rect.PtInRect(pt) == TRUE)
				{
					bkcrRef = m_optDlg.m_crefBlackColor;
				}			 	 				 
				CBrush brush(m_optDlg.m_crefBlackColor);
				ldc.SetBkColor(m_optDlg.m_crefBlackColor);
				ldc.SelectObject(brush); 
				ldc.FillRect(&rect,&brush);
			}
			else if(cb[i][j].GetColorType() == WHITE)
			{
				CPoint pt(m_moveRect.left+25,m_moveRect.top+25);
				if(rect.PtInRect(pt) == TRUE)
				{
					bkcrRef = m_optDlg.m_crefWhiteColor ;
				}
				CBrush brush(m_optDlg.m_crefWhiteColor);
				ldc.SetBkColor(m_optDlg.m_crefWhiteColor);
				ldc.SelectObject(brush); 
				ldc.FillRect(&rect,&brush);
			}
			if(cb[i][j].GetPieceType() != BLANK && cb[i][j].GetPieceState() != PIECE_MOVING)
			{
				int piece_id;
				COLOR_TYPE  piece_color;
				PIECE_TYPE  piece_type;
				STATE piece_state;
				cb[i][j].GetPieceData(piece_id,piece_color,piece_type,piece_state);
				if(piece_id <= 0)
				{
					break;
				}
				/*CBitmap bitmap;
				//bitmap.LoadBitmap(piece_id);			 
				bitmap.LoadBitmap(GetBitmapId(piece_id));			 
				CDC bmpdc;
				bmpdc.CreateCompatibleDC(&ldc);
				bmpdc.SelectObject(&bitmap); 

				BITMAP bmp;
				bitmap.GetBitmap(&bmp);
				//ldc.SetStretchBltMode(HALFTONE);
				//POINT pt;
				//SetBrushOrgEx(ldc.GetSafeHdc(),0,0,&pt);
				 
				ldc.StretchBlt(rect.left+7,rect.top+7,m_squareWidth -15,m_squareWidth-15,&bmpdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); */
				CRect rect1(rect.left+5,rect.top+5,rect.right-5,rect.bottom-5);
				ldc.Ellipse(rect1);
				CRgn rgn;						 
				rgn.CreateEllipticRgn(rect1.left, rect1.top, rect1.right, rect1.bottom);	
				switch(piece_id)
				{
					case CHECKERS_WHITE:
						{
							CBrush brush(m_optDlg.m_crefWhitePieceColor);
							ldc.FillRgn(&rgn,&brush );						 
						}
						break; 

					case CHECKERS_BLACK:	
						{
							CBrush brush(m_optDlg.m_crefBlackPieceColor);
							ldc.FillRgn(&rgn,&brush);						 
						}
						break; 
					case CHECKERS_WHITE_KING:
						{
							POINT pt[6] = {
								{rect.left+10,rect.top+15},
								{rect.right -10, rect.top+15},
								{rect.left+10, rect.bottom - 10},
								{rect.left + 20,rect.top +10},
								{rect.right-10,rect.bottom-10},
								{rect.left+10,rect.top+15}};

							CBrush brush(m_optDlg.m_crefWhitePieceColor);
							ldc.FillRgn(&rgn,&brush );						 
							ldc.Polyline(pt,6); 
						}
						break;
					case CHECKERS_BLACK_KING:
						{
							POINT pt[6] = {
								{rect.left+10,rect.top+15},
								{rect.right -10, rect.top+15},
								{rect.left+10, rect.bottom - 10},
								{rect.left + 20,rect.top +10},
								{rect.right-10,rect.bottom-10},
								{rect.left+10,rect.top+15}};

							CBrush brush(m_optDlg.m_crefBlackPieceColor);
							ldc.FillRgn(&rgn,&brush);						 
							ldc.Polyline(pt,6); 
						}
						break;
				}
			}
			///ldc.SelectObject(&redbluebrush);
		}			
	}
	for(i=0;i<m_level;i++)
	{
		ldc.SetBkColor(redbluecr);
		if(m_LetterFlag == true)
		{
			if(m_white_on_top == false)
			{
				if(m_level != 8)
				{
					ldc.TextOut(m_squareWidth * (i+1),5,(char)('A'+i));
					ldc.TextOut(m_squareWidth * (i+1),crect.bottom - 21, (char)('A'+i));
				}
				else
				{
					ldc.TextOut(m_squareWidth * (i+1)+50,5,(char)('A'+i));
					ldc.TextOut(m_squareWidth * (i+1)+50,crect.bottom - 21, (char)('A'+i));
				}
			}
			else
			{
				CString str;
				str.Format("%c",'A'+m_level -1-i);
				if(m_level != 8)
				{
					ldc.TextOut(m_squareWidth * (i+1),5,str);
					ldc.TextOut(m_squareWidth * (i+1),crect.bottom - 21, str);
				}
				else
				{
					ldc.TextOut(m_squareWidth * (i+1)+50,5,str);
					ldc.TextOut(m_squareWidth * (i+1)+50,crect.bottom - 21, str);
				}

			}
		}
		if(m_NumberFlag == true)
		{
			if(m_white_on_top == false) 
			{
				CString str;
				str.Format("%d",m_level -i);
				if(m_level != 8)
				{
					ldc.TextOut(5, m_squareWidth * (i+1), str);
					ldc.TextOut(crect.right - 20, m_squareWidth * (i+1), str);
				}
				else
				{
					ldc.TextOut(5, m_squareWidth * (i+1)+50, str);
					ldc.TextOut(crect.right - 20, m_squareWidth * (i+1)+50, str);
				}

			}
			else
			{
				CString str;
				if(i == 9)
				{
					str = "10";
				}
				else
				{
					str.Format("%c",'1'+i);
				}
				if(m_level != 8)
				{
					ldc.TextOut(5, m_squareWidth * (i+1), str);
					ldc.TextOut(crect.right - 20, m_squareWidth * (i+1), str);
				}
				else
				{
					ldc.TextOut(5, m_squareWidth * (i+1)+50, str);
					ldc.TextOut(crect.right - 20, m_squareWidth * (i+1)+50, str);
				}
			}
		}
	}

	COLORREF cr1(RGB(255,255,255));
	ldc.SetBkColor(cr1);

	if(m_mouseMoveFlag == true)
	{
		CRect rect = m_moveRect;
		int piece_id;
		ldc.SetBkColor(bkcrRef);
		COLOR_TYPE  piece_color;
		PIECE_TYPE  piece_type;
		STATE piece_state;
		cb[m_point.x][m_point.y].GetPieceData(piece_id,piece_color,piece_type,piece_state);
		if(piece_id < 0)
		{
			dc.BitBlt(0,0,600,700,&ldc,0,0,SRCCOPY);  
			return;
		}
		CRect rect1(rect.left+10,rect.top+10,rect.right-10,rect.bottom-10);
		ldc.Ellipse(rect1);
		CRgn rgn;						 
		rgn.CreateEllipticRgn(rect1.left, rect1.top, rect1.right, rect1.bottom);
		switch(piece_id)
		{
			case CHECKERS_WHITE:
				{
					CBrush brush(m_optDlg.m_crefWhitePieceColor);
					ldc.FillRgn(&rgn,&brush );						 
				}
				break; 

			case CHECKERS_BLACK:	
				{
					CBrush brush(m_optDlg.m_crefBlackPieceColor);
					ldc.FillRgn(&rgn,&brush);						 
				}
				break; 
			case CHECKERS_WHITE_KING:
					{
						POINT pt[6] = {
							{rect.left+15,rect.top+20},
							{rect.right -15, rect.top+20},
							{rect.left+15, rect.bottom - 15},
							{rect.left + 25,rect.top +15},
							{rect.right-15,rect.bottom-15},
							{rect.left+15,rect.top+20}};

						CBrush brush(m_optDlg.m_crefWhitePieceColor);
						ldc.FillRgn(&rgn,&brush );						 
						ldc.Polyline(pt,6); 
					}
					break;
				case CHECKERS_BLACK_KING:
					{
						POINT pt[6] = {
							{rect.left+15,rect.top+20},
							{rect.right -15, rect.top+20},
							{rect.left+15, rect.bottom - 15},
							{rect.left + 25,rect.top +15},
							{rect.right-15,rect.bottom-15},
							{rect.left+15,rect.top+20}};

						CBrush brush(m_optDlg.m_crefBlackPieceColor);
						ldc.FillRgn(&rgn,&brush);						 
						ldc.Polyline(pt,6); 
					}
					break;
		}
		/*CBitmap bitmap;
		//bitmap.LoadBitmap(piece_id);
		bitmap.LoadBitmap(GetBitmapId(piece_id));
		CDC bmpdc;
		bmpdc.CreateCompatibleDC(&ldc);
		bmpdc.SelectObject(&bitmap); 
		bmpdc.SelectObject(&bkcrRef);

		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		//ldc.SetStretchBltMode(HALFTONE);
		//POINT pt;
		//SetBrushOrgEx(ldc.GetSafeHdc(),0,0,&pt);
		 
		ldc.StretchBlt(rect.left+7,rect.top+7,m_squareWidth-15,m_squareWidth-15,&bmpdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 		 		 */
	}
	dc.BitBlt(0,0,600,700,&ldc,0,0,SRCCOPY);
}
void CNetChessView::Initialize()
{
	m_mouseMoveFlag = false;
	m_moveRect =0;	 
	m_iHistory = -1;	 	 	 	 
	m_topHistory = -1;
	m_timerFlag = false;
	m_squareWidth = 40;
	m_level = 8;
	m_GameType = AMERICAN; 
	m_white_on_top = false;
}

int CNetChessView::GetBitmapId(int piece_id)
{
	/*switch(m_optDlg.m_pieceType)
	{
 		case 1:
			switch(piece_id)
			{
				case CHECKERS_WHITE:
					return IDB_BITMAP_WHITE;

				case CHECKERS_BLACK:
					return IDB_BITMAP_BLACK;								 
			}
			break;
		case 2:
			break;
		case 3:			 
			break;
	}*/
	return -1;
}
void CNetChessView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();	 

	if(m_ChatDlg == NULL)
	{
		m_ChatDlg = new CMessageSend();
		m_ChatDlg->Create(IDD_DIALOG_MESSAGE,this);
	}
	int xstart,ystart;
	if(m_level == 8)
	{
		xstart = 70;
		ystart = 70;
	}	
	else
	{
		xstart = 30;
		ystart = 30;
	}
	 
	int x,y=ystart;
	for ( int i = 0; i < m_level; i++)
	{
		x = xstart;
		for( int j = 0; j < m_level; j++)
		{
			CRect rect(x,y, x+ m_squareWidth, y+m_squareWidth);

			cb[i][j].SetRect(rect);
			cb[i][j].SetPieceType(BLANK);			 
			cb[i][j].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);
			 
			x += m_squareWidth;
		}
		y += m_squareWidth;
	}
	COLOR_TYPE typex = BLACK;
	 
	for(i = 0; i< m_level; i++)
	{
		if(typex == WHITE)
			typex = BLACK;
		else
			typex = WHITE;
		COLOR_TYPE type = typex;
		for(int j=0; j < m_level; j++)
		{
			
			cb[i][j].SetColorType(type);
			if(type == WHITE)
				type = BLACK;
			else
				type = WHITE;
		}
	}	 	 

	for(i=0;i<m_level;i+=2)
	{	
		cb[0][i+1].SetPieceData(CHECKERS_BLACK,BLACK,NORMAL,PIECE_NOT_MOVING);
		cb[1][i].SetPieceData(CHECKERS_BLACK,BLACK,NORMAL,PIECE_NOT_MOVING);
		cb[2][i+1].SetPieceData(CHECKERS_BLACK,BLACK,NORMAL,PIECE_NOT_MOVING);
		if(m_GameType == CROWDED)
		{
			cb[3][i].SetPieceData(CHECKERS_BLACK,BLACK,NORMAL,PIECE_NOT_MOVING);
			cb[m_level-4][i+1 ].SetPieceData(CHECKERS_WHITE,WHITE,NORMAL,PIECE_NOT_MOVING);
		}
		cb[m_level-3][i].SetPieceData(CHECKERS_WHITE,WHITE,NORMAL,PIECE_NOT_MOVING);
		cb[m_level-2][i+1].SetPieceData(CHECKERS_WHITE,WHITE,NORMAL,PIECE_NOT_MOVING);
		cb[m_level-1][i].SetPieceData(CHECKERS_WHITE,WHITE,NORMAL,PIECE_NOT_MOVING);
	}	 
}

void CNetChessView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnLButtonDownAction(nFlags,point);	 
 	CView::OnLButtonDown(nFlags, point);
}

void CNetChessView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnLButtonUpAction(nFlags,point);	 
	CView::OnLButtonUp(nFlags, point);
}

void CNetChessView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	 
	OnMouseMoveAction(nFlags,point);
	CView::OnMouseMove(nFlags, point);
}

void CNetChessView::OnToolsClient() 
{
	// TODO: Add your command handler code here
	if(m_pServerSocket != NULL)
	{
		AfxMessageBox("Running as Server, cannot run as client");
		return;
	}
	if(m_pClientSocket != NULL)
	{
		AfxMessageBox("Already running as client");
		return;
	}
	if(m_iHistory > -1)
	{
		if(AfxMessageBox("Do you want to save the playing game",MB_YESNO) == IDYES)
		{
			OnFileSave();
			AfxMessageBox("Game is saved");
		}
		Initialize();
		OnInitialUpdate();
		DrawBoard();
	}
	CServerInfoDlg dlg(this,CLIENT);
	if(dlg.DoModal()==IDOK)
	{
		m_pClientSocket = new CClientSocket();
		CString str;
		((CClientSocket*)m_pClientSocket)->SetInfo(dlg.m_strIPAddress, dlg.m_port_nunber);
		m_pClientSocket->Create();
		m_pClientSocket->Connect(dlg.m_strIPAddress, dlg.m_port_nunber) !=0  || GetLastError();
		/*char a;
		m_pClientSocket->Receive(&a,1);
		if(a == 'A')
		{
			m_pClientSocket->AsyncSelect(FD_READ | FD_CONNECT| FD_CLOSE | FD_WRITE);
		}
		else
		{
			//m_pClientSocket->AsyncSelect(FD_READ | FD_CONNECT| FD_CLOSE | FD_WRITE);
			CString str;
			str.Format("Could not be conneted to Server");
			//ected,%s %d %d",dlg.m_strIPAddress,dlg.m_port_nunber,GetLastError());
			AfxMessageBox(str);
			delete m_pClientSocket;
			m_pClientSocket = NULL;
		}*/	 
	}		
}

void CNetChessView::OnToolsServer() 
{
	// TODO: Add your command handler code here
	if(m_pServerSocket != NULL)
	{
		AfxMessageBox("Already running as server");
		return;
	}
	if(m_pClientSocket != NULL)
	{
		AfxMessageBox("Already running as client");
		return;
	}
	if(m_iHistory > -1)
	{
		if(AfxMessageBox("Do you want to save the playing game",MB_YESNO) == IDYES)
		{
			OnFileSave();
			AfxMessageBox("Game is saved");
		}
		Initialize();
		OnInitialUpdate();
		DrawBoard();
	}
	CServerInfoDlg dlg(this,SERVER);
	if(dlg.DoModal()==IDOK)
	{
		//dlg.UpdateData(FALSE);
		m_pServerSocket = new CServerSocket();
		((CServerSocket*)m_pServerSocket)->SetInfo(dlg.m_port_nunber);
		((CServerSocket*)m_pServerSocket)->CreateServer(dlg.m_port_nunber);		 
	 
	}
}
void CNetChessView::SetClientSocket(CAsyncSocket* sock)
{
	if(m_iHistory > -1)
	{
		if(AfxMessageBox("Do you want to save the playing game",MB_YESNO) == IDYES)
		{
			OnFileSave();
			AfxMessageBox("Game is saved");
		}
		Initialize();
		OnInitialUpdate();
		DrawBoard();
	}
	m_pClientSocket = sock;
}

CAsyncSocket* CNetChessView::GetClientSocket()
{	 
	return m_pClientSocket;
}
void CNetChessView::SetData(char* data,int length)
{
	switch(data[0])
	{
		case MOVE:
			{				 
				int piece_id;
				/*COLOR_TYPE  piece_color;
				PIECE_TYPE  piece_type;*/
				int to_piece_id;
				int rm_piece_id;
				/*COLOR_TYPE  to_piece_color;
				PIECE_TYPE  to_piece_type;				 
				STATE piece_state,to_piece_state;*/
				memcpy(&piece_id, &data[4],4); 
				memcpy(&to_piece_id,&data[12],4);
				memcpy(&rm_piece_id, &data[20],4);
				if((data[1] == (int)true&& m_white_on_top == (int)true )|| (data[1] == (int)false && m_white_on_top == (int)false)) //both white are on top
				{				 
					//cb[data[2]][data[3]].GetPieceData(piece_id,piece_color,piece_type,piece_state);
					//cb[data[4]][data[5]].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);
					//cb[data[2]][data[3]].SetPieceData(to_piece_id,(COLOR_TYPE)data[16],(PIECE_TYPE)data[17],PIECE_NOT_MOVING); 
					cb[data[2]][data[3]].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);					 
					cb[data[10]][data[11]].SetPieceData(piece_id,
						(COLOR_TYPE)data[8],(PIECE_TYPE)data[9],PIECE_NOT_MOVING);					 
					PIECE_SIDE piece_side;
					if(data[1]==(int)true)
					{
						piece_side = TOP;
					}
					else
					{
						piece_side = BOTTOM;
					}
					if(data[18] != -1)
					{
						cb[data[18]][data[19]].SetPieceData(-1,
						NONE,BLANK,PIECE_NOT_MOVING);					 
					}
					m_History[++m_iHistory].SetHistory(
							piece_side,
							(PIECE_TYPE)data[9],(COLOR_TYPE)data[8],piece_id,							 
							data[2],data[3],
							(PIECE_TYPE)data[17],(COLOR_TYPE)data[16],to_piece_id,
							data[10],data[11],
							(PIECE_TYPE)data[25],(COLOR_TYPE)data[24],rm_piece_id,							 
							data[18],data[19]
							);
					 
				}
				 
				else if((data[1] == (int)false && m_white_on_top == (int)true)|| (data[1] == (int)true && m_white_on_top == (int)false) ) // white on top and black on top
				{				 
					//cb[7-data[2]][7-data[3]].GetPieceData(piece_id,piece_color,piece_type,piece_state);
					//cb[7-data[4]][7-data[5]].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);
					//cb[7-data[2]][7-data[3]].SetPieceData(to_piece_id,(COLOR_TYPE)data[16],(PIECE_TYPE)data[17],PIECE_NOT_MOVING); 
					cb[m_level-1-data[2]][m_level-1-data[3]].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);					 
					cb[m_level-1-data[10]][m_level-1-data[11]].SetPieceData(piece_id,(COLOR_TYPE)data[8],(PIECE_TYPE)data[9],PIECE_NOT_MOVING);
					if(data[18] != -1)
					{
						cb[m_level-1-data[18]][m_level-1-data[19]].SetPieceData(
							-1,NONE,BLANK,PIECE_NOT_MOVING);					 
					}
					PIECE_SIDE piece_side;
					if(data[1]==(int)true)
					{
						piece_side = TOP;
					}
					else
					{
						piece_side = BOTTOM;
					}
					m_History[++m_iHistory].SetHistory(
							piece_side,
							(PIECE_TYPE)data[9],(COLOR_TYPE)data[8],piece_id,							 
							data[2],data[3],
							(PIECE_TYPE)data[17],(COLOR_TYPE)data[16],to_piece_id,
							data[10],data[11],
							(PIECE_TYPE)data[25],(COLOR_TYPE)data[24],rm_piece_id,							 
							data[18],data[19]);
					 
				}
				memcpy(&m_topHistory,&data[26],4);				 
				DrawBoard();
				NOTIFYICONDATA nicondata;
				char data1[64] = "Changed the move state";				
				nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
				nicondata.uID = 10;
				nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
				nicondata.cbSize = sizeof(nicondata);
				nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
				nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
				strcpy(nicondata.szTip,data1);
				Shell_NotifyIcon(NIM_ADD,&nicondata);
				KillTimer(SHELL_ICON_TIMER_EVENT_ID);
				SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
				m_timerFlag = true;
			}
			break;
		case TEXT:
			{	
				((CMessageSend*)m_ChatDlg)->SetReceiveData(&data[1]);	
				DrawBoard();
				NOTIFYICONDATA nicondata;
				char data1[64] = "Message received";				 
				nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
				nicondata.uID = 10;
				nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
				nicondata.cbSize = sizeof(nicondata);
				nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
				nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
				strcpy(nicondata.szTip,data1);
				Shell_NotifyIcon(NIM_ADD,&nicondata);		
				KillTimer(SHELL_ICON_TIMER_EVENT_ID);
				SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
				m_timerFlag = true;				 
			}
			break;
	 
		case FILEDATA:
			{
				m_mouseMoveFlag = false;
				m_moveRect = 0;	 
				m_iHistory = -1;	 	 	 	 
				m_topHistory = -1;
				m_timerFlag = false;
				for(int i = 0; i< m_level; i++)
				{
					for(int j=0;j<m_level;j++)
					{
						cb[i][j].SetPieceType(BLANK);
					}
				}
				int total;
				memcpy(&total,&data[1],4);
				int j;
				i=5;
				m_optDlg.m_check_white_on_top = data[i++];
				m_white_on_top = data[i++];
				for(j=0; j< total;j++)
				{
					int k = data[i++];
					int l = data[i++];						 
					int pieceid;
					 
					PIECE_TYPE ptype = (PIECE_TYPE)data[i++];
					COLOR_TYPE ctype =(COLOR_TYPE) data[i++];
					memcpy(&pieceid,&data[i],4);
					i+=4; 
					if(k >= 0 && l >= 0)
					{
 						cb[k][l].SetPieceData(pieceid,ctype,ptype,PIECE_NOT_MOVING);					 
					} 
				}
				memcpy(&total,&data[i],4);
				i += 4;
				PIECE_SIDE piece_side;		 
				PIECE_TYPE from_piece_type;
				COLOR_TYPE from_color_type;
				int from_pieceid;
				int from_row_id;	
				int from_col_id;
				PIECE_TYPE to_piece_type;
				COLOR_TYPE to_color_type;
				int to_pieceid;
				int to_row_id;
				int to_col_id;			 
				PIECE_TYPE rm_piece_type;
				COLOR_TYPE rm_color_type;
				int rm_pieceid;
				int rm_row_id;
				int rm_col_id;			 
				m_iHistory = -1;

				for(j=0;j<total;j++)
				{
					piece_side = (PIECE_SIDE)data[i++];
					from_piece_type = (PIECE_TYPE)data[i++];
					from_color_type = (COLOR_TYPE)data[i++];			 
					memcpy(&from_pieceid,&data[i],4);
					i += 4;
					from_row_id = data[i++];
					from_col_id = data[i++];
					 
					to_piece_type = (PIECE_TYPE)data[i++];
					to_color_type = (COLOR_TYPE)data[i++];			 
					memcpy(&to_pieceid,&data[i],4);
					i += 4;
					to_row_id = data[i++];
					to_col_id = data[i++];

					rm_piece_type = (PIECE_TYPE)data[i++];
					rm_color_type = (COLOR_TYPE)data[i++];			 
					memcpy(&rm_pieceid,&data[i],4);
					i += 4;
					rm_row_id = data[i++];
					rm_col_id = data[i++];
					
					m_History[++m_iHistory].SetHistory(
						piece_side,from_piece_type,
						from_color_type,from_pieceid,
						from_row_id,from_col_id, to_piece_type,
						to_color_type,to_pieceid,to_row_id,
						to_col_id,
						rm_piece_type,rm_color_type,rm_pieceid,rm_row_id,
						rm_col_id);		 
				}
				m_topHistory = m_iHistory;
				DrawBoard();
				NOTIFYICONDATA nicondata;
				char data1[64] = "NetCheckers by A.V.Maheswara Rao";				 
				nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
				nicondata.uID = 10;
				nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
				nicondata.cbSize = sizeof(nicondata);
				nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
				nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
				strcpy(nicondata.szTip,data1);
				Shell_NotifyIcon(NIM_ADD,&nicondata);				 
				DrawBoard();
				KillTimer(SHELL_ICON_TIMER_EVENT_ID);
				m_timerFlag = true;
				SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
			}
			break;
		case UNDO:
				{
					OnEditUndoAction();
					NOTIFYICONDATA nicondata;
					char data1[64] = "Received undo action";				 
					nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
					nicondata.uID = 10;
					nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
					nicondata.cbSize = sizeof(nicondata);
					nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
					nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
					strcpy(nicondata.szTip,data1);
					Shell_NotifyIcon(NIM_ADD,&nicondata);				 
					DrawBoard();
					KillTimer(SHELL_ICON_TIMER_EVENT_ID);
					m_timerFlag = true;
					SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
				}
			break;
		case REDO:
				{
					OnEditRedoAction();
					NOTIFYICONDATA nicondata;
					char data1[64] = "Received Redo action";				 
					nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
					nicondata.uID = 10;
					nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
					nicondata.cbSize = sizeof(nicondata);
					nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
					nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
					strcpy(nicondata.szTip,data1);
					Shell_NotifyIcon(NIM_ADD,&nicondata);				 
					DrawBoard();
					KillTimer(SHELL_ICON_TIMER_EVENT_ID);
					m_timerFlag = true;
					SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
				}
			break;
		case NEWGAME:
				{
					NOTIFYICONDATA nicondata;
					char data1[64] = "Received new game request";				 
					nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
					nicondata.uID = 10;
					nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
					nicondata.cbSize = sizeof(nicondata);
					nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
					nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
					strcpy(nicondata.szTip,data1);
					Shell_NotifyIcon(NIM_ADD,&nicondata);				 
					DrawBoard();
					KillTimer(SHELL_ICON_TIMER_EVENT_ID);
					m_timerFlag = true;
					SetTimer(SHELL_ICON_TIMER_EVENT_ID,1000,NULL);
					AfxMessageBox("Your opponent has requested for new game");
					OnFileNewAction();
				}
				break;
		case SYNC:
			/*{
				for(int i = 0; i< 8; i++)
				{
					for(int j=0;j<8;j++)
					{
						cb[i][j].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);
					}
				}
				for(i = 2; i< data[1];)
				{
					int k = data[i++];
					int l = data[i++];
					int pieceid = data[i++];
					COLOR_TYPE ctype =(COLOR_TYPE) data[i++];
					PIECE_TYPE ptype = (PIECE_TYPE)data[i++];
					if(k >= 0 && l >= 0)
					{
 						cb[k][l].SetPieceData(pieceid,ctype,ptype,PIECE_NOT_MOVING);					 
					}
				}
				memcpy(&m_iHistory,&data[i],4);
				i+=4;
				memcpy(&m_topHistory,&data[i],4);
				i+=4;
				 
				for(int j=0;i < length;j++)
				{
					m_History[j].SetHistory((PIECE_TYPE)data[i++],(COLOR_TYPE)data[i++],
						data[i++], data[i++], data[i++], (PIECE_TYPE)data[i++],
						(COLOR_TYPE)data[i++], data[i++], data[i++], data[i++]);
				}
			}*/
			break;
		case NOTACCEPTED:
				AfxMessageBox("server not accepted for playing the game");
				break;

		default:
			break;
	}
 
}
void CNetChessView::SendSockData(unsigned char *data,int length)
{
	char clength[5];	 
	memcpy(clength,&length,4);
	if(m_pClientSocket != NULL)
	{	 
		m_pClientSocket->Send(clength,4);	 
		m_pClientSocket->Send(data,length);	 	
	}
}

void CNetChessView::OnToolsSendmessage() 
{
	if(m_pClientSocket != NULL)
	{	 
		m_ChatDlg->ShowWindow(SW_SHOW);	
	}
	else
	{
		AfxMessageBox("Not connected to network");
	}
}

void CNetChessView::OnFileOpen() 
{
	if(m_iHistory > -1)
	{
		if(AfxMessageBox("Do you want to save the playing game",MB_YESNO) == IDYES)
		{
			OnFileSave();
			AfxMessageBox("Game is saved");
		}
	}
	CFileDialog fdialog(TRUE);
	if(fdialog.DoModal() == IDOK)
	{
		m_mouseMoveFlag = false;
		m_moveRect = 0;	 
		m_iHistory = -1;	 	 	 	 
		m_topHistory = -1;
		m_timerFlag = false;
		
		for(int i = 0; i< m_level; i++)
		{
			for(int j=0;j<m_level;j++)
			{
				cb[i][j].SetPieceType(BLANK);
			}
		} 
		CString file = fdialog.GetPathName(); 
		FILE *fp = fopen(file,"r");		 
		int count = 1;
		int total =0;
		fscanf(fp,"%d %d %d\n",&total,&m_optDlg.m_check_white_on_top,&m_white_on_top);
		int totLines = 0;
		char data[2054];		 
		data[0] = FILEDATA;
		memcpy(&data[count],&total,4);
		count+=4;
		data[count++] = m_optDlg.m_check_white_on_top;
		data[count++] = m_white_on_top;

		while(!feof(fp) && totLines < total)
		{			 
			int i,j;
			char hformat;
			PIECE_TYPE piece_type;
			COLOR_TYPE piece_color;
			int pieceid;
			fscanf(fp,"%c %d %d %d %d %d\n",
 					 &hformat,&i,&j,&piece_type,&piece_color,&pieceid);
			if(hformat != 'C')
			{
				CString str = file + " file not in history format";
				AfxMessageBox(str);
				Initialize();
				OnInitialUpdate();
				return;
			}
			data[count++] = i;
			data[count++] = j;
			data[count++] = piece_type;
			data[count++] = piece_color;
			memcpy(&data[count],&pieceid,4);
			count += 4;
			cb[i][j].SetPieceData(pieceid,piece_color,piece_type,PIECE_NOT_MOVING);	
			totLines++;
		}		 
		total =0;
		fscanf(fp,"%d\n",&total);
		totLines = 0;
		m_iHistory = -1;
		memcpy(&data[count],&total,4);
		count+=4;
		while(!feof(fp) && totLines < total)
		{			 	 
			char hformat;
			PIECE_SIDE piece_side;		 
			PIECE_TYPE from_piece_type;
			COLOR_TYPE from_color_type;
			int from_pieceid;
			int from_row_id;	
			int from_col_id;
			PIECE_TYPE to_piece_type;
			COLOR_TYPE to_color_type;
			int to_pieceid;
			int to_row_id;
			int to_col_id;
			
			PIECE_TYPE rm_piece_type;
			COLOR_TYPE rm_color_type;
			int rm_pieceid;
			int rm_row_id;
			int rm_col_id;
			fscanf(fp,"%c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
				&hformat,&piece_side,&from_piece_type,
				&from_color_type,&from_pieceid,
				&from_row_id,&from_col_id, 
				&to_piece_type,	&to_color_type,&to_pieceid,&to_row_id,&to_col_id,
				&rm_piece_type,	&rm_color_type,&rm_pieceid,&rm_row_id,&rm_col_id);


			if(hformat != 'H')
			{
				CString str = file + " file not in history format";
				AfxMessageBox(str);
				Initialize();
				OnInitialUpdate();
				return;
			}
			data[count++] = piece_side;
			data[count++] = from_piece_type;
			data[count++] = from_color_type;			 
			memcpy(&data[count],&from_pieceid,4);
			count += 4;
			data[count++] = from_row_id;
			data[count++] = from_col_id;
			 
			data[count++] = to_piece_type;
			data[count++] = to_color_type;			 
			memcpy(&data[count],&to_pieceid,4);
			count += 4;
			data[count++] = to_row_id;
			data[count++] = to_col_id;

			data[count++] = rm_piece_type;
			data[count++] = rm_color_type;			 
			memcpy(&data[count],&rm_pieceid,4);
			count += 4;
			data[count++] = rm_row_id;
			data[count++] = rm_col_id;

			m_History[++m_iHistory].SetHistory(
				piece_side,from_piece_type,
				from_color_type,from_pieceid,
				from_row_id,from_col_id, 
				to_piece_type,to_color_type,to_pieceid,to_row_id,to_col_id,
				rm_piece_type,rm_color_type,rm_pieceid,rm_row_id,rm_col_id);	 			  			 
			totLines++;
		}
		fclose(fp);	
		m_topHistory = m_iHistory;
		SendSockData((unsigned char*)data,count);
	}
	DrawBoard();	
}

void CNetChessView::OnFileSave() 
{
	// TODO: Add your command handler code here
	if(m_iHistory <0)
	{
		AfxMessageBox("Game not started");
		return;
	}

	CFileDialog fdialog(FALSE);
	if(fdialog.DoModal() == IDOK)
	{ 
		CString file = fdialog.GetPathName(); 
		FILE *fp = fopen(file,"w");
		int count=0;
		for(int i=0;i<m_level;i++)
		{
			for(int j=0;j<m_level;j++)
			{				 
				PIECE_TYPE piece_type;
				COLOR_TYPE piece_color;
				int pieceid;
				STATE piece_state;
				cb[i][j].GetPieceData(pieceid,piece_color,piece_type,piece_state);
				if(piece_type != BLANK)
				{
				  count++;
				}
			}
		}

		fprintf(fp,"%d %d %d\n",count,m_optDlg.m_check_white_on_top,m_white_on_top);

		for(i=0;i<m_level;i++)
		{
			for(int j=0;j<m_level;j++)
			{				 
				PIECE_TYPE piece_type;
				COLOR_TYPE piece_color;
				int pieceid;
				STATE piece_state;
				cb[i][j].GetPieceData(pieceid,piece_color,piece_type,piece_state);
				if(piece_type != BLANK)
				{
				 fprintf(fp,"C %d %d %d %d %d\n",
 					 i,j,piece_type,piece_color,pieceid);
				}
			}
		}
		fprintf(fp,"%d\n",m_iHistory+1);
		 
		PIECE_SIDE piece_side;		 
		PIECE_TYPE from_piece_type;
		COLOR_TYPE from_color_type;
		int from_pieceid;
		int from_row_id;
		int from_col_id;
		PIECE_TYPE to_piece_type;
		COLOR_TYPE to_color_type;
		int to_pieceid;
		int to_row_id;
		int to_col_id;

		PIECE_TYPE rm_piece_type;
		COLOR_TYPE rm_color_type;
		int rm_pieceid;
		int rm_row_id;
		int rm_col_id;

		for(i=0;i<=m_iHistory;i++)
		{		 
			m_History[i].GetHistory(			 
				piece_side,from_piece_type,
				from_color_type,from_pieceid,
				from_row_id,from_col_id, to_piece_type,
				to_color_type,to_pieceid,to_row_id,
				to_col_id,	rm_piece_type,rm_color_type,rm_pieceid,rm_row_id,rm_col_id);
			fprintf(fp,"H %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
				piece_side,from_piece_type,
				from_color_type,from_pieceid,
				from_row_id,from_col_id, 
				to_piece_type,to_color_type,to_pieceid,to_row_id,to_col_id,
				rm_piece_type,rm_color_type,rm_pieceid,rm_row_id,rm_col_id); 
		} 
		fclose(fp);
		DrawBoard();
	}	 
}

/*void CNetChessView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	CFileDialog fdialog(TRUE);
	if(fdialog.DoModal() == IDOK)
	{
 
		CString file = fdialog.GetPathName(); 
		FILE *fp = fopen(file,"w");
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{				 
				PIECE_TYPE piece_type;
				COLOR_TYPE piece_color;
				STATE piece_state;
				int pieceid;
				cb[i][j].GetPieceData(pieceid,piece_color,piece_type,piece_state);
				if(piece_type != BLANK)
				{
				 fprintf(fp,"H %d %d %d %d %d\n",
 					 i,j,piece_type,piece_color,pieceid);
				}
			}
		}
		fclose(fp);
	}
	DrawBoard();
	
}*/
 

void CNetChessView::OnViewLetter() 
{
	// TODO: Add your command handler code here
	if(m_LetterFlag == false)
	{	 
		m_LetterFlag = true;
	}
	else
	{	 
		m_LetterFlag = false;
	}
	DrawBoard(); 
}

void CNetChessView::OnUpdateViewLetter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_LetterFlag == false)
	{
		pCmdUI->SetCheck(0);	
	}
	else
	{
		pCmdUI->SetCheck(1);
	}
}

void CNetChessView::OnViewNumber() 
{
	// TODO: Add your command handler code here
	 if(m_NumberFlag == false)
	{	 
		m_NumberFlag = true;
	}
	else
	{	 
		m_NumberFlag = false;
	}
	DrawBoard();
}

void CNetChessView::OnUpdateViewNumber(CCmdUI* pCmdUI) 
{
	if(m_NumberFlag == false)
	{
		pCmdUI->SetCheck(0); 
	}
	else
	{
		pCmdUI->SetCheck(1);		 
	};
}
LRESULT CNetChessView::OnMessageColorData(WPARAM wParam,LPARAM lParam)
{	 
	DrawBoard();
	return 0;
}


void CNetChessView::OnFileSavehistory() 
{
	// TODO: Add your command handler code here
	if(m_iHistory < 0)
	{
		AfxMessageBox("No history to save");
		return;
	}
	CFileDialog fdialog(FALSE);
	if(fdialog.DoModal() == IDOK)
	{
 
		CString file = fdialog.GetPathName(); 
		FILE *fp = fopen(file,"w");
		PIECE_SIDE piece_side;
		PIECE_TYPE from_piece_type;
		COLOR_TYPE from_color_type;
		int from_pieceid;
		int from_row_id;
		int from_col_id;
		PIECE_TYPE to_piece_type;
		COLOR_TYPE to_color_type;
		int to_pieceid;
		int to_row_id;
		int to_col_id;
		PIECE_TYPE rm_piece_type;
		COLOR_TYPE rm_color_type;
		int rm_pieceid;
		int rm_row_id;
		int rm_col_id;
		for(int i=0;i<=m_iHistory;i++)
		{		 
			m_History[i].GetHistory(piece_side,from_piece_type,
				from_color_type,from_pieceid,
				from_row_id,from_col_id, to_piece_type,
				to_color_type,to_pieceid,to_row_id,
				to_col_id,
				rm_piece_type,
				rm_color_type,rm_pieceid,rm_row_id,
				rm_col_id
				);
			CString str;
			/*str.Format("%d) %d %d %d %d %d %d %d %d %c%d",i+1,
				from_piece_type,
				from_color_type,from_pieceid,
				from_col_id+'A', from_row_id+1,to_piece_type,
				to_color_type,to_pieceid,
				to_col_id+'A',
				to_row_id);*/
			char frompiececolor= ' ';
			switch(from_color_type)
			{
				case BLACK:
					frompiececolor = 'B';
					break;
				case WHITE:
					frompiececolor = 'W';
					break;
			}
			char from_type=' ';
			switch(from_piece_type)
			{
			case KING:
					from_type = 'K';
					break;
				default:
					from_type = ' ';
					break;
			}
			char topiececolor= ' ';
			switch(to_color_type)
			{
				case BLACK:
					topiececolor = 'B';
					break;
				case WHITE:
					topiececolor = 'W';
					break;
			}
			char to_type=' ';
			switch(to_piece_type)
			{
				 
				case KING:
					to_type = 'K';
					break;		 
				default:
					to_type = ' ';
					break;
			}
			if(piece_side == TOP)
			{
				fprintf(fp,"%3d) %c%c%c%d to %c%c%c%d\n",i+1,
					from_type,frompiececolor, 
					m_level-1-from_col_id+'A', (from_row_id+1),			 
					to_type,topiececolor, m_level-1-to_col_id+'A',
					(to_row_id+1));
			}		
			else
			{
				fprintf(fp,"%3d) %c%c%c%d to %c%c%c%d\n",i+1,
					from_type,frompiececolor, 
					from_col_id+'A', m_level- (from_row_id+1),			 
					to_type,topiececolor, to_col_id+'A',
					m_level-(to_row_id+1));
			} 
			 
			//m_edit_history += str + (CString)"\r\n";
			UpdateData(FALSE);
		} 
		fclose(fp);
	}
	DrawBoard();
}
bool CNetChessView::CheckValidMove(int i,int j, int& rmx,int& rmy)
{
	PIECE_TYPE from_piece_type;
	COLOR_TYPE from_piece_color;
	int from_pieceid;
	STATE from_piece_state;
	cb[i][j].GetPieceData(from_pieceid,from_piece_color,from_piece_type,from_piece_state);
	 	
	PIECE_TYPE to_piece_type;
	COLOR_TYPE to_piece_color;
	int to_pieceid;
	STATE to_piece_state;
	cb[m_point.x][m_point.y].GetPieceData(to_pieceid,to_piece_color,to_piece_type,to_piece_state);
	if(m_point.x+1 == i-1 && m_point.y+1 == j - 1)//BOTTOM
	{ 
		rmx = i-1;
		rmy = j-1;
	} 
	else if	(m_point.x-1 == i+1 && m_point.y-1 == j + 1)//TOP
	{
		rmx = i+1;
		rmy = j+1;
	}
	else if(m_point.x+1 == i-1 && m_point.y-1 == j +1)
	{
		rmx = i-1;
		rmy = j+1;
	}
	else if(m_point.x-1 == i+1 && m_point.y+1 == j - 1)
	{		 
		rmx = i+1;
		rmy = j-1;
	}
	else
	{
		rmx = rmy = -1;
		return true;
	}
	if(cb[rmx][rmy].GetPieceColor() == cb[m_point.x][m_point.y].GetPieceColor())
		return false;
	//cb[rmx][rmy].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);
	return true;
}

/*void CNetChessView::OnToolsPlayhistory() 
{
	// TODO: Add your command handler code here
	if(m_iHistory < 0)
	{
		return;
	}
	CHistory *tempHistory= new CHistory[MAXHISTORY];
	int totHistory = m_iHistory;
	PIECE_SIDE piece_side;
	PIECE_TYPE from_piece_type;
	COLOR_TYPE from_color_type;
	int from_pieceid;
	int from_row_id;
	int from_col_id;

	PIECE_TYPE to_piece_type;
	COLOR_TYPE to_color_type;
	int whiteontop = m_optDlg.m_check_white_on_top;
	int to_pieceid;
	int to_row_id;
	int to_col_id;
	for(int i=0;i<=m_iHistory;i++)
	{
		m_History[i].GetHistory(piece_side,from_piece_type,from_color_type,
			from_pieceid, from_row_id, from_col_id, to_piece_type,
			to_color_type, to_pieceid, to_row_id, to_col_id);
		tempHistory[i].SetHistory(piece_side,from_piece_type,from_color_type,
			from_pieceid, from_row_id, from_col_id, to_piece_type,
			to_color_type, to_pieceid, to_row_id, to_col_id); 
	}
	OnInitialUpdate();
	m_white_on_top = true;	 
	//DrawBoard();
	 
	for(i=0;i<=totHistory;i++)
	{
		tempHistory[i].GetHistory(piece_side,from_piece_type,from_color_type,
			from_pieceid, from_row_id, from_col_id, to_piece_type,
			to_color_type, to_pieceid, to_row_id, to_col_id);
		CRect rect;
		rect = cb[from_row_id][from_col_id].GetRect();
		CPoint pt(rect.left+10,rect.top+10);
		OnLButtonDownAction(255,pt);
		rect = cb[to_row_id][to_col_id].GetRect();
		Sleep(1000);
		CPoint pt1(rect.left + 10, rect.top + 10);
		OnLButtonUpAction(255,pt1);
	}
	delete[] tempHistory;
	tempHistory = NULL;	
}*/

void CNetChessView::OnLButtonDownAction(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NOTIFYICONDATA nicondata;
	char data[64] = "NetCheckers by A.V.Maheswara Rao";				 
	nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
	nicondata.uID = 10;
	nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
	nicondata.cbSize = sizeof(nicondata);
	nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
	nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nicondata.szTip,data);
	Shell_NotifyIcon(NIM_DELETE,&nicondata);		
	KillTimer(SHELL_ICON_TIMER_EVENT_ID);
	m_timerFlag = false;
	for(int i = 0; i < m_level; i++)
	{
		for( int j = 0; j < m_level; j++)
		{
			CRgn rgn;
			CRect rect = cb[i][j].GetRect();
			rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
			if(rgn.PtInRegion(point))// && m_player_turn == cb[i][j].GetPieceColor())
			{		 				 
				m_point.x = i; m_point.y = j;
				cb[i][j].SetPieceState(PIECE_MOVING);
			 	m_mouseMoveFlag = true;
				return;	 
			}
		}
	}
	 
 	CView::OnLButtonDown(nFlags, point);
}

void CNetChessView::OnLButtonUpAction(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_mouseMoveFlag == false)
	{	 
				return;
	}	
	m_mouseMoveFlag = false;
	m_moveRect =0;
	cb[m_point.x][m_point.y].SetPieceState(PIECE_NOT_MOVING);
    for(int i = 0; i < m_level; i++)
	{
		for( int j = 0; j < m_level; j++)
		{			 
			if(cb[i][j].GetColorType() == BLACK && cb[i][j].GetPieceId() == -1)
			{
				CRgn rgn;
				CRect rect = cb[i][j].GetRect();
				rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);	
				if(rgn.PtInRegion(point)&&rect != cb[m_point.x][m_point.y].GetRect())
				{
					int piece_id;
					COLOR_TYPE  piece_color;
					PIECE_TYPE  piece_type;
					STATE piece_state;
					int to_piece_id;
					COLOR_TYPE  to_piece_color;
					PIECE_TYPE  to_piece_type;
					STATE to_piece_state;
					int rm_piece_id=-1;
					COLOR_TYPE  rm_piece_color=NONE;
					PIECE_TYPE  rm_piece_type=BLANK;
					STATE rm_piece_state=PIECE_NOT_MOVING;
					cb[m_point.x][m_point.y].GetPieceData(piece_id,piece_color,piece_type,piece_state);
					cb[i][j].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);					 
					cb[m_point.x][m_point.y].SetPieceState(PIECE_NOT_MOVING);
					if(piece_color == to_piece_color)
					{
						m_point.x = m_point.y = -1;
						DrawBoard();
						return;
					}
					int rmx,rmy;
					if(CheckValidMove(i,j,rmx,rmy) == true)
					{
						m_player_turn = m_player_turn == WHITE ? BLACK: WHITE;
						if(nFlags != 255)
						{
							if(rmx != -1)
							{
								cb[rmx][rmy].GetPieceData(rm_piece_id,rm_piece_color,rm_piece_type,rm_piece_state);					 
								cb[rmx][rmy].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);								 
							}
							if(m_white_on_top == false)
							{

								m_History[++m_iHistory].SetHistory(BOTTOM,
									piece_type,piece_color,piece_id,m_point.x,m_point.y,
									to_piece_type,to_piece_color,to_piece_id,i,j,
									rm_piece_type,rm_piece_color,rm_piece_id,rmx,rmy);
							}
							else
							{
								m_History[++m_iHistory].SetHistory(TOP,piece_type,piece_color,piece_id,m_point.x,m_point.y,
									to_piece_type,to_piece_color,to_piece_id,i,j,
									rm_piece_type,rm_piece_color,rm_piece_id,rmx,rmy);
							}
							m_topHistory = m_iHistory;
						}
						cb[i][j].SetPieceData(piece_id,piece_color,piece_type,PIECE_NOT_MOVING);
						cb[m_point.x][m_point.y].SetPieceType(BLANK);
						cb[m_point.x][m_point.y].SetPieceData(-1,NONE,BLANK,PIECE_NOT_MOVING);
						if(nFlags != 255)
						{
							char data[100];							 
							int k=0;
							data[k++] = MOVE;
							data[k++] = m_white_on_top;
							data[k++] = (char)m_point.x;
							data[k++] = (char)m_point.y;
							memcpy(&data[k],&piece_id,4);
							k+=4;
							data[k++] = piece_color;
							data[k++] = piece_type;
							data[k++] = i;
							data[k++] = j;
							memcpy(&data[k],&to_piece_id,4);
							k+=4;
							data[k++] = to_piece_color;
							data[k++] = to_piece_type;
							data[k++] = rmx;
							data[k++] = rmy;
							memcpy(&data[k],&rm_piece_id,4);
							k+=4;
							data[k++] = rm_piece_color;
							data[k++] = rm_piece_type;
							memcpy(&data[k],&m_topHistory,4);
							k+=4;
							SendSockData((unsigned char*)data,k);						 
						}
					}
				}
			}
		}
	}			 
	m_point.x = m_point.y = -1;
	DrawBoard();	 
}

void CNetChessView::OnMouseMoveAction(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_mouseMoveFlag == false)
		return;	 
	 
	CRect rect( point.x -25, point.y - 25, point.x + 25, point.y + 25);				  
	m_moveRect = rect;	 
	DrawBoard();	 
}

void CNetChessView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	OnEditUndoAction();
 	unsigned char msg = UNDO;
	SendSockData((unsigned char*)&msg,1);

}
void CNetChessView::OnEditUndoAction()
{
	if(m_iHistory < 0)
	{
		return;
	}
	PIECE_SIDE piece_side;
	PIECE_TYPE from_piece_type;
	COLOR_TYPE from_color_type;
	int from_pieceid;
	int from_row_id;
	int from_col_id;
	PIECE_TYPE to_piece_type;
	COLOR_TYPE to_color_type;
	int to_pieceid;
	int to_row_id;
	int to_col_id;

	PIECE_TYPE rm_piece_type;
	COLOR_TYPE rm_color_type;
	int rm_pieceid;
	int rm_row_id;
	int rm_col_id;


	m_History[m_iHistory].GetHistory(
		piece_side,
		from_piece_type, from_color_type,from_pieceid,
		from_row_id,from_col_id, to_piece_type,
		to_color_type,to_pieceid,to_row_id,
		to_col_id,
		rm_piece_type,
		rm_color_type,rm_pieceid,rm_row_id,
		rm_col_id);

	if(piece_side == BOTTOM && m_white_on_top == false) 		 
	{

		cb[from_row_id][from_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);

		cb[to_row_id][to_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);
		if(rm_pieceid != -1)
		{
			cb[rm_row_id][rm_col_id].SetPieceData(
				rm_pieceid,rm_color_type,rm_piece_type,
				PIECE_NOT_MOVING);
		}
	}
	else if(piece_side == TOP && m_white_on_top == false)
	{
		cb[m_level-1-from_row_id][m_level-1-from_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);

		cb[m_level-1-to_row_id][m_level-1-to_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);
		if(rm_pieceid != -1)
		{
			cb[m_level-1-rm_row_id][m_level-1-rm_col_id].SetPieceData(
				rm_pieceid,rm_color_type,rm_piece_type,
				PIECE_NOT_MOVING);
		}
	} 
	else if(piece_side == BOTTOM && m_white_on_top == true)
	{
		cb[m_level-1-from_row_id][m_level-1-from_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);

		cb[m_level-1-to_row_id][m_level-1-to_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);	 	 
		if(rm_pieceid != -1)
		{
			cb[m_level-1-rm_row_id][m_level-1-rm_col_id].SetPieceData(
				rm_pieceid,rm_color_type,rm_piece_type,
				PIECE_NOT_MOVING);
		}
	}
	else if(piece_side == TOP && m_white_on_top == true)
	{
		cb[from_row_id][from_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);

		cb[to_row_id][to_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);	 	 
		if(rm_pieceid != -1)
		{
			cb[rm_row_id][rm_col_id].SetPieceData(
				rm_pieceid,rm_color_type,rm_piece_type,
				PIECE_NOT_MOVING);
		}
	}
	m_iHistory--;
	DrawBoard();
}

void CNetChessView::OnEditRedo() 
{
	// TODO: Add your command handler code here	 	 
	OnEditRedoAction();
 	unsigned char msg = REDO;
	SendSockData((unsigned char*)&msg,1);
}

void CNetChessView::OnEditRedoAction()
{
	m_iHistory++;
	if(m_iHistory > m_topHistory)
	{
		m_iHistory--;
		return;
	}
	PIECE_SIDE piece_side;
	PIECE_TYPE from_piece_type;
	COLOR_TYPE from_color_type;
	int from_pieceid;
	int from_row_id;
	int from_col_id;
	PIECE_TYPE to_piece_type;
	COLOR_TYPE to_color_type;
	int to_pieceid;
	int to_row_id;
	int to_col_id;
	PIECE_TYPE rm_piece_type;
	COLOR_TYPE rm_color_type;
	int rm_pieceid;
	int rm_row_id;
	int rm_col_id;


	m_History[m_iHistory].GetHistory(
		piece_side,
		from_piece_type, from_color_type,from_pieceid,
		from_row_id,from_col_id, to_piece_type,
		to_color_type,to_pieceid,to_row_id,
		to_col_id,
		rm_piece_type,
		rm_color_type,rm_pieceid,rm_row_id,
		rm_col_id);
	
	if(piece_side == BOTTOM && m_white_on_top == false)		 
	{
		cb[from_row_id][from_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);	 	 
		cb[to_row_id][to_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);	 
		if(rm_pieceid != -1)
		{
			cb[rm_row_id][rm_col_id].SetPieceData(
				-1,NONE,BLANK,
				PIECE_NOT_MOVING);
		}
	}
	else if(piece_side == TOP && m_white_on_top == false)
	{
		cb[m_level-1-from_row_id][m_level-1-from_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);

		cb[m_level-1-to_row_id][m_level-1-to_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);		 
		if(rm_pieceid != -1)
		{
			cb[m_level-1-rm_row_id][m_level-1-rm_col_id].SetPieceData(
				-1,NONE,BLANK,
				PIECE_NOT_MOVING);
		}
	}
	else if (piece_side == BOTTOM && m_white_on_top == true)
	{
		cb[m_level-1-from_row_id][m_level-1-from_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);
		cb[m_level-1-to_row_id][m_level-1-to_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);
		if(rm_pieceid != -1)
		{
			cb[m_level-1-rm_row_id][m_level-1-rm_col_id].SetPieceData(
				-1,NONE,BLANK,
				PIECE_NOT_MOVING);
		}
	}
	else if(piece_side == TOP && m_white_on_top == true)
	{
		cb[from_row_id][from_col_id].SetPieceData(
				to_pieceid,to_color_type,to_piece_type,
				PIECE_NOT_MOVING);	 	 

		cb[to_row_id][to_col_id].SetPieceData(
			from_pieceid,from_color_type,from_piece_type,
			PIECE_NOT_MOVING);
		if(rm_pieceid != -1)
		{
			cb[rm_row_id][rm_col_id].SetPieceData(
				-1,NONE,BLANK,
				PIECE_NOT_MOVING);
		}
		 
	}
	DrawBoard();
}
void CNetChessView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_mouseMoveFlag == true)
	{
		return;
	}
	CPickPieceDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		//CString str;
		//str.Format("%d %d %d",dlg.m_piecked_piece,dlg.m_piece_color,dlg.m_piece_type);
		//AfxMessageBox(str);
			for(int i = 0; i < m_level; i++)
			{
				for( int j = 0; j < m_level; j++)
				{
					CRgn rgn;
					CRect rect = cb[i][j].GetRect();
					rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
					if(rgn.PtInRegion(point) && cb[i][j].GetColorType() != WHITE)
					{						 
						int piece_id;
						COLOR_TYPE  piece_color;
						PIECE_TYPE  piece_type;
						STATE piece_state = PIECE_NOT_MOVING;
						int to_piece_id;
						COLOR_TYPE  to_piece_color;
						PIECE_TYPE  to_piece_type;
						STATE to_piece_state=PIECE_NOT_MOVING;

						int rm_piece_id=-1;
						COLOR_TYPE  rm_piece_color=NONE;
						PIECE_TYPE  rm_piece_type=BLANK;
						STATE rm_piece_state=PIECE_NOT_MOVING;

						piece_id = dlg.m_piecked_piece;
						piece_color = dlg.m_piece_color;
						piece_type = dlg.m_piece_type;						 						 
						cb[i][j].GetPieceData(to_piece_id,to_piece_color,to_piece_type,to_piece_state);					 
						cb[i][j].SetPieceState(PIECE_NOT_MOVING);
						m_player_turn = m_player_turn == WHITE ? BLACK: WHITE;
						if(m_white_on_top == false)
						{
							m_History[++m_iHistory].SetHistory(BOTTOM,
								piece_type,piece_color,piece_id,i,j,
								to_piece_type,to_piece_color,to_piece_id,i,j,BLANK,NONE,-1,-1,-1);
						}
						else
						{
							m_History[++m_iHistory].SetHistory(TOP,
								piece_type,piece_color,piece_id,i,j,
								to_piece_type,to_piece_color,to_piece_id,i,j,BLANK,NONE,-1,-1,-1);
						}
						m_topHistory = m_iHistory;
						cb[i][j].SetPieceData(piece_id,piece_color,piece_type,PIECE_NOT_MOVING);						 
						char data[50];						 
						int k=0; 
						data[k++] = MOVE;
						data[k++] = m_white_on_top;
						data[k++] = i;
						data[k++] = j;
						memcpy(&data[k],&piece_id,4);
						k+=4;
						data[k++] = piece_color;
						data[k++] = piece_type;
	   					data[k++] = i;
						data[k++] = j;
						memcpy(&data[k],&to_piece_id ,4);
						k+=4;
						data[k++] = to_piece_color;
						data[k++] = to_piece_type;
						data[k++] = -1;
						data[k++] = -1;
						memcpy(&data[k],&rm_piece_id,4);
						k+=4;			
						data[k++] = rm_piece_color;
						data[k++] = rm_piece_type;
						memcpy(&data[k],&m_topHistory,4);
						k+=4;						 
						SendSockData((unsigned char*)data,k);
						DrawBoard();
						return;	 
					}
				}
			}		 
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CNetChessView::OnUpdateToolsServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*if(m_pServerSocket == NULL)
	{
		pCmdUI->SetCheck(0);	
	}
	else
	{
		pCmdUI->SetCheck(1);
	}*/
	
}

void CNetChessView::OnUpdateToolsClient(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*if(m_pServerSocket == NULL)
	{
		pCmdUI->SetCheck(0);	
	}
	else
	{
		pCmdUI->SetCheck(1);
	}*/	
}

void CNetChessView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	DrawBoard();
	CView::OnPrint(pDC, pInfo);
}

void CNetChessView::OnTimer(UINT nIDEvent) 
{
	static int state=1;	 
	switch(nIDEvent)
	{
		case SHELL_ICON_TIMER_EVENT_ID:

			{				
				NOTIFYICONDATA nicondata;
				char data[64] = "NetCheckers by A.V.Maheswara Rao";
				 
				nicondata.hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
				nicondata.uID = 10;
				nicondata.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP; 
				nicondata.cbSize = sizeof(nicondata);
				nicondata.uCallbackMessage = MY_MESSAGE_SHELLNOTIFY;
				nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
				strcpy(nicondata.szTip,data);				
				if(state == 1)
				{
					nicondata.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
					Shell_NotifyIcon(NIM_MODIFY,&nicondata);
					state = 0;
				}
				else
				{
					nicondata.hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME_OPPOSITE);
					state = 1;
					Shell_NotifyIcon(NIM_MODIFY,&nicondata);
				}
			}
			break;
		default:
			break;
		 
	}
	CView::OnTimer(nIDEvent);
}
void CNetChessView::KillTimerEvent()
{
	 
	KillTimer(SHELL_ICON_TIMER_EVENT_ID);
	m_timerFlag = false;
}

void CNetChessView::OnFileNew() 
{
	if(m_iHistory < 0)
	{
		AfxMessageBox("Game already started");
		return;
	}
	OnFileNewAction(); 
	unsigned char data=NEWGAME;
	SendSockData(&data,1);
	 
}
void CNetChessView::OnFileNewAction()
{
	if(m_iHistory > -1)
	{
		if(AfxMessageBox("Do you want to save the playing game",MB_YESNO) == IDYES)
		{
			OnFileSave();
			AfxMessageBox("Game is saved");
		}
		Initialize();
		OnInitialUpdate();
		DrawBoard();
	}	
}

 

/*void CNetChessView::OnToolsSync() 
{
	unsigned char data[1000];
	int count = 2;
	data[0]= SYNC;
 	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{				 
			PIECE_TYPE piece_type;
			COLOR_TYPE piece_color;
			int pieceid;
			STATE piece_state;
			cb[i][j].GetPieceData(pieceid,piece_color,piece_type,piece_state);
			if(piece_type != BLANK)
			{
				data[count++] = i;
				data[count++] = j;
				data[count++] = piece_type;
				data[count++] = piece_color;
				data[count++] = pieceid;			  
			}
		}
	}
	data[1] = count;
	memcpy(&data[count],&m_iHistory,4);
	count+=4;
	memcpy(&data[count],&m_topHistory,4);
	count+=4;
	PIECE_TYPE from_piece_type;
	COLOR_TYPE from_color_type;
	int from_pieceid;
	int from_row_id;
	int from_col_id;
	PIECE_TYPE to_piece_type;
	COLOR_TYPE to_color_type;
	int to_pieceid;
	int to_row_id;
	int to_col_id;
	 
	for(int j=0;j<=m_iHistory;j++)
	{
		m_History[j].GetHistory(
			from_piece_type, from_color_type,from_pieceid,
			from_row_id,from_col_id, to_piece_type,
			to_color_type,to_pieceid,to_row_id,
			to_col_id);
		data[count++] = from_piece_type;
		data[count++] = from_color_type;
		data[count++] = from_pieceid;
		data[count++] = from_row_id;
		data[count++] = from_col_id;
		data[count++] = to_piece_type;
		data[count++] = to_color_type;
		data[count++] = to_pieceid;
		data[count++] = to_row_id;
		data[count++] = to_col_id;
	}
	SendSockData(data,count);
}*/

void CNetChessView::OnViewHistory() 
{
	 if(m_iHistory < 0)
	 {
		 AfxMessageBox("History not found");
		 return;
	 }
	  CHistoryDlg dlg(this,m_History,m_iHistory,m_level);
	  dlg.DoModal();
}

void CNetChessView::OnToolsWhiteontop() 
{
	// TODO: Add your command handler code here
	m_optDlg.m_check_white_on_top = 
		m_optDlg.m_check_white_on_top == (int)true?m_optDlg.m_check_white_on_top = false:m_optDlg.m_check_white_on_top = (int)true;
	//m_optDlg.UpdateData(FALSE);
	DrawBoard();	
}

 

void CNetChessView::OnEditMovefirst() 
{
	// TODO: Add your command handler code here
	int total = m_iHistory;
	for(int i=0;i<=total;i++)
	{
		OnEditUndo();
	}
}

void CNetChessView::OnEditMovelast() 
{
	// TODO: Add your command handler code here
	int total = m_topHistory;
	for(int i=0;i<=total;i++)
	{
		OnEditRedo();
	}
		 	
}

void CNetChessView::OnHelpHowtoplay() 
{
	CHowToPlayDlg dlg;
	dlg.DoModal();
	/*CString helpMsg;

	helpMsg = "NetCheckers is an American Checkers game which can be played over lan, intranet using TCP/IP between two players.\n\n"
		"This software can be used for playing checkers as server, client or single board.\n"
		"To play as server, enter the Server port number by clicking Tools->Server menu option.\n"
		"To connect to the server, enter server ip and port number by clicking Tools->Client menu option.\n"
		"Two players can play in the same board also.\n\n"
		"Once the connection is established, mouse can be used to move the checkers.\n"
		"Same action will be reflected to the client/server side also. Features like undo, redo, move first, move last "
		"are also provided. The current game can be saved with history. History alone also can be saved. "
		"The saved game can be opened, the board will be placed with opened game with history. "
		"The actions New, Open, Undo, Redo, Move First, Move Last, Send Message, Moving a piece, selecting/promoting a piece "
		" will be reflected to client/server.\n"
		"\nOther features are:-----\n"
		"\"Edit->Option\" can be used to to change the color of the board squares.\n"
		"\"Edit->Propertis\" will display the current status of the game.\n"
		"\"Tools->White on top\" can be used to change the white piece side on top or bottom.\n"
		"\"Tools->SendMessage\" can be used to send instant message to the other player.\n"
		"\"Tools->Disconnect\" disconnects from the network.\n"
		"\"View->Letter\", \"View->Number\" displays letters or numbers on the board.\n"
		"\"View->History\" will display the history of the game.\n"
		"\"View->Hide\" will hide the current board and an icon will be placed in the system tray. "
		"On clicking on icon, the hidden board will be displayed\n\n"
		"To change an existing piece or to place new piece or to promote "
		"a piece, click on mouse right button and select the required piece.\n"
		"Whenever there is a move, a message or any other action, an icon will be toggled in the system tray. "
		"On clicking on icon in system tray, the hidden game will be displayed.\n\n"
		"This software is aimed at for playing checkers game between two players over network.\n"
		"No inteligence is implemented with this software.\n\n"
		"Enjoy the game!!!";  
		AfxMessageBox(helpMsg);*/
	// TODO: Add your command handler code here
	
}

void CNetChessView::OnToolsDisconnect() 
{
	// TODO: Add your command handler code here
	 
	if(m_pClientSocket == NULL)
	{
		AfxMessageBox("Not connected to network");
		if(m_pServerSocket != NULL)
		{
			if(AfxMessageBox("Are you sure, you want to disconnect",MB_YESNO)==IDYES)
			{
				delete m_pServerSocket;
				m_pServerSocket = NULL;
			}
		}
		return;
	}
	if(m_pClientSocket != NULL)
	{ 
		if(AfxMessageBox("Are you sure, you want to disconnect",MB_YESNO)==IDYES)
		{
			m_pClientSocket->ShutDown(2);
			m_pClientSocket->Close();
			delete m_pClientSocket;
			m_pClientSocket = NULL; 
		}
	}
}

void CNetChessView::OnEditProperties() 
{
	// TODO: Add your command handler code here
	CPropertiesDlg dlg(this);
	if(m_pServerSocket != NULL)
	{
		if(m_pClientSocket != NULL)
		{
			CString ipaddr;int port;
			((CClientSocket*)m_pClientSocket)->GetInfo(ipaddr,port);
			dlg.SetInfo(SERVER,ipaddr,port,((CServerSocket*)m_pServerSocket)->m_portnumber);
		}
		else
		{
			dlg.SetInfo(SERVER," ",0,((CServerSocket*)m_pServerSocket)->m_portnumber);			 
		}
	}
	else if(m_pClientSocket != NULL)
	{
		CString ipaddr;int port;
		((CClientSocket*)m_pClientSocket)->GetInfo(ipaddr,port);
		dlg.SetInfo(CLIENT,ipaddr,port,0);
	}
	else
	{
		dlg.SetInfo(-1,"",0,0);
	}
//dlg.UpdateData(FALSE);
	dlg.DoModal();	
}

/*void CNetChessView::OnToolsGametype() 
{
	// TODO: Add your command handler code here
	CGameTypeDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_level = dlg.m_level;
		m_GameType = dlg.m_GameType;
		OnInitialUpdate();
		DrawBoard();
	}
}*/

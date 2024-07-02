// HistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetChess.h"
#include "HistoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg dialog


CHistoryDlg::CHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistoryDlg)
	m_edit_history = _T("");
	//}}AFX_DATA_INIT
}

CHistoryDlg::CHistoryDlg(CWnd* pParent /*=NULL*/,CHistory *history,int historycount,int level)
	: CDialog(CHistoryDlg::IDD, pParent)
{ 
	m_edit_history = _T(""); 
	m_History = history;
	m_iHistory = historycount;
	m_level = level;

}

void CHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistoryDlg)
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_edit_history);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistoryDlg, CDialog)
	//{{AFX_MSG_MAP(CHistoryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryDlg message handlers

BOOL CHistoryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
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
		m_History[i].GetHistory(piece_side,
			from_piece_type,
			from_color_type,from_pieceid,
			from_row_id,from_col_id, to_piece_type,
			to_color_type,to_pieceid,to_row_id,
			to_col_id,
			rm_piece_type, rm_color_type, rm_pieceid,
			rm_row_id, rm_col_id);
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
			str.Format("%3d) %c%c%c%d to %c%c%c%d",i+1,
				from_type,frompiececolor, 
				m_level-1-from_col_id+'A', (from_row_id+1),			 
				to_type,topiececolor, m_level-1-to_col_id+'A',
				(to_row_id+1));
		}		
		else
		{
			str.Format("%3d) %c%c%c%d to %c%c%c%d",i+1,
				from_type,frompiececolor, 
				from_col_id+'A', 9- (from_row_id+1),			 
				to_type,topiececolor, to_col_id+'A',
				9-(to_row_id+1));
		}

		m_edit_history += str + (CString)"\r\n";
		UpdateData(FALSE);
	} 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

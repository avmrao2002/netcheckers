#if !defined(AFX_GAMETYPEDLG1_H__DBAA36ED_1454_49DA_B50F_2AC2C3645AF1__INCLUDED_)
#define AFX_GAMETYPEDLG1_H__DBAA36ED_1454_49DA_B50F_2AC2C3645AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameTypeDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameTypeDlg dialog

class CGameTypeDlg : public CDialog
{
// Construction
public:
	GAME_TYPE m_GameType;
	int m_level;
	CGameTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameTypeDlg)
	enum { IDD = IDD_DIALOG_GAME_TYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGameTypeDlg)
	afx_msg void OnRadioAmerican();
	afx_msg void OnRADIOCHINESE10x10();
	afx_msg void OnRADIOCHINESE8x8();
	afx_msg void OnRadioCrowded();
	afx_msg void OnRadioInternational();
	afx_msg void OnRadioItalian();
	afx_msg void OnRadioPolish();
	afx_msg void OnRadioRussian();
	afx_msg void OnRadioSparse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMETYPEDLG1_H__DBAA36ED_1454_49DA_B50F_2AC2C3645AF1__INCLUDED_)

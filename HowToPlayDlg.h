#if !defined(AFX_HOWTOPLAYDLG_H__763B58CE_1EFB_4D10_9C3F_A7232CE53300__INCLUDED_)
#define AFX_HOWTOPLAYDLG_H__763B58CE_1EFB_4D10_9C3F_A7232CE53300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HowToPlayDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHowToPlayDlg dialog

class CHowToPlayDlg : public CDialog
{
// Construction
public:
	CHowToPlayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHowToPlayDlg)
	enum { IDD = IDD_DIALOG_HOWTOPLAY };
	CString	m_edit_howtoplay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHowToPlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHowToPlayDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOWTOPLAYDLG_H__763B58CE_1EFB_4D10_9C3F_A7232CE53300__INCLUDED_)

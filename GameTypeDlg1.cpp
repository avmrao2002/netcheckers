// GameTypeDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "NetChess.h"
#include "GameTypeDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameTypeDlg dialog


CGameTypeDlg::CGameTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameTypeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_level= 8;
	m_GameType = AMERICAN;
}


void CGameTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameTypeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CGameTypeDlg)
	ON_BN_CLICKED(IDC_RADIO_AMERICAN, OnRadioAmerican)
	ON_BN_CLICKED(IDC_RADIO_CHINESE10x10, OnRADIOCHINESE10x10)
	ON_BN_CLICKED(IDC_RADIO_CHINESE8x8, OnRADIOCHINESE8x8)
	ON_BN_CLICKED(IDC_RADIO_CROWDED, OnRadioCrowded)
	ON_BN_CLICKED(IDC_RADIO_INTERNATIONAL, OnRadioInternational)
	ON_BN_CLICKED(IDC_RADIO_ITALIAN, OnRadioItalian)
	ON_BN_CLICKED(IDC_RADIO_POLISH, OnRadioPolish)
	ON_BN_CLICKED(IDC_RADIO_RUSSIAN, OnRadioRussian)
	ON_BN_CLICKED(IDC_RADIO_SPARSE, OnRadioSparse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameTypeDlg message handlers

void CGameTypeDlg::OnRadioAmerican() 
{
	// TODO: Add your control notification handler code here
	m_GameType = AMERICAN;
	m_level = 8;
}

void CGameTypeDlg::OnRADIOCHINESE10x10() 
{
	// TODO: Add your control notification handler code here
	m_GameType = CHINESE10x10;
	m_level = 10;
}

void CGameTypeDlg::OnRADIOCHINESE8x8() 
{
	// TODO: Add your control notification handler code here
	m_GameType = CHINESE8x8;
	m_level = 8;
}

void CGameTypeDlg::OnRadioCrowded() 
{
	// TODO: Add your control notification handler code here
	m_GameType = CROWDED;
	m_level = 10;
}

void CGameTypeDlg::OnRadioInternational() 
{
	// TODO: Add your control notification handler code here
	m_GameType = INTERNATIONAL;
	m_level = 10;
}
	
void CGameTypeDlg::OnRadioItalian() 
{
	// TODO: Add your control notification handler code here
	m_GameType = ITALIAN;
	m_level = 8;
}

void CGameTypeDlg::OnRadioPolish() 
{
	// TODO: Add your control notification handler code here
	m_GameType = POLISH;
	m_level = 10;
}

void CGameTypeDlg::OnRadioRussian() 
{
	// TODO: Add your control notification handler code here
	m_GameType = RUSSIAN;
	m_level = 10;
}

void CGameTypeDlg::OnRadioSparse() 
{
	// TODO: Add your control notification handler code here
	m_GameType = SPARSE;
	m_level = 10;
}

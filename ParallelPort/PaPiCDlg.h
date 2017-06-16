///////////////////////////////////
// PaPiCDlg.h : header file
//
// Copyright (C) 2007 Zsolt Pöcze 
//

/*/////////////////////////////////////////////////////////////////////////////////

	This file is a part of Class PaPiC Demo (Parallel Port Pin Control Library).

	Version 1.0

	Written by Zsolt Pöcze
	
	Contact: pocze_zsolt@hotmail.com

	This code may be used in compiled form in any way you desire. This
	file may be redistributed unmodified by any means PROVIDING it is 
	not sold for profit without the authors written consent, and 
	providing that this notice and the authors name is included. If 
	the source code in this file is used in any commercial application 
	then a simple email would be nice.

	This file is provided "as is" with no expressed or implied warranty.
	The author accepts no liability if it causes any damage to your
	computer, causes your pet to fall ill, increases baldness and so forth.
	
	Please use and enjoy. Please let me know of any bugs/mods/improvements 
	that you have found/implemented and I will fix/incorporate them into this
	file. 

	Thanks

		Jeremy Elson and Al Hooton

	the PARAPIN package has been developed by.

//////////////////////////////////////////////////////////////////////////////////*/

#if !defined(AFX_PAPICDLG_H__D52760FC_C9B8_4A6E_B5E6_845CC6ABB1BD__INCLUDED_)
#define AFX_PAPICDLG_H__D52760FC_C9B8_4A6E_B5E6_845CC6ABB1BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPaPiC.h"

/////////////////////////////////////////////////////////////////////////////
// CPaPiCDlg dialog

class CPaPiCDlg : public CDialog, CPaPiC
{
// Construction
public:
	lp_pin SelectedPins();
	void LoadOutputStatus();
	void LoadInputStatus();
	CPaPiCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPaPiCDlg)
	enum { IDD = IDD_PAPIC_DIALOG };
	BOOL	m_status_1;
	BOOL	m_status_2;
	BOOL	m_status_3;
	BOOL	m_status_4;
	BOOL	m_status_5;
	BOOL	m_status_6;
	BOOL	m_status_7;
	BOOL	m_status_8;
	BOOL	m_status_9;
	BOOL	m_status_14;
	BOOL	m_status_16;
	BOOL	m_status_17;
	BOOL	m_status_10;
	BOOL	m_status_11;
	BOOL	m_status_12;
	BOOL	m_status_13;
	BOOL	m_status_15;
	BOOL	m_select_1;
	BOOL	m_select_2;
	BOOL	m_select_3;
	BOOL	m_select_4;
	BOOL	m_select_5;
	BOOL	m_select_6;
	BOOL	m_select_7;
	BOOL	m_select_8;
	BOOL	m_select_9;
	BOOL	m_select_14;
	BOOL	m_select_16;
	BOOL	m_select_17;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaPiCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPaPiCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton_pin_is_set();
	afx_msg void OnButton_set_pin();
	afx_msg void OnButton_clear_pin();
	afx_msg void OnButton_invert_pin();
	afx_msg void OnButton_pin_pattern();
	afx_msg void OnButton_select_all();
	afx_msg void OnButton_clear_all();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPICDLG_H__D52760FC_C9B8_4A6E_B5E6_845CC6ABB1BD__INCLUDED_)

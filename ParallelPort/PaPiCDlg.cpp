///////////////////////////////////////
// PaPiCDlg.cpp : implementation file
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

#include "stdafx.h"
#include "PaPiC.h"
#include "PaPiCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaPiCDlg dialog

CPaPiCDlg::CPaPiCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaPiCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaPiCDlg)
	m_status_1 = FALSE;
	m_status_2 = FALSE;
	m_status_3 = FALSE;
	m_status_4 = FALSE;
	m_status_5 = FALSE;
	m_status_6 = FALSE;
	m_status_7 = FALSE;
	m_status_8 = FALSE;
	m_status_9 = FALSE;
	m_status_14 = FALSE;
	m_status_16 = FALSE;
	m_status_17 = FALSE;
	m_status_10 = FALSE;
	m_status_11 = FALSE;
	m_status_12 = FALSE;
	m_status_13 = FALSE;
	m_status_15 = FALSE;
	m_select_1 = FALSE;
	m_select_2 = FALSE;
	m_select_3 = FALSE;
	m_select_4 = FALSE;
	m_select_5 = FALSE;
	m_select_6 = FALSE;
	m_select_7 = FALSE;
	m_select_8 = FALSE;
	m_select_9 = FALSE;
	m_select_14 = FALSE;
	m_select_16 = FALSE;
	m_select_17 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaPiCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaPiCDlg)
	DDX_Check(pDX, IDC_CHECK1, m_status_1);
	DDX_Check(pDX, IDC_CHECK2, m_status_2);
	DDX_Check(pDX, IDC_CHECK3, m_status_3);
	DDX_Check(pDX, IDC_CHECK4, m_status_4);
	DDX_Check(pDX, IDC_CHECK5, m_status_5);
	DDX_Check(pDX, IDC_CHECK6, m_status_6);
	DDX_Check(pDX, IDC_CHECK7, m_status_7);
	DDX_Check(pDX, IDC_CHECK8, m_status_8);
	DDX_Check(pDX, IDC_CHECK9, m_status_9);
	DDX_Check(pDX, IDC_CHECK10, m_status_14);
	DDX_Check(pDX, IDC_CHECK11, m_status_16);
	DDX_Check(pDX, IDC_CHECK12, m_status_17);
	DDX_Check(pDX, IDC_CHECK13, m_status_10);
	DDX_Check(pDX, IDC_CHECK14, m_status_11);
	DDX_Check(pDX, IDC_CHECK15, m_status_12);
	DDX_Check(pDX, IDC_CHECK16, m_status_13);
	DDX_Check(pDX, IDC_CHECK17, m_status_15);
	DDX_Check(pDX, IDC_CHECK18, m_select_1);
	DDX_Check(pDX, IDC_CHECK19, m_select_2);
	DDX_Check(pDX, IDC_CHECK20, m_select_3);
	DDX_Check(pDX, IDC_CHECK21, m_select_4);
	DDX_Check(pDX, IDC_CHECK22, m_select_5);
	DDX_Check(pDX, IDC_CHECK23, m_select_6);
	DDX_Check(pDX, IDC_CHECK24, m_select_7);
	DDX_Check(pDX, IDC_CHECK25, m_select_8);
	DDX_Check(pDX, IDC_CHECK26, m_select_9);
	DDX_Check(pDX, IDC_CHECK27, m_select_14);
	DDX_Check(pDX, IDC_CHECK28, m_select_16);
	DDX_Check(pDX, IDC_CHECK29, m_select_17);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPaPiCDlg, CDialog)
	//{{AFX_MSG_MAP(CPaPiCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton_pin_is_set)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton_set_pin)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton_clear_pin)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton_invert_pin)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton_pin_pattern)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton_select_all)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton_clear_all)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaPiCDlg message handlers

BOOL CPaPiCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	clear_pin(LP_OUTPUT_PINS);
	LoadInputStatus();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaPiCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaPiCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaPiCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPaPiCDlg::OnButton_pin_is_set() 
{
	// TODO: Add your control notification handler code here
	
	LoadInputStatus();
}

void CPaPiCDlg::OnButton_set_pin() 
{
	// TODO: Add your control notification handler code here

	set_pin(SelectedPins());
	LoadOutputStatus();
	
}

void CPaPiCDlg::OnButton_clear_pin() 
{
	// TODO: Add your control notification handler code here
	clear_pin(SelectedPins());
	LoadOutputStatus();
	
}

void CPaPiCDlg::OnButton_invert_pin() 
{
	// TODO: Add your control notification handler code here
	invert_pin(SelectedPins());
	LoadOutputStatus();
	
}

void CPaPiCDlg::OnButton_pin_pattern() 
{
	// TODO: Add your control notification handler code here
	pin_pattern(SelectedPins());
	LoadOutputStatus();
	
}

void CPaPiCDlg::OnButton_select_all() 
{
	// TODO: Add your control notification handler code here

	m_select_1 = TRUE;
	m_select_2 = TRUE;
	m_select_3 = TRUE;
	m_select_4 = TRUE;
	m_select_5 = TRUE;
	m_select_6 = TRUE;
	m_select_7 = TRUE;
	m_select_8 = TRUE;
	m_select_9 = TRUE;
	m_select_14 = TRUE;
	m_select_16 = TRUE;
	m_select_17 = TRUE;

	UpdateData(FALSE);
	
}

void CPaPiCDlg::OnButton_clear_all() 
{
	// TODO: Add your control notification handler code here

	m_select_1 = FALSE;
	m_select_2 = FALSE;
	m_select_3 = FALSE;
	m_select_4 = FALSE;
	m_select_5 = FALSE;
	m_select_6 = FALSE;
	m_select_7 = FALSE;
	m_select_8 = FALSE;
	m_select_9 = FALSE;
	m_select_14 = FALSE;
	m_select_16 = FALSE;
	m_select_17 = FALSE;

	UpdateData(FALSE);
	
}

void CPaPiCDlg::LoadInputStatus()
{
	UpdateData(TRUE);

	lp_pin input_pins = pin_is_set(LP_INPUT_PINS);

	m_status_10 = (input_pins & LP_PIN[10]) == 0;
	m_status_11 = (input_pins & LP_PIN[11]) == 0;
	m_status_12 = (input_pins & LP_PIN[12]) == 0;
	m_status_13 = (input_pins & LP_PIN[13]) == 0;
	m_status_15 = (input_pins & LP_PIN[15]) == 0;

	UpdateData(FALSE);
}

void CPaPiCDlg::LoadOutputStatus()
{
	lp_pin output_pins = pin_is_set(LP_OUTPUT_PINS);

	m_status_1 = (output_pins & LP_PIN[1]) == 0;
	m_status_2= (output_pins & LP_PIN[2]) == 0;
	m_status_3= (output_pins & LP_PIN[3]) == 0;
	m_status_4= (output_pins & LP_PIN[4]) == 0;
	m_status_5= (output_pins & LP_PIN[5]) == 0;
	m_status_6= (output_pins & LP_PIN[6]) == 0;
	m_status_7= (output_pins & LP_PIN[7]) == 0;
	m_status_8= (output_pins & LP_PIN[8]) == 0;
	m_status_9= (output_pins & LP_PIN[9]) == 0;
	m_status_14 = (output_pins & LP_PIN[14]) == 0;
	m_status_16 = (output_pins & LP_PIN[16]) == 0;
	m_status_17 = (output_pins & LP_PIN[17]) == 0;

	UpdateData(FALSE);
}



lp_pin CPaPiCDlg::SelectedPins()
{
	lp_pin selected = 0;

	UpdateData(TRUE);

	if(m_select_1) selected |= LP_PIN[1];
	if(m_select_2) selected |= LP_PIN[2];
	if(m_select_3) selected |= LP_PIN[3];
	if(m_select_4) selected |= LP_PIN[4];
	if(m_select_5) selected |= LP_PIN[5];
	if(m_select_6) selected |= LP_PIN[6];
	if(m_select_7) selected |= LP_PIN[7];
	if(m_select_8) selected |= LP_PIN[8];
	if(m_select_9) selected |= LP_PIN[9];
	if(m_select_14) selected |= LP_PIN[14];
	if(m_select_16) selected |= LP_PIN[16];
	if(m_select_17) selected |= LP_PIN[17];

	return selected; 
}

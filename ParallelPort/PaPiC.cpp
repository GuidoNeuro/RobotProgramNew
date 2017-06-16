///////////////////////////////////////////////////////////////
//
// PaPiC.cpp : Defines the class behaviors for the application.
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
// CPaPiCApp

BEGIN_MESSAGE_MAP(CPaPiCApp, CWinApp)
	//{{AFX_MSG_MAP(CPaPiCApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaPiCApp construction

CPaPiCApp::CPaPiCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPaPiCApp object

CPaPiCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPaPiCApp initialization

BOOL CPaPiCApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CPaPiCDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

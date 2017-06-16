////////////////////////////////////////////////////////
//
// PaPiC.h : main header file for the PAPIC application
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

	Thanks for

		Jeremy Elson and Al Hooton

	the PARAPIN package has been developed by.

//////////////////////////////////////////////////////////////////////////////////*/

#if !defined(AFX_PAPIC_H__4459B4AB_86AA_4BA6_9341_26F5C6FA77B9__INCLUDED_)
#define AFX_PAPIC_H__4459B4AB_86AA_4BA6_9341_26F5C6FA77B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPaPiCApp:
// See PaPiC.cpp for the implementation of this class
//

class CPaPiCApp : public CWinApp
{
public:
	CPaPiCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaPiCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPaPiCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPIC_H__4459B4AB_86AA_4BA6_9341_26F5C6FA77B9__INCLUDED_)

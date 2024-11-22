//*****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzMagnifier.h
// Module		: 
// Description	: Class definition of the gzMagnifier class
// Author		: Anders Mod�n		
// Product		: Gizmo3D 2.12.200
//		
//
//			
// NOTE:	Gizmo3D is a high performance 3D Scene Graph and effect visualisation 
//			C++ toolkit for Linux, Mac OS X, Windows, Android, iOS and HoloLens for  
//			usage in Game or VisSim development.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	991209	Created file 	
//
//******************************************************************************
#ifndef __GZ_MAGNIFIER_H__
#define __GZ_MAGNIFIER_H__

/*!	\file 
	\brief Base definitions for magnification nodes

*/

#include "gzPortal.h"

class gzMagnifier : public gzPortal
{
public:
	GZ_GRAPH_EXPORT gzMagnifier(const gzString & name=GZ_EMPTY_STRING);

	GZ_GRAPH_EXPORT virtual ~gzMagnifier(){};

	GZ_DECLARE_TYPE_INTERFACE_EXPORT(GZ_GRAPH_EXPORT);	// typed interface


	// ---------- Clone interface ---------------------------------------
	GZ_GRAPH_EXPORT virtual gzReference* clone() const override;

	// ---------- gzMagnifier API -----------------------------------------

	GZ_GRAPH_EXPORT gzVoid setMagnification(gzFloat magnification);

protected:

	GZ_GRAPH_EXPORT virtual gzVoid calculateTransform(gzContext *context) override;	// Override to calculate other than magnification

	gzFloat m_magnification;
};


#endif
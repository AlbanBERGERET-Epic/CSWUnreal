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
// File			: gzIO.h
// Module		: gzBase
// Description	: Class definitions and macros for debugging aid
// Author		: Anders Mod�n		
// Product		: GizmoBase 2.12.200
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
// AMO	060302	Created file 	
// AMO	101202	Added a fast implementation of gzFileExist		(2.5.16)
//
//******************************************************************************

#ifndef __GZ_IO_H__
#define __GZ_IO_H__

/*!	\file 
	\brief Basic utilites for low level file management

	Blah
*/
#include "gzBase.h"

#define GZ_F_FILEMODE

// ------------- TypeDefines --------------

#if defined GZ_WINDOWS && !defined GZ_F_FILEMODE
	// Raw native mode
	typedef int	gzFileHandle;
	#define GZ_FILE_INVALID_HANDLE	-1
#else
	// fxxx buffered mode
	typedef FILE *	gzFileHandle;
	#define GZ_FILE_INVALID_HANDLE	NULL
#endif

enum gzOriginPos
{
	GZ_ORIGIN_SET,
	GZ_ORIGIN_CUR,
	GZ_ORIGIN_END,
	GZ_ORIGIN_SIZE,
};

GZ_BASE_EXPORT gzFileHandle gzFileOpenRead(const gzString &name,gzMemSize *filesize);
GZ_BASE_EXPORT gzFileHandle gzFileOpenWrite(const gzString &name,gzBool append=FALSE);

GZ_BASE_EXPORT gzMemSize	gzFileRead(gzFileHandle handle,gzUByte *buffer,gzMemSize maxbytes);
GZ_BASE_EXPORT gzVoid		gzFileWrite(gzFileHandle handle,gzUByte *buffer,gzMemSize bytes);
GZ_BASE_EXPORT gzVoid		gzFileFlush(gzFileHandle handle);
GZ_BASE_EXPORT gzVoid		gzFileClose(gzFileHandle handle);
GZ_BASE_EXPORT gzMemSize	gzFileSize(gzFileHandle handle);
GZ_BASE_EXPORT gzMemSize	gzFileSize(const gzString &name);
GZ_BASE_EXPORT gzMemSize	gzFileTell(gzFileHandle handle);
GZ_BASE_EXPORT gzBool		gzFileReset(gzFileHandle handle,gzMemOffset position);
GZ_BASE_EXPORT gzBool		gzFileSeek(gzFileHandle handle,gzMemOffset offset, gzOriginPos origin);
GZ_BASE_EXPORT gzBool		gzFileExist(const gzString &name);
GZ_BASE_EXPORT gzBool		gzFileDelete(const gzString &name);

GZ_BASE_EXPORT gzBool		gzIsDirURL(const gzString &url);
GZ_BASE_EXPORT gzBool		gzDirExist(const gzString &directory);
GZ_BASE_EXPORT gzBool		gzMakeDir(const gzString &directory);


#endif	//__GZ_IO_H__ 
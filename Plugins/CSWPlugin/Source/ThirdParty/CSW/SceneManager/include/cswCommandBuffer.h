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
// File			: cswCommandBuffer.h
// Module		: cswSceneManager
// Description	: Management of communication buffers
// Author		: Anders Mod�n		
// Product		: CSW 1.1.1
//		
//
//			
// NOTE:	CSW (Common Synthetic World) is a simulation and presentation
//			framework for large scale digital twins on multiple platforms
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	240912	Created file 					(1.1.1)
//
//******************************************************************************
#pragma once

#include "cswSceneManagerBase.h"
#include "cswSceneCommands.h"

enum cswCommandBufferType
{
	CSW_BUFFER_TYPE_GENERIC,
	CSW_BUFFER_TYPE_ERROR,
	CSW_BUFFER_TYPE_FRAME,
	CSW_BUFFER_TYPE_NEW,
	CSW_BUFFER_TYPE_DELETE,
};

enum cswCommandBufferDeleteMode
{
	CSW_BUFFER_DELETE_MODE_UNLOCKED,
	CSW_BUFFER_DELETE_MODE_EDIT_LOCK,
	CSW_BUFFER_DELETE_MODE_RENDER_LOCK,
};

//******************************************************************************
// Class	: cswCommandBuffer
//
// Purpose  : Contains the command used in communcation with Scenemanager. Buffer
//			  can be locked and allow acces to scene commands and items
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	240912	Created		(1.1.1)
//									
//******************************************************************************
class cswCommandBuffer : public gzReference
{
public:

	CSW_SM_EXPORT cswCommandBuffer(const cswCommandBufferType &type = CSW_BUFFER_TYPE_GENERIC);
	CSW_SM_EXPORT ~cswCommandBuffer();

	//! Command management
	CSW_SM_EXPORT gzVoid addCommand(cswSceneCommand* command);

	//! Locking
	CSW_SM_EXPORT gzBool tryLockRender(gzUInt32 waitValue = 10);
	CSW_SM_EXPORT gzBool tryLockEdit(gzUInt32 waitValue = 10);

	CSW_SM_EXPORT gzVoid unLock();

	//! Access to data when locked depending on content
	CSW_SM_EXPORT cswSceneCommandPtr getCommand();
	CSW_SM_EXPORT gzBool hasCommands();
	CSW_SM_EXPORT gzUInt32 entries();
	CSW_SM_EXPORT gzVoid clear();

	GZ_PROPERTY_GET_EXPORT(cswCommandBufferType, BufferType, CSW_SM_EXPORT);
	GZ_PROPERTY_EXPORT(cswCommandBufferDeleteMode, BufferDeleteMode, CSW_SM_EXPORT);

private:

	gzRefList<cswSceneCommand>			m_commandBuffer;
};

GZ_DECLARE_REFPTR(cswCommandBuffer);

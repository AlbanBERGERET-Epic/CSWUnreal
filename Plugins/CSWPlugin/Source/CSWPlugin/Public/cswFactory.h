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
// File			: cswFactoryInterface.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface to Factory builders
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
// AMO	241107	Created file 							(1.1.1)
//
//******************************************************************************
#pragma once

#include "gzNode.h"
class USceneComponent;

class cswFactory : public gzObject
{
public:

	// Type info
	GZ_DECLARE_TYPE_INTERFACE_EXPORT(CSWPLUGIN_API);			// Each factory has a specific type and hierarchy

	CSWPLUGIN_API static USceneComponent* newObject(gzNode* node , USceneComponent *parent);

	CSWPLUGIN_API static gzBool registerFactoryLookup(const gzUInt32& in, const gzUInt32& out);

	CSWPLUGIN_API static gzBool unregisterFactoryLookup(const gzUInt32& in);

	CSWPLUGIN_API static gzUInt32 getFactoryLookup(const gzUInt32& in);
	
protected:

	CSWPLUGIN_API virtual USceneComponent* newObjectInstance(gzNode *node,USceneComponent* parent) = 0;

private:

	// factory uses clone to create instance and must bve derived 
	virtual gzReference* clone() const = 0;

	static gzMutex s_factoryLock;

	static gzDict< gzUInt32CompareInterface, gzVoid>	s_factoryLookup;
};

GZ_DECLARE_REFPTR(cswFactory);
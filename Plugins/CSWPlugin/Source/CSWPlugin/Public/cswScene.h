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
// File			: cswScene.h
// Module		: CSW StreamingMap Unreal
// Description	: Interface for StreamingMapComponent
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


#include "cswSceneComponent.h"
#include "cswGeoComponent.h"

#include "cswSceneManager.h"
#include "cswCommandReceiver.h"
#include "cswResourceManager.h"

#include "UEGlue/cswUETemplates.h"
#include "UEGlue//cswUETypes.h"


#include "CSWScene.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSWPLUGIN_API UCSWScene : public UCSWSceneComponent,
								public cswCommandReceiverInterface,
								public cswUEPropertyChain<UCSWScene>
{
	GENERATED_BODY()
public:

	UCSWScene(const FObjectInitializer& ObjectInitializer);
	~UCSWScene();

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditUndo() override;
	virtual void PostEditImport() override;
#endif

	// Properties ------------------------------------------------------------------
	// 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSW")
	FString MapUrls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	FString CoordSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	TEnumAsByte<CoordType> CoordType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double RenderTime;

	UPROPERTY(EditAnywhere, Category = "CSW")
	uint32 MaxPrimitivesPerFrame=10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	UCSWGeoComponent* GeoOrigin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double ModelOriginX=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double ModelOriginY = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CSW")
	double ModelOriginZ = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CSW")
	bool CenterOrigin = true;

protected:

	// Init scenemanager and set up context
	void initSceneManager();
	void initResourceManager();

	bool isEditorComponent();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Transfer buffers from in to out
	bool fetchBuffers(bool waitForFrame=false, gzUInt32 timeOut = 200);

	// Perform work on buffers Out
	gzUInt32 processPendingBuffers(gzUInt32 maxFrames=10,gzUInt32 maxBuilds=10000);



	// Perform work on specific buffer
	bool processGenericBuffer(cswCommandBuffer *buffer);

	// Perform work on specific buffer
	bool processErrorBuffer(cswCommandBuffer* buffer);

	// Perform work on specific buffer
	bool processFrameBuffer(cswCommandBuffer* buffer, gzUInt32 & maxFrames);

	// Perform work on specific buffer
	bool processNewBuffer(cswCommandBuffer* buffer, gzUInt32& maxBuilds);

	// Perform work on specific buffer
	bool processDeleteBuffer(cswCommandBuffer* buffer);


	// Perform work on specific commands
	bool processGeoInfo(cswSceneCommandGeoInfo* command);
	bool processNewNode(cswSceneCommandNewNode* command);
	bool processDeleteNode(cswSceneCommandDeleteNode* command);

	bool processActivation(cswSceneCommandActivation* command);


	// Property Update callbacks
	bool onMapUrlsPropertyUpdate();
	bool onCoordTypePropertyUpdate();
	bool onCenterOriginPropertyUpdate();

	// Utilities
	double getWorldScale();
	void updateOriginTransform();

	virtual gzVoid onCommand(cswCommandBuffer* buffer) override;

	FVector3d localToGlobal(const gzVec3D& local, enum CoordType type);
	gzVec3D globalToLocal(const FVector3d& global,enum CoordType type);


	// Register component
	bool registerComponent(UCSWSceneComponent* component, gzNode* node, gzUInt64 pathID);

	// Unregister component
	bool unregisterComponent(gzNode* node, gzUInt64 pathID);

	UCSWSceneComponent* getComponent(gzNode* node, gzUInt64 pathID);

	// the scene manager of components
	cswSceneManagerPtr		m_manager;

	// the shared resources
	cswResourceManagerPtr	m_resource;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInterface> m_baseMaterial;

private:

	gzEvent									m_bufferInLock;		// Lock for callback accessing bufferIn
	gzRefList<cswCommandBuffer>				m_bufferIn;			// Buffer In
	gzRefList<cswCommandBuffer>				m_pendingBuffers;		// Buffer Out

	gzDict<CSWPathIdentyIndex, gzVoid>		m_indexLUT;
	gzQueue<gzUInt32>						m_slots;
	gzDynamicArray<UCSWSceneComponent*>		m_components;

	BuildProperties							m_buildProperties;

	bool									m_firstRun=true;
};



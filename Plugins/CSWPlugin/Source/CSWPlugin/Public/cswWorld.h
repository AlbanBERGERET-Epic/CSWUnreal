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
// File			: cswWorld.h
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

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "cswScene.h"
#include "cswCamera.h"

#include "cswWorld.generated.h"

UCLASS()
class CSWPLUGIN_API ACSWWorld : public AActor
{
	GENERATED_BODY()
	
public:	

	ACSWWorld();

	virtual ~ACSWWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;
	virtual void PostEditUndo() override;
	virtual void PostEditImport() override;
#endif

	UPROPERTY(EditAnywhere, Category = "CSW")
	FString MapUrls;

	UPROPERTY(EditAnywhere, Category = "CSW")
	UCSWScene* Scene;

	UPROPERTY(EditAnywhere,Category = "CSW")
	UCSWCamera* DefaultCamera;



};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "cswGeometry.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CSWPLUGIN_API UCSWGeometry : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSWGeometry();

	void build();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Transient, VisibleAnywhere, Category = "CSW");
	UStaticMeshComponent* m_meshComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

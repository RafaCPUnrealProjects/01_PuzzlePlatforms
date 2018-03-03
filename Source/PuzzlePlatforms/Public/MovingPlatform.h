// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

	AMovingPlatform();

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "MovingPlatform")
	FVector Speed;
	
};
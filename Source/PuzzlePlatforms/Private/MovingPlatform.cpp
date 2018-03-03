// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"




AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += Speed * DeltaSeconds;

		SetActorLocation(Location);
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

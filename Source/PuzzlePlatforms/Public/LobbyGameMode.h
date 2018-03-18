// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformsGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ALobbyGameMode : public APuzzlePlatformsGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void StartGame();

	virtual void Logout(AController* Exiting) override;

private:

	uint32 MaxNumberOfPlayers = 2;
	uint32 NumberOfPlayers = 0;
	FTimerHandle TimerHandle_GameStart;
};

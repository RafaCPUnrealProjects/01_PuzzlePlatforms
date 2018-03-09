// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
//#include "SharedPointer.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UMainMenu;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget(); 
	
	UFUNCTION(BlueprintCallable)
	void InGameMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	virtual void LoadMainMenu() override;

private:

	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	UMainMenu* Menu;

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);

	void OnDestroySessionComplete(FName SessionName, bool bSuccess);

	void OnFindSessionsComplete(bool bSuccess);

	void CreateSession();

	IOnlineSessionPtr SessionInterface;
	IOnlineSubsystem* OSS;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};

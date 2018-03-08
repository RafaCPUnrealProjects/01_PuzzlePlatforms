// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"


class UButton;
class UWidgetSwitcher;
class UWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	
protected:

	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);

private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void BackToMainMenu();

	UFUNCTION()
	void JoinGame();

	IMenuInterface* MenuInterface;
};

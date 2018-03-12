// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"


class UButton;
class UWidgetSwitcher;
class UWidget;
class UEditableTextBox;
class UPanelWidget;
class UUserWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
	
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FString> ServeNames);

protected:

	virtual bool Initialize() override;

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
	UButton* QuitGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void BackToMainMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void QuitGameAndClose();

	TSubclassOf<UUserWidget> ServerRowClass;
};

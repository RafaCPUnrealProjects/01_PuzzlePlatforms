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
 * Comment
 */
USTRUCT()
struct FServerData
{
	GENERATED_USTRUCT_BODY()
	
	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
	
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServeNames);

	void SelectIndex(uint32 Index);

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* OpenHostMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OpenJoinMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackFromJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackFromHostMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* HostGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu; 
	
	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ServerHostName;
	
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitPressed();

	void UpdateChildren();

	TSubclassOf<UUserWidget> ServerRowClass;

	TOptional<uint32> SelectedIndex;
};

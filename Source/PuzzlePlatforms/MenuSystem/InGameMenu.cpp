// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"



bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitGame);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelAndCloseWidget);

	return true;
}

void UInGameMenu::QuitGame()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->LoadMainMenu();
}

void UInGameMenu::CancelAndCloseWidget()
{
	OnLevelRemovedFromWorld(nullptr, GetWorld());
}

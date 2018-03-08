// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "Components/EditableTextBox.h"
#include "GameFramework/PlayerController.h"




void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	APlayerController* PC = World->GetFirstPlayerController();
	if (!ensure(PC != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputModeData);
	
	PC->bShowMouseCursor = true;
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this,&UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	
	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);

	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	BackToMainMenu();

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	this->RemoveFromViewport();

	if (!ensure(InWorld != nullptr)) return;

	APlayerController* PC = InWorld->GetFirstPlayerController();
	if (!ensure(PC != nullptr)) return;

	FInputModeGameOnly InputModeData;
	InputModeData.SetConsumeCaptureMouseDown(true);

	PC->SetInputMode(InputModeData);

	PC->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface != nullptr)) return;
	
	MenuInterface->Host();
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::BackToMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinGame()
{
	if (!ensure(MenuInterface != nullptr)) return;
	if (!ensure(IPAddressField != nullptr)) return;
	const FString& Address = IPAddressField->GetText().ToString();
	MenuInterface->Join(Address);
}

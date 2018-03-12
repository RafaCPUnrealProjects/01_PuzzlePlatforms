// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "OnlineSessionSettings.h"


const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	OSS = IOnlineSubsystem::Get();
	if (!ensureAlways(OSS != nullptr)) return;

	SessionInterface = OSS->GetSessionInterface();
	if(SessionInterface.IsValid())
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
		SessionInterface->OnPingSearchResultsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);
	}
}

void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	
	Menu->SetMenuInterface(this);
	Menu->Setup();
}

void UPuzzlePlatformsGameInstance::InGameMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;

	InGameMenu->SetMenuInterface(this);
	InGameMenu->Setup();
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
//	RefreshServerList();
// 	UEngine* Engine = GetEngine();
// 	if (!ensure(Engine != nullptr)) return;
// 	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
// 
// 	APlayerController* PC = GetFirstLocalPlayerController();
// 	if (!ensure(PC != nullptr)) return;
// 
// 	PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!ensure(PC != nullptr)) return;

	PC->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch);
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting find session"));
		if (SessionInterface.IsValid())
		{
			SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		}
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	if(bSuccess)
	{
		UEngine* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;

		Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session creation failed!"));
	}
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete"));
	if (bSuccess && SessionSearch.IsValid() && Menu != nullptr)
	{

		TArray<FString> ServerNames;
		for (const FOnlineSessionSearchResult& SessionResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session name: %s"), *SessionResult.GetSessionIdStr());
			ServerNames.Add(SessionResult.GetSessionIdStr());
		}

		Menu->SetServerList(ServerNames);
	}
}

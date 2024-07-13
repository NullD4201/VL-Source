// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "VClass/Data/VClassSaveGame.h"
#include "VClass/UI/MainMenuWidget.h"
#include "VClass/UI/Panels/CEditorHome.h"


AMainMenuPlayerController::AMainMenuPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UHomeUI> HOMEUICLASS(TEXT("/Game/Blueprints/UI/UI_HomeScreen.UI_HomeScreen_C"));
	if (HOMEUICLASS.Succeeded())
	{
		mHomeUIClass = HOMEUICLASS.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> EDITORWIDGETCLASS(TEXT("/Game/Blueprints/UI/EditorModeUI.EditorModeUI_C"));
	if(EDITORWIDGETCLASS.Succeeded())
	{
		mEditorModeWidgetClass = EDITORWIDGETCLASS.Class;
	}

	bShowMouseCursor = true;

	SetReplicates(true);
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (mPlayerType == EPlayerType::Host)
	{
		FInputModeGameAndUI InputModeGameAndUI;
		SetInputMode(InputModeGameAndUI);
	}
	else if (mPlayerType == EPlayerType::Client)
	{
		FInputModeGameOnly InputModeGameOnly;
		SetInputMode(InputModeGameOnly);
	}
	else
	{
		FInputModeUIOnly InputModeUIOnly;
		SetInputMode(InputModeUIOnly);
	}

	mHomeUI = CreateWidget<UHomeUI>(this, mHomeUIClass);
	mEditorModeWidget = CreateWidget<UEditorModeWidget>(this, mEditorModeWidgetClass);
		
	mHomeUI->AddToViewport();
}

void AMainMenuPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainMenuPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMainMenuPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMainMenuPlayerController::SetPlayer(const FString& Address, const FString& Port, const bool IsHost, const FString& Key)
{
	UVClassSaveGame* SaveGame = Cast<UVClassSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Main"),0));
	FString Options = "";
	Options.Append("IsHost=");
	Options.Append(IsHost ? "true" : "false");
	Options.Append("?Key=");
	Options.Append(Key);
	Options.Append(FString::Format(TEXT("?ImageAppearMode={0}"),{static_cast<int32>(SaveGame->ImageMode)}));

	if (IsHost)
		mPlayerType = EPlayerType::Host;
	else
		mPlayerType = EPlayerType::Client;

	UGameplayStatics::OpenLevel(GetWorld(), FName(Address + ":" + Port), true, Options);
}

void AMainMenuPlayerController::OpenEditorModeUI()
{
	mHomeUI->RemoveFromViewport();
	mEditorModeWidget->AddToViewport();
}

void AMainMenuPlayerController::OpenHomeScreenUI()
{
	mEditorModeWidget->RemoveFromViewport();
	mHomeUI->AddToViewport();
}



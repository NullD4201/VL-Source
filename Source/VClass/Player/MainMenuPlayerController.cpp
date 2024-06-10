// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "VClass/UI/MainMenuWidget.h"


AMainMenuPlayerController::AMainMenuPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> _Widget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/UI_MainMenu.UI_MainMenu_C'"));
	if (_Widget.Succeeded())
	{
		mMainMenuWidgetClass = _Widget.Class;
	}

	bShowMouseCursor = true;

	SetReplicates(true);
}

void AMainMenuPlayerController::BeginPlay()
{
	if (!HasAuthority())
	{
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

		mMainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), mMainMenuWidgetClass);
		mMainMenuWidget->AddToViewport();
	}
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

void AMainMenuPlayerController::SetPlayer(const FString& Address, const FString& Port, const bool IsHost, const FString& SeatLine, const FString& SeatNum)
{
	FString Options = "";
	Options.Append("IsHost=");
	Options.Append(IsHost ? "true" : "false");
	Options.Append("?SeatNum=");
	Options.Append(SeatNum);

	if (IsHost)
		mPlayerType = EPlayerType::Host;
	else
		mPlayerType = EPlayerType::Client;

	UGameplayStatics::OpenLevel(GetWorld(), FName(Address + ":" + Port), true, Options);
}

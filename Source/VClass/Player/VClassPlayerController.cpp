// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassPlayerController.h"

#include "VClass/UI/MainMenuWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "VClass/Data/Input/InputDataConfig.h"
#include "VClassGameMode.h"
#include <PlayerVoiceChatActor.h>

AVClassPlayerController::AVClassPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

void AVClassPlayerController::BeginPlay()
{
	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);

	ServerSendHostRequest(HostRequest::TEST_REQ);
	
	if (!HasAuthority()) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
		Subsystem->AddMappingContext(InputDataConfig->DefaultContext, 0);
	}
	
}

void AVClassPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
	EnhancedInputComponent->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &AVClassPlayerController::OnMove);
	EnhancedInputComponent->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &AVClassPlayerController::OnLook);
	EnhancedInputComponent->BindAction(InputDataConfig->Interact, ETriggerEvent::Triggered, this, &AVClassPlayerController::OnInteract);
}

void AVClassPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AVClassPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControllerPawn = GetPawn();

	if (!bIsHost) return;

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControllerPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	ControllerPawn->AddMovementInput(RightVector, ActionValue.X);

	mMoveDir = ActionValue.X * 90;

	if (ActionValue.Y > 0)
	{
		if (ActionValue.X < 0)
			mMoveDir = -45;
		else if (ActionValue.X > 0)
			mMoveDir = 45;
	}
	else if (ActionValue.Y < 0)
	{
		if (ActionValue.X < 0)
			mMoveDir = -135;
		else if (ActionValue.X > 0)
			mMoveDir = 135;
		else
			mMoveDir = 180;
	}
}

void AVClassPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	FVector2D value = InputActionValue.Get<FVector2D>();

	AddPitchInput(value.Y);
	AddYawInput(value.X);
}

void AVClassPlayerController::OnInteract(const FInputActionValue& InputActionValue)
{
	InteractionDelegate.Execute(InputActionValue);
}

void AVClassPlayerController::ServerSendHostRequest_Implementation(HostRequest request) {
	int32 id = PlayerState->GetPlayerId();

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController->IsA<AVClassPlayerController>())
		{
			AVClassPlayerController* controller = Cast<AVClassPlayerController>(PlayerController);
			if (controller->bIsHost) {
				controller->ClientGetHostRequest(request, id);
			}
		}
	}
}

void AVClassPlayerController::ServerSendClientRequest_Implementation(ClientRequest request, int32 Id) {
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator) {
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController->IsA<AVClassPlayerController>() && PlayerController->PlayerState->GetPlayerId() == Id) {
			AVClassPlayerController* controller = Cast<AVClassPlayerController>(PlayerController);
			controller->ClientGetClientRequest(request);
		}
	}
}

void AVClassPlayerController::ClientGetHostRequest_Implementation(HostRequest request, int32 Id) {
	switch (request)
	{
	case HostRequest::TEST_REQ:
		ServerSendClientRequest(ClientRequest::TEST_REPL, Id);
		break;
	case HostRequest::QUESTION:
		break;
	default:
		break;
	}
}

void AVClassPlayerController::ClientGetClientRequest_Implementation(ClientRequest request) {
	switch (request)
	{
	case ClientRequest::TEST_REPL:
		UE_LOG(LogTemp, Warning, TEXT("Test Request Complete!"));
		break;
	case ClientRequest::QUESTION_VAILD:
		UUniversalVoiceChat::VoiceChatStartSpeak(false, true, 0, false);
		break;
	case ClientRequest::QUESTION_INVAILD:
		UUniversalVoiceChat::VoiceChatStopSpeak();
		break;
	default:
		break;
	}
}

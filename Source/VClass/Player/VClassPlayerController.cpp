// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassPlayerController.h"

#include "VClass/UI/MainMenuWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "VClass/Data/Input/InputDataConfig.h"

AVClassPlayerController::AVClassPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

void AVClassPlayerController::BeginPlay()
{
	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
	Subsystem->AddMappingContext(InputDataConfig->DefaultContext, 0);
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
}

void AVClassPlayerController::OnInteract(const FInputActionValue& InputActionValue)
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerType mPlayerType = EPlayerType::None;

protected:
	TSubclassOf<UUserWidget> mMainMenuWidgetClass;
	class UMainMenuWidget* mMainMenuWidget;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void SetPlayer(const FString& Address, const FString& Port, const bool IsHost, const FString& SeatLine, const FString& SeatNum);
};

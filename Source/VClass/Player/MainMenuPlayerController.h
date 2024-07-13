// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include <VClass/UI/EditorModeWidget.h>

#include "Structures/PlayerInfo.h"
#include "VClass/UI/HomeUI.h"
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
	TSubclassOf<UHomeUI> mHomeUIClass;
	class UHomeUI* mHomeUI;

	TSubclassOf<UUserWidget> mEditorModeWidgetClass;
	class UEditorModeWidget* mEditorModeWidget;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void OpenEditorModeUI();
	void OpenHomeScreenUI();

	UFUNCTION(BlueprintCallable)
	void SetPlayer(const FString& Address, const FString& Port, const bool IsHost, const FString& Key);

};

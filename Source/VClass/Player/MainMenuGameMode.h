// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameMode();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StageServerIPAddress = "127.0.0.1";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StageServerPort = 7777;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImageServerIPAddress = "127.0.0.1";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ImageServerPort = 8000;

	UPROPERTY(EditAnywhere)
	bool IsHost;

	UPROPERTY(EditAnywhere)
	FString Key;
};

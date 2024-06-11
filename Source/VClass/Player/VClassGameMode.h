// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/GameModeBase.h"
#include "VClassGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AVClassGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVClassGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

private:
	bool ReadTextFile(FString FilePath, FString& FileContent);

	TArray<FString> key_list;
};

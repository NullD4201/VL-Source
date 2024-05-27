// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectInfo.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString lastLoginRequestOption;
};

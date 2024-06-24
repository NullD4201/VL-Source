// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/GameModeBase.h"
#include "VClassGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClientLoginDelegate, AVClassPlayerController*, player);

UCLASS()
class VCLASS_API AVClassGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVClassGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController *NewPlayer) override;

	virtual void BeginPlay() override;

	virtual void Logout(AController* Exiting) override;

	FOnClientLoginDelegate OnClientLogin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> HostPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> ClientPawn;

	int CurrentPlayerNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxPlayer;

private:
	bool ReadTextFile(FString FilePath, FString& FileContent);

	TMap<FString, bool> keyMap;

	FString lastLoginRequestOption;
};

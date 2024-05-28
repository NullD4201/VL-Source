// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioCaptureComponent.h"
#include <WebSocketsModule.h>
#include <IWebSocket.h>
#include "STTStateMachine.generated.h"

UENUM(BlueprintType)
enum class ESTTState : uint8{
	SS_LISTEN UMETA(DisplayName="STT Listening"),
	SS_OFF UMETA(DisplayName="STT Off")
};

UCLASS()
class STT_API ASTTStateMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTTStateMachine();

	UPROPERTY(VisibleAnywhere, Category=Scene)
	USceneComponent* defaultSceneComponent;

	UPROPERTY(VisibleAnywhere, Category=Mic)
	UAudioCaptureComponent* audioCaptureComponent;

	TSharedPtr<IWebSocket> webSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString sttHost = "https://openapi.vito.ai/v1/authenticate";
	FString clientId = "xknMcq3FxldEX5y6Mupl";
	FString clientSecret = "k9w4FQQcmc_kGO5pYJDJm9BRMWrSvAUVwtCnJW3F";
	
};

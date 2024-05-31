// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "STTAudioCaptureComponent.h"
#include <WebSocketsModule.h>
#include <IWebSocket.h>
#include <HttpModule.h>
#include "Http.h"
#include "STTManager.generated.h"

UCLASS()
class STTMODULE_API ASTTManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTTManager();

	UPROPERTY(VisibleAnywhere, Category = Mic)
	USTTAudioCaptureComponent* audioCaptureComponent;

	TSharedPtr<IWebSocket> webSocket;
	bool bWebSocketSetted;

	FHttpModule* http;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	void OnAuthorityRequestReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);

	void GetAuthorityToken();
	void SetupWebsocket();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FString httpHost = "https://openapi.vito.ai/v1/authenticate";
	FString clientId = "xknMcq3FxldEX5y6Mupl";
	FString clientSecret = "k9w4FQQcmc_kGO5pYJDJm9BRMWrSvAUVwtCnJW3F";

	FString sttHost = "wss://openapi.vito.ai/v1/transcribe:streaming?sample_rate=48000&encoding=LINEAR16&use_itn=true&use_disfluency_filter=true&use_profanity_filter=false";

	FString authorityToken;
	int tokenExpiration;
	
};

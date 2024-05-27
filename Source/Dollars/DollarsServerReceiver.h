// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <OSCServer.h>
#include <OSCManager.h>
#include "DollarsServerReceiver.generated.h"

UCLASS()
class DOLLARS_API ADollarsServerReceiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADollarsServerReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString ipAddress;
	int port;
	UOSCServer* oscServer;
	TArray<float> oscFloatArray;
	TArray<FString> oscAddressArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnOSCMessageReceived(const FOSCMessage& message,const FString& address, int port);
	
};

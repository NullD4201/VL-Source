// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HostSpawnableObject.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GameFramework/Actor.h"
#include "MediaDisplay.generated.h"

UCLASS()
class VCLASS_API AMediaDisplay : public AHostSpawnableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMediaDisplay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ImageServerAddress = "http://localhost:8000";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HandleImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	UStaticMeshComponent* mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(NetMulticast, Reliable)
	void SetImage(const FString& MediaName);
	
};

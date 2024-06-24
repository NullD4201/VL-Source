// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <HttpModule.h>
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GameFramework/Actor.h"
#include <VClass/Player/VClassPlayerController.h>
#include "ImageDisplayManager.generated.h"

UENUM(BlueprintType)
enum class ImageAppearMode : uint8 {
	IAM_TWOSIDED UMETA(DisplayName = "Two Sided Appearance"),
	IAM_ONESIDED UMETA(DisplayName = "One Sided Appearance"),
	IAM_TRIPLE UMETA(DisplayName = "Triple Appearance"),
	IAM_ONESIDED_LONG UMETA(DisplayName = "One Sided with Long Panel"),
	IAM_FRONT_WIDE UMETA(DisplayName = "Front Appearance with Wide Panel"),
	IAM_BACKWARD_FULL UMETA(DisplayName = "Backward Appearance with Full Panel")
};



UCLASS()
class VCLASS_API AImageDisplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImageDisplayManager();

	UPROPERTY(EditAnywhere)
	FString ImageServerURL = "http://localhost:8000";

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing=OnRep_CurrentMode)
	ImageAppearMode CurrentMode;

	UFUNCTION()
	void OnClientLogin(AVClassPlayerController* player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	TArray<uint8> ReceivedImage;

	UFUNCTION()
	void OnRep_CurrentMode();

public:
	virtual void Tick(float DeltaTime) override;

	static FString ImageAppearModeToString(ImageAppearMode mode);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerDisplayImage(ImageAppearMode Mode, int Index);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void ClientDisplayImage(ImageAppearMode Mode, int Index);
	
	UFUNCTION(BlueprintCallable)
	void SendImageToServer(const TArray<uint8>& ImageData);

	UFUNCTION(BlueprintCallable)
	void GetImageFromServer(FString ImageName);

	void HandleImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
};

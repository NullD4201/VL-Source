// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "HostSpawnableObject.generated.h"

UCLASS()
class VCLASS_API AHostSpawnableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHostSpawnableObject();
	
	void ChangeScale(FVector NewScale);

	UFUNCTION(NetMulticast, Reliable)
	virtual void Despawn();

	UPROPERTY(VisibleAnywhere)
	UTextureRenderTarget2D* RenderTarget;

	UFUNCTION(BlueprintCallable)
	UTexture2D* CaptureSceneToTexture();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneCaptureComponent2D* SceneCaptureComponent;
	
private:
	
	UPROPERTY(ReplicatedUsing=OnRep_Scale)
	FVector ReplicatedScale;

	UFUNCTION()
	void OnRep_Scale();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

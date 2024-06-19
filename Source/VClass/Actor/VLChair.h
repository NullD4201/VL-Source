// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/Actor.h"
#include <VClass/Player/VClassPlayerController.h>
#include "VLChair.generated.h"

UCLASS()
class VCLASS_API AVLChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVLChair();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChairBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChairButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SitTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	bool IsSetted = false;

	UFUNCTION(BlueprintCallable)
	FTransform GetSittingTransform();

	UFUNCTION(BlueprintCallable)
	bool SetClient(AVClassPlayerController* Controller);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/Actor.h"
#include "ScreenActor.generated.h"

UCLASS()
class VCLASS_API AScreenActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScreenActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Screen;

	UFUNCTION()
	void StartSlideTransition();

	UFUNCTION()
	void StartSlideTransitionReverse();

private:
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* SlideCurve;

	UPROPERTY()
	UTimelineComponent* SlideTimeline;

	UFUNCTION()
	void UpdateMaterial(float Value);

	UFUNCTION()
	void OnTransitionFinished();
};

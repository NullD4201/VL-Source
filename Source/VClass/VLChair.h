// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VLChair.generated.h"

UCLASS()
class VCLASS_API AVLChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVLChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SitTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UFUNCTION(BlueprintCallable)
	FTransform GetSittingTransform();
	
};

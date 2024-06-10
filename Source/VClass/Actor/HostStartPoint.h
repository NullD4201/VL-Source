// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/Actor.h"
#include "HostStartPoint.generated.h"

UCLASS()
class VCLASS_API AHostStartPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHostStartPoint();

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* mScene;

	UPROPERTY(BlueprintReadOnly)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* mArrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

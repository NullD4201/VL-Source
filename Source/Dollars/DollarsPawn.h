// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "DollarsClientReceiver.h"
#include "DollarsPawn.generated.h"

UCLASS()
class DOLLARS_API ADollarsPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADollarsPawn();

	UPROPERTY(VisibleAnywhere, Category=Collision)
	UCapsuleComponent* capsule;

	UPROPERTY(VisibleAnywhere, Category=Visual)
	USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UFloatingPawnMovement* movement;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, Category = MoCap)
	UDollarsClientReceiver* moCapClientReceiver;
	UPROPERTY(VisibleAnywhere, Category = MoCap, Replicated)
	float speed;
	UPROPERTY(VisibleAnywhere, Category=MoCap, Replicated)
	float rotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerSideMovement(const FTransform& newTransform, const float newSpeed, const float newRotation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float CalculateDirection(const FVector& velocity, const FRotator& baseRotator);
	
};

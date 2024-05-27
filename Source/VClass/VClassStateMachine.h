// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectInfo.h"
#include "GameFramework/Actor.h"
#include "VClassStateMachine.generated.h"

UENUM(BlueprintType)
enum class VClassState :uint8 {
	VCS_PLAIN UMETA(DisplayName = "Plain"),
	VCS_TESTING UMETA(DisplayName = "Testing"),
	VCS_CONTROLUI UMETA(DisplayName = "Control UI")
};

UCLASS()
class VCLASS_API AVClassStateMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVClassStateMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitVClassStateMachine();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	VClassState CurrentState = VClassState::VCS_PLAIN;

	UFUNCTION(BlueprintImplementableEvent)
	void OnGestureChangedEvent(const FString& startGesture,const FString& endGesture);

	UFUNCTION(BlueprintCallable)
	void SetVClassState(VClassState new_state);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Components/ActorComponent.h"
#include "VClassGestureCaptor.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VCLASS_API UVClassGestureCaptor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVClassGestureCaptor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	static FString ReadStringToFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable)
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);
	
	UFUNCTION(BlueprintCallable)
	static void AddStringToFile(FString FilePath, FString String);
};

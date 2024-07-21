// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HostSpawnableObject.h"
#include "GameFramework/Actor.h"
#include "VClassElectraPlayer.generated.h"

UCLASS()
class VCLASS_API AVClassElectraPlayer : public AHostSpawnableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVClassElectraPlayer();

	UFUNCTION(NetMulticast,Reliable)
	void NativeSetURL(const FString& url);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintableSetURL(const FString& url);
	
};

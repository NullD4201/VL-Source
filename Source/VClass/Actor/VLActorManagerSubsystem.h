// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VLActorManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UVLActorManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void ServerSpawnActor(TSubclassOf<AActor> ClassToSpawn, FTransform Transform);
};

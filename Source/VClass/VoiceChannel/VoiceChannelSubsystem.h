// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VoiceChannelSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UVoiceChannelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void OnGetVoice(TArray<uint8> pcmData);
	
};

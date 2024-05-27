// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DollarsMoCap.h"
#include "VClass/MoCapData.h"
#include "DollarsClientReceiver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOLLARS_API UDollarsClientReceiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDollarsClientReceiver();

	FVector tempVector;
	FTransform tempTransform;
	FDollarsMoCap dollarsMoCapActor;
	FMoCapData moCapData;

protected:

	void MoCapMapping();

public:	

	UFUNCTION(Client, Reliable)
	void ClientReceiveMoCapData(const FMoCapData& data);
		
	
};

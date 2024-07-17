// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HostObjectSpawnActor.generated.h"

UCLASS()
class VCLASS_API AHostObjectSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHostObjectSpawnActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server,Reliable)
	void ServerSpawnActor(TSubclassOf<class AHostSpawnableObject> ActorToSpawn, FTransform Transform);

	UFUNCTION(Server,Reliable)
	void ServerMoveActor(AHostSpawnableObject* Actor, FTransform Transform);
	
	UFUNCTION(Server,Reliable, BlueprintCallable)
	void ServerLoadScene(const FString& Scene);
	
};

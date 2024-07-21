// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VClassElectraPlayer.h"
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

	TSubclassOf<AVClassElectraPlayer> ElectraPlay_class;

	FVector LocationIndex[11] = {FVector(-2.0,-1115.0,242.0),
								FVector(-121.0,-992.0,242.0),
								FVector(135.0,-992.0,242.0),
								FVector(-232.0,-894.0,242.0),
								FVector(-126.0,-894.0,242.0),
								FVector(-7.0,-894.0,242.0),
								FVector(135.0,-894.0,242.0),
								FVector(250.0,-849.0,242.0),
								FVector(-126.0,-794.0,242.0),
								FVector(-7.0,-800.0,242.0),
								FVector(135.0,-802.0,242.0)};

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

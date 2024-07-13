// Fill out your copyright notice in the Description page of Project Settings.


#include "VLActorManagerSubsystem.h"

void UVLActorManagerSubsystem::ServerSpawnActor_Implementation(TSubclassOf<AActor> ClassToSpawn, FTransform Transform)
{
	UE_LOG(LogTemp, Warning, TEXT("Server Spawn Actor"));
	//GetWorld()->SpawnActor<AActor>(ClassToSpawn, Transform);
}




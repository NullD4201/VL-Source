// Fill out your copyright notice in the Description page of Project Settings.


#include "HostSpawnableObject.h"

#include "Net/UnrealNetwork.h"


// Sets default values
AHostSpawnableObject::AHostSpawnableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicatingMovement(true);
}

void AHostSpawnableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register properties for replication
	DOREPLIFETIME(AHostSpawnableObject, ReplicatedScale);
}

void AHostSpawnableObject::ChangeScale(FVector NewScale)
{
	if(HasAuthority())
	{
		ReplicatedScale = NewScale;
		OnRep_Scale();
	}
}

void AHostSpawnableObject::OnRep_Scale()
{
	SetActorScale3D(ReplicatedScale);
}


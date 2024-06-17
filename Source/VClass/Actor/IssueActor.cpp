// Fill out your copyright notice in the Description page of Project Settings.


#include "IssueActor.h"

#include "VClass/Player/VClassPlayerController.h"


AIssueActor::AIssueActor(int32 HostIdentifier, int32 PlayerIdentifier)
{
	this->HostIdentifier = HostIdentifier;
	this->PlayerIdentifier = PlayerIdentifier;
}

void AIssueActor::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (AVClassPlayerController* VClassPlayerController = Cast<AVClassPlayerController>(PlayerController))
		{
			if (VClassPlayerController->PlayerId == this->HostIdentifier || VClassPlayerController->PlayerId == this->PlayerIdentifier)
			{
				SetActorHiddenInGame(false);
			}
			else
			{
				SetActorHiddenInGame(true);
			}
		}
	}
}

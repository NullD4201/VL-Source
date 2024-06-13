// Fill out your copyright notice in the Description page of Project Settings.


#include "IssueActor.h"

#include "VClass/Player/JihoonTestPlayerController.h"


AIssueActor::AIssueActor()
{
}

void AIssueActor::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (AJihoonTestPlayerController* JihoonTestPlayerController = Cast<AJihoonTestPlayerController>(PlayerController))
		{
			if (JihoonTestPlayerController->PlayerId == 0 || JihoonTestPlayerController->PlayerId == 1)
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

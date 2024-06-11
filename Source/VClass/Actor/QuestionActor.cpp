// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestionActor.h"


// Sets default values
AQuestionActor::AQuestionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestionActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}


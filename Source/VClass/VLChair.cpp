// Fill out your copyright notice in the Description page of Project Settings.

#include "VLChair.h"
#include "VLChairManagerSubsystem.h"


// Sets default values
AVLChair::AVLChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	SitTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SIT_TRANSFORM"));
	RootComponent = Body;
	SitTransform->SetupAttachment(Body);

	SitTransform->SetRelativeLocation(FVector(0.0, 0.0, 50.0));
}

// Called when the game starts or when spawned
void AVLChair::BeginPlay()
{
	Super::BeginPlay();

	UVLChairManagerSubsystem* chairSubsystem = GetGameInstance()->GetSubsystem<UVLChairManagerSubsystem>();
	chairSubsystem->ChairMap.Add(name, this);
}

// Called every frame
void AVLChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform AVLChair::GetSittingTransform() {
	return SitTransform->GetComponentTransform();
}


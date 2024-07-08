// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenActor.h"


// Sets default values
AScreenActor::AScreenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Screen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen"));
	SetRootComponent(Screen);

	SlideTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SlideTimeline"));
}

// Called when the game starts or when spawned
void AScreenActor::BeginPlay()
{
	Super::BeginPlay();

	if (SlideCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("UpdateMaterial"));
		SlideTimeline->AddInterpFloat(SlideCurve, TimelineProgress);
		
		FOnTimelineEvent TimelineFinished;
		TimelineFinished.BindUFunction(this, FName("OnTransitionFinished"));
		SlideTimeline->SetTimelineFinishedFunc(TimelineFinished);
	}

	SlideTimeline->RegisterComponent();

    DynamicMaterial = Screen->CreateAndSetMaterialInstanceDynamic(0);
}

// Called every frame
void AScreenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SlideTimeline->TickComponent(DeltaTime, LEVELTICK_TimeOnly, nullptr);
}

void AScreenActor::StartSlideTransition()
{
	if (SlideTimeline)
	{
		SlideTimeline->PlayFromStart();
	}
}

void AScreenActor::StartSlideTransitionReverse()
{
	if (SlideTimeline)
	{
		SlideTimeline->ReverseFromEnd();
	}
}

void AScreenActor::UpdateMaterial(float Value)
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName("SlideAmount"), Value);
	}
}

void AScreenActor::OnTransitionFinished()
{
}


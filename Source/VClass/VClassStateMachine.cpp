// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassStateMachine.h"
#include <Kismet/GameplayStatics.h>
#include "VClassGestureRecognitor.h"


// Sets default values
AVClassStateMachine::AVClassStateMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVClassStateMachine::BeginPlay()
{
	Super::BeginPlay();
	if(!HasAuthority())
		InitVClassStateMachine();
}

void AVClassStateMachine::InitVClassStateMachine() {
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (controller) {
		UVClassGestureRecognitor* gestureRecognitor = controller->GetComponentByClass<UVClassGestureRecognitor>();
		if (gestureRecognitor) {
			UE_LOG(LogTemp, Warning, TEXT("Mapped Delegate"));
			gestureRecognitor->OnGestureChanged.AddDynamic(this, &AVClassStateMachine::OnGestureChangedEvent);
		}
	}
}

void AVClassStateMachine::SetVClassState(VClassState new_state) {
	CurrentState = new_state;
}

// Called every frame
void AVClassStateMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


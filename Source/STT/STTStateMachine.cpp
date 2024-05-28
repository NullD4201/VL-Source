// Fill out your copyright notice in the Description page of Project Settings.


#include "STTStateMachine.h"


// Sets default values
ASTTStateMachine::ASTTStateMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneComponent = CreateDefaultSubobject<USceneComponent>("ROOT");
	audioCaptureComponent = CreateDefaultSubobject<UAudioCaptureComponent>("AUDIO");

	RootComponent = defaultSceneComponent;
	audioCaptureComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASTTStateMachine::BeginPlay()
{
	Super::BeginPlay();
	audioCaptureComponent->Start();

	webSocket = FWebSocketsModule::Get().CreateWebSocket(sttHost, TEXT("wss"));
}

// Called every frame
void ASTTStateMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


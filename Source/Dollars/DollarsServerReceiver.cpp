// Fill out your copyright notice in the Description page of Project Settings.


#include "DollarsServerReceiver.h"


// Sets default values
ADollarsServerReceiver::ADollarsServerReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADollarsServerReceiver::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		oscServer = UOSCManager::CreateOSCServer(ipAddress, port, false, true, TEXT("VL"));
		oscServer->OnOscMessageReceived.AddDynamic(this, &ADollarsServerReceiver::OnOSCMessageReceived);
	}
}

// Called every frame
void ADollarsServerReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADollarsServerReceiver::OnOSCMessageReceived(const FOSCMessage& Message, const FString& Address, int Port) {

}


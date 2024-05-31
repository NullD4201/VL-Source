// Fill out your copyright notice in the Description page of Project Settings.


#include "STTOscReceiver.h"
#include <vector>
#include <codecvt>


// Sets default values
ASTTOscReceiver::ASTTOscReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTTOscReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTTOscReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ASTTOscReceiver::ASCIIToFString(TArray<int> asciiArr) {
	wchar_t temp[200] = L"";
	for (int i = 0; i < asciiArr.Num(); i++) {
		if (asciiArr[i] < 55199) {
			temp[i] = (wchar_t)asciiArr[i];
		}
	}
	return FString(UTF16_TO_TCHAR(temp));
}


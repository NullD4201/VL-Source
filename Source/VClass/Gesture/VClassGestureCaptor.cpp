// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassGestureCaptor.h"
#include "HAL/PlatformFileManager.h"


// Sets default values for this component's properties
UVClassGestureCaptor::UVClassGestureCaptor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVClassGestureCaptor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVClassGestureCaptor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UVClassGestureCaptor::ReadStringToFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage) {
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath)) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String To File Failed - Was not able to write to file. Is your file read-only? Is the path vaild? %s"), *FilePath);
		return "";
	}
	FString RetString = "";

	if (!FFileHelper::LoadFileToString(RetString, *FilePath)) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String To File Failed - Was not able to write to file. Is your file read-only? Is the path vaild? %s"), *FilePath);
		return "";
	}
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write String To File Successed. %s"), *FilePath);
	return RetString;
}

void UVClassGestureCaptor::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage) {
	if (!FFileHelper::SaveStringToFile(String, *FilePath)) {
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String To File Failed - Was not able to write to file. Is your file read-only? Is the path vaild? %s"), *FilePath);
		return;
	}
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write String To File Successed. %s"), *FilePath);
}

void UVClassGestureCaptor::AddStringToFile(FString FilePath, FString String) {
	bool bOutSuccess;
	FString OutInfoMessage;
	FString retString = ReadStringToFile(FilePath, bOutSuccess, OutInfoMessage);
	if (bOutSuccess) {
		retString += "\n" + String;
		WriteStringToFile(FilePath, retString, bOutSuccess, OutInfoMessage);
	}
	if (!bOutSuccess) {
		WriteStringToFile(FilePath, String, bOutSuccess, OutInfoMessage);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), bOutSuccess ? TEXT("True") : TEXT("False"));
}
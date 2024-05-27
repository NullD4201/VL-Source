// Fill out your copyright notice in the Description page of Project Settings.


#include "VLChairManagerSubsystem.h"
#include <Kismet/GameplayStatics.h>

void UVLChairManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

AVLChair* UVLChairManagerSubsystem::GetChairByName(FString name) {
	if (ChairMap.Contains(name)) {
		return ChairMap[name];
	}
	else {
		return nullptr;
	}
}

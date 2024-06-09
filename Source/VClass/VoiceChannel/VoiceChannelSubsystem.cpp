// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceChannelSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include "VLAudioCaptureComponent.h"


void UVoiceChannelSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UVoiceChannelSubsystem::OnGetVoice(TArray<uint8> pcmData) {
	TArray<AActor*> controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), controllers);

	int i = 0;
	for (AActor* actor : controllers) {
		UE_LOG(LogTemp, Warning, TEXT("tlfgod %d"), i);
		i++;
		UVLAudioCaptureComponent* audioComp = Cast<UVLAudioCaptureComponent>(actor->GetComponentByClass(UVLAudioCaptureComponent::StaticClass()));
		audioComp->ClientGetVoice(pcmData);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryPlayerController.h"


AEntryPlayerController::AEntryPlayerController() {
	static ConstructorHelpers::FClassFinder<UEntryUI> UI_ENTRY_C(TEXT("/Game/UI/UW_EntryUI.UW_EntryUI_C"));
	if (UI_ENTRY_C.Succeeded()) {
		entryUIClass = UI_ENTRY_C.Class;
	}

	bShowMouseCursor = true;
}

void AEntryPlayerController::BeginPlay() {
	UEntryUI* ui = CreateWidget<UEntryUI>(this, entryUIClass);
	ui->AddToViewport();
}

void AEntryPlayerController::EntryServer(const FString& address, const FString& port, const bool isHost, const FString& seatNum) {
	FString options = "";
	options.Append("isHost=");
	options.Append(isHost ? "True" : "False");
	options.Append("?seatNum=");
	options.Append(seatNum);

	UGameplayStatics::OpenLevel(GetWorld(), FName(address + ":" + port), true, options);
}
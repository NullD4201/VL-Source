// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryUI.h"
#include "../EntryPlayerController.h"

void UEntryUI::NativeConstruct() {
	Super::NativeConstruct();

	addressTextBox = Cast<UEditableText>(GetWidgetFromName(TEXT("et_address")));
	if (!addressTextBox) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"et_address\" UEditableTextBox Widget"));
	}

	portTextBox = Cast<UEditableText>(GetWidgetFromName(TEXT("et_port")));
	if (!addressTextBox) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"et_port\" UEditableTextBox Widget"));
	}

	seatnumTextBox = Cast<UEditableText>(GetWidgetFromName(TEXT("et_seatnum")));
	if (!addressTextBox) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"et_seatnum\" UEditableTextBox Widget"));
	}

	hostCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("cb_host")));
	if (!addressTextBox) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"cb_host\" UCheckBox Widget"));
	}

	clientCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("cb_client")));
	if (!addressTextBox) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"cb_client\" UCheckBox Widget"));
	}

	entryButton = Cast<UButton>(GetWidgetFromName(TEXT("btn_entry")));
	if (!entryButton) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"btn_entry\" UButton Widget"));
	}


	hostCheckBox->OnCheckStateChanged.AddDynamic(this, &UEntryUI::ToggleHostCheckBox);
	clientCheckBox->OnCheckStateChanged.AddDynamic(this, &UEntryUI::ToggleClientCheckBox);
}
void UEntryUI::ToggleHostCheckBox(bool bisChecked) {
	if (bisChecked) {
		clientCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		isHost = true;
	}
}

void UEntryUI::ToggleClientCheckBox(bool bisChecked) {
	if (bisChecked) {
		hostCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		isHost = false;
	}
}

void UEntryUI::OnClickEntryButton() {
	this->RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("tlfgod"));
	AEntryPlayerController* controller = Cast<AEntryPlayerController>(GetOwningPlayer());
	if (!controller) {
		UE_LOG(LogTemp, Error, TEXT("Local Player Controller is NOT AEntryPlayerController!"));
	}

	controller->EntryServer(addressTextBox->GetText().ToString(),
							portTextBox->GetText().ToString(),
							isHost,
							seatnumTextBox->GetText().ToString());

}




// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "VClass/Player/MainMenuPlayerController.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mCheckHost = Cast<UCheckBox>(GetWidgetFromName(TEXT("HostCheckBox")));
	if (!mCheckHost)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find HostCheckBox Widget."));

	mCheckClient = Cast<UCheckBox>(GetWidgetFromName(TEXT("ClientCheckBox")));
	if (!mCheckClient)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find ClientCheckBox Widget"));

	mTextBoxAddress = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("AddressTextBox")));
	if (!mTextBoxAddress)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find AddressTextBox Widget"));

	mTextBoxPort = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PortTextBox")));
	if (!mTextBoxPort)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find PortTextBox Widget"));

	mComboSeatLine = Cast<UComboBoxString>(GetWidgetFromName(TEXT("SeatLineCombo")));
	if (!mComboSeatLine)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find SeatLineCombo Widget"));

	mComboSeatNumber = Cast<UComboBoxString>(GetWidgetFromName(TEXT("SeatNumCombo")));
	if (!mComboSeatNumber)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find SeatNumCombo Widget"));

	mButtonConnect = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));
	if (!mButtonConnect)
		UE_LOG(VClass, Type::Error, TEXT("Cannot find ConnectButton Widget"));

	mButtonConnect->SetIsEnabled(false);

	mCheckHost->OnCheckStateChanged.AddDynamic(this, &UMainMenuWidget::ToggleCheckHost);
	mCheckClient->OnCheckStateChanged.AddDynamic(this, &UMainMenuWidget::ToggleCheckClient);
	mTextBoxAddress->OnTextChanged.AddDynamic(this, &UMainMenuWidget::OnAddressTextChanged);
	mTextBoxPort->OnTextChanged.AddDynamic(this, &UMainMenuWidget::OnPortTextChanged);
	mComboSeatLine->OnSelectionChanged.AddDynamic(this, &UMainMenuWidget::OnComboSeatLineChanged);
	mComboSeatNumber->OnSelectionChanged.AddDynamic(this, &UMainMenuWidget::OnComboSeatNumberChanged);
}

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	mButtonConnect->SetIsEnabled(bAddress && bPort && bSeatLine && bSeatNum);
}

void UMainMenuWidget::ToggleCheckHost(bool bIsChecked)
{
	if (bIsChecked)
	{
		mCheckClient->SetCheckedState(ECheckBoxState::Unchecked);
		bIsHost = true;
	}
	else
	{
		mCheckClient->SetCheckedState(ECheckBoxState::Checked);
		bIsHost = false;
	}
}

void UMainMenuWidget::ToggleCheckClient(bool bIsChecked)
{
	if (bIsChecked)
	{
		mCheckHost->SetCheckedState(ECheckBoxState::Unchecked);
		bIsHost = false;
	}
	else
	{
		mCheckHost->SetCheckedState(ECheckBoxState::Checked);
		bIsHost = true;
	}
}

void UMainMenuWidget::OnAddressTextChanged(const FText& Text)
{
	int32 TextLength = Text.ToString().Len();
	bAddress = TextLength > 0;
}

void UMainMenuWidget::OnPortTextChanged(const FText& Text)
{
	int32 TextLength = Text.ToString().Len();
	bPort = TextLength > 0;
}

void UMainMenuWidget::OnComboSeatLineChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	bSeatLine = true;
}

void UMainMenuWidget::OnComboSeatNumberChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	bSeatNum = true;
}

void UMainMenuWidget::OnClickButtonConnect()
{
	this->RemoveFromParent();

	AMainMenuPlayerController* PlayerController = Cast<AMainMenuPlayerController>(GetOwningPlayer());
	if (!PlayerController)
	{
		UE_LOG(VClass, Type::Error, TEXT("Local Player Controller is not AMainMenuPlayerController."));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectGenerationUI.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Components/CanvasPanelSlot.h>

#include "VClass/VClass.h"
#include "VClass/Actor/VLActorManagerSubsystem.h"
#include "VClass/Player/VClassPlayerController.h"

void UObjectGenerationUI::NativeConstruct() {
	Super::NativeConstruct();

	selectionImg = Cast<UImage>(GetWidgetFromName(TEXT("pbSelectionImg")));
	if (!selectionImg) {
		UE_LOG(LogTemp, Error, TEXT("Can't find \"pbSelectionImg\" UImage Widget"));
	}
}

void UObjectGenerationUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (CurrentState)
	{
	case HostUIState::HOST_PLAIN:
		break;
	case HostUIState::HOST_GENERATEOBJ:
		OnGenerateObjectMode();
		break;
	case HostUIState::HOST_GRABOBJ:
		OnGrabObjectMode();
		break;
	default:
		break;
	}
}

void UObjectGenerationUI::SetHostState(HostUIState newState) {
	CurrentState = newState;
}

void UObjectGenerationUI::GetMouseToWidgetOffset(float& offsetLeft, float& offsetTop, float& offsetRight, float& offsetBottom) {
	float mouseX, mouseY;
	GetOwningPlayer()->GetMousePosition(mouseX, mouseY);

	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));

	offsetLeft = mouseX / viewportScale;
	offsetTop = mouseY / viewportScale;
	offsetRight = (viewportSize.X - mouseX) / viewportScale;
	offsetBottom = (viewportSize.Y - mouseY) / viewportScale;
}

//Resizing Controlling Object
void UObjectGenerationUI::ResizeObject(float AxisValue)
{
	if(!ControllingObj) return;

	ControllingObj->SetActorScale3D(ControllingObj->GetActorScale3D() + AxisValue*OBJ_RESIZING_DELTA);
	UE_LOG(VClass, Warning, TEXT("%s"), *ControllingObj->GetActorScale3D().ToString())
}

//Generate New Object
void UObjectGenerationUI::StartObjGeneration() {
	SetHostState(HostUIState::HOST_GENERATEOBJ);
	
	float mouseX, mouseY;
	GetOwningPlayer()->GetMousePosition(mouseX, mouseY);

	FVector worldPosition, worldDirection;
	GetOwningPlayer()->DeprojectScreenPositionToWorld(mouseX, mouseY, worldPosition, worldDirection);

	FRotator rotator = worldDirection.Rotation();
	FTransform Transform = FTransform(rotator, worldPosition + worldDirection * OBJ_GENERATING_DISTANCE);

	ControllingObj = GetWorld()->SpawnActor<AHostSpawnableObject>(spawningActorClass, Transform);
	ControllingObj->SetReplicates(false);
}
void UObjectGenerationUI::EndObjGeneration() {
	SetHostState(HostUIState::HOST_PLAIN);
	FTransform Transform = ControllingObj->GetTransform();
	UE_LOG(VClass, Warning, TEXT("%s"), *Transform.GetScale3D().ToString());

	if(AVClassPlayerController* player = Cast<AVClassPlayerController>(GetOwningPlayer()))
	{
		if(player->ObjectSpawner)
		{
			if(spawningActorClass)
			{
				player->ObjectSpawner->ServerSpawnActor(spawningActorClass,Transform);
				ControllingObj->Destroy();
			}
			else
			{
				UE_LOG(VClass, Error, TEXT("Spawning Actor Class doesn't set!"));
			}
		}
		else
		{
			UE_LOG(VClass, Error, TEXT("Player's ObjectSpawner Doesn't Set! Is Gamemode Subclass of \"VClassGameMode\"?"));
		}
	}
}
void UObjectGenerationUI::OnGenerateObjectMode() {
	float mouseX, mouseY;
	GetOwningPlayer()->GetMousePosition(mouseX, mouseY);

	FVector worldPosition, worldDirection;
	GetOwningPlayer()->DeprojectScreenPositionToWorld(mouseX, mouseY, worldPosition, worldDirection);

	FRotator rotator = worldDirection.Rotation();

	ControllingObj->SetActorLocation(worldPosition + worldDirection * OBJ_GENERATING_DISTANCE);
	ControllingObj->SetActorRotation(rotator);
}

//Grab And Control Object
void UObjectGenerationUI::StartObjGrab(AHostSpawnableObject* ObjToGrab)
{
	SetHostState(HostUIState::HOST_GRABOBJ);
	ControllingObj = ObjToGrab;
	ObjToGrab->SetReplicates(false);
}
void UObjectGenerationUI::EndObjGrab()
{
	SetHostState(HostUIState::HOST_PLAIN);
	FTransform Transform = ControllingObj->GetTransform();
	ControllingObj->SetReplicates(true);
	
	if(AVClassPlayerController* player = Cast<AVClassPlayerController>(GetOwningPlayer()))
	{
		if(player->ObjectSpawner)
		{
			if(spawningActorClass)
			{
				player->ObjectSpawner->ServerMoveActor(ControllingObj,Transform);
			}
			else
			{
				UE_LOG(VClass, Error, TEXT("Spawning Actor Class doesn't set!"));
			}
		}
		else
		{
			UE_LOG(VClass, Error, TEXT("Player's ObjectSpawner Doesn't Set! Is Gamemode Subclass of \"VClassGameMode\"?"));
		}
	}
}
void UObjectGenerationUI::OnGrabObjectMode()
{
	float mouseX, mouseY;
	GetOwningPlayer()->GetMousePosition(mouseX, mouseY);

	FVector worldPosition, worldDirection;
	GetOwningPlayer()->DeprojectScreenPositionToWorld(mouseX, mouseY, worldPosition, worldDirection);

	FRotator rotator = worldDirection.Rotation();

	ControllingObj->SetActorLocation(worldPosition + worldDirection * OBJ_GENERATING_DISTANCE);
	ControllingObj->SetActorRotation(rotator);
}



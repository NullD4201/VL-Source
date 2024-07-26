// Fill out your copyright notice in the Description page of Project Settings.


#include "HostSpawnableObject.h"

#include "Kismet/KismetRenderingLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AHostSpawnableObject::AHostSpawnableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
	
	RenderTarget = NewObject<UTextureRenderTarget2D>();
	RenderTarget->InitAutoFormat(1024, 1024); // 원하는 해상도로 초기화
	SceneCaptureComponent->TextureTarget = RenderTarget;

	bReplicates = true;
	SetReplicatingMovement(true);
}

void AHostSpawnableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register properties for replication
	DOREPLIFETIME(AHostSpawnableObject, ReplicatedScale);
}

void AHostSpawnableObject::ChangeScale(FVector NewScale)
{
	if(HasAuthority())
	{
		ReplicatedScale = NewScale;
		OnRep_Scale();
	}
}

void AHostSpawnableObject::OnRep_Scale()
{
	SetActorScale3D(ReplicatedScale);
}

void AHostSpawnableObject::Despawn_Implementation()
{
	Destroy();
}


UTexture2D* AHostSpawnableObject::CaptureSceneToTexture()
{
	if (!RenderTarget)
	{
		UE_LOG(LogTemp, Error, TEXT("RenderTarget is not initialized."));
		return nullptr;
	}

	// RenderTarget을 UTexture2D로 변환
	UTexture2D* CapturedTexture = UKismetRenderingLibrary::RenderTargetCreateStaticTexture2DEditorOnly(RenderTarget, GetName());
    
	if (CapturedTexture)
	{
		return CapturedTexture;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to capture scene to texture."));
		return nullptr;
	}
}

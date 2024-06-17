// Fill out your copyright notice in the Description page of Project Settings.


#include "DissolveActor.h"


// Sets default values
ADissolveActor::ADissolveActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent를 가져와서 머티리얼 인스턴스를 설정합니다.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// 머티리얼 인스턴스를 다이나믹 인스턴스로 변환합니다.
	if (Mesh->GetMaterial(0))
	{
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
		Mesh->SetMaterial(0, DynamicMaterialInstance);
	}
}

// Called when the game starts or when spawned
void ADissolveActor::BeginPlay()
{
	Super::BeginPlay();
    
	// 예제: 시작 시 머티리얼 파라미터를 설정합니다.
	if (DynamicMaterialInstance)
	{
		SetMaterialParameter(FName("progress"), 0);
	}
}

void ADissolveActor::SetMaterialParameter(FName ParameterName, float Value)
{
	if (DynamicMaterialInstance)
	{
		DynamicMaterialInstance->SetScalarParameterValue(ParameterName, Value);
	}
}

void ADissolveActor::SetMaterialParameterDelayed(FName ParameterName, float EndValue, float Delay)
{
	if (DynamicMaterialInstance)
	{
		CurrentParameterName = ParameterName;
		CurrentEndValue = EndValue;
		CurrentDelay = Delay;

		// 현재 파라미터 값을 가져옵니다.
		DynamicMaterialInstance->GetScalarParameterValue(ParameterName, InitialValue);

		// 타이머를 설정하여 딜레이 후 파라미터 값을 변경합니다.
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADissolveActor::UpdateMaterialParameter, Delay, true);
	}
}

void ADissolveActor::UpdateMaterialParameter()
{
	// 현재 파라미터 값을 점진적으로 목표 값으로 변경합니다.
	float CurrentValue;
	DynamicMaterialInstance->GetScalarParameterValue(CurrentParameterName, CurrentValue);

	float NewValue = FMath::FInterpTo(CurrentValue, CurrentEndValue, GetWorld()->GetDeltaSeconds(), 0.1f);

	DynamicMaterialInstance->SetScalarParameterValue(CurrentParameterName, NewValue);

	// 목표 값에 도달하면 타이머를 클리어합니다.
	if (FMath::IsNearlyEqual(NewValue, CurrentEndValue, 0.01f))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

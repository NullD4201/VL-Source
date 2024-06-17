// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "GameFramework/Actor.h"
#include "DissolveActor.generated.h"

UCLASS()
class VCLASS_API ADissolveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADissolveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

public:
	UFUNCTION(BlueprintCallable, Category="Material")
	void SetMaterialParameter(FName ParameterName, float Value);

	UFUNCTION(BlueprintCallable, Category="Material")
	void SetMaterialParameterDelayed(FName ParameterName, float EndValue, float Delay);

private:
	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	FTimerHandle TimerHandle;
	FName CurrentParameterName;
	float CurrentEndValue;
	float CurrentDelay;
	float InitialValue;

	void UpdateMaterialParameter();
};

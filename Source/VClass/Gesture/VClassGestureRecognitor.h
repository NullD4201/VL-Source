// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "Components/ActorComponent.h"
#include "VClassGestureRecognitor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGestureChangedDelegate, const FString&, startGesture, const FString&, endGesture);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VCLASS_API UVClassGestureRecognitor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVClassGestureRecognitor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> InputData;

	UFUNCTION(BlueprintCallable)
	FString Predict();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CurrentGesture;

	UPROPERTY(BlueprintAssignable)
	FOnGestureChangedDelegate OnGestureChanged;

private:
	float weights[16][5] = {
		{-7.71369793e-01,1.76806760e+00,6.75368683e-02,3.19600741e-01,-3.83835418e-01},
		{1.04803473e-02,-1.20789080e-02,7.99018089e-03,4.16635227e-03,-1.05579724e-02},
		{-1.02778444e-02,1.34972668e-02,6.53546030e-03,-2.31223094e-02,1.33674267e-02},
		{-2.13063988e-03,2.58427189e-03,-2.04974067e-02,2.11042657e-02,-1.06049096e-03},
		{4.68705014e-03,-1.46178938e-03,-2.12569060e-02,6.98946502e-05,1.79617506e-02},
		{-5.04885792e-03,-5.41138596e-04,9.83027364e-03,4.28646095e-04,-4.66892323e-03},
		{-1.77005218e-04,7.30043129e-04,1.38802071e-02,4.06573291e-04,-1.48398183e-02},
		{-7.18329499e-03,1.20062833e-02,9.03980557e-03,6.51640174e-03,-2.03791956e-02},
		{3.05242110e-03,1.95842039e-03,-7.17506972e-03,-4.43975446e-03,6.60398270e-03},
		{2.64510424e-03,3.38958126e-03,-8.43408992e-03,-3.00499056e-03,5.40439498e-03},
		{1.64370176e-02,-1.73556466e-02,-1.06083566e-04,-2.44424235e-03,3.46895493e-03},
		{-1.12283956e-03,-4.87212211e-03,5.45937436e-04,2.86739434e-03,2.58162990e-03},
		{-5.33152719e-04,-1.60436918e-02,9.64658616e-03,3.13980732e-04,6.61627758e-03},
		{3.12003772e-03,-3.68162375e-03,-2.00737163e-03,-5.49676665e-03,8.06572431e-03},
		{-5.36852265e-02,1.13084904e-02,3.47422767e-02,2.23938477e-02,-1.47593883e-02},
		{5.44752690e-02,-9.06564535e-03,-3.11413974e-02,-2.46259348e-02,1.03577086e-02} 
	};

	TArray<FString> categories = { "Thumbs_up","open_hands","pointing","rock","v_sign" };

	float** MatrixM2D(float** A, int* A_Shape, float** B, int* B_Shape, bool& bOutSuccessful);
};

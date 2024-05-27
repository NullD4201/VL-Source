// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassGestureRecognitor.h"


// Sets default values for this component's properties
UVClassGestureRecognitor::UVClassGestureRecognitor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVClassGestureRecognitor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVClassGestureRecognitor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString prediction = Predict();
	if (!GetOwner()->HasAuthority()) {
		if (*CurrentGesture != nullptr && !CurrentGesture.Equals(*prediction)) {
			OnGestureChanged.Broadcast(*CurrentGesture, *prediction);
			CurrentGesture = *prediction;
		}
		else if (*CurrentGesture == nullptr) {
			CurrentGesture = *prediction;
		}
	}
}

float** UVClassGestureRecognitor::MatrixM2D(float** A, int* A_Shape, float** B, int* B_Shape, bool& bOutSuccessful) {
	int A_N = A_Shape[0];
	int A_M = A_Shape[1];
	int B_N = B_Shape[0];
	int B_M = B_Shape[1];

	float** result;
	result = new float* [A_N];
	for (int i = 0; i < A_N; i++) {
		result[i] = new float[B_M] {0};
	}


	FString tempStr = TEXT("");
	if (A_M != B_N) {
		bOutSuccessful = false;
	}
	else {
		for (int i = 0; i < A_N; i++) {
			for (int j = 0; j < B_M; j++) {
				for (int k = 0; k < A_M; k++) {
					/*
					tempStr.Append(FString::SanitizeFloat(result[i][j]));
					tempStr.Append(TEXT(","));
					tempStr.Append(FString::SanitizeFloat(A[i][k]));
					tempStr.Append(TEXT(","));
					tempStr.Append(FString::SanitizeFloat(B[k][j]));
					*/
					result[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *tempStr);
		bOutSuccessful = true;
	}

	delete[] A_Shape;
	delete[] B_Shape;
	return result;
}

FString UVClassGestureRecognitor::Predict() {
	float** Phi = new float* [1];
	Phi[0] = new float[InputData.Num()+1] {1};
	for (int i = 0; i < InputData.Num(); i++) {
		Phi[0][i + 1] = InputData[i];
	}

	float** w_pointer = new float* [InputData.Num() + 1];
	for (int i = 0; i < InputData.Num() + 1; i++) {
		w_pointer[i] = weights[i];
	}

	bool bSuccessful = false;
	float** prediction = MatrixM2D(Phi, new int[] {1, InputData.Num() + 1}, w_pointer, new int[]{ InputData.Num() + 1,sizeof(weights[0]) / sizeof(float) }, bSuccessful);
	/*
	for (int i = 0; i < 5; i++) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), prediction[0][i]);
	}
	UE_LOG(LogTemp, Warning, TEXT("____________________"));
	*/

	int max_index = 0;
	if (bSuccessful) {
		for (int i = 0; i < sizeof(weights[0]) / sizeof(float); i++) {
			if (prediction[0][max_index] < prediction[0][i]) {
				max_index = i;
			}
		}
	}
	return categories[max_index];
}
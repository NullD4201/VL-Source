// Fill out your copyright notice in the Description page of Project Settings.

#include "DollarsPawn.h"
#include <Net/UnrealNetwork.h>


// Sets default values
ADollarsPawn::ADollarsPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = capsule;
	skeletalMesh->SetupAttachment(capsule);
	springArm->SetupAttachment(capsule);
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void ADollarsPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADollarsPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADollarsPawn, speed);
	DOREPLIFETIME(ADollarsPawn, rotation);
}

// Called every frame
void ADollarsPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority()) {
		float _speed = GetVelocity().Length();
		float _rotation = CalculateDirection(GetVelocity(), FRotator(0.0, 0.0, GetBaseAimRotation().Yaw));
		ServerSideMovement(GetActorTransform(), _speed, _rotation);
	}
}

// Called to bind functionality to input
void ADollarsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADollarsPawn::ServerSideMovement_Implementation(const FTransform& newTransform, const float newSpeed, const float newRotation) {
	speed = newSpeed;
	rotation = newRotation;
	SetActorTransform(newTransform);
}

float ADollarsPawn::CalculateDirection(const FVector& velocity, const FRotator& baseRotator) {
	if (!velocity.IsNearlyZero())
	{
		const FMatrix RotMatrix = FRotationMatrix(baseRotator);
		const FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		const FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		const FVector NormalizedVel = velocity.GetSafeNormal2D();

		// get a cos(alpha) of forward vector vs velocity
		const float ForwardCosAngle = static_cast<float>(FVector::DotProduct(ForwardVector, NormalizedVel));
		// now get the alpha and convert to degree
		float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

		// depending on where right vector is, flip it
		const float RightCosAngle = static_cast<float>(FVector::DotProduct(RightVector, NormalizedVel));
		if (RightCosAngle < 0.f)
		{
			ForwardDeltaDegree *= -1.f;
		}

		return ForwardDeltaDegree;
	}
	return 0.f;
}

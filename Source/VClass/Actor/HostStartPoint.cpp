// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStartPoint.h"


// Sets default values
AHostStartPoint::AHostStartPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// mScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	// mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	mSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HostModel"));
	mArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardDirection"));

	SetRootComponent(mSkeletalMesh);
	mArrow->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
    if (Asset.Succeeded())
    {
	    mSkeletalMesh->SetSkeletalMeshAsset(Asset.Object);
    }
	mSkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));

	mArrow->ArrowColor = FColor(150, 200, 255);
	mArrow->ArrowSize = 1;
	mArrow->bIsScreenSizeScaled = true;
	mArrow->bTreatAsASprite = true;
	mArrow->SetRelativeRotation(FRotator(0, 90, 0));

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AHostStartPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHostStartPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


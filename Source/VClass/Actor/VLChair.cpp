// Fill out your copyright notice in the Description page of Project Settings.

#include "VLChair.h"
#include "VLChairManagerSubsystem.h"


// Sets default values
AVLChair::AVLChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChairBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	ChairButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	SitTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SIT_TRANSFORM"));
	
	SetRootComponent(ChairBody);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> _Mesh1(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/ChairBody.ChairBody'"));
    if (_Mesh1.Succeeded())
    {
	    ChairBody->SetStaticMesh(_Mesh1.Object);
    }
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _Mesh2(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/ChairButton.ChairButton'"));
    if (_Mesh2.Succeeded())
    {
	    ChairButton->SetStaticMesh(_Mesh2.Object);
    }

	ChairButton->SetupAttachment(GetRootComponent());
	SitTransform->SetupAttachment(GetRootComponent());

	SitTransform->SetRelativeLocation(FVector(0.0, 0.0, 50.0));
}

// Called when the game starts or when spawned
void AVLChair::BeginPlay()
{
	Super::BeginPlay();

	UVLChairManagerSubsystem* chairSubsystem = GetGameInstance()->GetSubsystem<UVLChairManagerSubsystem>();
	chairSubsystem->ChairMap.Add(Name, this);
}

// Called every frame
void AVLChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AVLChair::SetClient(AVClassPlayerController* Controller) {
	if (IsSetted) return false;

	APawn* pawn = Controller->GetPawn();
	pawn->SetActorTransform(GetSittingTransform());

	Controller->InteractionDelegate.BindLambda([Controller](const FInputActionValue& value) {
		if(value.Get<bool>())
			Controller->ServerSendHostRequest(HostRequest::QUESTION);
	});
	Controller->LogoutDelegate.BindLambda([this]() {
		this->IsSetted = false;
	});
	IsSetted = true;

	return true;
}

FTransform AVLChair::GetSittingTransform() {
	return SitTransform->GetComponentTransform();
}
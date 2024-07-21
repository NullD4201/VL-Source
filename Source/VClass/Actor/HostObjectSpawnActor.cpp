// Fill out your copyright notice in the Description page of Project Settings.


#include "HostObjectSpawnActor.h"

#include "HostSpawnableObject.h"
#include "MediaDisplay.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "UObject/UnrealTypePrivate.h"
#include "VClass/VClass.h"
#include "VClass/Player/VClassPlayerController.h"


// Sets default values
AHostObjectSpawnActor::AHostObjectSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	bReplicates = true;
}

void AHostObjectSpawnActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 필요한 리플리케이션 설정
}

// Called when the game starts or when spawned
void AHostObjectSpawnActor::BeginPlay()
{
	Super::BeginPlay();

	if(!HasAuthority())
	{
		AVClassPlayerController* LocalPlayerController = Cast<AVClassPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(LocalPlayerController)
		{
			LocalPlayerController->ObjectSpawner = this;
		}
	}
}

// Called every frame
void AHostObjectSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AHostObjectSpawnActor::ServerSpawnActor_Implementation(TSubclassOf<class AHostSpawnableObject> ActorToSpawn, FTransform Transform)
{
	AHostSpawnableObject* actor = GetWorld()->SpawnActor<AHostSpawnableObject>(ActorToSpawn, Transform);
	actor->ChangeScale(Transform.GetScale3D());
}
void AHostObjectSpawnActor::ServerMoveActor_Implementation(AHostSpawnableObject* Actor, FTransform Transform)
{
	if(Actor)
	{
		Actor->SetActorTransform(Transform);
		Actor->ChangeScale(Transform.GetScale3D());
	}
	else
	{
		UE_LOG(VClass, Error, TEXT("Actor Doesn't Exist"));
	}
}
void AHostObjectSpawnActor::ServerLoadScene_Implementation(const FString& Scene)
{
	for(TActorIterator<AHostSpawnableObject> IT(GetWorld()); IT; ++IT)
	{
		AHostSpawnableObject* SpawnableObject = *IT;
		SpawnableObject->Despawn();
		SpawnableObject->SetReplicates(false);
		SpawnableObject->Destroy();
	}
	TArray<FString> strArray;
	Scene.ParseIntoArray(strArray,TEXT("\n"),true);

	for(FString s : strArray)
	{
		TArray<FString> _arr;
		s.ParseIntoArray(_arr,TEXT(","),true);
		UE_LOG(VClass, Warning, TEXT("%s"), *_arr[0]);
		
		if(_arr[0].Equals(TEXT("A")))
		{
			UClass* LoadedClass = StaticLoadClass(AHostSpawnableObject::StaticClass(), nullptr, *_arr[1]);
			if(LoadedClass)
			{
				TSubclassOf<AHostSpawnableObject> ActorClass = LoadedClass;

				GetWorld()->SpawnActor<AHostSpawnableObject>(ActorClass, LocationIndex[FCString::Atoi(*_arr[2])], FRotator::ZeroRotator);
			}
			else
			{
				UE_LOG(VClass, Error, TEXT("Class \"%s\" is not exist"), *_arr[1]);
			}
		}
		else if(_arr[0].Equals(TEXT("M")))
		{
			AMediaDisplay* media = GetWorld()->SpawnActor<AMediaDisplay>(AMediaDisplay::StaticClass(), LocationIndex[FCString::Atoi(*_arr[2])], FRotator::ZeroRotator);
			media->SetImage(_arr[1]);
		}
		else
		{
			AVClassElectraPlayer* electraPlayer = GetWorld()->SpawnActor<AVClassElectraPlayer>(ElectraPlay_class, LocationIndex[FCString::Atoi(*_arr[2])], FRotator::ZeroRotator);
			electraPlayer->NativeSetURL(_arr[1]);
		}
	}
}






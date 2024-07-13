// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/VClassGameMode.h"

#include "VClassPlayerController.h"
#include "Misc/Paths.h"
#include "PlayerVoiceChatActor.h"
#include <VClass/Actor/VLChair.h>
#include <VClass/Actor/VLChairManagerSubsystem.h>

#include "VClass/Actor/ImageDisplayManager.h"


AVClassGameMode::AVClassGameMode()
{
    DefaultPawnClass = nullptr;
	PlayerControllerClass = AVClassPlayerController::StaticClass();
}

void AVClassGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    FString key = UGameplayStatics::ParseOption(Options, TEXT("Key"));

    UE_LOG(LogTemp, Warning, TEXT("%s"), *key);

    if (!keyMap.Contains(key) || keyMap[key]) {
        ErrorMessage = TEXT("Your key is not vaild");
        return;
    }

    if (CurrentPlayerNum >= MaxPlayer) {
        ErrorMessage = TEXT("The Server is FULL!");
    }
    

    lastLoginRequestOption = *Options;
    keyMap[key] = true;

    CurrentPlayerNum += 1;
}

void AVClassGameMode::PostLogin(APlayerController* NewPlayerController) {

    Super::PostLogin(NewPlayerController);

    AVClassPlayerController* player = Cast<AVClassPlayerController>(NewPlayerController);
    if (!player) {
        UE_LOG(LogTemp, Error, TEXT("Player Controller connected is not vaild!"));
        return;
    }
    
    FString isHost = UGameplayStatics::ParseOption(lastLoginRequestOption, TEXT("IsHost"));

    player->bIsHost = isHost == TEXT("true") ? true : false;

    player->info.Key = UGameplayStatics::ParseOption(lastLoginRequestOption, TEXT("Key"));
    player->info.isHost = TEXT("true") ? true : false;

    if(player->info.isHost) player->ClientGetClientRequest(ClientRequest::UISETTING_HOST);
    else player->ClientGetClientRequest(ClientRequest::UISETTING_CLIENT);

    UE_LOG(LogTemp, Warning, TEXT("bIsHost set %s"), player->bIsHost ? TEXT("true") : TEXT("false"));

    FActorSpawnParameters params;
    params.Owner = NewPlayerController;

    GetWorld()->SpawnActor<APlayerVoiceChatActor>(APlayerVoiceChatActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, params);

    TActorIterator<APlayerStart> It(GetWorld());
    APlayerStart* playerStart = *It;
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = NewPlayerController;
    //Run when client is "Host"
    if (player->bIsHost) {
        APawn* pawn = GetWorld()->SpawnActor<APawn>(HostPawn, playerStart->GetTransform(), SpawnParams);
        player->Possess(pawn);

        if(GetWorld()->SpawnActor<AHostObjectSpawnActor>(AHostObjectSpawnActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, params))
        {
            UE_LOG(VClass, Warning, TEXT("HostObjectSpawnActor Spawned"));
        }

        FString ImageAppearModeStr = UGameplayStatics::ParseOption(lastLoginRequestOption, TEXT("ImageAppearMode"));
        if(!ImageAppearModeStr.IsEmpty())
        {
            ImageAppearMode Mode = static_cast<ImageAppearMode>(FCString::Atoi(*ImageAppearModeStr));
            UE_LOG(VClass, Warning, TEXT("%s"), *AImageDisplayManager::ImageAppearModeToString(Mode));
            TActorIterator<AImageDisplayManager> ImageDisplayActors(GetWorld());
            AImageDisplayManager* ImageDisplayActor = *ImageDisplayActors;
            ImageDisplayActor->CurrentMode = Mode;
        }
    }
    //Run when client is "Client"
    else {
        APawn* pawn = GetWorld()->SpawnActor<APawn>(ClientPawn, playerStart->GetTransform(), SpawnParams);
        player->Possess(pawn);
        FString seatNum = UGameplayStatics::ParseOption(lastLoginRequestOption, TEXT("SeatNum"));
        UVLChairManagerSubsystem* chairManager = GetGameInstance()->GetSubsystem<UVLChairManagerSubsystem>();
        if (seatNum.IsEmpty()) {
            for(auto ValueIter = chairManager->ChairMap.CreateConstIterator(); ValueIter; ++ValueIter) {
                AVLChair* chair = ValueIter.Value();
                UE_LOG(LogTemp, Warning, TEXT("%s"), *chair->Name);
                if (chair->SetClient(player)) {
                    break;
                }
            }
        }
        else {
            if (chairManager) {
                chairManager->GetChairByName(seatNum)->SetClient(player);
            }
        }
    }
    OnClientLogin.Broadcast(player);
}

void AVClassGameMode::BeginPlay() {
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("ProjectDir: %s"), *FPaths::ProjectDir());

    FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("keys.txt"));
    FString FileContent;

    TArray<FString> key_list;

    if (ReadTextFile(FilePath, FileContent))
    {
        UE_LOG(LogTemp, Log, TEXT("Text File Content:\n%s"), *FileContent);

        FileContent.ParseIntoArrayLines(key_list);

        for (const FString& line : key_list)
        {
            UE_LOG(LogTemp, Log, TEXT("Line: %s"), *line);
            keyMap.Add(line, false);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read the text file."));
    }
}

void AVClassGameMode::Logout(AController* Exiting) {
    Super::Logout(Exiting);
    UE_LOG(LogTemp, Warning, TEXT("AVClassGameMode::Logout"));
    CurrentPlayerNum -= 1;
    if (AVClassPlayerController* player = Cast<AVClassPlayerController>(Exiting)) {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *player->info.Key);
        keyMap[player->info.Key] = false;
        player->UnPossess();
    }
}

bool AVClassGameMode::ReadTextFile(FString FilePath, FString& FileContent) {
    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        return FFileHelper::LoadFileToString(FileContent, *FilePath);
    }
    return false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/VClassGameMode.h"

#include "VClassPlayerController.h"
#include "Misc/Paths.h"


AVClassGameMode::AVClassGameMode()
{
	PlayerControllerClass = AVClassPlayerController::StaticClass();
}

void AVClassGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    FString key = UGameplayStatics::ParseOption(Options, TEXT("Key"));

    UE_LOG(LogTemp, Warning, TEXT("%s"), *key);

    if (!keyMap.Contains(key) && keyMap[key]) {
        ErrorMessage = TEXT("Your key is not vaild");
        return;
    }

    lastLoginRequestOption = *Options;
    keyMap[key] = true;
}

void AVClassGameMode::PostLogin(APlayerController* NewPlayerController) {
    AVClassPlayerController* player = Cast<AVClassPlayerController>(NewPlayerController);
    if (!player) {
        UE_LOG(LogTemp, Error, TEXT("Player Controller connected is not vaild!"));
        return;
    }
    
    FString isHost = UGameplayStatics::ParseOption(lastLoginRequestOption, TEXT("IsHost"));

    player->bIsHost = isHost == TEXT("true") ? true : false;

    UE_LOG(LogTemp, Warning, TEXT("bIsHost set %s"), player->bIsHost ? TEXT("true") : TEXT("false"));
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

bool AVClassGameMode::ReadTextFile(FString FilePath, FString& FileContent) {
    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        return FFileHelper::LoadFileToString(FileContent, *FilePath);
    }
    return false;
}

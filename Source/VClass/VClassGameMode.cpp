// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassGameMode.h"
#include "Misc/Paths.h"


void AVClassGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    FString key;
    FParse::Value(*Options, TEXT("Key="), key);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *key);

    if (!key_list.Contains(key)) {
        ErrorMessage = TEXT("Your key is not vaild");
        return;
    }
}

void AVClassGameMode::BeginPlay(){
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("ProjectDir: %s"), *FPaths::ProjectDir());

    FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("keys.txt"));
    FString FileContent;

    if (ReadTextFile(FilePath, FileContent))
    {
        UE_LOG(LogTemp, Log, TEXT("Text File Content:\n%s"), *FileContent);

        FileContent.ParseIntoArrayLines(key_list);

        for (const FString& line : key_list)
        {
            UE_LOG(LogTemp, Log, TEXT("Line: %s"), *line);
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


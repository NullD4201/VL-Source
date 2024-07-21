// Fill out your copyright notice in the Description page of Project Settings.


#include "VClassElectraPlayer.h"


// Sets default values
AVClassElectraPlayer::AVClassElectraPlayer()
{

}

void AVClassElectraPlayer::NativeSetURL_Implementation(const FString& url)
{
	BlueprintableSetURL(TEXT("https://www.youtube.com/watch?v=")+url+TEXT("&start_radio=1"));
}



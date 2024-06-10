// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImportFiles.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UImportFiles : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static UTexture2D* OpenFIleDialogueAndLoadImage();	
};

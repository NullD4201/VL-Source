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

public:
	UFUNCTION(BlueprintCallable)
	static UTexture2D* OpenFIleDialogueAndLoadImage();	

	UFUNCTION(BlueprintCallable)
	static void OpenFileDialogueAndUploadImage(FString ImageName, FString Url);

	UFUNCTION(BlueprintCallable)
	static UTexture2D* CreateTextureFromBytes(const TArray<uint8>& ImageData, int32 Width, int32 Height, EPixelFormat PixelFormat, bool bSRGB);

	UFUNCTION(BlueprintCallable)
	static bool ConvertTextureToByteArray(UTexture2D* Texture, TArray<uint8>& OutByteArray);

	UFUNCTION(BlueprintCallable)
	static UTexture2D* LoadTextureFromBytes(const TArray<uint8>& ImageData);

	UFUNCTION(BlueprintCallable)
	static FString ConvertFSoftPathToFString(FSoftClassPath path);
};

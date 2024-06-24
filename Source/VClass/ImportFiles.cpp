// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportFiles.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include <HttpModule.h>


UTexture2D* UImportFiles::OpenFIleDialogueAndLoadImage()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	if (DesktopPlatform)
	{
		TArray<FString> OutFilenames;
		bool bOpened = DesktopPlatform->OpenFileDialog(
			nullptr,
			TEXT("Select PNG File"),
			FPaths::ProjectContentDir(),
			TEXT(""),
			TEXT("Image Files (*.png; *.jpg| *.png;*.jpg)"),
			EFileDialogFlags::None,
			OutFilenames
		);

		if (bOpened && OutFilenames.Num() > 0)
		{
			FString SelectedImagePath = OutFilenames[0];

			TArray<uint8> ImageData;

			if (FFileHelper::LoadFileToArray(ImageData, *SelectedImagePath))
			{
				IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

				EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageData.GetData(), ImageData.Num());

				TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

				if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
				{
					TArray64<uint8> RawData;

					if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, RawData))
					{
						TArray64<uint8>* RawDataProcessed = &RawData;
						UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_R8G8B8A8);

						if (Texture)
						{
							FTexture2DMipMap& MipMap = Texture->GetPlatformData()->Mips[0];
							void* Data = MipMap.BulkData.Lock(LOCK_READ_WRITE);

							FMemory::Memcpy(Data, RawDataProcessed->GetData(), RawDataProcessed->Num());
							MipMap.BulkData.Unlock();

							Texture->GetPlatformData()->SetNumSlices(1);
							Texture->NeverStream = true;
							Texture->UpdateResource();

							return Texture;
						}
					}
				}
			}
		}
	}

	return nullptr;
}

void UImportFiles::OpenFIleDialogueAndUploadImage(FString ImageName)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	if (DesktopPlatform)
	{
		TArray<FString> OutFilenames;
		bool bOpened = DesktopPlatform->OpenFileDialog(
			nullptr,
			TEXT("Select PNG File"),
			FPaths::ProjectContentDir(),
			TEXT(""),
			TEXT("Image Files (*.png; *.jpg| *.png;*.jpg)"),
			EFileDialogFlags::None,
			OutFilenames
		);
		if (bOpened && OutFilenames.Num() > 0)
		{
			FString SelectedImagePath = OutFilenames[0];

			TArray<uint8> ImageData;

			if (FFileHelper::LoadFileToArray(ImageData, *SelectedImagePath))
			{
				// HTTP 요청 생성
				TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
				HttpRequest->SetVerb("POST");
				HttpRequest->SetURL("http://localhost:8000");
				HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("image/png"));
				HttpRequest->SetHeader(TEXT("Image-Name"), ImageName);
				HttpRequest->SetContent(ImageData);

				// 요청 보내기
				HttpRequest->ProcessRequest();
			}
		}
	}
}

bool UImportFiles::ConvertTextureToByteArray(UTexture2D* Texture, TArray<uint8>& OutByteArray) 
{
	if (!Texture)
	{
		return false;
	}

	FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_ONLY);

	int32 Width = Texture->GetSizeX();
	int32 Height = Texture->GetSizeY();
	int32 Size = Width * Height * 4; // Assuming the texture format is RGBA

	OutByteArray.SetNumUninitialized(Size);
	FMemory::Memcpy(OutByteArray.GetData(), Data, Size);

	Mip.BulkData.Unlock();

	return true;
}

UTexture2D* UImportFiles::CreateTextureFromBytes(const TArray<uint8>& ImageData, int32 Width, int32 Height, EPixelFormat PixelFormat, bool bSRGB)
{
	UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PixelFormat);
	if (!Texture)
	{
		return nullptr;
	}

	Texture->SRGB = bSRGB;

	// Lock the texture so we can write to it
	uint8* TextureData = static_cast<uint8*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	FMemory::Memcpy(TextureData, ImageData.GetData(), ImageData.Num());
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

	// Update the texture with new mip data
	Texture->UpdateResource();

	return Texture;
}

UTexture2D* UImportFiles::LoadTextureFromBytes(const TArray<uint8>& ImageData)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);  // 이미지 포맷에 맞게 수정

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		TArray<uint8> RawData;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
		{
			UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

			void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());
			Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

			Texture->UpdateResource();
			return Texture;
		}
	}

	return nullptr;
}

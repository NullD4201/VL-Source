// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageDisplayManager.h"
#include "../ImportFiles.h"
#include <VClass/Player/VClassGameMode.h>


FString AImageDisplayManager::ImageAppearModeToString(ImageAppearMode mode) {
	FString result;
	switch (mode) {
	case ImageAppearMode::IAM_ONESIDED: result = TEXT("OneSided");
	case ImageAppearMode::IAM_TWOSIDED: result = TEXT("TwoSided");
	case ImageAppearMode::IAM_TRIPLE:	result = TEXT("Triple");
	case ImageAppearMode::IAM_ONESIDED_LONG:	result = TEXT("OneSidedLong");
	case ImageAppearMode::IAM_BACKWARD_FULL:	result = TEXT("BackwardFull");
	case ImageAppearMode::IAM_FRONT_WIDE:	result = TEXT("FrontWide");
	default: nullptr;
	}
	return result;
}

// Sets default values
AImageDisplayManager::AImageDisplayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void AImageDisplayManager::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		AVClassGameMode* gamemode = Cast<AVClassGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gamemode) {
			gamemode->OnClientLogin.AddDynamic(this, &AImageDisplayManager::OnClientLogin);
		}
	}
	if (!HasAuthority()) {
		TArray<UStaticMeshComponent*> planes;
		GetComponents<UStaticMeshComponent>(planes);
		for (UStaticMeshComponent* comp : planes) {
			UMaterialInterface* material = comp->GetMaterial(0);
			if (!material) continue;

			UMaterialInstanceDynamic* dynamic_mat = UMaterialInstanceDynamic::Create(material, nullptr);
			if (!dynamic_mat) continue;

			comp->SetMaterial(0,dynamic_mat);
		}
	}
}

// Called every frame
void AImageDisplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImageDisplayManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AImageDisplayManager, CurrentMode);
}

void AImageDisplayManager::OnRep_CurrentMode() {

}

void AImageDisplayManager::OnClientLogin(AVClassPlayerController* player) {
	if (player->bIsHost) {
		SetOwner(player);
		ForceNetUpdate();
	}
}

void AImageDisplayManager::ServerDisplayImage_Implementation(ImageAppearMode Mode, int Index) {
	ClientDisplayImage(Mode, Index);
}

void AImageDisplayManager::ClientDisplayImage_Implementation(ImageAppearMode Mode, int Index) {

}

void AImageDisplayManager::SendImageToServer(const TArray<uint8>& ImageData) {
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetURL("http://localhost:8000"); // 서버의 이미지 업로드 API 엔드포인트

	// HTTP 헤더 설정 (예시: 이미지 파일의 MIME 타입)
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("image/jpeg"));

	// 바이너리 데이터 설정
	HttpRequest->SetContent(ImageData);

	// 요청 보내기
	HttpRequest->ProcessRequest();
}

void AImageDisplayManager::GetImageFromServer(FString ImageName) {
	FString UrlWithImageName = FString::Printf(TEXT("%s/%s"), *ImageServerURL, *ImageName);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(UrlWithImageName);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AImageDisplayManager::HandleImageReceived);
	HttpRequest->ProcessRequest();
}

void AImageDisplayManager::HandleImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response.IsValid() && Response->GetContentLength() > 0)
	{
		TArray<uint8> ImageData = Response->GetContent();

		UTexture2D* Texture = UImportFiles::LoadTextureFromBytes(ImageData);
		if (Texture)
		{
			// 텍스처를 성공적으로 로드한 후 원하는 작업을 수행합니다.
			// 예를 들어, UI에 텍스처를 표시하거나 다른 객체에 할당할 수 있습니다.
			USceneComponent* parent = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("OneSided")));
			TArray<USceneComponent*> panels;
			parent->GetChildrenComponents(true, panels);
			UStaticMeshComponent* panel_mesh = Cast<UStaticMeshComponent>(panels[0]);
			if (!panel_mesh) return;

			UMaterialInterface* material = panel_mesh->GetMaterial(0);
			if (!material) return;

			UMaterialInstanceDynamic* dynamic_mat = Cast<UMaterialInstanceDynamic>(material);
			if (!dynamic_mat) return;

			dynamic_mat->SetTextureParameterValue(TEXT("MainTex"), Texture);
			UE_LOG(LogTemp, Warning, TEXT("Texture received and loaded successfully!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load texture from received image data."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to receive image from server."));
	}
}
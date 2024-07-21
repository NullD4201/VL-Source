// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaDisplay.h"

#include "HttpModule.h"
#include "VClass/ImportFiles.h"


// Sets default values
AMediaDisplay::AMediaDisplay()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));

	// Attach mesh component to the root
	RootComponent = mesh;

	// Find the plane mesh in the Engine's content and assign it to the mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PLANE_MESH_ASSET(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (PLANE_MESH_ASSET.Succeeded())
	{
		mesh->SetStaticMesh(PLANE_MESH_ASSET.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MATERIAL(TEXT("Material'/Game/Materials/M_ImagePanel.M_ImagePanel'"));
	if (MATERIAL.Succeeded())
	{
		UMaterial* FoundMaterial = MATERIAL.Object;
		mesh->SetMaterial(0, FoundMaterial);
	}

	mesh->SetWorldRotation(FRotator(0.0,0.0,90.0));
}

// Called when the game starts or when spawned
void AMediaDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInterface* material = mesh->GetMaterial(0);
	if(!material) return;

	UMaterialInstanceDynamic* material_dynamic = UMaterialInstanceDynamic::Create(material, nullptr);
	if(!material_dynamic) return;

	mesh->SetMaterial(0,material_dynamic);
}

// Called every frame
void AMediaDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMediaDisplay::SetImage_Implementation(const FString& MediaName)
{
	FString UrlWithImageName = FString::Printf(TEXT("%s/%s"), *ImageServerAddress, *MediaName);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(UrlWithImageName);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AMediaDisplay::HandleImageReceived);
	HttpRequest->ProcessRequest();
}


void AMediaDisplay::HandleImageReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response.IsValid() && Response->GetContentLength() > 0)
	{
		TArray<uint8> ImageData = Response->GetContent();

		UTexture2D* Texture = UImportFiles::LoadTextureFromBytes(ImageData);
		if (Texture)
		{
			// 텍스처를 성공적으로 로드한 후 원하는 작업을 수행합니다.
			// 예를 들어, UI에 텍스처를 표시하거나 다른 객체에 할당할 수 있습니다.
			UMaterialInterface* material = mesh->GetMaterial(0);
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
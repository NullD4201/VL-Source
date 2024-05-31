// Fill out your copyright notice in the Description page of Project Settings.


#include "STTManager.h"
#include "Json.h"
#include <ctime>


// Sets default values
ASTTManager::ASTTManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	audioCaptureComponent = CreateDefaultSubobject<USTTAudioCaptureComponent>(TEXT("AUDIO"));

	http = &FHttpModule::Get();
	bWebSocketSetted = false;
}

// Called when the game starts or when spawned
void ASTTManager::BeginPlay()
{
	Super::BeginPlay();
	audioCaptureComponent->Start();
	GetAuthorityToken();
}

void ASTTManager::BeginDestroy() {
	Super::BeginDestroy();
	if (bWebSocketSetted) {
		bWebSocketSetted = false;
		webSocket->Send("EOS");
		webSocket->Close();
	}
}

// Called every frame
void ASTTManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (audioCaptureComponent->pcmLinear16.Num() > 0 && bWebSocketSetted) {
		/*
		TArray<uint8> tempArr;
		tempArr.Init(0, sizeof(int16)/sizeof(uint8)*audioCaptureComponent->pcmSamplesNum);
		FMemory::Memcpy(tempArr.GetData(), audioCaptureComponent->pcmLinear16.GetData(), sizeof(int16) * audioCaptureComponent->pcmSamplesNum);
		webSocket->Send(tempArr.GetData(), sizeof(int16) * audioCaptureComponent->pcmSamplesNum);*/
		void* tempPtr = &audioCaptureComponent->pcmLinear16;
		webSocket->Send(tempPtr, sizeof(int16) * audioCaptureComponent->pcmSamplesNum);
	}
}

void ASTTManager::GetAuthorityToken() {
	TSharedRef<IHttpRequest> req = http->CreateRequest();
	req->OnProcessRequestComplete().BindUObject(this, &ASTTManager::OnAuthorityRequestReceived);
	req->SetURL(httpHost);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	req->SetContentAsString(TEXT("client_id=" + clientId + "&client_secret=" + clientSecret));
	req->ProcessRequest();
}

void ASTTManager::OnAuthorityRequestReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful) {
	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(response->GetContentAsString());

	if (FJsonSerializer::Deserialize(reader, jsonObject)) {
		authorityToken = jsonObject->GetStringField("access_token");
		tokenExpiration = jsonObject->GetIntegerField("expire_at");
	}

	std::time_t now = std::time(nullptr);
	UE_LOG(LogTemp, Warning, TEXT("%s %d %d"), *authorityToken, tokenExpiration, now);

	SetupWebsocket();
}

void ASTTManager::SetupWebsocket() {
	UE_LOG(LogTemp, Warning, TEXT("WebSocket Setup..."));
	webSocket = FWebSocketsModule::Get().CreateWebSocket("ws://127.0.0.1:7777", TEXT("ws"), TMap<FString, FString>({ {TEXT("Authorization"), TEXT("Bearer " + authorityToken)} }));
	webSocket->OnConnected().AddLambda([]()->void {
		UE_LOG(LogTemp, Warning, TEXT("Socket has Successfully been Connected"));
		});
	webSocket->OnConnectionError().AddLambda([](const FString& err)->void{
		UE_LOG(LogTemp, Error, TEXT("Connection Error: %s"), *err);
		});
	webSocket->OnMessage().AddLambda([](const FString& msg)->void {
		UE_LOG(LogTemp, Warning, TEXT("Received: %s"), *msg);
		});
	webSocket->OnMessageSent().AddLambda([](const FString& msg)->void {
		//UE_LOG(LogTemp, Warning, TEXT("Send: %s"), *msg);
		});
	webSocket->Connect();
	bWebSocketSetted = true;
	UE_LOG(LogTemp, Warning, TEXT("WebSocket Setup Complete!"));
}
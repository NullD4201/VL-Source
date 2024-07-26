// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include <VClass/Gesture/VClassGestureRecognitor.h>
#include <VClass/Player/Structures/PlayerInfo.h>

#include "VClass/Actor/HostObjectSpawnActor.h"
#include "VClass/UI/Panels/CPanelLiveHost.h"
#include "VClassPlayerController.generated.h"

DECLARE_DELEGATE_OneParam(FVClassInteractonDelegate, const FInputActionValue&);
DECLARE_DELEGATE(FVClassControllerLogoutDelegate);

UENUM()
enum class HostRequest : uint8 {
	TEST_REQ,
	QUESTION
};

UENUM()
enum class ClientRequest : uint8 {
	TEST_REPL,
	QUESTION_VAILD,
	QUESTION_INVAILD,
	UISETTING_HOST,
	UISETTING_CLIENT
};

UCLASS()
class VCLASS_API AVClassPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVClassPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int32 PlayerId;

	float mMoveDir;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server,Reliable)
	void ServerSendHostRequest(HostRequest request);
	void ServerSendHostRequest_Implementation(HostRequest request);

	UFUNCTION(Server, Reliable)
	void ServerSendClientRequest(ClientRequest request, int32 Id);
	void ServerSendClientRequest_Implementation(ClientRequest request, int32 Id);

	UFUNCTION(Client,Reliable)
	void ClientGetHostRequest(HostRequest request, int32 Id);
	void ClientGetHostRequest_Implementation(HostRequest request,int32 Id);

	UFUNCTION(Client,Reliable)
	void ClientGetClientRequest(ClientRequest request);
	void ClientGetClientRequest_Implementation(ClientRequest request);

	UFUNCTION(BlueprintCallable)
	void HostLoadScene(int SceneNumber);
	UFUNCTION(BlueprintCallable)
	void LoadNextScene();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVClassGestureRecognitor* GestureRecognitor;

	UPROPERTY(VisibleAnywhere, replicated)
	FPlayerInfo info;
	UPROPERTY(VisibleAnywhere, replicated)
	AHostObjectSpawnActor* ObjectSpawner;

	FVClassInteractonDelegate InteractionDelegate;
	FVClassControllerLogoutDelegate LogoutDelegate;

	bool bIsHost = false;
	FString SeatNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCPanelLiveHost* HostPanel;
	TSubclassOf<class UCPanelLiveHost> HostPanelClass;
	
protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnInteract(const FInputActionValue& InputActionValue);

	void CallLiveLoadingScreen();
	
	int CurrentSceneNum = -1;
};

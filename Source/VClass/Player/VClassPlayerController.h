// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "../ProjectInfo.h"
#include "GameFramework/PlayerController.h"
#include "VClassPlayerController.generated.h"

DECLARE_DELEGATE_OneParam(FVClassInteractonDelegate, const FInputActionValue&);

UENUM()
enum class HostRequest : uint8 {
	TEST_REQ,
	QUESTION
};

UENUM()
enum class ClientRequest : uint8 {
	TEST_REPL,
	QUESTION_VAILD,
	QUESTION_INVAILD
};

UCLASS()
class VCLASS_API AVClassPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AVClassPlayerController();

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

	FVClassInteractonDelegate InteractionDelegate;

	bool bIsHost = false;
	FString SeatNum;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnInteract(const FInputActionValue& InputActionValue);
};

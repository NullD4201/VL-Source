// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "EngineMinimal.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

DECLARE_LOG_CATEGORY_EXTERN(VClass, Log, All);

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	Client,
	Host,
	None
};

UENUM(BlueprintType)
enum class EScreenTransitionType : uint8
{
	Normal,
	Vanish,
	PullUp,
	PullDown,
	PullLeft,
	PullRight,
	CoverUp,
	CoverDown,
	CoverLeft,
	CoverRight,
};
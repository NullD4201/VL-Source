// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ProjectInfo.h"
#include "InputMappingContext.h"
#include "UObject/NoExportTypes.h"
#include "InputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UInputDataConfig();

	UInputMappingContext* DefaultContext = nullptr;

	UInputAction* Move		= nullptr;
	UInputAction* Look		= nullptr;
	UInputAction* Interact	= nullptr;
};

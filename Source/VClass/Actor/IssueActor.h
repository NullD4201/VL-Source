// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ProjectInfo.h"
#include "QuestionActor.h"
#include "IssueActor.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API AIssueActor : public AQuestionActor
{
	GENERATED_BODY()

public:
	void Initialize();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HostIdentifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PlayerIdentifier;
};

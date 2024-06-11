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
	AIssueActor();

	virtual void BeginPlay() override;
};

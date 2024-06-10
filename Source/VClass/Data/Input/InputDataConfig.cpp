// Fill out your copyright notice in the Description page of Project Settings.


#include "InputDataConfig.h"

UInputDataConfig::UInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			IMC_Default(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Input/IMC_Default.IMC_Default'"));
		if (IMC_Default.Succeeded())
		{
			DefaultContext = IMC_Default.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			IA_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Move.IA_Move'"));
		if (IA_Move.Succeeded())
		{
			Move = IA_Move.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			IA_Look(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Look.IA_Look'"));
		if (IA_Look.Succeeded())
		{
			Look = IA_Look.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			IA_Interact(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Interact.IA_Interact'"));
		if (IA_Interact.Succeeded())
		{
			Interact = IA_Interact.Object;
		}
	}
}

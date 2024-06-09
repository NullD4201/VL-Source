// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioCaptureComponent.h"
#include "DSP/Osc.h"
#include "OpusAudioCompressor.h"
#include "VLAudioCaptureComponent.generated.h"

// ========================================================================
// UVLAudioCaptureComponent
// Synth component class which implements USynthComponent
// This is a simple hello-world type example which generates a sine-wave
// tone using a DSP oscillator class and implements a single function to set
// the frequency. To enable example:
// 1. Ensure "SignalProcessing" is added to project's .Build.cs in PrivateDependencyModuleNames
// 2. Enable macro below that includes code utilizing SignalProcessing Oscilator
// ========================================================================

#define SYNTHCOMPONENT_EX_OSCILATOR_ENABLED 0

UCLASS(ClassGroup = Synth, meta = (BlueprintSpawnableComponent))
class VCLASS_API UVLAudioCaptureComponent : public UAudioCaptureComponent
{
	GENERATED_BODY()
	
	// Called when synth is created
	virtual bool Init(int32& SampleRate) override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called to generate more audio
	virtual int32 OnGenerateAudio(float* OutAudio, int32 NumSamples) override;

	// Sets the oscillator's frequency
	UFUNCTION(BlueprintCallable, Category = "Synth|Components|Audio")
	void SetFrequency(const float FrequencyHz = 440.0f);

public:

	UPROPERTY(BlueprintReadOnly)
	USoundWaveProcedural* pcmSoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 encoderFrameSize;
	UPROPERTY(EditAnywhere)
	int16 noiseThreshold;

	UFUNCTION(Client, Reliable)
	void ClientGetVoice(const TArray<uint8>& pcmData);

	UFUNCTION(Server, Reliable)
	void ServerUpdateVoice(const TArray<uint8>& pcmData);

	TArray<int16> LINEAR16_PCM;
	TArray<uint8> encodedPCM;
	TArray<uint8> receivedPCM;

	UPROPERTY(BlueprintReadOnly)
	UOpusAudioCompressor* audioCompressor;

protected:
#if SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	// A simple oscillator class. Can also generate Saw/Square/Tri/Noise.
	Audio::FOsc Osc;
#endif // SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
};
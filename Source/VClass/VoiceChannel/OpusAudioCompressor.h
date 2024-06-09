// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <ThirdParty/libOpus/opus-1.3.1-12/include/opus.h>
#include "OpusAudioCompressor.generated.h"

/**
 * 
 */
UCLASS()
class VCLASS_API UOpusAudioCompressor : public UObject
{
	GENERATED_BODY()
	
public:
	UOpusAudioCompressor();

	TArray<uint8> EncodePCM(int16* pcm_LINEAR16);
	uint8* DecodePCM(const uint8* opusEncodedData, int32 dataSize, int32& decodedSamplesOutput);
	void ApplyNoiseGate(int16* buffer, int size, float threshold);
	void ApplyLowPassFilter(int16* buffer, int32 size, float cutoffFrequency, float sampleRate);

	int32 FrameSize = 2880;
	
private:
	OpusEncoder* opusEncoderInstance;
	OpusDecoder* opusDecoderInstance;
	
};

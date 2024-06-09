// Fill out your copyright notice in the Description page of Project Settings.


#include "OpusAudioCompressor.h"


UOpusAudioCompressor::UOpusAudioCompressor() {
	int32 error;
	opusEncoderInstance = opus_encoder_create(48000, 1, OPUS_APPLICATION_AUDIO, &error);
	if (error != OPUS_OK) {
		UE_LOG(LogTemp, Error, TEXT("Opus Encoder doesn't be generated!"));
	}
	opus_encoder_ctl(opusEncoderInstance, OPUS_SET_BITRATE(768000));
	opus_encoder_ctl(opusEncoderInstance, OPUS_SET_COMPLEXITY(10));
	opus_encoder_ctl(opusEncoderInstance, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
	error = OPUS_OK;
	opusDecoderInstance = opus_decoder_create(48000, 1, &error);
	if (error != OPUS_OK) {
		UE_LOG(LogTemp, Error, TEXT("Opus Decoder doesn't be generated!"));
	}
}

TArray<uint8> UOpusAudioCompressor::EncodePCM(int16* pcm_LINEAR16) {
	TArray<uint8> CompressedData;
	CompressedData.SetNum(FrameSize);
	int32 CompressedBytes = opus_encode(opusEncoderInstance, pcm_LINEAR16, FrameSize, CompressedData.GetData(), CompressedData.Num());
	TArray<uint8> output;
	if (CompressedBytes < 0) {
		UE_LOG(LogTemp, Error, TEXT("%hs"), opus_strerror(CompressedBytes));
	}
	for (int i = 0; i < CompressedBytes; i++) {
		output.Add(CompressedData[i]);
	}

	return CompressedData;
}

uint8* UOpusAudioCompressor::DecodePCM(const uint8* opusEncodedData, int32 dataSize, int32& decodedSamplesOutput) {
	TArray<int16> DecodedAudio;
	DecodedAudio.SetNumUninitialized(FrameSize);
	int32 decodedSamples = opus_decode(opusDecoderInstance, opusEncodedData, dataSize, DecodedAudio.GetData(), FrameSize, 0);
	if (decodedSamples < 0) {
		opus_strerror(decodedSamples);
	}
	decodedSamplesOutput = decodedSamples;
	return reinterpret_cast<uint8*>(DecodedAudio.GetData());
}

void UOpusAudioCompressor::ApplyNoiseGate(int16* buffer, int size, float threshold) {
	for (int i = 0; i < size; ++i) {
		if (fabs(buffer[i]) < threshold) {
			buffer[i] = 0;
		}
		buffer[i] = buffer[i] / 2;
	}
}

void UOpusAudioCompressor::ApplyLowPassFilter(int16* buffer, int32 size, float cutoffFrequency, float sampleRate) {
	float RC = 1.0 / (cutoffFrequency * 2.0 * 3.1415);
	float dt = 1.0 / sampleRate;
	float alpha = dt / (RC + dt);

	int16 previous = buffer[0];
	for (int i = 1; i < size; ++i) {
		buffer[i] = previous + (alpha * (buffer[i] - previous));
		previous = buffer[i];
	}
}
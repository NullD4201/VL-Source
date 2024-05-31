// Fill out your copyright notice in the Description page of Project Settings.


#include "STTAudioCaptureComponent.h"


bool USTTAudioCaptureComponent::Init(int32& SampleRate)
{
	NumChannels = 1;

#if SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	// Initialize the DSP objects
	Osc.Init(SampleRate);
	Osc.SetFrequency(440.0f);
	Osc.Start();
#endif // SYNTHCOMPONENT_EX_OSCILATOR_ENABLED

	return true;
}

int32 USTTAudioCaptureComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
{
#if SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	// Perform DSP operations here
	for (int32 Sample = 0; Sample < NumSamples; ++Sample)
	{
		OutAudio[Sample] = Osc.Generate();
	}
#endif // SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	int32 OutputSamplesGenerated = 0;
	OutputSamplesGenerated = Super::OnGenerateAudio(OutAudio, NumSamples);

	TArray<float> pcmData;
	pcmData.Init(0.f, OutputSamplesGenerated);
	FMemory::Memcpy(pcmData.GetData(), OutAudio, OutputSamplesGenerated * sizeof(float));

	for (float f : pcmData) {
		pcmLinear16.Add((int16)(f * 32767));
	}
	
	FDateTime currentTime = FDateTime::Now();
	//UE_LOG(LogTemp, Log, TEXT("[%d : %d]PCM Data, NumSamples: %d"), currentTime.GetSecond(), currentTime.GetMillisecond(), OutputSamplesGenerated);
	//
	pcmSamplesNum = OutputSamplesGenerated;
	return OutputSamplesGenerated;
}

void USTTAudioCaptureComponent::SetFrequency(const float InFrequencyHz)
{
#if SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	// Use this protected base class method to push a lambda function which will safely execute in the audio render thread.
	SynthCommand([this, InFrequencyHz]()
	{
		Osc.SetFrequency(InFrequencyHz);
		Osc.Update();
	});
#endif // SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
}
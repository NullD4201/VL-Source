// Fill out your copyright notice in the Description page of Project Settings.


#include "VLAudioCaptureComponent.h"
#include "VoiceChannelSubsystem.h"


void UVLAudioCaptureComponent::BeginPlay(){
	Super::BeginPlay();

	pcmSoundWave = NewObject<USoundWaveProcedural>();
	pcmSoundWave->SetSampleRate(48000);
	pcmSoundWave->NumChannels = 1;
	pcmSoundWave->Duration = INDEFINITELY_LOOPING_DURATION;

	audioCompressor = NewObject<UOpusAudioCompressor>();
	audioCompressor->FrameSize = encoderFrameSize;

	SetVolumeMultiplier(0.0f);
}

void UVLAudioCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("tlfgod"));

	
}
bool UVLAudioCaptureComponent::Init(int32& SampleRate)
{
	Super::Init(SampleRate);

	NumChannels = 1;
	

#if SYNTHCOMPONENT_EX_OSCILATOR_ENABLED
	// Initialize the DSP objects
	Osc.Init(SampleRate);
	Osc.SetFrequency(440.0f);
	Osc.Start();
#endif // SYNTHCOMPONENT_EX_OSCILATOR_ENABLED

	return true;
}

int32 UVLAudioCaptureComponent::OnGenerateAudio(float* OutAudio, int32 NumSamples)
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

	TArray<uint8> PCMData;
	PCMData.SetNumUninitialized(OutputSamplesGenerated * sizeof(int16));

	int16* PCMDataPtr = reinterpret_cast<int16*>(PCMData.GetData());

	for (int32 i = 0; i < OutputSamplesGenerated; ++i)
	{
		PCMDataPtr[i] = static_cast<int16>(FMath::Clamp(OutAudio[i], -1.0f, 1.0f) * 32767);
	}

	audioCompressor->ApplyNoiseGate(PCMDataPtr, OutputSamplesGenerated, noiseThreshold);

	LINEAR16_PCM.Append(PCMDataPtr, audioCompressor->FrameSize);
	if (LINEAR16_PCM.Num() > audioCompressor->FrameSize) {
		TArray<int16> TempBuf;
		TempBuf.Append(LINEAR16_PCM.GetData(), audioCompressor->FrameSize);

		LINEAR16_PCM.RemoveAt(0, audioCompressor->FrameSize);
		encodedPCM = audioCompressor->EncodePCM(TempBuf.GetData());

		AsyncTask(ENamedThreads::GameThread, [this]() {
			int32 decodedSamples;
			uint8* decodedData = audioCompressor->DecodePCM(encodedPCM.GetData(), encodedPCM.Num(), decodedSamples);
			int16* decodedData_16 = reinterpret_cast<int16*>(decodedData);
			//audioCompressor->ApplyLowPassFilter(decodedData_16, decodedSamples / sizeof(int16), 8000, 48000);
			receivedPCM.Append(decodedData, decodedSamples);
		});
		/*
		AsyncTask(ENamedThreads::GameThread, [this]() {
			ServerUpdateVoice(encodedPCM);
		});*/
	}

	if (receivedPCM.Num() > 1024 * sizeof(int16)) {

		pcmSoundWave->QueueAudio(receivedPCM.GetData(), 1024 * sizeof(int16));
		receivedPCM.RemoveAt(0, 1024 * sizeof(int16));
	}

	return OutputSamplesGenerated;
}

void UVLAudioCaptureComponent::SetFrequency(const float InFrequencyHz)
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

void UVLAudioCaptureComponent::ClientGetVoice_Implementation(const TArray<uint8>& pcmData) {
	int32 decodedSamples;
	uint8* decodedData = audioCompressor->DecodePCM(pcmData.GetData(), pcmData.Num(), decodedSamples);
	receivedPCM.Append(decodedData, decodedSamples);
}

void UVLAudioCaptureComponent::ServerUpdateVoice_Implementation(const TArray<uint8>& pcmData) {
	UVoiceChannelSubsystem* voiceChannelSubsystem =  UGameInstance::GetSubsystem<UVoiceChannelSubsystem>(GetWorld()->GetGameInstance());
	voiceChannelSubsystem->OnGetVoice(pcmData);
}
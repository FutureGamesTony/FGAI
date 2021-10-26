#include "FGHearingSensingTargetComponent.h"
#include "Audio/FGNoiseActor.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

TArray<UFGHearingSensingTargetComponent*> UFGHearingSensingTargetComponent::HearingSensingComponents;


UFGHearingSensingTargetComponent::UFGHearingSensingTargetComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}
static FFGNoiseData* source = nullptr;
void UFGHearingSensingTargetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (source != nullptr)
	{
		if(IsNoiseAudible())
			OnTargetHeard.Broadcast(*source);
	}
	source = nullptr;

}

void UFGHearingSensingTargetComponent::NoiseHeard(FFGNoiseData& HearingResult)
{
	
	static FFGNoiseData& result = HearingResult;
	source = &HearingResult;

	if (source == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("HearingResult was nullptr"));
		return;
	}

	if (source->NoiseInstigator == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NoiseInstigator was not set!"));
		return;
	}
	if (source->Sound == nullptr)
		UE_LOG(LogTemp, Log, TEXT("Sound variable has not been set in: %s"), *source->NoiseInstigator->GetName());

}

bool UFGHearingSensingTargetComponent::IsNoiseAudible()
{
	if (source == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("No Valid Data: "))
			return false;
	}
	if (source->dB <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("dB has not been set in: %s"), *source->NoiseInstigator->GetName())
		return false;
	}
	//SPL = Sound Pressure at Location (dB)
	//SPL2 = SPL1 - 20 * log (R2 / R1)
	static double distanceToSound = FVector::Dist(GetOwner()->GetActorLocation(), source->NoiseInstigator->GetActorLocation());
	// R1 is set to 1 (m)
	static double dBAtLocation = source->dB - (20 * log(distanceToSound * source->ConvertMtoCMMultiple()));

	if(HearingSettings == nullptr)
	{ 
		UE_LOG(LogTemp, Log, TEXT("Hearing Settings Variable has not been set"))
		return false;
	}
	if (source->Sound == nullptr)
		UE_LOG(LogTemp, Log, TEXT("Sound variable has not been set in: %s"), *source->NoiseInstigator->GetName())

	return dBAtLocation > HearingSettings->dBEnterDetect;
}

void UFGHearingSensingTargetComponent::GetHearingSensingTargets(TArray<UFGHearingSensingTargetComponent*>& OutTargets, float dB)
{
	for (UFGHearingSensingTargetComponent* Target : HearingSensingComponents)
	{
		if (Target == nullptr)
			continue;
		if(dB < 0)
			continue;
		if (Target->HearingSettings->dBEnterDetect < dB)
			OutTargets.Add(Target);
	}
}
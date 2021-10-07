#include "FGHearingSensingTargetComponent.h"
#include "FGNoiseActor.h"
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
		{ 
			OnTargetHeard.Broadcast(*source);
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), source->Sound, GetOwner()->GetActorLocation(), source->SoundRotation, source->dB);
		}
	}
	source = nullptr;

}

void UFGHearingSensingTargetComponent::NoiseHeard(FFGNoiseData& HearingResult)
{
	source = &HearingResult;

	if (source == nullptr)
		return;

	bool IsSoundSet = (source->Sound != nullptr) ? true : false;
	if (!IsSoundSet)
		UE_LOG(LogTemp, Log, TEXT("Sound variable has not been set in: %s"), *source->NoiseInstigator->GetName());

}
bool UFGHearingSensingTargetComponent::IsNoiseAudible()
{
	
	if(HearingSettings == nullptr)
	{ 
		UE_LOG(LogTemp, Log, TEXT("Hearing Settings Variable has not been set"))
		return false;
	}
	if (source == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("No Valid Data: "))
		return false;
	}
	if (source->Sound == nullptr)
		UE_LOG(LogTemp, Log, TEXT("Sound variable has not been set in: %s"), *source->NoiseInstigator->GetName())

	double I = source->Watt / (4 * PI * UKismetMathLibrary::Square(FVector::Dist(GetOwner()->GetActorLocation(), source->NoiseInstigator->GetActorLocation())));
	source->dB = UKismetMathLibrary::Log(I / source->IZero, 10.0f);
	return source->dB > HearingSettings->dBEnterDetect;

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

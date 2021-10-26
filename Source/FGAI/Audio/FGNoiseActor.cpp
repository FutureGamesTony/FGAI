#include "FGNoiseActor.h"
#include "Hearing/FGHearingSensingTargetComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void AFGNoiseActor::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void AFGNoiseActor::Tick(float DeltaSeconds)
{
	//SPL2 = SPL1 - 20 * log (R2 / R1)
	Super::Tick(DeltaSeconds);

	//int conversion because when the decibel is too low nothing can detect it anyway
	bool IsSoundAudible = (int)(Noise.dB - (20 * log(Noise.SpeedOfSound * DeltaSeconds)) > 0);

	UFGHearingSensingTargetComponent::NoiseHeard(Noise);
	
	if (!IsSoundAudible)
	{	
		Destroy();
		return;
	}

	NoiseSphereRadius += (Noise.SpeedOfSound * DeltaSeconds);

	if (bDrawDebugSphere)
		DrawDebugSphere(GetWorld(), GetActorLocation(), NoiseSphereRadius, 10, FColor::Magenta, true, 3.0f, 1, 1.0f);

	UFGHearingSensingTargetComponent::NoiseHeard(Noise);
}

void AFGNoiseActor::SpawnNoise_Implementation(FFGNoiseData NoiseData)
{
	Noise = NoiseData;	
}

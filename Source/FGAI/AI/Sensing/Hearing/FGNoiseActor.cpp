#include "FGNoiseActor.h"
#include "FGHearingSensingTargetComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

AFGNoiseActor::AFGNoiseActor()
{
	SoundWave = CreateDefaultSubobject<USphereComponent>(TEXT("SoundWave"));
	SoundWave->SetSphereRadius(NoiseSphereRadius);
	SoundWave->SetCollisionProfileName(TEXT("NoCollision"));
	RootComponent = SoundWave;

}
void AFGNoiseActor::BeginPlay()
{
	Super::BeginPlay();
	
	SoundWave->PrimaryComponentTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
}
void AFGNoiseActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	double I = Noise.Watt / (4 * PI * UKismetMathLibrary::Square(NoiseSphereRadius));
	double dBAtLocation = UKismetMathLibrary::Log(I / Noise.IZero, 10.0f);
	
	if ((int)dBAtLocation <= 0)
	{
		FFGNoiseData* non = nullptr;
		UFGHearingSensingTargetComponent::NoiseHeard(*non);
		Destroy();
		return;
	}

	NoiseSphereRadius += (Noise.SpeedOfSound * DeltaSeconds);
	SoundWave->SetSphereRadius(NoiseSphereRadius);

	if (bDrawDebugSphere)
		DrawDebugSphere(GetWorld(), SoundWave->GetComponentLocation(), NoiseSphereRadius, 10, FColor::Magenta, true, 3.0f, 1, 1.0f);

	UFGHearingSensingTargetComponent::NoiseHeard(Noise);
}
void AFGNoiseActor::SpawnNoise_Implementation(FFGNoiseData NoiseData)
{
	Noise = NoiseData;	
}

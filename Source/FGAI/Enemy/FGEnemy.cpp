#include "FGEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGAI/AI/Sensing/Vision/FGVisionSensingComponent.h"
#include "FGAI/AI/Sensing/Hearing/FGHearingSensingTargetComponent.h"
#include "Damage/FGDamageSensingComponent.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"

AFGEnemy::AFGEnemy()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	VisionSensingComponent = CreateDefaultSubobject<UFGVisionSensingComponent>(TEXT("VisionSensing"));
	HearingSenseComponent = CreateDefaultSubobject<UFGHearingSensingTargetComponent>(TEXT("HearingSenseComponent"));
	NavMovementComponent = CreateDefaultSubobject<UFGNavMovementComponent>(TEXT("NavMovementComponent"));
	DamageSenseComp = CreateDefaultSubobject<UFGDamageSensingComponent>(TEXT("DamageSenseComp"));
}

float AFGEnemy::GetDefaultHalfHeight() const
{
	// Don't scale...
	return Capsule->GetScaledCapsuleHalfHeight();
}

void AFGEnemy::BeginPlay()
{
	Super::BeginPlay();

}

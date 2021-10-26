#include "FGWeaponPickup.h"
#include "FGAI/Player/FGCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "Weapons/FGWeaponBase.h"
#include "FGAI/Audio/FGNoiseActor.h"

AFGWeaponPickUp::AFGWeaponPickUp()
{
	WeaponCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCapsule"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFGWeaponPickUp::OnCapsuleBeginOverlap);
	WeaponCapsule->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = WeaponCapsule;
	PickupSoundData.NoiseInstigator = this;
	
	
}

void AFGWeaponPickUp::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	auto* Player = Cast<AFGCharacter>(OtherActor);
	if (Player == nullptr)
		return;
	if (!Player->PickUpWeapon(WeaponType))
		return;
	Player->EquipWeapon(WeaponType);

	Destroy();
}
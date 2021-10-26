#pragma once
#include "GameFramework/Pawn.h"
#include "FGAI/AI/Sensing/Hearing/FGHearingSensingTargetComponent.h"
#include "FGWeaponPickup.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class AFGWeaponBase;
class AFGNoiseActor;
UCLASS()
class AFGWeaponPickUp : public APawn
{
public:	
	GENERATED_BODY()
	AFGWeaponPickUp();
	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AFGWeaponBase> WeaponType;
	UCapsuleComponent* WeaponCapsule;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	AFGWeaponBase* PickUpWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	FFGNoiseData PickupSoundData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TSubclassOf<AFGNoiseActor> PickupNoise;
};
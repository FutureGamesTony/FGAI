#pragma once
#include "DataAssets/FGHearingSenseSettings.h"
#include "GameFramework/Pawn.h"
#include "FGCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGMovementComponent;
class UFGDamageSensingComponent;
class AFGWeaponBase;
class AFFGGun;
class AFGNoiseActor;

UCLASS()
class AFGCharacter : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UFGMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = Damage)
	UFGDamageSensingComponent* DamageComponent;
	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TArray<AFGWeaponBase*> Weapons;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AFGWeaponBase* CurrentWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	AFGWeaponBase* WeaponComponent;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	int WeaponItterator = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	FFGNoiseData DebugNoiseData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	TSubclassOf<AFGNoiseActor> DebugNoiseToSpawn;
	/** First person camera */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	AFGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* WeaponAttachRoot;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	TArray<UStaticMeshComponent*>WeaponMeshes;
	virtual void Tick(float DeltaTime) override;
	bool PickUpWeapon(TSubclassOf<AFGWeaponBase> Type);
	void EquipWeapon(TSubclassOf<AFGWeaponBase> Type);
protected:
	virtual void BeginPlay();

protected:

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Gravity;

	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);



	void OnFire();

	void NextWeapon();
	void PreviousWeapon();
	
	void DebugSpawnNoiseActor();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UCapsuleComponent* GetCapsule() const { return Capsule; }

};


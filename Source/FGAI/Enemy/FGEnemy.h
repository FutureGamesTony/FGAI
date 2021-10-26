#pragma once
#include "GameFramework/Pawn.h"
#include "FGEnemy.generated.h"
USTRUCT(BlueprintType)
struct FFGEnemyProperties
{
	GENERATED_BODY()
	int CurrentHealth;
	int MaxHealth;
};

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGVisionSensingComponent;
class UFGNavMovementComponent;
class UFGHearingSensingTargetComponent;
class UFGDamageSensingComponent;

UCLASS()
class AFGEnemy : public APawn
{
	GENERATED_BODY()
public:
	AFGEnemy();

	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Vision)
	UFGVisionSensingComponent* VisionSensingComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Hearing)
	UFGHearingSensingTargetComponent* HearingSenseComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UFGNavMovementComponent* NavMovementComponent;

	UPROPERTY(EditAnywhere, Category = Damage)
	UFGDamageSensingComponent* DamageSenseComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	FFGEnemyProperties EnemySettings;

	virtual float GetDefaultHalfHeight() const override;

protected:
	virtual void BeginPlay();

	UCapsuleComponent* GetCapsule() const { return Capsule; }
};


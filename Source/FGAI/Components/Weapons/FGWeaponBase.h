#pragma once
#include "FGAI/DataAssets/FGDamageData.h"
#include "GameFramework/Actor.h"
#include "FGWeaponBase.generated.h"
class UStaticMeshComponent;
class UStaticMesh;
class AFGCharacter;
USTRUCT(BlueprintType)
struct FWeaponDebug
{
	GENERATED_BODY()
	TEnumAsByte<ETraceTypeQuery> TraceType;
};

USTRUCT(BlueprintType)
struct FWeaponProperties
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	EDamageType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int WeaponDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int Ammo = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int InClip = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int Clips = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int ClipMaxBullet = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int MaxAmmo = 0;

};
UCLASS(BlueprintType, Blueprintable, Meta = (BlueprintSpawnableComponent))
class AFGWeaponBase : public AActor
{
	GENERATED_BODY()
public:

	AFGWeaponBase();
	virtual void Fire() {}
	AFGCharacter* PlayerOwner;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	virtual void FireWeapon(FVector Location, FVector ForwardVector);
	virtual void Reload();
	
	UFUNCTION(BlueprintCallable)
	virtual int GetAmmunitionCurrentAmount();
	
	UFUNCTION(BlueprintCallable)
	virtual int GetAmmunitionMaxAmount();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStaticMeshComponent> WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponProperties WeaponProperties;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UStaticMeshComponent> GetWeaponMesh();
	virtual EDamageType GetDamageType();
	virtual EDamageType SetDamageType(EDamageType Type);

};


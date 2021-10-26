#pragma once
#include "Weapons/FGWeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FGRifle.generated.h"
UCLASS(BlueprintType, Blueprintable, Meta = (BlueprintSpawnableComponent))
class AFGRifle : public AFGWeaponBase
{
	GENERATED_BODY()

public:
	AFGRifle();
	
	UFUNCTION(BlueprintNativeEvent)
	void FireWeapon(FVector Location, FVector ForwardVector) override;
	UFUNCTION(BlueprintNativeEvent)
	void Reload() override;
	
	int GetAmmunitionCurrentAmount() override;
	int GetAmmunitionMaxAmount() override;
	
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;
	
	EDamageType GetDamageType() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	TEnumAsByte<EDrawDebugTrace::Type> DrawTrace;

private:
	EDamageType SetDamageType(EDamageType Type) override;

	int SetClipsAmount();


};
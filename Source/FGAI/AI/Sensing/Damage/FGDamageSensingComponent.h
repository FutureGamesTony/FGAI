#pragma once
#include "FGAI/DataAssets/FGDamageData.h"
#include "Components/ActorComponent.h"
#include "FGDamageSensingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGDamageSensingDelegate, const int&, Results);
UCLASS(BlueprintType, Blueprintable, Meta = (BlueprintSpawnableComponent))
class UFGDamageSensingComponent : public UActorComponent
{
public:
	GENERATED_BODY()
	UFGDamageSensingComponent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyDamage(int Damage);
	UPROPERTY(BlueprintAssignable)
	FFGDamageSensingDelegate OnDamageSensed;
private:

};


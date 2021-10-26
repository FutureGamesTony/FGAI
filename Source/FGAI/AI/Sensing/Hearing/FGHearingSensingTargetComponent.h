#pragma once
#include "Components/ActorComponent.h"
#include "DataAssets/FGHearingSenseSettings.h"
#include "FGHearingSensingTargetComponent.generated.h"

class AActor;
class AFGNoiseActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSensingDelegate, const FFGNoiseData&, Results);
UCLASS(BlueprintType, Blueprintable, Meta = (BlueprintSpawnableComponent))
class UFGHearingSensingTargetComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGHearingSensingTargetComponent();
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);


	UFUNCTION(BlueprintCallable, Category = Noise)
	static void NoiseHeard(FFGNoiseData& HearingResult);
	UFUNCTION(BlueprintCallable, Category = Hearing)
	void GetHearingSensingTargets(TArray<UFGHearingSensingTargetComponent*>& OutTargets, float dB);
	bool IsNoiseAudible();
	
	UPROPERTY(BlueprintAssignable)
	FFGHearingSensingDelegate OnTargetHeard;
	FFGNoiseData* NoiseSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hearing)
	UFGHearingSenseSettings* HearingSettings = nullptr;

	//TODO: Remove array
	static TArray<UFGHearingSensingTargetComponent*> HearingSensingComponents;
};
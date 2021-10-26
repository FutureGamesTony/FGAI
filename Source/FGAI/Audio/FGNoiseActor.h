#pragma once
#include "GameFramework/Actor.h"
#include "DataAssets/FGHearingSenseSettings.h"
#include "FGNoiseActor.generated.h"
class USphereComponent;
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class AFGNoiseActor : public AActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Noise)
	void SpawnNoise(FFGNoiseData NoiseData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bDrawDebugSphere = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	FFGNoiseData Noise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NoiseSphereRadius = 1.0f;
};
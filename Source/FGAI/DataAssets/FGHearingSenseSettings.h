#pragma once
#include "Engine/DataAsset.h"
#include "FGHearingSenseSettings.generated.h"
class USoundBase;
USTRUCT(BlueprintType)
struct FFGNoiseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* NoiseInstigator;

	/* Specific sound to be played*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;
	
	/* Rotation of the sound, based on the instigator and target */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator SoundRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SoundActorLocation;

	/*	
	SPL = Sound Pressure at Location (dB)
	dB = SPL1 when spawned
	SPL2 is the dB at location of HearingSensingTargetComponent
	SPL2 = SPL1 - 20 * log (R2 / R1)  
	R1 is set to 1 (m) simplifying the formula to
	SPL2 = SPL1 - 20 * log (R2)  
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hearing)
	float dB;

	/* Aproximate Value For Speed Of Sound in Air at 20 degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedOfSound = 332000.f;

	const static double ConvertMtoCMMultiple() { return 0.01; };
};
UCLASS()
class UFGHearingSenseSettings : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hearing | Alert")
	float dBEnterAlert = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hearing | Alert")
	float AlertStateMaxSeconds = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hearing | Detect")
	float dBEnterDetect = 25.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hearing | Detect")
	float dBAlertDetect = 15.0f;



};
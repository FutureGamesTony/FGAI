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

	/* 0.01 Watt = 100 dB  W/m^2 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0.00000001"))
	float Watt = 0.01f;

	/*
		dB = Sound Intensity = 10 log(I / IZero)
		IZero = 1/10^8 W/m^2
		I = Watt/Area 
		The intesity is calculated in "FGNoiseActor" 
		the dB variable is the result of the calculation.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hearing)
	float dB;

	/* Aproximate Value For Speed Of Sound in Air */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedOfSound = 332000.f;

	double IZero = 0.00000001;
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
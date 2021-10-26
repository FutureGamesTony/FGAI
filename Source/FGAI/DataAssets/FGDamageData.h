#pragma once
#include "Engine/DataAsset.h"
#include "UObject/Class.h"
#include "FGDamageData.generated.h"
/*	This is not relevant at the moment. In the 
	future I plan to have different properties 
	that are affected by the type
 */
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	ENormal,
	ESlashing,
	EPiercing,
	Poison,
	EFreezing,
	EBurning,
};
UCLASS()
class UFGDamageData : public UDataAsset
{
public:
	GENERATED_BODY()

};
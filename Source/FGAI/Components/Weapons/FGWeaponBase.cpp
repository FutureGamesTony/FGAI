#include "FGWeaponBase.h"
AFGWeaponBase::AFGWeaponBase()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}
void AFGWeaponBase::FireWeapon(FVector Location, FVector ForwardVector)
{

}

void AFGWeaponBase::Reload()
{

}
int AFGWeaponBase::GetAmmunitionCurrentAmount()
{
	return 0;
}
int AFGWeaponBase::GetAmmunitionMaxAmount()
{
	return 0;
}
TSubclassOf<UStaticMeshComponent> AFGWeaponBase::GetWeaponMesh()
{
	return WeaponMesh;
}
EDamageType AFGWeaponBase::GetDamageType()
{
	return EDamageType::ENormal;
}
EDamageType AFGWeaponBase::SetDamageType(EDamageType type)
{
	return type;
}
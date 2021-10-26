#include "FGDamageSensingComponent.h"
UFGDamageSensingComponent::UFGDamageSensingComponent()
{

}
int* dmg = nullptr;
void UFGDamageSensingComponent::ApplyDamage_Implementation(int Damage)
{
	dmg = &Damage;
	if(dmg)
	OnDamageSensed.Broadcast(*dmg);
	dmg = nullptr;
}
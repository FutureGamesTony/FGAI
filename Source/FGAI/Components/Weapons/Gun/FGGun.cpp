#include "FGGun.h"
#include "Player/FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Damage/FGDamageSensingComponent.h"
AFGGun::AFGGun()
{
	SetDamageType(EDamageType::ENormal);
	
}
void AFGGun::FireWeapon_Implementation(FVector Location, FVector ForwardVector)
{
	if (WeaponProperties.InClip <= 0)
	{
		Reload_Implementation();
		return;
	}
	FTransform CamTransform = PlayerOwner->FirstPersonCameraComponent->GetComponentTransform();
	FVector Start = CamTransform.GetLocation();
	FVector Finish = Start + CamTransform.GetRotation().GetForwardVector() * 20000.f;
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(PlayerOwner, Start, Finish, TraceType, false, TArray<AActor*>(), DrawTrace, Hit, true);

	
	if (Hit.bBlockingHit)
	{
		UFGDamageSensingComponent* dmgComp = nullptr;
		for (auto* dmg : Hit.GetActor()->GetComponents())
		{
			dmgComp = Cast<UFGDamageSensingComponent>(dmg);
			if(dmgComp != nullptr)
				break;
		}
		if(dmgComp)
		 dmgComp->ApplyDamage_Implementation(WeaponProperties.WeaponDamage);
	}
	WeaponProperties.InClip--;
}
void AFGGun::Reload_Implementation()
{
	if (WeaponProperties.Clips < 0)
	{
		return;
	}
	SetClipsAmount();
}
int AFGGun::GetAmmunitionCurrentAmount()
{
	return WeaponProperties.Ammo;
}
int AFGGun::GetAmmunitionMaxAmount()
{
	return WeaponProperties.MaxAmmo;
}
EDamageType AFGGun::GetDamageType()
{
	return WeaponProperties.WeaponType;
}
int AFGGun::SetClipsAmount()
{
	if(WeaponProperties.InClip == WeaponProperties.ClipMaxBullet)
		return WeaponProperties.Clips;
	WeaponProperties.Clips = WeaponProperties.Ammo / WeaponProperties.ClipMaxBullet;

	if(WeaponProperties.InClip < WeaponProperties.ClipMaxBullet)
	{
		WeaponProperties.InClip = WeaponProperties.Ammo % WeaponProperties.ClipMaxBullet;
		if (WeaponProperties.InClip == 0)
		{
			WeaponProperties.Clips--;
			WeaponProperties.InClip = WeaponProperties.ClipMaxBullet;
			WeaponProperties.Ammo -= WeaponProperties.ClipMaxBullet;
		}
		else
		{
			WeaponProperties.Ammo -= WeaponProperties.ClipMaxBullet - WeaponProperties.InClip;
			WeaponProperties.InClip = WeaponProperties.ClipMaxBullet;
		}
	}
	return WeaponProperties.Clips;
}
EDamageType AFGGun::SetDamageType(EDamageType Type)
{
	WeaponProperties.WeaponType = Type;
	return WeaponProperties.WeaponType;
	
}
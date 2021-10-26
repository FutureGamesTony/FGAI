#include "FGRifle.h"
#include "Player/FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Sensing/Damage/FGDamageSensingComponent.h"
AFGRifle::AFGRifle()
{
	SetDamageType(EDamageType::ENormal);
	
}
void AFGRifle::FireWeapon_Implementation(FVector Location, FVector ForwardVector)
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

		UFGDamageSensingComponent* dmgComp = Cast<UFGDamageSensingComponent>(Hit.Component);
		if(dmgComp)
		 dmgComp->ApplyDamage_Implementation(WeaponProperties.WeaponDamage);
	}
	WeaponProperties.InClip--;
}
void AFGRifle::Reload_Implementation()
{
	if (WeaponProperties.Clips < 0)
	{
		return;
	}
	SetClipsAmount();
}
int AFGRifle::GetAmmunitionCurrentAmount()
{
	return WeaponProperties.Ammo;
}
int AFGRifle::GetAmmunitionMaxAmount()
{
	return WeaponProperties.MaxAmmo;
}
EDamageType AFGRifle::GetDamageType()
{
	return WeaponProperties.WeaponType;
}
int AFGRifle::SetClipsAmount()
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
EDamageType AFGRifle::SetDamageType(EDamageType Type)
{
	WeaponProperties.WeaponType = Type;
	return WeaponProperties.WeaponType;
	
}
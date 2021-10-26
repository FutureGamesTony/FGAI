#include "FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGMovementComponent.h"
#include "Weapons/FGWeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Audio/FGNoiseActor.h"
#include "FGAI/FGMovementStatics.h"


AFGCharacter::AFGCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 2.5f;
	BaseLookUpRate = 2.5f;

	Speed = 1000.0f;
	Gravity = 900.0f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(Capsule);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	WeaponAttachRoot = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttach"));
	WeaponAttachRoot->SetupAttachment(FirstPersonCameraComponent);

	MovementComponent = CreateDefaultSubobject<UFGMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(Capsule);
}

void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	FFGFrameMovement FrameMovement = MovementComponent->CreateFrameMovement();
	
	FrameMovement.AddGravity(Gravity * DeltaTime);

	if (!InputVector.IsNearlyZero())
	{
		FVector Forward = FVector::VectorPlaneProject(FirstPersonCameraComponent->GetForwardVector(), FVector::UpVector);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector Right = FirstPersonCameraComponent->GetRightVector() * InputVector.Y;
		FVector Velocity = (ForwardMovement + Right).GetSafeNormal() * Speed * DeltaTime;
		FrameMovement.AddDelta(Velocity);
	}
	
	MovementComponent->Move(FrameMovement);
}

void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AFGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// set up weapon key bindings
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFGCharacter::OnFire);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AFGCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AFGCharacter::NextWeapon);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently

	PlayerInputComponent->BindAxis("Turn", this, &AFGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFGCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("DebugSpawnNoiseActor", IE_Pressed, this, &AFGCharacter::DebugSpawnNoiseActor);

}



void AFGCharacter::MoveForward(float Value)
{
	InputVector.X = Value;
}

void AFGCharacter::MoveRight(float Value)
{
	InputVector.Y = Value;
}

void AFGCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate);
}

void AFGCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate);
}

void AFGCharacter::OnFire()
{
	if(Weapons.Num() == 0)
		return;
	const FVector EndLoc = FVector(GetActorLocation().X + GetActorForwardVector().X * 1000, GetActorLocation().Y + GetActorForwardVector().Y * 1000, GetActorLocation().Z);

	if(Weapons[WeaponItterator] != WeaponComponent)
	{

		WeaponComponent = Weapons[WeaponItterator];
		return;
	}
	WeaponComponent->FireWeapon(FirstPersonCameraComponent->GetComponentLocation(), GetActorForwardVector());
	
	
}
void AFGCharacter::PreviousWeapon()
{
	if (Weapons.Num() == 0)
		return;
	WeaponItterator--;
	if (WeaponItterator == -1)
	WeaponItterator = Weapons.Num()-1;
	

	
}
void AFGCharacter::NextWeapon()
{
	if(Weapons.Num() == 0)
		return;
	if (Weapons.Num() == 0) return;
	Weapons[WeaponItterator]->SetActorHiddenInGame(true);
	WeaponItterator++;
	WeaponItterator = (WeaponItterator % Weapons.Num() == 0) ? 0 : WeaponItterator;

	Weapons[WeaponItterator]->SetActorHiddenInGame(false);

}

void AFGCharacter::EquipWeapon(TSubclassOf<AFGWeaponBase> Type)
{
	auto* Weapon = GetWorld()->SpawnActor<AFGWeaponBase>(Type);
	Weapon->PlayerOwner = this;
	Weapon->SetActorHiddenInGame(true);
	Weapons.Add(Weapon);
	Weapon->AttachToComponent(WeaponAttachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
bool AFGCharacter::PickUpWeapon(TSubclassOf<AFGWeaponBase> Type)
{

	for (auto* Weapon : Weapons)
	{
		if (Weapon->IsA(Type))
			return false;
	}
	return true;

}
void AFGCharacter::DebugSpawnNoiseActor()
{
	const FVector Loc = GetActorLocation();
	const FRotator Rot = GetActorRotation();
	DebugNoiseData.SoundActorLocation = GetActorLocation();
	DebugNoiseData.SoundRotation = GetActorRotation();
	DebugNoiseData.NoiseInstigator = this;
	AFGNoiseActor* noise = Cast<AFGNoiseActor>(GetWorld()->SpawnActor(DebugNoiseToSpawn, &Loc, &Rot));
	

	noise->SpawnNoise_Implementation(DebugNoiseData);
	
}
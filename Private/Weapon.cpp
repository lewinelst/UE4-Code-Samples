// Weapon.cpp
// Lewin Elston 2022.


#include "Weapon.h"
#include "LineTrace.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = MeshComp;

	LineTraceComp = CreateDefaultSubobject<ULineTrace>("LineTraceComponent");
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponDataTable)
	{
		static const FString PString = FString("SMGDT");
		WeaponData = WeaponDataTable->FindRow<FWeaponData>(FName("SMG"), PString, true);
		if (WeaponData)
		{
			MeshComp->SetSkeletalMesh(WeaponData->WeaponMesh);
		}
	}
	
}

FHitResult AWeapon::Fire()
{
	if (WeaponData && WeaponData->FireAnimation)
	{
		MeshComp->PlayAnimation(WeaponData->FireAnimation, false);
	}

	FVector StartLocation = MeshComp->GetSocketLocation(FName("MuzzleSocket"));
	FRotator Rotation = MeshComp->GetSocketRotation(FName("MuzzleSocket"));
	FVector EndLocation = StartLocation + Rotation.Vector() * 1500.0f;

	return LineTraceComp->LineTraceSingle(StartLocation, EndLocation, true);
}
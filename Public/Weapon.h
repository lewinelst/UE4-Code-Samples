// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
		FString WeaponName;

	UPROPERTY(EditAnywhere)
		class UAnimationAsset* FireAnimation;
};

UCLASS()
class TERRAINTECH_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	class USkeletalMeshComponent* MeshComp;

	class ULineTrace* LineTraceComp;

	UPROPERTY(EditAnywhere)
		class UDataTable* WeaponDataTable;

	FWeaponData* WeaponData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FHitResult Fire();


};

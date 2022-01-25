// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TERRAINTECH_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		class UAnimationAsset* FireAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Fire();


};

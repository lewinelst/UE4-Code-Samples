// GameCharacter.h
// Lewin Elston 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class TERRAINTECH_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* BoomArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void CheckJump();
	UPROPERTY()
		bool Jumping;

	void ToggleCrouch();

	void ToggleSprint();
	UPROPERTY()
		bool Sprinting;

	float WalkSpeed;
	float RunSpeed;

	float TurnRate;
	float LookRate;

	// Weapon stuff
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeapon> WeaponClass;

	class AWeapon* Weapon;

	void Attack();

	UFUNCTION(BlueprintCallable)
		bool GetHasWeapon();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// GameCharacter 
// Lewin

#include "GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Public/Weapon.h"


// Sets default values (Constructor) 
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 380.f;
	BoomArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(8, 540, 8);

	WalkSpeed = 325.0f; 
	RunSpeed = 500.0f;

	TurnRate = 45;
	LookRate = 45;

	Sprinting = false; 
	Jumping = false;
	
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Weapon spawning. 
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (WeaponClass)
	{
		FTransform WeaponTransform;
		WeaponTransform.SetLocation(FVector::ZeroVector);
		WeaponTransform.SetRotation(FQuat(FRotator::ZeroRotator));

		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, WeaponTransform, SpawnParams);
		if (Weapon)
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
		}
	}
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Movement & Camera
	PlayerInputComponent->BindAxis("MoveForward", this, &AGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGameCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//Sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AGameCharacter::ToggleSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AGameCharacter::ToggleSprint);

	//Jumping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGameCharacter::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGameCharacter::CheckJump);

	//Crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AGameCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AGameCharacter::ToggleCrouch);

	//Attack (Add Released for full auto implementation) 
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGameCharacter::Attack);

}

void AGameCharacter::MoveForward(float Value)
{
	if (Controller != NULL && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);

		//Changes speed of movement based on direction. 
		if (FVector::DotProduct(GetActorForwardVector(), GetVelocity()) >= 0)
		{

			AddMovementInput(direction, Value);

		}
		else 
		{
			AddMovementInput(direction, (Value / 2)); //Edit denominator value to change backwards speed
		}
		
	}
}

void AGameCharacter::MoveRight(float Value)
{
	if (Controller != NULL && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

		//AddMovementInput(direction, Value);
		
		//Changes speed of movement based on direction. 
		if (FVector::DotProduct(GetActorForwardVector(), GetVelocity()) >= 0)
		{
			AddMovementInput(direction, Value);
		}
		else 
		{
			AddMovementInput(direction, (Value / 2)); //Edit denominator value to change backwards speed
		}
	}
}

void AGameCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void AGameCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void AGameCharacter::CheckJump()
{
	if (Jumping)
	{
		Jumping = false;
	}
	else 
	{
		Jumping = true; 
	}
}

void AGameCharacter::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else 
	{
		Crouch();
	}
}

void AGameCharacter::ToggleSprint()
{
	if (Sprinting)
	{
		Sprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; // Walk/Jog Speed 
	} 
	else
	{
		Sprinting = true; 
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed; // Sprint Speed 
	}
}

void AGameCharacter::Attack()
{
	if (Weapon)
	{
		FHitResult HitResult = Weapon->Fire();
	}
}

bool AGameCharacter::GetHasWeapon()
{
	if (Weapon)
	{
		return true;
	}
	else 
	{
		return false;
	}
}


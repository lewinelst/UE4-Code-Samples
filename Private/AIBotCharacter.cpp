// Lewin Elston 2022


#include "AIBotCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIBotCharacter::AAIBotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	WalkSpeed = 200.f;
	RunSpeed = 400.f;


	GetCharacterMovement()->MaxWalkSpeed = 200.f;



}

// Called when the game starts or when spawned
void AAIBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIBotCharacter::WalkRunChange(bool SetToRun) //Sets to run speed if true or sets to walk speed if false
{
	if (SetToRun == false)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

// Called every frame
void AAIBotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIBotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


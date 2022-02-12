// Lewin Elston 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBotCharacter.generated.h"

UCLASS()
class TERRAINTECH_API AAIBotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBotCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWaypoint* NextWaypoint;

	void WalkRunChange(bool SetToRun);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float WalkSpeed;
	float RunSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

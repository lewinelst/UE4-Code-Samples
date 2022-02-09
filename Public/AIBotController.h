// Lewin Elston 2022

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBotController.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINTECH_API AAIBotController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIBotController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* AIPawn) override; 

	virtual void Tick(float DeltaSeconds) override;

	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;


};

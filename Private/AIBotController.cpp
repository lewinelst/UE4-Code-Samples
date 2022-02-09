// Lewin Elston 2022


#include "AIBotController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIBotController::AAIBotController()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIBotController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AAIBotController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Systems Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Systems Aren't Set"));
	}
}

void AAIBotController::OnPossess(APawn* AIPawn)
{
	Super::OnPossess(AIPawn);
}

void AAIBotController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AAIBotController::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(0.0f, 0.0f, 0.0f);
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
	
}

void AAIBotController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{

}




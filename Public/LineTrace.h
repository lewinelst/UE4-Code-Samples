// LineTrace.h
// Lewin Elston 2022.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTrace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERRAINTECH_API ULineTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULineTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	FHitResult LineTraceSingle(FVector Start, FVector End);
	FHitResult LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine);
};

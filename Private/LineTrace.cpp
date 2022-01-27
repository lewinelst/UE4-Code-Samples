// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTrace.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
// Sets default values for this component's properties
ULineTrace::ULineTrace()
{

}


// Called when the game starts
void ULineTrace::BeginPlay()
{
	Super::BeginPlay();

	
}

FHitResult ULineTrace::LineTraceSingle(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisisonParams;
	FCollisionQueryParams CollisisionQueryParams;
	CollisisionQueryParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		Start,
		End,
		CollisisonParams,
		CollisisionQueryParams
	))
	{
		return HitResult;
	}
	else 
	{
		return HitResult;
	}
}

FHitResult ULineTrace::LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine) //Creates visible line for debugging for the line trace. 
{
	FHitResult Actor = LineTraceSingle(Start, End);
	if (ShowDebugLine)
	{
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor::Red,
			false,
			3.0f,
			0,
			3.0f
		);
	}

	return Actor;
}



https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/Engine.h"



void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//null checks
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) )
	{
		return; 
	}

	FVector MovementThisFrame = ConsumeInputVector() * DeltaTime * DirectionalSpeed;
	//MovementThisFrame.Y = 0; 
		
	//UE_LOG(LogTemp, Warning, TEXT("MovementThisFrame %s"), *MovementThisFrame.ToString());
	
	if (!MovementThisFrame.IsNearlyZero() )
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(MovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
		

		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("HIT %s"), *Hit.ImpactPoint.ToString());
			GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, DebugMessage);

		}
		if (Hit.IsValidBlockingHit())
		{
			
			SlideAlongSurface(MovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
	
}



void UTankMovementComponent::AddTurnVector (float add)
{
	Turn += add; 
}

float UTankMovementComponent::ConsumeTurnVector()
{
	float result = Turn; 
	Turn = 0; 
	return result; 
}




https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"

#include "TankMovementComponent.generated.h"



/**
 * 
 */
UCLASS()
class TANKW1W2_API UTankMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

		virtual void TickComponent
		(
			float DeltaTime,
			enum ELevelTick TickType,
			FActorComponentTickFunction * ThisTickFunction
		) override; 
	
	
public:

	float DirectionalSpeed = 200.0f;
	float AngularSpeed = 5.0f;
	
	float Blocked = false; 
public: 

	void AddTurnVector (float add);
	float ConsumeTurnVector(); 		
	
protected:
	float Turn; 
};

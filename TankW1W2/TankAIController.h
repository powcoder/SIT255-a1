https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseTank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKW1W2_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private: 
		ABaseTank *player; 
		ABaseTank *controlledTank;
		float currentAngle;

public:
	ATankAIController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//get the player tank
	ABaseTank* GetPlayerTank() const; 


};

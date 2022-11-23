https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKW1W2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

	//return the tank point
	ABaseTank* GetTank() const; 
	
};

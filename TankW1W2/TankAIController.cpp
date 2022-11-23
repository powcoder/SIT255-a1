https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller created"));
}



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller BeginPlay"));

	player = GetPlayerTank();
	controlledTank = Cast<ABaseTank>(GetPawn());

	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Access to player %s"), *player->GetName());
	}

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	player = GetPlayerTank();
	controlledTank = Cast<ABaseTank>(GetPawn());

	if (player && controlledTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI Controller tick"));
		controlledTank->AimAt(player->GetActorForwardVector());
	}
}


ABaseTank* ATankAIController::GetPlayerTank() const
{
	if (GetWorld() && GetWorld()->GetFirstPlayerController()) {
		AActor* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (playerPawn)
		{
			return Cast<ABaseTank>(playerPawn);
		}
	}
	return NULL; 

}



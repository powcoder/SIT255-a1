https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "TankSpawner.h"
#include "Engine/World.h"
#include "TankW1W2.h"




// Sets default values
ATankSpawner::ATankSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfTanks = 10; 
	MaxWidthFloor = 5000; 
	MaxDepthFloor = 5000; 
	Height = 20; 
}

// Called when the game starts or when spawned
void ATankSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnTanks();
}

// Called every frame
void ATankSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FVector ATankSpawner::GetRandomLocation()
{
	return FVector(FMath::RandRange(-MaxWidthFloor, MaxWidthFloor),
		FMath::RandRange(-MaxDepthFloor, MaxDepthFloor),
		Height); 

}


FRotator ATankSpawner::GetRandomRotation()
{

	return FRotator(0, FMath::RandRange(-180, 180), 0);

}


void ATankSpawner::SpawnTanks()
{
	if (TankBP != NULL)
	{
		if (GetWorld() != NULL)
		{
			FActorSpawnParameters sparams;
			sparams.Owner = this;

			for (int i = 0; i < NumberOfTanks; i++)
			{
							
				UE_LOG(LogTemp, Warning, TEXT("Spawning tanks"));
				UE_LOG(LogTank, Verbose, TEXT("Creating tanks no %d"), i); 

				FVector location = GetRandomLocation();
				FRotator rotator = GetRandomRotation(); 
				ABaseTank* tank = GetWorld()->SpawnActor<ABaseTank>(TankBP,
					location, rotator, sparams);

			}
		}
	}

}
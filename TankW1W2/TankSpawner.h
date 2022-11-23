https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTank.h"
#include "TankSpawner.generated.h"


UCLASS()
class TANKW1W2_API ATankSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Tank", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ABaseTank> TankBP;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY (Category = "Tank", EditAnywhere, BlueprintReadWrite)
		int32 NumberOfTanks;

	UPROPERTY(Category = "Tank", EditAnywhere, BlueprintReadWrite)
		int32 MaxWidthFloor; 

	UPROPERTY(Category = "Tank", EditAnywhere, BlueprintReadWrite)
		int32 MaxDepthFloor;

	UPROPERTY(Category = "Tank", EditAnywhere, BlueprintReadWrite)
		int32 Height; 

	void SpawnTanks(); 

	//get random location 
	FVector GetRandomLocation(); 

	//get random yaw rotation
	FRotator GetRandomRotation();

	
};

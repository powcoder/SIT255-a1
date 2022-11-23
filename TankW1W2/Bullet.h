https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Bullet.generated.h"

UCLASS()
class TANKW1W2_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* body; 

	//speed of the bullet
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed = 500; 

	//directional vector
	FVector Direction; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USphereComponent* collisionComponent; 


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//method to control the shooting
	void Shoot();


	
};

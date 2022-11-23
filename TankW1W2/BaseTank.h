https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankMovementComponent.h"
#include "Components/InputComponent.h"
#include "Bullet.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "BaseTank.generated.h"

DECLARE_STATS_GROUP(TEXT("Tank Stats"), STATGROUP_TankManagement, STATCAT_Advanced);


UCLASS()
class TANKW1W2_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//vector to store movement from keyboard
	FVector2D MovementInput;

	float rotation; 

	UTankMovementComponent* MovementComponent; 

	//archetype bullet blueprint class
	UPROPERTY(Category = "Bullet", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ABullet> BulletBP; 
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent *camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* collisionComponent; 

	                                                                                                                                                     
	//speed of movement
	UPROPERTY (Category = "Speed", EditAnywhere, BlueprintReadWrite)
		float MovementSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MeshBounds; 

	//Move the actor left or right based on keyboard input
	void MoveRight(float val);

	//Move the actor left or right based on keyboard input
	void MoveForward(float val);

	//Getter method for movement component
	virtual UPawnMovementComponent* GetMovementComponent() const override; 
	
	//shoot bullets by spawning
	void SpawnBullets();
	
	//turn the tank towards a location
	void AimAt(FVector location); 

	UFUNCTION()
		void OnComponentBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};

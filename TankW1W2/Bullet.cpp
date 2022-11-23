https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialise static mesh
	body = CreateDefaultSubobject<UStaticMeshComponent>("body"); 
	this->RootComponent = body; 

	//collision component
	collisionComponent = CreateDefaultSubobject<USphereComponent>("bullet collision");
	collisionComponent->SetSphereRadius(60); 
	collisionComponent->SetupAttachment(body);
	collisionComponent->bGenerateOverlapEvents = true; 


		
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector MovementThisFrame = this->GetActorForwardVector() * Speed * DeltaTime; 
	this->SetActorLocation(this->GetActorLocation() + MovementThisFrame); 
	
}




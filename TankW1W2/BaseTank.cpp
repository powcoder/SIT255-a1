https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTank.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"

DECLARE_CYCLE_STAT(TEXT("Tank Shoot"), STAT_TankShoot, STATGROUP_TankManagement);

#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel1


// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	//initialise body and cameara
	body = CreateDefaultSubobject<UStaticMeshComponent>("body");
	RootComponent = body;
	body->SetSimulatePhysics(false); 
	camera = CreateDefaultSubobject<UCameraComponent>("camera");

	springArm = CreateDefaultSubobject<USpringArmComponent>("springarm");
	springArm->SetupAttachment(RootComponent);
		
	springArm->TargetArmLength = 1500.0f;
	springArm->RelativeLocation = FVector(0.f, 0.f, 0.f);
	springArm->RelativeRotation = FRotator(-45.f, 0.0f, 0.0f);
	

	/*
	//hard code mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(
		TEXT("StaticMesh'/Game/StaticMesh/Tanks/tank_hover.tank_hover'"));
	if (Asset.Succeeded())
	{
		body->SetStaticMesh(Asset.Object); 		
	}
	*/

	camera->SetupAttachment(springArm);
	
	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>("movementcomponent");
	MovementComponent->UpdatedComponent = RootComponent;
	//MovementComponent->DirectionalSpeed = this->MovementSpeed; 

	collisionComponent = CreateDefaultSubobject<UBoxComponent>("collision component");
	//collisionComponent->SetBoxExtent(FVector(100, 100, 100)); 
	collisionComponent->bGenerateOverlapEvents = true; 
	collisionComponent->SetupAttachment(body); 
	collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTank::OnComponentBeginOverlap);
	
}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();
	FVector origin;
	FVector boxExtent; 
	this->GetActorBounds(true, origin, boxExtent);
	collisionComponent->SetBoxExtent(boxExtent); 

	MovementComponent->DirectionalSpeed = this->MovementSpeed;
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//move actor
	
	if (!MovementInput.IsZero()) {
		FVector NewLocation = this->GetActorLocation();
		NewLocation += this->GetActorForwardVector() * MovementInput.X * MovementSpeed;
		RootComponent->SetWorldLocation(NewLocation);
	}

	if (rotation > 5)
	{

		FRotator NewRotation = GetActorRotation();
		NewRotation.Add(0, 1, 0);
		//NewRotation.Yaw = angle;
		SetActorRotation(NewRotation);
		

	}
}

// Called to bind functionality to input
void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("TankMoveRight", this, &ABaseTank::MoveRight);
	PlayerInputComponent->BindAxis("TankMoveForward", this, &ABaseTank::MoveForward);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseTank::SpawnBullets);
}

void ABaseTank::MoveRight(float val)
{
	//save movement to value
	//MovementInput.Y = FMath::Clamp<float>(val, -1.0f, 1.0f);

	//add turn vector
	/*
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		
		MovementComponent->AddTurnVector(val);
	}
	*/
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += val;
	SetActorRotation(NewRotation);


	/*
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("MovementThisFrame %s"), *NewRotation.ToString());
		GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Green, DebugMessage);

	}
	*/
		
	

}


void ABaseTank::MoveForward(float val)
{
	//MovementInput.X = FMath::Clamp<float>(val, -1.0f, 1.0f);

	//add input vector
	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * val);
	}

}

UPawnMovementComponent* ABaseTank::GetMovementComponent() const {
	return MovementComponent;
}



void ABaseTank::SpawnBullets()
{
	SCOPE_CYCLE_COUNTER(STAT_TankShoot);
	//null check
	if (BulletBP != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bullet"));
		const UWorld* world = this->GetWorld();

		if (world)
		{
			FActorSpawnParameters sparams;
			sparams.Owner = this; 
			sparams.Instigator = this;

			//get socket location and rotation
			TArray<FName> sockets = body->GetAllSocketNames();


			if (sockets[0] == TEXT("BulletSocket"))
			{
				FVector SocketLocation = body->GetSocketLocation(sockets[0]);
				FRotator SocketRotation = body->GetSocketRotation(sockets[0]);

				ABullet *bullet = GetWorld()->SpawnActor<ABullet>(BulletBP,
					SocketLocation, SocketRotation, sparams);
			}			
		}
	}
}


void ABaseTank::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped!!")); 

	if (OtherActor->IsA(ABullet::StaticClass()))
	{
		//cast the other actor to bullet
		ABullet* bullet = Cast<ABullet>(OtherActor);
		AActor* instigator = bullet->GetInstigator();

		if (instigator && !instigator->GetName().Equals(this->GetName()))
		{
			//destroy the tank
			this->Destroy();
			bullet->Destroy();
		}
		
	}

}


void ABaseTank::AimAt(FVector target)
{
	//calcuate the angle between forward vector and the new target
	FVector desired = this->GetActorLocation(); 
	desired.Normalize();
	target.Normalize();
	
	float dp = FVector::DotProduct(desired, target); 
	
	rotation =FMath::RadiansToDegrees<float>( FMath::Acos(dp));
	UE_LOG(LogTemp, Warning, TEXT("angle %f"),  rotation);

		
}
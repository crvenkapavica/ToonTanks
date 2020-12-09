#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	SpringArm->AddLocalRotation(FQuat(FRotator(-15.f, 0.f, 0.f)), false);
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Cast<APlayerControllerBase>(PlayerController)->bIsPlayerAlive)
	{
		Rotate();
		Strafe();
		Move();
	}
	
	if (PlayerController)
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		RotateTurret(Hit.ImpactPoint);
	}

}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("StrafeForward", this, &APawnTank::CalculateStrafeInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateDirection);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}

void APawnTank::CalculateStrafeInput(float Value)
{
	int Strafe = Value ? 1 : 0;
	StrafeDirection = FVector(Strafe * StrafeSpeed * GetWorld()->DeltaTimeSeconds, Value * StrafeSpeed * GetWorld()->DeltaTimeSeconds, 0.f);
}

void APawnTank::CalculateRotateDirection(float Value)
{
	float RotationValue = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation{ 0.f, RotationValue, 0.f };
	RotateDirection = FQuat{ Rotation };
}


void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Strafe()
{
	AddActorLocalOffset(StrafeDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotateDirection);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

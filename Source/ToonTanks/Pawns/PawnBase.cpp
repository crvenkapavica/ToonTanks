#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector TargetLocation)
{
	FVector StartLocation{ TurretMesh->GetComponentLocation().X, TurretMesh->GetComponentLocation().Y, 0 };
	FRotator Rotation = (FVector(TargetLocation.X, TargetLocation.Y, 0) - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(FQuat(Rotation), false);
}

void APawnBase::RotateBase(FRotator Rotation)
{
	BaseMesh->AddLocalRotation(Rotation);
}

void APawnBase::Fire()
{
	if (ProjectileClass)
	{
		FVector Location{ ProjectileSpawnPoint->GetComponentLocation() };
		FRotator Rotation{ ProjectileSpawnPoint->GetComponentRotation() };
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
		TempProjectile->SetOwner(this);
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
	}
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

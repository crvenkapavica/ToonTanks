#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APawnTurret::APawnTurret()
{

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFireCondition();
}

float APawnTurret::DistanceToPlayer()
{
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || DistanceToPlayer() > FireRange || !PlayerPawn->GetIsPlayerAlive())
	{
		if (FireTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		}
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
	if (!FireTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &APawnBase::Fire, 0.22f, true, 0);
		UE_LOG(LogTemp, Warning, TEXT("Starting Timer"));
	}
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}



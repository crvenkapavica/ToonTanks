#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
class ATankGameModeBase;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerPawn;
	ATankGameModeBase* GameMode;
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere)
	float FireRange = 500.f;

	void CheckFireCondition();
	float DistanceToPlayer();

	FTimerHandle Handle;

public:
	APawnTurret();
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

};

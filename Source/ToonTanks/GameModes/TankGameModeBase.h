#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	APawnTank* PlayerTank;
	int32 TurretsLeft = 0;

	void HandleGameStart();
	void HandleGameOver(bool bPlayerWon);

public:
	void ActorDied(AActor* DeadActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Loop")
	float StartDelay = 0.f;

	APlayerControllerBase* PlayerController;

	int32 GetTurretCount();

	UFUNCTION(BlueprintCallable)
	float GetStartDelay();
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);
};

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerInputEnabled(bool bPlayerInputEnabled)
{
	if (bPlayerInputEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bIsPlayerAlive = bPlayerInputEnabled;
	bShowMouseCursor = bPlayerInputEnabled;
}

#include "RDPlayerState.h"
#include "Net/UnrealNetwork.h"

void ARDPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARDPlayerState, RemainingAttempts);
}

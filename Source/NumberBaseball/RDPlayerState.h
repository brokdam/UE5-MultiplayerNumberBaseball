#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RDPlayerState.generated.h"

UCLASS()
class NUMBERBASEBALL_API ARDPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
	int32 RemainingAttempts = 3;
	
	UPROPERTY(Replicated)
	bool bGameOver = false;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

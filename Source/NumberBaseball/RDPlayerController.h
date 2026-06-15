#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RDPlayerController.generated.h"

struct FRDGuessResult;

UCLASS()
class NUMBERBASEBALL_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(Server, Reliable)
	void ServerSubmitGuess(const FString& Guess);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastReceiveResult(const FRDGuessResult& Result, int32 AttemptsLeft);
	
protected:
	virtual void SetupInputComponent() override;
	void OnTestSubmit();
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RDPlayerController.generated.h"

UCLASS()
class NUMBERBASEBALL_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(Server, Reliable)
	void ServerSubmitGuess(const FString& Guess);
	
protected:
	virtual void SetupInputComponent() override;
	void OnTestSubmit();
};

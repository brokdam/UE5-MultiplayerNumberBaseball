// RDGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RDGameMode.generated.h"

UCLASS()
class NUMBERBASEBALL_API ARDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	ARDGameMode();

protected:
	virtual void BeginPlay() override;

private:
	TArray<int32> Answer;
	void GenerateRandomNumbers();
	FString CheckAnswer(const FString& Input) const;
	bool IsValidInput(const FString& Input) const;
};

// RDGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RDGameMode.generated.h"

USTRUCT(BlueprintType)
struct FRDGuessResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	int32 Strike = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Ball = 0;
};

UCLASS()
class NUMBERBASEBALL_API ARDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	ARDGameMode();
	void ProcessGuess(const FString& Input);
	bool bGameOver = false;

protected:
	virtual void BeginPlay() override;

private:
	TArray<int32> Answer;
	int32 RemainingAttempts = 3; 
	
	void GenerateRandomNumbers();
	FRDGuessResult CheckAnswer(const FString& Input) const;
	bool IsValidInput(const FString& Input) const;
	void ResetGame();
};

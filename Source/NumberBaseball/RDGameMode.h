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
	// 데이터
	TArray<int32> Answer;
	int32 RemainingAttempts = 3; // 임시

	// 함수
	void GenerateRandomNumbers();
	FString CheckAnswer(const FString& Input) const;
	bool IsValidInput(const FString& Input) const;
	void ResetGame();
	void ProcessGuess(const FString& Input);
};

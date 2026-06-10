// RDGameMode.cpp

#include "RDGameMode.h"
#include "RDPlayerController.h"
#include "RDPlayerState.h"
#include "RDGameState.h"

ARDGameMode::ARDGameMode()
{
	PlayerControllerClass = ARDPlayerController::StaticClass();
	PlayerStateClass = ARDPlayerState::StaticClass();
	GameStateClass = ARDGameState::StaticClass();
}

void ARDGameMode::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomNumbers();

	UE_LOG(LogTemp, Warning, TEXT("Answer: %d %d %d"), Answer[0], Answer[1], Answer[2]);
	UE_LOG(LogTemp, Warning, TEXT("429 -> %s"), *CheckAnswer(TEXT("429")));
}

void ARDGameMode::GenerateRandomNumbers()
{
	TArray<int32> Candidates = { 1,2,3,4,5,6,7,8,9 };

	for (int32 i = Candidates.Num() - 1; i > 0; --i)
	{
		const int32 j = FMath::RandRange(0, i);
		Candidates.Swap(i, j);
	}

	Answer.Empty();
	Answer.Add(Candidates[0]);
	Answer.Add(Candidates[1]);
	Answer.Add(Candidates[2]);
}

FString ARDGameMode::CheckAnswer(const FString& Input) const
{
	int32 Strike = 0;
	int32 Ball = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		const int32 InputDigit = Input[i] - '0';

		if (InputDigit == Answer[i])
		{
			Strike++;
		}
		else if (Answer.Contains(InputDigit))
		{
			Ball++;
		}
	}

	if (Strike == 0 && Ball == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS %dB"), Strike, Ball);
}

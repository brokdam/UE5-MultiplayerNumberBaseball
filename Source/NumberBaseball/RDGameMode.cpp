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
	ProcessGuess(TEXT("12"));   // 잘못된 입력 → 기회 유지
	ProcessGuess(TEXT("429"));  // 채점 + 기회 차감
	ProcessGuess(TEXT("447"));  // 중복 → 기회 유지
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

FRDGuessResult ARDGameMode::CheckAnswer(const FString& Input) const
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

	return FRDGuessResult{ Strike, Ball };
}

bool ARDGameMode::IsValidInput(const FString& Input) const
{
	if (Input.Len() != 3)
	{
		return false;
	}

	TArray<int32> Seen;
	for (int32 i = 0; i < Input.Len(); ++i)
	{
		const TCHAR C = Input[i];

		if (C < '1' || C > '9')
		{
			return false;
		}

		const int32 Digit = C - '0';

		if (Seen.Contains(Digit))
		{
			return false;
		}
		Seen.Add(Digit);
	}

	return true;
}

void ARDGameMode::ResetGame()
{
	GenerateRandomNumbers();
	RemainingAttempts = 3;
}

void ARDGameMode::ProcessGuess(const FString& Input)
{
	// 입력 확인
	if (!IsValidInput(Input))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid input"));
		return;
	}

	// 채점
	const FRDGuessResult Result = CheckAnswer(Input);

	// 기회 차감
	RemainingAttempts--;
	
	FString Display;
	if (Result.Strike == 0 && Result.Ball == 0)
	{
		Display = TEXT("OUT");
	}
	else
	{
		Display = FString::Printf(TEXT("%dS %dB"), Result.Strike, Result.Ball);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s -> %s (attempts left: %d)"), *Input, *Display, RemainingAttempts);

	// 승패 판정
	if (Result.Strike == 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Win!"));
	}
	else if (RemainingAttempts <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Draw"));
	}
}

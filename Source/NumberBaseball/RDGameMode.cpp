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
	bGameOver = false;
}

void ARDGameMode::ProcessGuess(const FString& Input, APlayerController* Sender)
{
	if (bGameOver)   
	{
		return;
	}
	
	// 입력 확인
	if (!IsValidInput(Input))
	{
		return;
	}

	ARDPlayerState* PS = Sender->GetPlayerState<ARDPlayerState>();
	if (!PS)
	{
		return;
	}
	
	// 채점
	const FRDGuessResult Result = CheckAnswer(Input);

	// 기회 차감
	PS->RemainingAttempts--;
	
	ARDPlayerController* PC = Cast<ARDPlayerController>(Sender);
	if (PC)
	{
		PC->MulticastReceiveResult(Result, PS->RemainingAttempts);
	}

	// 승패 판정
	if (Result.Strike == 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Win!"));
		bGameOver = true;
	}
	else if (PS->RemainingAttempts <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Draw"));
		bGameOver = true;
	}
}

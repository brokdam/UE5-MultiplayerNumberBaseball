// RDGameMode.cpp

#include "RDGameMode.h"
#include "RDPlayerController.h"
#include "RDPlayerState.h"
#include "RDGameState.h"

ARDGameMode::ARDGameMode()
{
	PlayerStateClass = ARDPlayerState::StaticClass();
	GameStateClass = ARDGameState::StaticClass();
}

void ARDGameMode::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomNumbers();
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

bool ARDGameMode::IsValidInput(const FString& Input)
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
}

void ARDGameMode::ProcessGuess(const FString& Input, APlayerController* Sender)
{
	ARDPlayerState* PS = Sender->GetPlayerState<ARDPlayerState>();
	if (!PS) return;
	
	if (PS->bGameOver)   
	{
		return;
	}
	
	// 입력 확인
	if (!IsValidInput(Input))
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
		PS->bGameOver = true;
		FString WinMessage = FString::Printf(TEXT("%s 승리!"), *PS->GetPlayerName());

		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			ARDPlayerController* EachPC = Cast<ARDPlayerController>(
				PlayerState->GetPlayerController()
			);
			if (EachPC)
			{
				EachPC->MulticastReceiveGameResult(WinMessage);
			}
		}
	}
	else if (PS->RemainingAttempts <= 0)
	{
		PS->bGameOver = true;

		bool bAllGameOver = true;
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			ARDPlayerState* OtherPS = Cast<ARDPlayerState>(PlayerState);
			if (OtherPS && !OtherPS->bGameOver)
			{
				bAllGameOver = false;
				break;
			}
		}

		if (bAllGameOver)
		{
			for (APlayerState* PlayerState : GameState->PlayerArray)
			{
				ARDPlayerController* EachPC = Cast<ARDPlayerController>(
					PlayerState->GetPlayerController()
				);
				if (EachPC)
				{
					EachPC->MulticastReceiveGameResult(TEXT("무승부!"));
				}
			}
		}
	}
}

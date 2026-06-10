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

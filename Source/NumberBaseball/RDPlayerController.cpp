#include "RDPlayerController.h"
#include "RDGameMode.h"

void ARDPlayerController::ServerSubmitGuess_Implementation(const FString& Guess)
{
	UE_LOG(LogTemp, Warning, TEXT("[Server] ServerSubmitGuess running, guess: %s"), *Guess);
	
	ARDGameMode* GM = GetWorld()->GetAuthGameMode<ARDGameMode>();
	if (GM)
	{
		GM->ProcessGuess(Guess, this);
	}
}

void ARDPlayerController::MulticastReceiveResult_Implementation(const FRDGuessResult& Result, int32 AttemptsLeft)
{
	UE_LOG(LogTemp, Warning, TEXT("[Multicast] 실행됨 - %s"), *GetName());

	FString Display;
	if (Result.Strike == 0 && Result.Ball == 0)
	{
		Display = TEXT("OUT");
	}
	else
	{
		Display = FString::Printf(TEXT("%dS %dB"), Result.Strike, Result.Ball);
	}

	UE_LOG(LogTemp, Warning, TEXT("[Client] Result: %s, attempts left: %d"), *Display, AttemptsLeft);
}

void ARDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &ARDPlayerController::OnTestSubmit);

}

void ARDPlayerController::OnTestSubmit()
{
	UE_LOG(LogTemp, Warning, TEXT("[Client] OnTestSubmit -> calling ServerSubmitGuess"));
	ServerSubmitGuess(TEXT("429"));
}

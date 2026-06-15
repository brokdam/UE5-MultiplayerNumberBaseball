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

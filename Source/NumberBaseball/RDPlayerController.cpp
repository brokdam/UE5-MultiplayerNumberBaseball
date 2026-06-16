#include "RDPlayerController.h"
#include "RDGameMode.h"
#include "RDChatInput.h"
#include "Kismet/KismetSystemLibrary.h"


void ARDPlayerController::ServerSubmitGuess_Implementation(const FString& Guess)
{
	ARDGameMode* GM = GetWorld()->GetAuthGameMode<ARDGameMode>();
	if (GM)
	{
		GM->ProcessGuess(Guess, this);
	}
}

void ARDPlayerController::MulticastReceiveResult_Implementation(const FRDGuessResult& Result, int32 AttemptsLeft)
{
	FString Display;
	if (Result.Strike == 0 && Result.Ball == 0)
	{
		Display = TEXT("OUT");
	}
	else
	{
		Display = FString::Printf(TEXT("%dS %dB"), Result.Strike, Result.Ball);
	}

	if (ChatInputWidgetInstance)
	{
		ChatInputWidgetInstance->UpdateResult(Display, AttemptsLeft);
	}
}

void ARDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) return;

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<URDChatInput>(this, ChatInputWidgetClass);

		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void ARDPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	PrintChatMessageString(ChatMessageString);
	ServerSubmitGuess(ChatMessageString);
}

void ARDPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
}

void ARDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &ARDPlayerController::OnTestSubmit);

}

void ARDPlayerController::OnTestSubmit()
{
	ServerSubmitGuess(TEXT("429"));
}

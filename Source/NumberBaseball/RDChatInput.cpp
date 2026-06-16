#include "RDChatInput.h"
#include "Components/EditableTextBox.h"
#include "RDPlayerController.h"

void URDChatInput::NativeConstruct()
{
	Super::NativeConstruct();
	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);		
	}	
}

void URDChatInput::NativeDestruct()
{
	Super::NativeDestruct();
	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void URDChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ARDPlayerController* OwningCXPlayerController = Cast<ARDPlayerController>(OwningPlayerController);
			if (IsValid(OwningCXPlayerController) == true)
			{
				OwningCXPlayerController->SetChatMessageString(Text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}

void URDChatInput::UpdateResult(const FString& Result, int32 AttemptsLeft)
{
	if (Text_Result)
	{
		Text_Result->SetText(FText::FromString(Result));
	}
	if (Text_Attempts)
	{
		Text_Attempts->SetText(FText::FromString(
			FString::Printf(TEXT("남은 기회: %d"), AttemptsLeft)
		));
	}
}

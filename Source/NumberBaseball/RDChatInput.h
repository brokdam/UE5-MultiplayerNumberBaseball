#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SlateEnums.h"
#include "Components/TextBlock.h"
#include "RDChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class NUMBERBASEBALL_API URDChatInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Result;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Attempts;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ResultMessage;

	void ShowGameResult(const FString& Message);
	
	void UpdateResult(const FString& Result, int32 AttemptsLeft);

};

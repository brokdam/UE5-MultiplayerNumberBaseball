#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RDPlayerController.generated.h"

class URDChatInput;
struct FRDGuessResult;

UCLASS()
class NUMBERBASEBALL_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URDChatInput> ChatInputWidgetClass;
	
	UPROPERTY()
	TObjectPtr<URDChatInput> ChatInputWidgetInstance;	
	
public: 
	UFUNCTION(Server, Reliable)
	void ServerSubmitGuess(const FString& Guess);
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastReceiveResult(const FRDGuessResult& Result, int32 AttemptsLeft);
	
	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);
	
protected:
	virtual void SetupInputComponent() override;
	void OnTestSubmit();
	
	FString ChatMessageString;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THECOOPEXPERIENCE_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UClass* CurrentPawnClass;

	UPROPERTY()
	UClass* HeroClass;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	float CurrentHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	float CurrentStamina;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	int32 Gold;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Player Stats")
	int32 MonsterPoints;

	UPROPERTY(BlueprintReadWrite)
	APlayerController* MyPlayerController;


	ADefaultPlayerState();

private:
	void CopyProperties(APlayerState* PlayerState) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CoopExperienceLevelsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THECOOPEXPERIENCE_API UCoopExperienceLevelsSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	//The Pawn the Player is controlling
	UPROPERTY(VisibleAnywhere)
	UClass* CurrentPawnClass;

	UCoopExperienceLevelsSaveGame();
};

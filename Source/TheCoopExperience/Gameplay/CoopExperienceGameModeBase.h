// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoopExperienceGameModeBase.generated.h"




class UWorld;
class AGameState;
/**
 * 
 */
UCLASS()
class THECOOPEXPERIENCE_API ACoopExperienceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACoopExperienceGameModeBase();

	UWorld* World;
	AGameState* GameState;
};
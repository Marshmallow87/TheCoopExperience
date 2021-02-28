// Fill out your copyright notice in the Description page of Project Settings.


#include "CoopExperienceGameMode.h"
#include "TheCoopExperienceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "DefaultGameInstance.h"

ACoopExperienceGameMode::ACoopExperienceGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
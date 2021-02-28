// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "TheCoopExperienceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Gameplay/DefaultGameState.h"
#include "DefaultPlayerState.h"
#include "DefaultGameInstance.h"



ADefaultGameMode::ADefaultGameMode()
{
	bUseSeamlessTravel = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADefaultGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	PlayerControllers.AddUnique(NewPlayer);

	if (NumTravellingPlayers == 0 && IsMatchInProgress())
	{
		for (auto& PlayerController : PlayerControllers)
		{
			if (PlayerController != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Vienas Ciklo Dalis"));
				UE_LOG(LogTemp, Warning, TEXT("NewPlayer %s"), *PlayerController->GetName());

				FVector Location(-390.0f, -100.0f, 705.0f);
				Location.X = FMath::FRand() *1000.0f;
				Location.Y = FMath::FRand() *1400.0f;
				Location.Z = (FMath::FRand() + 1.0f) *360.0f;
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnParams;

				ADefaultPlayerState* PlayerState = Cast<ADefaultPlayerState>(PlayerController->PlayerState);
				if (PlayerState == nullptr) return;
				TSubclassOf<APawn> WhatToSpawn = PlayerState->CurrentPawnClass;
				if (WhatToSpawn == nullptr) return;

				UWorld* World = GetWorld();
				if (!ensure(World != nullptr)) return;

				APawn* SpawnedPawn = World->SpawnActor<APawn>(WhatToSpawn, Location, Rotation, SpawnParams);

				PlayerController->Possess(SpawnedPawn);
			}
		}
	}
}


void ADefaultGameMode::RespawnPlayer(TSubclassOf<APawn> ClassToSpawn, APlayerController* PlayerController)
{
	FVector Location(0.0f, -0.0f, 300.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APawn* SpawnedPawn = World->SpawnActor<APawn>(ClassToSpawn, Location, Rotation, SpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("Atspawnino Pawn"));

	PlayerController->GetPawn()->Destroy();

	PlayerController->Possess(SpawnedPawn);

	auto PlayerState = Cast<ADefaultPlayerState>(PlayerController->PlayerState);

	if (IsValid(PlayerState))
	{
		PlayerState->CurrentHealth = PlayerState->MaxHealth;
		PlayerState->CurrentPawnClass = ClassToSpawn;
	}
}


void ADefaultGameMode::HeroDies(APlayerController* PlayerController)
{
	ADefaultGameState* MyGameState = Cast<ADefaultGameState>(GameState);
	if (MyGameState != nullptr)
	{
		MyGameState->bHeroExists = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameState == nullptr"));
	}
	if (GhostClass != nullptr && PlayerController != nullptr)
	{
		RespawnPlayer(GhostClass, PlayerController);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GhostClass == nullptr && PlayerController==nullptr"));
	}
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	int32 PlayerControllersLastIndex = PlayerControllers.Num() - 1;

	int HeroIndex = FMath::RandRange(0, PlayerControllersLastIndex);

	APlayerController* RandomPlayerController = PlayerControllers[HeroIndex];



	UE_LOG(LogTemp, Warning, TEXT("PlayerControllerLastIndex = %d. HeroIndex = %d"), PlayerControllersLastIndex, HeroIndex);
	if (RandomPlayerController != nullptr)
	{
		PlayerBecomesHero(RandomPlayerController);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RandomPlayerController == nullptr"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Galas Hero Dies"));
}

void ADefaultGameMode::PlayerBecomesHero(APlayerController* PlayerController)
{
	ADefaultGameState* MyGameState = Cast<ADefaultGameState>(GameState);
	if (MyGameState != nullptr)
	{
		if (MyGameState->bHeroExists == false)
		{
			RespawnPlayer(HeroClass, PlayerController);
			MyGameState->bHeroExists = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hero Already Exists"));
		}
	}
}



void ADefaultGameMode::NextLevel(const FString& LevelReference)
{
	auto GameInstance = Cast<UDefaultGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;


	bUseSeamlessTravel = true;
	World->ServerTravel(LevelReference);
	UE_LOG(LogTemp, Warning, TEXT("Turejo ivykti travel"));

}
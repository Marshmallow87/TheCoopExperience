// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/CoopExperienceGameMode.h"
#include "DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THECOOPEXPERIENCE_API ADefaultGameMode : public ACoopExperienceGameMode
{
	GENERATED_BODY()
	


public:

	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> GhostClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> HeroClass;




	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;


	UFUNCTION(BlueprintCallable, Category = "Spawn")
		void RespawnPlayer(TSubclassOf<APawn> ClassToSpawn, APlayerController* PlayerController);

	UFUNCTION()
		void PlayerBecomesHero(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
		void HeroDies(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Test")
		void NextLevel(const FString& LevelReference);






	//void HandleSeamlessTravelPlayer(AController*& C) override;

private:
	ADefaultGameMode();
};

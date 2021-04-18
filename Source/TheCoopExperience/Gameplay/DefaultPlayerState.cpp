// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "TheCoopExperienceCharacter.h"
#include "UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CoopExperience/Blueprints/Characters/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> HeroPawnBPClass(TEXT("/Game/CoopExperience/Blueprints/Characters/BP_FirstPersonCharacter"));
	UE_LOG(LogTemp, Warning, TEXT("Iskviestas PlayerState Constructorius"));
	CurrentPawnClass = PlayerPawnBPClass.Class;
	HeroClass = HeroPawnBPClass.Class;
}


void ADefaultPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (PlayerState != nullptr)
	{
		ADefaultPlayerState* MyPlayerState = Cast<ADefaultPlayerState>(PlayerState);

		if (MyPlayerState)
		{
			MyPlayerState->CurrentPawnClass = CurrentPawnClass;
			MyPlayerState->CurrentHealth = CurrentHealth;
			MyPlayerState->MaxHealth = MaxHealth;
			MyPlayerState->CurrentStamina = CurrentStamina;
			MyPlayerState->MaxStamina = MaxStamina;
			MyPlayerState->Gold = Gold;
			MyPlayerState->MonsterPoints = MonsterPoints;
		}
	}


}
void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const //The perma Squigly lines tho
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerState, CurrentHealth);
	DOREPLIFETIME(ADefaultPlayerState, MaxHealth);
	DOREPLIFETIME(ADefaultPlayerState, CurrentStamina);
	DOREPLIFETIME(ADefaultPlayerState, MaxStamina);
	DOREPLIFETIME(ADefaultPlayerState, Gold);
	DOREPLIFETIME(ADefaultPlayerState, MonsterPoints);
}
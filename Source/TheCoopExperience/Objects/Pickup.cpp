// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Pickup.h"
#include "Classes/Components/ShapeComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/DefaultPlayerState.h"
#include "TheCoopExperienceCharacter.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	RootComponent = PickupRoot;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PickupBox->SetGenerateOverlapEvents(true);
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox);
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!ensure(OtherActor != nullptr)) return;
	if (Cast<ATheCoopExperienceCharacter>(OtherActor))
	{
		auto PlayerState = Cast<ATheCoopExperienceCharacter>(OtherActor)->GetPlayerState();
		Cast<ADefaultPlayerState>(PlayerState)->Gold++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player touched and picked me up"));
	}
	else
	{
	}
	Destroy();
}


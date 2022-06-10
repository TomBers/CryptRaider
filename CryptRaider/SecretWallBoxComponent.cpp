// Fill out your copyright notice in the Description page of Project Settings.


#include "SecretWallBoxComponent.h"

USecretWallBoxComponent::USecretWallBoxComponent()
{
	// Constructor
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USecretWallBoxComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("SecretWallBoxCollison"));
}

void USecretWallBoxComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}


void USecretWallBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (const AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag("UNLOCK_DOOR"))
		{
			Mover->SetShouldMove(true);
			UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *Actor->GetName());
		}
	}
	
}
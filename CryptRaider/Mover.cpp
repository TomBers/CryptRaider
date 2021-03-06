// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());

	AActor* Owner = GetOwner();

	UE_LOG(LogTemp, Warning, TEXT("%u"), Owner);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Owner->GetActorNameOrLabel());
	
	const FVector OwnerLocation = Owner->GetActorLocation();
	const FString OwnerLocationString = OwnerLocation.ToCompactString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerLocationString);

	OriginLocation = OwnerLocation;
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ShouldMove)
	{
		const FVector CurrentLocation = GetOwner()->GetActorLocation();
		const FVector TargetLocation = OriginLocation + MoveOffset;
		const float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;
	
		const FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}


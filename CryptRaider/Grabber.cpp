// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics: %s"), *PhysicsHandle->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	
	
	// const FRotator MyRotation = GetComponentRotation();
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Rot: %s"), *MyRotation.ToCompactString());
	//
	// float Time = World->TimeSeconds;
	// UE_LOG(LogTemp, Warning, TEXT("Time: %f"), Time);

	

	// Find Objects in our way

	
}


void UGrabber::Grab()
{
	UWorld* World = GetWorld();
	
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(World, Start, End, FColor::Red);
	
	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	if(HasHit)
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		HitComp->WakeAllRigidBodies();
		
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
			HitComp,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
		AActor *HitActor = HitResult.GetActor();
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, true, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, true, 5);
		UE_LOG(LogTemp, Warning, TEXT("Grabber Hit: %s"), *HitActor->GetName());
	}
}

void UGrabber::DrawDebug()
{
	
}

void UGrabber::GrabberRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("Release Func"));
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


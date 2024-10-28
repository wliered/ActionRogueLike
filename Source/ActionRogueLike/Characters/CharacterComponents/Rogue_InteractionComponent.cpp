// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue_InteractionComponent.h"

#include "ActionRogueLike/Interfaces/Rogue_GameplayInterface.h"


// Sets default values for this component's properties
URogue_InteractionComponent::URogue_InteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URogue_InteractionComponent::PrimaryInteract()
{
	if (UWorld* World = GetWorld())
	{
		//FHitResult Hit;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		AActor* MyOwner = GetOwner();
	

		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		FVector End = EyeLocation + (EyeRotation.Vector() * 1000.f);
		
		//World->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
		

		TArray<FHitResult> Hits;
		float Radius = 30.f;
		FCollisionShape TraceShape;
		TraceShape.SetSphere(Radius);
		
		bool bBlockingHit = World->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, TraceShape);
		FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;


		for (FHitResult Hit : Hits)
		{
			if (AActor* HitActor = Hit.GetActor())
			{
				if (HitActor->Implements<URogue_GameplayInterface>())
				{
					APawn* MyPawn = Cast<APawn>(MyOwner);
					IRogue_GameplayInterface::Execute_Interact(HitActor, MyPawn);
					break;
				}
			}

			if (bDrawInteractDebug)
			{
				DrawDebugSphere(World, Hit.ImpactPoint, Radius, 12, LineColor, false, 2.f, 0, 2.f);
			}
		}
		if (bDrawInteractDebug)
		{
			DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 3.f);
		}
		
	}
	
}


// Called when the game starts
void URogue_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URogue_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


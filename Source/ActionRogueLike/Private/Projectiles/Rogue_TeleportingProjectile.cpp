// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue_TeleportingProjectile.h"

#include "NiagaraComponent.h"


// Sets default values
ARogue_TeleportingProjectile::ARogue_TeleportingProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplodeEffectComponent = CreateDefaultSubobject<UNiagaraComponent>("ExplodeEffect");
	ExplodeEffectComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ARogue_TeleportingProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle ExplodeTimerHandle;
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ARogue_TeleportingProjectile::ExplodeTimer_Elapsed, TeleportTimerLength);
}

void ARogue_TeleportingProjectile::TeleportTimer_Elapsed()
{
	FHitResult SweepHit;
	GetWorld()->LineTraceSingleByChannel(SweepHit,GetInstigator()->GetActorLocation(),GetActorLocation(),ECC_Visibility);
	if (SweepHit.bBlockingHit)
	{
		GetInstigator()->TeleportTo(SweepHit.ImpactPoint, SweepHit.ImpactPoint.Rotation());
	}
	else
	{
		GetInstigator()->TeleportTo(GetActorLocation(), GetActorRotation());
	}

	SetLifeSpan(ExplodeTimerLength);
}

void ARogue_TeleportingProjectile::ExplodeTimer_Elapsed()
{
	if (ExplodeEffectComponent)
	{
		ExplodeEffectComponent->Activate();
	}

	FTimerHandle TeleportTimerHandle;
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ARogue_TeleportingProjectile::TeleportTimer_Elapsed, TeleportTimerLength);
}

// Called every frame
void ARogue_TeleportingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


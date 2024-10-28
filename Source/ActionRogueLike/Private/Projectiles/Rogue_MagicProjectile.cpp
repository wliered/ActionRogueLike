// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/Rogue_MagicProjectile.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/ShapeElem.h"


// Sets default values
ARogue_MagicProjectile::ARogue_MagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereComponent = CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UNiagaraComponent>("VFX Component");
	EffectComponent->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ARogue_MagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogue_MagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


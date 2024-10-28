// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AExplodingBarrel::AExplodingBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(GetRootComponent());
	RadialForce->SetAutoActivate(false);
	RadialForce->Radius=250.f;
	RadialForce->ImpulseStrength= 2500.f;
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
}

void AExplodingBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
}

void AExplodingBarrel::PostInitializeComponents()
{
	BaseMesh->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnActorHit);
	Super::PostInitializeComponents();
	
}

// Called when the game starts or when spawned
void AExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


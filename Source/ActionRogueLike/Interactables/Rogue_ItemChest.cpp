// Fill out your copyright notice in the Description page of Project Settings.


#include "Rogue_ItemChest.h"


void ARogue_ItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}

// Sets default values
ARogue_ItemChest::ARogue_ItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(GetRootComponent());

	TargetPitch = 110.f;
}

// Called when the game starts or when spawned
void ARogue_ItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogue_ItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


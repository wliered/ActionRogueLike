// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionRogueLike/Public/Characters/Rogue_Character.h"


// Sets default values
ARogue_Character::ARogue_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARogue_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogue_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARogue_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionRogueLike/Public/Characters/Rogue_Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/Rogue_MagicProjectile.h"
#include "Projectiles/Rogue_TeleportingProjectile.h"


// Sets default values
ARogue_Character::ARogue_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<URogue_InteractionComponent>("InteractionComponent");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ARogue_Character::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void ARogue_Character::Move(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator ControlRotatorForward = GetControlRotation();
	ControlRotatorForward.Pitch = 0.f;
	ControlRotatorForward.Roll = 0.f;
	AddMovementInput(ControlRotatorForward.Vector(), InputValue.X);

	FRotator ControlRotatorRight = GetControlRotation();
	ControlRotatorForward.Pitch = 0.f;
	ControlRotatorForward.Roll = 0.f;
	AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRotatorRight), InputValue.Y);
}

void ARogue_Character::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ARogue_Character::JumpUp(const FInputActionValue& Value)
{
	Jump();
}

void ARogue_Character::PrimaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle TimerHandle_PrimaryAttack;

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ThisClass::PrimaryAttack_TimeElapsed, .2f);
	
}

void ARogue_Character::SecondaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle TimerHandle_SecondaryAttack;

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ThisClass::SecondaryAttack_TimeElapsed, .2f);
}

void ARogue_Character::Interact(const FInputActionValue& Value)
{
	InteractionComponent->PrimaryInteract();
}

void ARogue_Character::Teleport(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle TimerHandle_Teleport;

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ThisClass::TeleportProjectile_TimeElapsed, .2f);
}

FRotator ARogue_Character::GetProjectileRotation(FVector SpawnLocation)
{
	FRotator SpawnRotation;
	FHitResult LineTraceHit;
	
	FVector Start = CameraComp->GetComponentLocation();
	FVector End =  CameraComp->GetComponentLocation() + (CameraComp->GetComponentRotation().Vector() * 3000);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	GetWorld()->LineTraceSingleByObjectType(LineTraceHit, Start, End, ObjectQueryParams);
	if(bDebugCameraLineTrace)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f, 0, 2.f);
	}

	if (LineTraceHit.bBlockingHit)
	{
		 SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, LineTraceHit.ImpactPoint);
	}
	else
	{
		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, End);
	}

	return SpawnRotation;
}

void ARogue_Character::PrimaryAttack_TimeElapsed()
{
	FireProjectile(PrimaryAttackProjectileClass);
}

void ARogue_Character::SecondaryAttack_TimeElapsed()
{
	FireProjectile(SecondaryAttackProjectileClass);
}

void ARogue_Character::TeleportProjectile_TimeElapsed()
{
	FireProjectile(TeleportingProjectileClass);
}

void ARogue_Character::FireProjectile(const TSubclassOf<ARogue_MagicProjectile>& ProjectileClass)
{
	if (UWorld* World = GetWorld())
	{
		const FVector HandLocation = GetMesh()->GetSocketLocation("PrimaryAttackSpawnSocket");

		const FTransform SpawnTransform = FTransform(GetProjectileRotation(HandLocation), HandLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Instigator = this;
		
		World->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
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

	//Setup Action Bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARogue_Character::Look);
		//Primary Attack
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ARogue_Character::PrimaryAttack);
		//Secondary Attack
		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Triggered, this, &ThisClass::SecondaryAttack);
		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARogue_Character::JumpUp);
		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARogue_Character::Interact);
		//Teleport
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &ARogue_Character::Teleport);

	}
}


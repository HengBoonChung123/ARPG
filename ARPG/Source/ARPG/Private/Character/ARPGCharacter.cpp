// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AARPGCharacter::AARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 500.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	
	// Auto Possess Player 
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARPGCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		
		AddMovementInput(Direction, Value);
	}
}

void AARPGCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

// Called every frame
void AARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARPGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AARPGCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AARPGCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AARPGCharacter::Jump);
}


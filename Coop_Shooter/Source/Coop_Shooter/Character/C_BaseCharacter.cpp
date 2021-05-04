// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
AC_BaseCharacter::AC_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Called when the game starts or when spawned
void AC_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//Forward Movement of the player
void AC_BaseCharacter::MoveForward(float Direction)
{
	AddMovementInput(GetActorForwardVector() * Direction);
}

//Side movement of the player
void AC_BaseCharacter::MoveRight(float Direction)
{
	AddMovementInput(GetActorRightVector() * Direction);
}

void AC_BaseCharacter::BeginCrouch()
{
	Crouch();
}

void AC_BaseCharacter::EndCrouch()
{
	UnCrouch();
}

//Jump mechanic
void AC_BaseCharacter::StartJump()
{
	Jump();
}

// Called every frame
void AC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_BaseCharacter::MoveRight);

	//Camera movement of the player
	PlayerInputComponent->BindAxis("LookUp", this, &AC_BaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AC_BaseCharacter::AddControllerYawInput);

	//Crouch input
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AC_BaseCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AC_BaseCharacter::EndCrouch);

	//Jump Input
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AC_BaseCharacter::StartJump);
}


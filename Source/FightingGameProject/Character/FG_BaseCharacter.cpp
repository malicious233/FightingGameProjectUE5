﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FG_BaseCharacter.h"



// Sets default values
AFG_BaseCharacter::AFG_BaseCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	MoveComp = CreateDefaultSubobject<UFG_CharacterMovementComponent>(TEXT("MovementComponent"));
	MoveComp->ColliderRef = Collider;
	InputBinderComp = CreateDefaultSubobject<UFG_InputBinderComponent>(TEXT("InputBinderComponent"));
	
}

// Called when the game starts or when spawned
void AFG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentButtonBufferDuration -= DeltaTime;
	if (CurrentButtonBufferDuration < 0)
	{
		ButtonInputBuffer = EButtonInput::NONE;
	}
	
	ActiveState->Tick(DeltaTime);
}

// Called to bind functionality to input
void AFG_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AFG_BaseCharacter::HandleJumpInput);
	InputComponent->BindAxis(FName("Horizontal"), this, &AFG_BaseCharacter::HandleHorizontalInput);
	
}

UFG_BaseState* AFG_BaseCharacter::GetState()
{
	return ActiveState;
}

void AFG_BaseCharacter::HandleHorizontalInput(float Axis)
{
	if (Axis != 0)
	{
		OnButtonInput(EButtonInput::JUMP);
	}
	
}

void AFG_BaseCharacter::HandleVerticalInput(float Axis)
{
}

void AFG_BaseCharacter::HandleJumpInput()
{
	OnButtonInput(EButtonInput::JUMP);
	
}

void AFG_BaseCharacter::Test()
{
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Test"))); //Printf returns a string
}

void AFG_BaseCharacter::OnButtonInput(EButtonInput Input)
{
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE,
		1.0f,
		FColor::Blue,
		FString::Printf(TEXT("Input: h"))); //Printf returns a string
	CurrentButtonBufferDuration = BufferDuration;
	ButtonInputBuffer = Input;
}

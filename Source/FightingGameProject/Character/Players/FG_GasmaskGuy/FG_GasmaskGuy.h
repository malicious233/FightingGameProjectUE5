// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG_GasmaskGuy_IdleState.h"
#include "FightingGameProject/Character/FG_BaseCharacter.h"
#include "GameFramework/Pawn.h"
#include "FG_GasmaskGuy.generated.h"

UENUM(BlueprintType)
enum class EGasmaskGuy_State : uint8
{
	NONE,
	IDLE,
};

UCLASS()
class FIGHTINGGAMEPROJECT_API AFG_GasmaskGuy : public AFG_BaseCharacter
{
	GENERATED_BODY()

	AFG_GasmaskGuy();

public: //Overrides
	virtual void BeginPlay() override;

public: //Functions

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed = 700.f;
	
	UFUNCTION(BlueprintCallable)
	void SetState(UFG_BaseState* ToState);
	
	//Ugly debug functions
	void Ping(); 
	void Pinging();


public: //States
	//Idle
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFG_BaseState> IdleStateClass; //Just so I can use a BP overridden state
	
	UPROPERTY()
	UFG_BaseState* IdleState;
	
	//Airborne
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFG_BaseState> AirborneStateClass;

	UPROPERTY()
	UFG_BaseState* AirborneState;
	//...
	
	
	
	
};

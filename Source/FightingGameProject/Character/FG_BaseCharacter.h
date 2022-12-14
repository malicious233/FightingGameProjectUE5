// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG_CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Players/FG_InputBinderComponent.h"
#include "FG_BaseCharacter.generated.h"

class UFG_BaseState;
class UserClass;

UENUM(BlueprintType)
enum class EButtonInput : uint8
{
	NONE,
	LIGHT,
	HEAVY,
	JUMP,
};

UENUM(BlueprintType)
enum class EDirectionInput : uint8
{
	NONE,
	FORWARD,
	BACKWARD,
	UP,
	DOWN
};

UCLASS()
class FIGHTINGGAMEPROJECT_API AFG_BaseCharacter : public APawn
{
	GENERATED_BODY()

	///---------
	///Custom abstract base character that does not inherit from ACharacter. (At the moment it is only GasmaskGuy that uses this)
	///Features a custom movement component, a finite statemachine to seperate logic and a system for input buffering actions
	///---------

public:
	// Sets default values for this pawn's properties
	AFG_BaseCharacter();

protected: //Protected Overrides
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: //Public Overrides
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: //Functions

	//Gets active state
	UFUNCTION(BlueprintPure)
	inline UFG_BaseState* GetState();
	//TODO: Perhaps with interfaces we can know more info about the BaseState for use for AI?

	UFUNCTION(BlueprintPure)
	FVector GetRootSomething();
	
	UFUNCTION(BlueprintPure)
	inline float GetHorizontalInput();

	UFUNCTION(BlueprintPure)
	inline float GetVerticalInput();

	//Gets normalized input vector, not relative to camera
	UFUNCTION(BlueprintPure)
	inline FVector GetInputVector();

	UFUNCTION(BlueprintPure)
	inline FVector GetCameraInputVector();
	
private:
	
	void HandleHorizontalInput(const float Axis);
	void HandleVerticalInput(const float Axis);

	void HandleJumpInput();

	void Test();

	
	
public: //Public Variables

	
	
	
	//Editor Exposed Variables
	UPROPERTY(EditAnywhere)
	float BufferDuration = 0.2f;
	
	//Components
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UFG_CharacterMovementComponent* MoveComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UFG_InputBinderComponent* InputBinderComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UCapsuleComponent* ColliderComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USpringArmComponent* CameraSpringArmComp;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY()
	FVector RootSomething;
	
	//Values
	TArray<EButtonInput> ButtonInputBufferArray;
	//List of the order of button inputs. Will be relevant for the command input thing, currently does nothing

	UPROPERTY()
	EButtonInput ButtonInputBuffer;
	//Last button input performed before buffer clears. Might be replaced by the Inputbuffer Array if we add Streetfighter style command inputs

protected: //Protected Stuff
	UPROPERTY()
	UFG_BaseState* ActiveState;

	/**
	 * @brief Call this on any button input. Resets the buffer timer.
	 */
	UFUNCTION()
	void OnButtonInput(const EButtonInput InputEnum);

private: //Private Variables

	float CurrentButtonBufferDuration = 0;
	
	float HorizontalInput;
	
	float CameraHorizontalInput;
	
	float VerticalInput;
	
	float CameraVerticalInput;

	FVector InputVector;

	FVector CameraInputVector;
};



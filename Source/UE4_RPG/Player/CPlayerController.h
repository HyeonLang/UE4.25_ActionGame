// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayerCharacter;

UCLASS()
class UE4_RPG_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void OnInputKey_R();
	void OnInputKey_F();
	void OnInputKey_Q();
	void OnInputKey_E();

	void OnInputMoveForward(float Axis);
	void OnInputMoveRight(float Axis);

	void OnInputKey_1();
	void OnInputKey_2();
	void OnInputKey_3();
	void OnInputKey_4();

	void OnInputKey_C();
	void OnInputKey_Z();

	void OnInputKey_Shift();

	void OnInputKey_ESC();

	void OnInputMouse_Left(float Axis);
	void OnInputMouse_Right(float Axis);

	void OnInputMouse_Wheel(float Axis);

private:
	ACPlayerCharacter* PlayerCharacter;
	
};

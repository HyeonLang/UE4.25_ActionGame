// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "../Character/CPlayerCharacter.h"
#include "../Global.h"

#include "Components/CapsuleComponent.h"

ACPlayerController::ACPlayerController()
{

}

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	PlayerCharacter->GetMesh()->SetVisibility(true);
	PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Forward", this, &ACPlayerController::OnInputMoveForward);
}




void ACPlayerController::OnInputKey_R()
{
}

void ACPlayerController::OnInputKey_F()
{
}

void ACPlayerController::OnInputKey_Q()
{
}

void ACPlayerController::OnInputKey_E()
{
}

void ACPlayerController::OnInputMoveForward(float Axis)
{
	PlayerCharacter->OnForward(Axis);
}

void ACPlayerController::OnInputMoveRight(float Axis)
{
}

void ACPlayerController::OnInputKey_1()
{
}

void ACPlayerController::OnInputKey_2()
{
}

void ACPlayerController::OnInputKey_3()
{
}

void ACPlayerController::OnInputKey_4()
{
}

void ACPlayerController::OnInputKey_C()
{
}

void ACPlayerController::OnInputKey_Z()
{
}

void ACPlayerController::OnInputKey_Shift()
{
}

void ACPlayerController::OnInputKey_ESC()
{
}

void ACPlayerController::OnInputMouse_Left(float Axis)
{
}

void ACPlayerController::OnInputMouse_Right(float Axis)
{
}

void ACPlayerController::OnInputMouse_Wheel(float Axis)
{
}

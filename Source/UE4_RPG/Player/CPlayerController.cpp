// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "../Character/CPlayerCharacter.h"
#include "../Global.h"

#include "Components/CapsuleComponent.h"

ACPlayerController::ACPlayerController()
{
	CurrentLocation = FVector(0, 0, 88);
	MaxPlayerCharacterCount = 3;
}

//void ACPlayerController::OnPossess(APawn* InPawn)
//{	
//	PlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
//	if (PlayerCharacter)
//	{
//		PlayerCharacter->SetActorLocation(CurrentLocation);
//		PlayerCharacter->SetActorRotation(CurrentRotation);
//		PlayerCharacter->AddMovementInput(CurrentRotation.Vector(), CurrentWalkSpeed);
//		PlayerCharacter->GetMesh()->SetVisibility(true);
//		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//	}
//	Super::OnPossess(InPawn);
//	//SetViewTarget(PlayerCharacter);
//}

//void ACPlayerController::OnUnPossess()
//{
//
//	if (PlayerCharacter)
//	{
//		CurrentLocation = PlayerCharacter->GetActorLocation();
//		CurrentRotation = PlayerCharacter->GetActorRotation();
//		CurrentWalkSpeed = PlayerCharacter->GetVelocity().Size2D();
//		//PlayerCharacter->GetMesh()->SetVisibility(false);
//		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	}
//
//	Super::OnUnPossess();
//}


void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Forward", this, &ACPlayerController::OnInputForward);
	InputComponent->BindAxis("Right", this, &ACPlayerController::OnInputRight);
	InputComponent->BindAction("Key_1", IE_Pressed, this, &ACPlayerController::OnInputKey_1);
	InputComponent->BindAction("Key_2", IE_Pressed, this, &ACPlayerController::OnInputKey_2);
	InputComponent->BindAction("Key_3", IE_Pressed, this, &ACPlayerController::OnInputKey_3);
}

void ACPlayerController::SetPlayerCharacterCurrentIndex(int32 InIndex)
{
	PlayerCharacterCurrentIndex = InIndex;
}

void ACPlayerController::AddControlledPlayerCharacter(ACharacter* InPlayerCharacter)
{
	if (InPlayerCharacter)
	{
		PlayerCharacters.Add(InPlayerCharacter);
		//Possess(InPlayerCharacter);
	}
	
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

void ACPlayerController::OnInputForward(float Axis)
{
	for (auto* PC : PlayerCharacters)
	{
		(Cast<ACPlayerCharacter>(PC))->OnMoveForward(Axis);
		
	}
}

void ACPlayerController::OnInputRight(float Axis)
{
	for (auto* PC : PlayerCharacters)
	{
		(Cast<ACPlayerCharacter>(PC))->OnMoveRight(Axis);
	}
}

void ACPlayerController::OnInputKey_1()
{
	if (PlayerCharacterCurrentIndex == 0) return;
	SetViewTarget(PlayerCharacters[0]);
	CLog::Print("11");
	Cast<ACPlayerCharacter>(PlayerCharacters[0])->GetMesh()->SetVisibility(true);
	Cast<ACPlayerCharacter>(PlayerCharacters[1])->GetMesh()->SetVisibility(false);
	Cast<ACPlayerCharacter>(PlayerCharacters[2])->GetMesh()->SetVisibility(false);
	PlayerCharacterCurrentIndex = 0;
}

void ACPlayerController::OnInputKey_2()
{
	if (PlayerCharacterCurrentIndex == 1) return;
	SetViewTarget(PlayerCharacters[1]);
	CLog::Print("22");
	Cast<ACPlayerCharacter>(PlayerCharacters[0])->GetMesh()->SetVisibility(false);
	Cast<ACPlayerCharacter>(PlayerCharacters[1])->GetMesh()->SetVisibility(true);
	Cast<ACPlayerCharacter>(PlayerCharacters[2])->GetMesh()->SetVisibility(false);
	PlayerCharacterCurrentIndex = 1;
}

void ACPlayerController::OnInputKey_3()
{
	if (PlayerCharacterCurrentIndex == 2) return;
	SetViewTarget(PlayerCharacters[2]);
	CLog::Print("33");
	Cast<ACPlayerCharacter>(PlayerCharacters[0])->GetMesh()->SetVisibility(false);
	Cast<ACPlayerCharacter>(PlayerCharacters[1])->GetMesh()->SetVisibility(false);
	Cast<ACPlayerCharacter>(PlayerCharacters[2])->GetMesh()->SetVisibility(true);
	PlayerCharacterCurrentIndex = 2;
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

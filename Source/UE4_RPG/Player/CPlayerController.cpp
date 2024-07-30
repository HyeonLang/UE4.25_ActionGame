// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/CPlayerCharacter.h"
#include "../Global.h"



ACPlayerController::ACPlayerController()
{
	CurrentLocation = FVector(0, 0, 88);
	MaxPlayerCharacterCount = 3;

	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", RootComponent);
	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);

	//-> SpringArmComp
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 140));
	SpringArmComp->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
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

	InputComponent->BindAxis("Mouse_X", this, &ACPlayerController::OnMouseX);
	InputComponent->BindAxis("Mouse_Y", this, &ACPlayerController::OnMouseY);
}

void ACPlayerController::SetPlayerCharacterCurrentIndex(int32 InIndex)
{
	PlayerCharacterCurrentIndex = InIndex;
}

void ACPlayerController::AddControlledPlayerCharacter(ACPlayerCharacter* InPlayerCharacter)
{
	if (InPlayerCharacter)
	{
		PlayerCharacters.Add(InPlayerCharacter);
	}
	
}

void ACPlayerController::SpawnPlayerCharacter(FTransform StartTransform)
{
	
	for (int32 i = 0; i < GetMaxPlayerCharacterCount(); i++)
	{
		if (CharacterClasses[i])
		{
			TSubclassOf<ACPlayerCharacter> CharacterClass = GetCharacterClasses()[i];
			PlayerCharacter = GetWorld()->SpawnActorDeferred<ACPlayerCharacter>(CharacterClass, StartTransform);
			PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PlayerCharacter->GetMesh()->SetVisibility(false);
			PlayerCharacter->FinishSpawning(StartTransform);
			AddControlledPlayerCharacter(PlayerCharacter);
		}
	}
}

void ACPlayerController::PossessCharacter(ACPlayerCharacter* InNewCharacter)
{
	Possess(InNewCharacter);
	InNewCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InNewCharacter->GetMesh()->SetVisibility(true);
	SetViewTarget(InNewCharacter);
	PlayerCharacter = InNewCharacter;
}

void ACPlayerController::UnPossessCharacter()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerCharacter->GetMesh()->SetVisibility(false);
		UnPossess();
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
	PlayerCharacter->OnMoveForward(Axis);
	for (int32 i = 0; i < MaxPlayerCharacterCount; i++)
	{
		
		if (i == PlayerCharacterCurrentIndex) continue;
		ACPlayerCharacter* PC = PlayerCharacters[i];
		if (PC) {
			PC->SetActorLocation(PlayerCharacter->GetActorLocation());
			PC->SetActorRotation(PlayerCharacter->GetActorRotation());
		}
	}
}

void ACPlayerController::OnInputRight(float Axis)
{
	PlayerCharacter->OnMoveRight(Axis);
	for (int32 i = 0; i < MaxPlayerCharacterCount; i++)
	{
		if (i == PlayerCharacterCurrentIndex) continue;
		ACPlayerCharacter* PC = PlayerCharacters[i];
		if (PC) {
			PC->SetActorLocation(PlayerCharacter->GetActorLocation());
			PC->SetActorRotation(PlayerCharacter->GetActorRotation());
		}
	}
}

void ACPlayerController::OnInputKey_1()
{
	if (PlayerCharacterCurrentIndex == 0) return;
	ChangePlayerCharacter(0);

}

void ACPlayerController::OnInputKey_2()
{
	if (PlayerCharacterCurrentIndex == 1) return;
	ChangePlayerCharacter(1);
}

void ACPlayerController::OnInputKey_3()
{
	if (PlayerCharacterCurrentIndex == 2) return;
	ChangePlayerCharacter(2);
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

void ACPlayerController::OnMouseX(float Axis)
{
	PlayerCharacter->OnTurn(Axis);
}

void ACPlayerController::OnMouseY(float Axis)
{
	PlayerCharacter->OnLookUp(Axis);
}

void ACPlayerController::ChangePlayerCharacter(uint32 InIndex)
{
	UnPossessCharacter();
	PlayerCharacterCurrentIndex = InIndex;
	PossessCharacter(Cast<ACPlayerCharacter>(PlayerCharacters[InIndex]));
}

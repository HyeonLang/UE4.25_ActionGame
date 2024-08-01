// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/CPlayerCharacter.h"
#include "CPlayerCameraActor.h"
#include "../Global.h"



ACPlayerController::ACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentLocation = FVector(0, 0, 88.f);
	CameraRotation = GetControlRotation();
	MaxPlayerCharacterCount = 3;

	CHelpers::GetClass(&PlayerCameraActorClass, TEXT("/Game/Player/BP_CPlayerCameraActor"));

}


void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerCameraActorClass)
	{
		FTransform StartTransform;

		PlayerCameraActor = GetWorld()->SpawnActorDeferred<ACPlayerCameraActor>(PlayerCameraActorClass, StartTransform);
		PlayerCameraActor->FinishSpawning(StartTransform);

		SetViewTarget(PlayerCameraActor);
	}
}	


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

void ACPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Location = PlayerCharacter->GetActorLocation();
	Location.Z += 88.f;
	PlayerCameraActor->SetActorLocation(Location);

	CLog::Print(GetControlRotation(), -1, GetWorld()->GetDeltaSeconds(), FColor::Red);
	CLog::Print(PlayerCameraActor->GetActorRotation(), -1, DeltaSeconds);
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
	FRotator Rotation;
	Rotation = GetControlRotation();

	Possess(InNewCharacter);

	InNewCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InNewCharacter->GetMesh()->SetVisibility(true);
	PlayerCharacter = InNewCharacter;
	if (PlayerCameraActor)
	{
		PlayerCameraActor->SetActorRotation(Rotation);
		ControlRotation = Rotation;
	}
	SetViewTarget(PlayerCameraActor);
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
	PlayerCameraActor->SetActorRotation(GetControlRotation());
}

void ACPlayerController::OnMouseY(float Axis)
{
	PlayerCharacter->OnLookUp(Axis);
	PlayerCameraActor->SetActorRotation(GetControlRotation());

}

void ACPlayerController::ChangePlayerCharacter(uint32 InIndex)
{
	UnPossessCharacter();
	PlayerCharacterCurrentIndex = InIndex;
	PossessCharacter(Cast<ACPlayerCharacter>(PlayerCharacters[InIndex]));
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UE4_RPG_API ACPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnTurn(float Axis);
	void OnLookUp(float Axis);

public:

protected:

};

#include "UE4_RPGGameModeBase.h"

#include "Character/CPlayerCharacter.h"
#include "Player/CPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Global.h"

AUE4_RPGGameModeBase::AUE4_RPGGameModeBase()
{
	MaxPlayerCharacterCount = 3;
	PlayerCharacterStartIndex = 0;
}

void AUE4_RPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	StartSpawnTransform.SetLocation(FVector(0, 0, 88));

	for (int32 i = 0; i < MaxPlayerCharacterCount; i++)
	{
		if (CharacterClasses[i])
		{
			TSubclassOf<APawn> CharacterClass = CharacterClasses[i];
			ACPlayerCharacter* PlayerCharacter = GetWorld()->SpawnActorDeferred<ACPlayerCharacter>(CharacterClass, StartSpawnTransform);
			PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PlayerCharacter->GetMesh()->SetVisibility(false);
			PlayerCharacter->FinishSpawning(StartSpawnTransform);
			PlayerCharacters.Add(PlayerCharacter);
			CLog::Print("SPawnd");
		}
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerCharacters[PlayerCharacterStartIndex] && PlayerController)
	{
		PlayerController->Possess(PlayerCharacters[PlayerCharacterStartIndex]);
		CLog::Print("Possess");
	}
}

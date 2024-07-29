#include "UE4_RPGGameModeBase.h"

#include "Character/CPlayerCharacter.h"
#include "Player/CPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Global.h"

AUE4_RPGGameModeBase::AUE4_RPGGameModeBase()
{
	PlayerCharacterStartIndex = 0;
	StartSpawnTransform.SetLocation(FVector(0, 0, 130));
}

void AUE4_RPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndPossessCharacters();
}

void AUE4_RPGGameModeBase::SpawnAndPossessCharacters()
{
	ACPlayerController* PlayerController = Cast<ACPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PlayerController) return;

	for (int32 i = 0; i < PlayerController->GetMaxPlayerCharacterCount(); i++)
	{
		if (PlayerController->GetCharacterClasses()[i])
		{
			TSubclassOf<APawn> CharacterClass = PlayerController->GetCharacterClasses()[i];
			ACPlayerCharacter* PlayerCharacter = GetWorld()->SpawnActorDeferred<ACPlayerCharacter>(CharacterClass, StartSpawnTransform);
			PlayerCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PlayerCharacter->GetMesh()->SetVisibility(false);
			PlayerCharacter->FinishSpawning(StartSpawnTransform);
			PlayerController->AddControlledPlayerCharacter(PlayerCharacter);
			CLog::Print("Spawned");
		}
	}


	if (PlayerController->GetPlayerCharacters()[PlayerCharacterStartIndex])
	{
		PlayerController->Possess(PlayerController->GetPlayerCharacters()[PlayerCharacterStartIndex]);
		Cast<ACPlayerCharacter>(PlayerController->GetPlayerCharacters()[PlayerCharacterStartIndex])->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Cast<ACPlayerCharacter>(PlayerController->GetPlayerCharacters()[PlayerCharacterStartIndex])->GetMesh()->SetVisibility(true);
		PlayerController->SetViewTarget(PlayerController->GetPlayerCharacters()[PlayerCharacterStartIndex]);
		CLog::Print("Possess");
	}
}

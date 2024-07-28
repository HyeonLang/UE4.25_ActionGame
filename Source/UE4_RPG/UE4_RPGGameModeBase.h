#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4_RPGGameModeBase.generated.h"

UCLASS()
class UE4_RPG_API AUE4_RPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUE4_RPGGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE int32 GetMaxPlayerCharacterCount() { return MaxPlayerCharacterCount; }
	FORCEINLINE TArray<TSubclassOf<APawn>> GetCharacterClasses() { return CharacterClasses; }
	FORCEINLINE	TArray<APawn*> GetPlayerCharacters() { return PlayerCharacters; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	int32 MaxPlayerCharacterCount;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	int32 PlayerCharacterStartIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TArray<TSubclassOf<APawn>> CharacterClasses;

	TArray<APawn*> PlayerCharacters;

	FTransform StartSpawnTransform;
};

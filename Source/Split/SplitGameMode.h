// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SplitGameMode.generated.h"

UCLASS(minimalapi)
class ASplitGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASplitGameMode();

	virtual void BeginPlay() override;

	void CloneCharacter();

	void BuildPlayerTwo();


};




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Split3GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPLIT_API ASplit3GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASplit3GameMode();

	virtual void BeginPlay() override;


	void BuildPlayerTwo();
	
};

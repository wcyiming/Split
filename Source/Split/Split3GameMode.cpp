// Fill out your copyright notice in the Description page of Project Settings.


#include "Split3GameMode.h"
#include <Kismet/GameplayStatics.h>
#include "EngineUtils.h"              
#include "GameFramework/PlayerStart.h"

ASplit3GameMode::ASplit3GameMode() { 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASplit3GameMode::BeginPlay() {
	Super::BeginPlay();

	BuildPlayerTwo();
}

void ASplit3GameMode::BuildPlayerTwo() {
    APlayerController* PC1 = UGameplayStatics::GetPlayerController(this, 0);

    AActor* StartSpot1 = nullptr;
    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        if (It->PlayerStartTag == FName("P1"))
        {
            StartSpot1 = *It;
            break;
        }
    }

    if (StartSpot1)
    {
        RestartPlayerAtPlayerStart(PC1, StartSpot1);
    }


    if (!UGameplayStatics::GetPlayerController(this, 1))
    {
        UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
    }

    APlayerController* PC2 = UGameplayStatics::GetPlayerController(this, 1);

    AActor* StartSpot = nullptr;
    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        if (It->PlayerStartTag == FName("P2"))
        {
            StartSpot = *It;
            break;
        }
    }

    if (StartSpot)
    {
        RestartPlayerAtPlayerStart(PC2, StartSpot);
    }
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "SplitGameMode.h"
#include "SplitCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "EngineUtils.h"              
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraComponent.h" 

ASplitGameMode::ASplitGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASplitGameMode::BeginPlay()
{
    Super::BeginPlay();
    

    BuildPlayerTwo();

    CloneCharacter();
    
}

void ASplitGameMode::CloneCharacter()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC || !PC->GetPawn()) continue;

        FVector Offset = (PC->GetLocalPlayer()->GetControllerId() == 1) ? FVector(0, 0, 15300)
            : FVector(0, 0, -14700);

        ASplitCharacter* SplitChar = Cast<ASplitCharacter>(PC->GetPawn());
		if (!SplitChar || SplitChar->Tags.Contains(FName("Clone"))) {
			return;
		}

        ASplitCharacter* Clone = GetWorld()->SpawnActor<ASplitCharacter>(
            SplitChar->GetClass(),
            SplitChar->GetActorLocation() + Offset,
            SplitChar->GetActorRotation());
        if (!Clone) {
            return;
        }

		Clone->SpawnDefaultController();

		SplitChar->clonedCharacter = Clone;

        if (UCameraComponent* Cam = Clone->FindComponentByClass<UCameraComponent>())
            Cam->Deactivate();

        Clone->Tags.Add(FName("Clone"));
    }
}

void ASplitGameMode::BuildPlayerTwo()
{
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

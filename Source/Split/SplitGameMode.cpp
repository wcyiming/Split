// Copyright Epic Games, Inc. All Rights Reserved.

#include "SplitGameMode.h"
#include "SplitCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "EngineUtils.h"              
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraComponent.h" 
#include "Components/CapsuleComponent.h"
#include "GameType.h"

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

        FVector Offset = (PC->GetLocalPlayer()->GetControllerId() == 0) ? FVector(0, 0, 16000)
            : FVector(0, 0, -14000);

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

        EObjectChannel Channel = (EObjectChannel)EObjectChannel::EOC_Character1;
        if ((PC->GetLocalPlayer()->GetControllerId() == 0)) {
            Channel = (EObjectChannel)EObjectChannel::EOC_Character2;
        }

        UCapsuleComponent* CapClone = Clone->GetCapsuleComponent();
        if (CapClone)
        {
            CapClone->SetCollisionResponseToChannel(
                static_cast<ECollisionChannel>(Channel),
                ECR_Ignore);
            Clone->ChangeMesh();
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

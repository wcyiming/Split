#pragma once

#include "Engine/EngineTypes.h"   


UENUM(BlueprintType)
enum class EObjectChannel : uint8
{
    EOC_None = 0     UMETA(Hidden),
    EOC_Character1 = ECC_GameTraceChannel1 UMETA(DisplayName = "Interact P0"),
    EOC_Character2 = ECC_GameTraceChannel2 UMETA(DisplayName = "Interact P1"),

    EOC_MAX UMETA(DisplayName = "DefaultMAX")
};
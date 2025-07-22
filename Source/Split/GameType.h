#pragma once

#include "Engine/EngineTypes.h"   


UENUM(BlueprintType)
enum class EObjectChannel : uint8
{
    EOC_None = 0     UMETA(Hidden),
    EOC_Character1 = ECC_GameTraceChannel1 UMETA(DisplayName = "Interact P0"),
    EOC_Character2 = ECC_GameTraceChannel2 UMETA(DisplayName = "Interact P1"),
    EOC_B = ECC_GameTraceChannel3 UMETA(DisplayName = "Channel B"),
    EOC_Bost = ECC_GameTraceChannel4 UMETA(DisplayName = "Channel Bost"),
    EOC_A = ECC_GameTraceChannel5 UMETA(DisplayName = "Channel A"),

	EOC_Slice = ECC_GameTraceChannel8 UMETA(DisplayName = "Slice"),

	EOC_SliceA = ECC_GameTraceChannel9 UMETA(DisplayName = "SliceA"),
	EOC_SliceB = ECC_GameTraceChannel10 UMETA(DisplayName = "SliceB"),

    EOC_MAX UMETA(DisplayName = "DefaultMAX")
};
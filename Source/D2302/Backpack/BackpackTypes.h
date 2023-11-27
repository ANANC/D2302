

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "BackpackTypes.generated.h"


USTRUCT(BlueprintType)
struct FPropTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName TitleName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* StataMesh;
};



#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "WorkmanshipTypes.generated.h"

UENUM(BlueprintType)
enum class EWorkmanshipType : uint8
{
	Knit,//编织
	Dressmaker,//裁缝
	Cook,//厨艺
	Medicine,//煮药
	Production,//制作
	Handmade,//手工
};


USTRUCT(BlueprintType)
struct FWorkmanshipTableConfigData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWorkmanshipType WorkmanshipType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int DefaultGrade{1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EWorkmanshipType,int> Precondition;//前置开启的技能和等级
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int,int> UpgradeExperience;//升级所需经验
};

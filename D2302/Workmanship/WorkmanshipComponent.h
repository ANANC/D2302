#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorkmanshipTypes.h"
#include "WorkmanshipComponent.generated.h"

UCLASS()
class UWorkmanshipInfo : public UObject
{
	GENERATED_BODY()

	friend UWorkmanshipComponent;
protected:
	UPROPERTY(VisibleAnywhere)
	EWorkmanshipType WorkmanshipType;
	
	UPROPERTY(VisibleAnywhere)
	bool IsActive{false};
	
	UPROPERTY(VisibleAnywhere)
	int CurGrade;
	
	UPROPERTY(VisibleAnywhere)
	int CurExperience{0};
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UWorkmanshipComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWorkmanshipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	UDataTable* WorkmanshipTable;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UWorkmanshipInfo*> WorkmanshipInfos;
	
	TArray<FWorkmanshipTableConfigData*> WorkmanshipConfigInfos;

public:

	bool GetWorkmanshipTableConfigData(EWorkmanshipType workmanshipType,FWorkmanshipTableConfigData& data);

	bool GetWorkmanshipActive(EWorkmanshipType workmanshipType);
	
protected:
	UWorkmanshipInfo* GetWorkmanshipInfo(EWorkmanshipType workmanshipType);
	
	void InitWorkmanship();

	bool IsWorkmanshipEnableActive(EWorkmanshipType workmanshipType);
};

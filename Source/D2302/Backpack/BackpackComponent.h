// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBackpackItemNumberChangeDelegate,FName,itemName,int,oldNumber,int,newNumber);

UCLASS(BlueprintType)
class UBackpackCell:public UObject
{
GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int CellIndex;
	
	UPROPERTY(BlueprintReadOnly)
	bool HasProp{false};
	
	UPROPERTY(BlueprintReadOnly)
	FName PropName;
	
	UPROPERTY(BlueprintReadOnly)
	int PropNumber;
public:
	void SetProp(FName propName){ HasProp = true; PropName = propName; PropNumber = 0;}
	void AddPropNumber(int number){PropNumber += number;}
	void RemovePropNumber(int number){PropNumber -= number;}
	void SetPropNumber(int number){PropNumber = number;}
	void ClearProp(){HasProp = false; PropName = ""; PropNumber = 0;}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackpackComponent();

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxCellNumber{100};

	UPROPERTY(BlueprintAssignable)
	FBackpackItemNumberChangeDelegate BackpackItemNumberChangeDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	TArray<UBackpackCell*> ValidCells;
	UPROPERTY()
	TArray<UBackpackCell*> AllCells;
	
	TMap<int,UBackpackCell*> Cell2Valid;

	TMap<FName,UBackpackCell*> Prop2Cell;

	int BackpackCapacity;
public:

	UFUNCTION(BlueprintCallable)
	bool AddPorp(FName propName,int propNumber,int cellIndex = -1);

	UFUNCTION(BlueprintCallable)
	bool RemoveProp(FName propName,int propNumber,int cellIndex = -1);

	UFUNCTION(BlueprintCallable)
	int GetPropNumber(FName propName);

	UFUNCTION(BlueprintPure)
	bool IsBackpackFull();
	
protected:

	UBackpackCell* CreateCellAtFirstUnValidCell();

	UBackpackCell* CreateCell(int cellIndex);

	UBackpackCell* GetValidCellByIndex(int cellIndex);

	UBackpackCell* GetValidCellByPropName(FName propName);
};

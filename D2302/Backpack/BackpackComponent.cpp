// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackComponent.h"


// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

	BackpackCapacity = MaxCellNumber;
}


// Called when the game starts
void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

bool UBackpackComponent::AddPorp(FName propName,int propNumber,int cellIndex)
{
	UBackpackCell* cell = nullptr;
	if(cellIndex == -1)
	{
		cell = GetValidCellByPropName(propName);
	}else
	{
		cell = GetValidCellByIndex(cellIndex);
		if(cell && cell->HasProp && cell->PropName != propName)
		{
			return false;
		}
	}

	if(!cell)
	{
		cell = CreateCellAtFirstUnValidCell();
		if(!cell)
		{
			return false;
		}
		cell->SetProp(propName);
		
		ValidCells.Add(cell);
		Cell2Valid.Add(cell->CellIndex,cell);
		Prop2Cell.Add(propName,cell);
	}

	cell->AddPropNumber(propNumber);
	return true;
}

bool UBackpackComponent::RemoveProp(FName propName,int propNumber,int cellIndex)
{
	UBackpackCell* cell = nullptr;
    if(cellIndex == -1)
    {
    	cell = GetValidCellByPropName(propName);
    }else
    {
    	cell = GetValidCellByIndex(cellIndex);
    	if(cell && cell->HasProp && cell->PropName != propName)
    	{
    		return false;
    	}
    }

	if(!cell)
	{
		return false;
	}

	bool isEnough = cell->PropNumber >= propNumber;
	if(!isEnough)
	{
		return false;
	}

	cell->RemovePropNumber(propNumber);
	
	if(cell->PropNumber == 0)
	{
		cell->ClearProp();
		
		ValidCells.Remove(cell);
		Cell2Valid.Remove(cell->CellIndex);
		Prop2Cell.Remove(propName);
	}

	return true;
}

int UBackpackComponent::GetPropNumber(FName propName)
{
	UBackpackCell* cell = GetValidCellByPropName(propName);
	if(!cell)
	{
		return 0;
	}
	return cell->PropNumber;
}

bool UBackpackComponent::IsBackpackFull()
{
	int validCellNumber = Cell2Valid.Num();
	return validCellNumber == BackpackCapacity;
}

UBackpackCell* UBackpackComponent::CreateCellAtFirstUnValidCell()
{
	int cellIndex = -1;
	for(int index = 0;index<BackpackCapacity;++index)
	{
		if(Cell2Valid.Contains(index))
		{
			continue;
		}

		cellIndex = index;
		break;
	}

	if(cellIndex == -1)
	{
		return nullptr;
	}

	UBackpackCell* cell = CreateCell(cellIndex);
	return cell;
}

UBackpackCell* UBackpackComponent::CreateCell(int cellIndex)
{
	for(int index = 0;index<AllCells.Num();++index)
	{
		if(AllCells[index]->CellIndex == cellIndex)
		{
			return AllCells[index];
		}
	}
	
	UBackpackCell* cell = NewObject<UBackpackCell>(this);
	cell->CellIndex = cellIndex;
	cell->ClearProp();

	AllCells.Add(cell);

	return cell;
}

UBackpackCell* UBackpackComponent::GetValidCellByIndex(int cellIndex)
{
	UBackpackCell** cellPtr = Cell2Valid.Find(cellIndex);
	if(cellPtr)
	{
		return *cellPtr;
	}
	return nullptr;
}

UBackpackCell* UBackpackComponent::GetValidCellByPropName(FName propName)
{
	UBackpackCell** cellPtr = Prop2Cell.Find(propName);
	if(cellPtr)
	{
		return *cellPtr;
	}
	return nullptr;
}
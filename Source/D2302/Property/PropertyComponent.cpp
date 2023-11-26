// Fill out your copyright notice in the Description page of Project Settings.


#include "PropertyComponent.h"

#include "D2302/Character/GameBaseCharacter.h"


// Sets default values for this component's properties
UPropertyComponent::UPropertyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPropertyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPropertyComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPropertyComponent::GetPropertyValueEqualorGreaterthanTargetValue(FName propertyName,int targetValue)
{
	int curValue = GetPropertyValue(propertyName);
	return curValue >= targetValue;
}

int UPropertyComponent::GetPropertyValue(FName propertyName)
{
	int* valuePtr = Propertys.Find(propertyName);
	if(valuePtr)
	{
		return *valuePtr;
	}
	return 0;
}

void UPropertyComponent::SetPropertyValue(FName propertyName,int value)
{
	int oldValue = 0;
	
	if(value<0){value = 0;}
	int* valuePtr = Propertys.Find(propertyName);
	if(valuePtr)
	{
		oldValue = *valuePtr;
		Propertys[propertyName] = value;
	}
	else
	{
		Propertys.Add(propertyName,value);
	}

	if(value!=oldValue)
	{
		PropertyChangeDelegate.Broadcast(propertyName,oldValue,value);
	}
}

void UPropertyComponent::PropertyValueAddValue(FName propertyName,int add)
{
	int* valuePtr = Propertys.Find(propertyName);
	if(valuePtr)
	{
		SetPropertyValue(propertyName,*valuePtr+add);
	}
	else
	{
		SetPropertyValue(propertyName,add);
	}
}

void UPropertyComponent::PropertySubtractValue(FName propertyName,int subtract)
{
	int* valuePtr = Propertys.Find(propertyName);
	if(valuePtr)
	{
		SetPropertyValue(propertyName,*valuePtr - subtract);
	}
}

bool UPropertyComponent::TransferMyValueToAnotherCharacter(class UGameBaseCharacter* otherCharacter,FName propertyName,int value)
{
	if(!otherCharacter)
	{
		return false;
	}
	
	if(!GetPropertyValueEqualorGreaterthanTargetValue(propertyName,value))
	{
		return false;
	}

	PropertySubtractValue(propertyName,value);
	otherCharacter->GetPropertyComponent()->PropertyValueAddValue(propertyName,value);
	return true;
}
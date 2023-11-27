// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PropertyComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPropertyChangeDelegate,FName,property,int,oldValue,int,newValue);

namespace PropertyName
{
	FName Money = "Money";
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2302_API UPropertyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPropertyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FPropertyChangeDelegate PropertyChangeDelegate;
	
protected:

	UPROPERTY()
	TMap<FName,int> Propertys;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintPure)
	bool GetPropertyValueEqualorGreaterthanTargetValue(FName propertyName,int targetValue);
	
	UFUNCTION(BlueprintPure)
	int GetPropertyValue(FName propertyName);

	UFUNCTION(BlueprintCallable)
	void SetPropertyValue(FName propertyName,int value);

	UFUNCTION(BlueprintCallable)
	void PropertyValueAddValue(FName propertyName,int add);
	
	UFUNCTION(BlueprintCallable)
	void PropertySubtractValue(FName propertyName,int subtract);
	
	UFUNCTION(BlueprintPure)
	bool TransferMyValueToAnotherCharacter(class AGameBaseCharacter* otherCharacter,FName propertyName,int value);
};

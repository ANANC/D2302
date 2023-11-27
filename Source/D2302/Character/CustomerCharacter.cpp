// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"

#include "D2302/AIConsumption/AIConsumptionComponent.h"


// Sets default values
ACustomerCharacter::ACustomerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIConsumptionComponent = CreateDefaultSubobject<UAIConsumptionComponent>(TEXT("AIConsumptionComponent"));
	
}

// Called when the game starts or when spawned
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAIConsumptionComponent* ACustomerCharacter::GetAIConsumptionComponent(){return AIConsumptionComponent;}

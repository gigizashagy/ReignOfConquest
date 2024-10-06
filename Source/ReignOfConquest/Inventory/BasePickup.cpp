// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"


ABasePickup::ABasePickup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}


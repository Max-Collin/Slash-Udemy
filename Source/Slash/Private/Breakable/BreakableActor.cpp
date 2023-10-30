// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"

#include "Components/CapsuleComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Items/Treasure.h"
#include "Components/ChildActorComponent.h"
// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
	SetRootComponent(Capsule);

	
	
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));

	
GeometryCollection->SetupAttachment(GetRootComponent());
	
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GeometryCollection->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);



}

// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableActor::GetHit_Implementation(const FVector& ImpactPoint)
{
	if(bBroken) return;
	bBroken = true;
	TObjectPtr<UWorld> World = GetWorld();
	if(World&&TreasureClasses.IsEmpty() == false)
	{
		FVector Location = GetActorLocation();
		const int32 Selection = FMath::RandRange(0,TreasureClasses.Num()-1);
		World->SpawnActor<ATreasure>(TreasureClasses[Selection],Location,GetActorRotation());
	}
	
	
}



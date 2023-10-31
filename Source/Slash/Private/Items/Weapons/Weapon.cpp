// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Characters/SlashCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/HitInterface.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECC_Pawn,ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd= CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this,&AWeapon::OnBoxOverlap);
	
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start =BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();

	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for(TObjectPtr<AActor> Actor :IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	
	
	FHitResult BoxHit;
	UKismetSystemLibrary::BoxTraceSingle(this,Start,End,FVector(5.f,5.f,5.f),BoxTraceStart->GetComponentRotation(),ETraceTypeQuery::TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::None,BoxHit,true);
	
	if(BoxHit.GetActor())
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
		if(HitInterface)
		{
			UGameplayStatics::ApplyDamage(BoxHit.GetActor(),Damage,GetInstigator()->GetController(),this,UDamageType::StaticClass());
			HitInterface->Execute_GetHit(BoxHit.GetActor(),BoxHit.ImpactPoint);
		}
		IgnoreActors.AddUnique(BoxHit.GetActor());
		

		CreateFields(BoxHit.ImpactPoint);

		
		
	}
}


void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWeapon::AttachMeshToSocket(TObjectPtr<USceneComponent>  InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,true);
	ItemMesh->AttachToComponent(InParent,TransformRules,InSocketName);
}

void AWeapon::Equip(TObjectPtr<USceneComponent> InParent, FName InSocketName, TObjectPtr<AActor> NewOwner,TObjectPtr<APawn>NewInstigator)
{

	AttachMeshToSocket(InParent, InSocketName);

	ItemState = EItemState::EIS_Equipped;

	if(EmberEffect)
	{
	EmberEffect->Deactivate();
	}
	
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	
	
}

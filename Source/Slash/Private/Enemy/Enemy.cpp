// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"


#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Slash/DebugMacros.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/LowLevelTestAdapter.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::PlayHitReactMontage(const FName& SectionName)
{
	TObjectPtr<UAnimInstance> AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance&&HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName,HitReactMontage);
	}

	
}


void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::DirectionalHitReact(const FVector& ImpactPoint)
{

	
	

	const FVector Forward = GetActorForwardVector();
	// lower impact point to enemy's actor Z , parallel to ground
	const FVector ImpactLowered(ImpactPoint.X,ImpactPoint.Y,GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

	// Forward * ToHit = |Forward||ToHit| * cos(theta)
	const double CosTheta = FVector::DotProduct(Forward,ToHit);
	double Theta = FMath::Acos(CosTheta);
	// convert to degrees from radians
	Theta = FMath::RadiansToDegrees(Theta);
	

	//If CrossProduct points down, Theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward,ToHit);

	if(CrossProduct.Z<0)
	{
		Theta*=-1.f;
		
	}
	FName Section("FromBack");

	if(Theta >= -45.f && Theta<45.f)
	{
		Section = FName("FromFront");
	}
	else if(Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if(Theta>= 45.f && Theta<135.f)
	{
		Section = FName("FromRight");
	}

	PlayHitReactMontage(Section);
	

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Green,FString::Printf(TEXT("Theta: %f"),Theta));
	}
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+Forward*60,5.f,FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+ToHit*60,5.f,FColor::Green,5.f);
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+CrossProduct*100,5.f,FColor::Blue, 5.f);
}

void AEnemy::GetHit(const FVector& ImpactPoint)
{
	DRAW_SPHERE_COLOR(ImpactPoint, FColor::Orange);
	
	DirectionalHitReact(ImpactPoint);

	
}

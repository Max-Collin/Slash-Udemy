// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"


#include "Components/AttributeComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Slash/DebugMacros.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include  "Components/AttributeComponent.h"
#include "Hud/HealthBarComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include  "AIController.h"

#include "Navigation/PathFollowingComponent.h"


// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	HealthBarWidget =CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());


	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if(HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	
	EnemyController = Cast<AAIController>(GetController());

	MovetoTarget(PatrolTarget);
	GetWorldTimerManager().SetTimer(PatrolTimer,this,&AEnemy::PatrolTimerFinished,5.f,true);
	
}

void AEnemy::Die()
{
	TObjectPtr<UAnimInstance> AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance&&DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
		const int32 Selection = FMath::RandRange(0,4);
		FName SectionName = FName();
		switch (Selection)
		{
		case  0:
			SectionName = FName("Death1");
			DeathPose = EDeathPose::EDP_Death1;
			break;
		case  1:
			SectionName = FName("Death2");
			DeathPose = EDeathPose::EDP_Death2;
			break;
		case  2:
			SectionName = FName("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;
		case  3:
			SectionName = FName("Death4");
			DeathPose = EDeathPose::EDP_Death4;
			break;
		case  4:
			SectionName = FName("Death5");
			DeathPose = EDeathPose::EDP_Death5;
			break;
		default:
			break;
		}
		
		AnimInstance->Montage_JumpToSection(SectionName,DeathMontage);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5.f);
	if(HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	
}

bool AEnemy::InTargetRange(TObjectPtr<AActor> Target, double Radius)
{

	if(Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	DRAW_SPHERE_SINGLE_FRAME(GetActorLocation())
	DRAW_SPHERE_SINGLE_FRAME(Target->GetActorLocation())
	
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %f"), DistanceToTarget);
	return DistanceToTarget <= Radius;
}

void AEnemy::MovetoTarget(TObjectPtr<AActor> Target)
{
	UE_LOG(LogTemp,Warning,TEXT("MovetoTarget"))
	if(EnemyController == nullptr || Target==nullptr)return;
	
	//FTimerDelegate TimerDelegate;
	//FTimerHandle TimerHandle; 
    
	//TimerDelegate.BindLambda([&] { 
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(15.f);
	EnemyController->MoveTo(MoveRequest);
//	}); 
 
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 3.f, false);		
			
		
		
	
}

TObjectPtr<AActor> AEnemy::ChoosePatrolTarget()
{
	

			TArray<TObjectPtr<AActor>> ValidTargets;
			for(TObjectPtr<AActor> Target:PatrolTargets)
			{
				if(Target != PatrolTarget)
				{
					ValidTargets.AddUnique(Target);
				}
				
			}
			
			const int32 NumPatrolTargets = ValidTargets.Num();
			if(NumPatrolTargets>0)
			{
				const int32 TargetSelection = FMath::RandRange(0,NumPatrolTargets-1);
				return  ValidTargets[TargetSelection];
				
			}
	return nullptr;
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

void AEnemy::PatrolTimerFinished()
{
	if(GetCharacterMovement()->Velocity.Size() == 0)
	{
			if(InTargetRange(PatrolTarget,PatrolRadius))
        	{
        		UE_LOG(LogTemp,Warning,TEXT("if good"))
        		PatrolTarget=ChoosePatrolTarget();
        		
        		
        	}
        
        	
        	UE_LOG(LogTemp,Warning,TEXT("patrol timer"))
        	MovetoTarget(PatrolTarget);
	}
	else{	UE_LOG(LogTemp,Warning,TEXT("still moving"))}

	
}


void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CombatTarget)
	{
		
		if(!InTargetRange(CombatTarget,CombatRadius))
		{
			CombatTarget=nullptr;
			HealthBarWidget->SetVisibility(false);
		}
	}
	
	
	
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
	
	/*
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Green,FString::Printf(TEXT("Theta: %f"),Theta));
	}
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+Forward*60,5.f,FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+ToHit*60,5.f,FColor::Green,5.f);
	UKismetSystemLibrary::DrawDebugArrow(this,GetActorLocation(),GetActorLocation()+CrossProduct*100,5.f,FColor::Blue, 5.f);


	*/
}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	if(HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
	//DRAW_SPHERE_COLOR(ImpactPoint, FColor::Orange);
	if(Attributes&&Attributes->IsAlive())
	{
		DirectionalHitReact(ImpactPoint);
	}
	else
	{
		Die();
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,ImpactPoint);
	}
	if(HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,ImpactPoint);
	}
	

	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(Attributes)
	{
		Attributes->ReceiveDamge(DamageAmount);

		if(HealthBarWidget)
		{
			HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
		}
	}

	CombatTarget = EventInstigator->GetPawn();
	
	return DamageAmount;

	
}

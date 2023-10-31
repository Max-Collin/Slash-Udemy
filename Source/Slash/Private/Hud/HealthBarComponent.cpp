// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/HealthBarComponent.h"
#include "Hud/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if(HealthBarWidget == nullptr)
	{
		HealthBarWidget  =	Cast<UHealthBar>(GetUserWidgetObject());
	}
	
	if(HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}
}

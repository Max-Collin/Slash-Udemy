// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/SlashHUD.h"
#include "HUD/SlashOverlay.h"
#include "Blueprint/UserWidget.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UWorld> World = GetWorld();
	if(World)
	{
		TObjectPtr<APlayerController> Controller =	World->GetFirstPlayerController();
		if(Controller&&SlashOverlayClass)
		{
			SlashOverlay =	CreateWidget<USlashOverlay>(Controller,SlashOverlayClass);
			SlashOverlay->AddToViewport();
		}
	}
	
}

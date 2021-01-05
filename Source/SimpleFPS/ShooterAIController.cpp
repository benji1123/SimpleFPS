// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay(){
    Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AAIController::LineOfSightTo(PlayerPawn)){
        AAIController::SetFocus(PlayerPawn);
        AAIController::MoveToActor(PlayerPawn);
    } else{
        AAIController::ClearFocus(EAIFocusPriority::Gameplay);
        AAIController::StopMovement();
    }
}
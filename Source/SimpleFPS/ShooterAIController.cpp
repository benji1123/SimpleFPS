// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay(){
    Super::BeginPlay();
    if(AIBehavior != nullptr){
        AAIController::RunBehaviorTree(AIBehavior);
    }
}

void AShooterAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
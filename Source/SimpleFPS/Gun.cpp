// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = UObject::CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = UObject::CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger(){
    // muzzle-flash
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr) return;
    AController* OwnerController = OwnerPawn->GetController();
    if (OwnerController == nullptr) return;

    // viewpoint
    FVector Location;
    FRotator Rotation;
    OwnerController->GetPlayerViewPoint(Location, Rotation);

    FVector End = Location + Rotation.Vector() * MaxRange;
    // TODO: linetrace
    FHitResult Hit;
    bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
    if(bSuccess){
        DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);

        FVector ShotDirection = -Rotation.Vector();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletCollision, Hit.Location, ShotDirection.Rotation());
        // damage
        AActor* HitActor = Hit.GetActor();
        if(HitActor != nullptr){
            FPointDamageEvent DamageEvent(AGun::Damage, Hit, ShotDirection, nullptr);
            HitActor->TakeDamage(AGun::Damage, DamageEvent, OwnerController, this);
        }
    }
}

// Called when the game starts or when spawned
void AGun::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}


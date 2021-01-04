// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay(){
	Super::BeginPlay();
	Health = MaxHealth;
	// Give Gun
    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    ACharacter::GetMesh()->USkinnedMeshComponent::HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
}

bool AShooterCharacter::IsDead() const{
    return Health <= 0;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent,
        class AController *EventInstigator, AActor *DamageCauser){
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    DamageToApply = FMath::Min(Health, DamageToApply);
    Health -= DamageToApply;
    UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
    return DamageToApply;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue){
    AddMovementInput(AActor::GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue){
    AddMovementInput(AActor::GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Shoot(){
    Gun->PullTrigger();
}




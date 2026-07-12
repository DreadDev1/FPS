// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPSCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Combat/CombatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/WeaponData.h"
#include "GameFramework/SpringArmComponent.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
#pragma region Camera Settings
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(SpringArm);
	FirstPersonCamera->bUsePawnControlRotation = false;
#pragma endregion 
#pragma region 1st Person View Settings
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh1P");
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
#pragma endregion
#pragma region Combat Settings
	Combat = CreateDefaultSubobject<UCombatComponent>("Combat");
	Combat->SetIsReplicated(true);
#pragma endregion
	
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* FPSInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	FPSInputComponent->BindAction(CycleWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_CycleWeapon);
	FPSInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_FireWeapon_Pressed);
	FPSInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &ThisClass::Input_FireWeapon_Released);
	FPSInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_Aim_Pressed);
	FPSInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this, &ThisClass::Input_Aim_Released);
	FPSInputComponent->BindAction(ReloadWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_ReloadWeapon);
}

FName AFPSCharacter::GetWeaponAttachPoint_Implementation(const FGameplayTag& WeaponType) const
{
	checkf(Combat->WeaponData, TEXT("No Weapon Data Asset - Please fill out BP_FPSCharacter"));
	return Combat->WeaponData->GripPoints.FindChecked(WeaponType);
}

void AFPSCharacter::Input_CycleWeapon()
{
	Combat->Initiate_CycleWeapon();
}

void AFPSCharacter::Input_ReloadWeapon()
{
	Combat->Initiate_ReloadWeapon();
}

void AFPSCharacter::Input_FireWeapon_Pressed()
{
	Combat->Initiate_FireWeapon_Pressed();
}

void AFPSCharacter::Input_FireWeapon_Released()
{
	Combat->Initiate_FireWeapon_Released();
}

void AFPSCharacter::Input_Aim_Pressed()
{
	Combat->Initiate_Aim_Pressed();
}

void AFPSCharacter::Input_Aim_Released()
{
	Combat->Initiate_Aim_Released();
}






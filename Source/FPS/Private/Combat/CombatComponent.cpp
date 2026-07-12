
#include "Combat/CombatComponent.h"

#include "Engine/Engine.h"

UCombatComponent::UCombatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::Initiate_CycleWeapon()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Green, TEXT("Initiate_CycleWeapon"), false);
}

void UCombatComponent::Initiate_FireWeapon_Pressed()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Red, TEXT("Initiate_FireWeapon_Pressed"), false);
}

void UCombatComponent::Initiate_FireWeapon_Released()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Blue, TEXT("Initiate_FireWeapon_Released"), false);
}

void UCombatComponent::Initiate_ReloadWeapon()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Green, TEXT("Initiate_ReloadWeapon"), false);
}

void UCombatComponent::Initiate_Aim_Pressed()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Red, TEXT("Initiate_Aim_Pressed"), false);
}

void UCombatComponent::Initiate_Aim_Released()
{
	GEngine->AddOnScreenDebugMessage(
	-1, 5.f, FColor::Blue, TEXT("Initiate_Aim_Released"), false);
}


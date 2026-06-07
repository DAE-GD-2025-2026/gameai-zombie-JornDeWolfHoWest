#include "BTD_CheckIfWeaponNeededAndAvailableDeWolfJorn.h"

#include "AIController.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_CheckIfWeaponNeededAndAvailableDeWolfJorn::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASurvivorPawn* MyPawn =
		Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (!MyPawn)
	{
		return false;
	}

	UStudentPerceptorDeWolfJorn* Perceptor =
		MyPawn->GetComponentByClass<UStudentPerceptorDeWolfJorn>();

	if (!Perceptor)
	{
		return false;
	}
	// Check for any weapons needed in our inv
	if (Perceptor->HasWeapon())
		return false;
	
	// Check if any on the map
	auto weapons = Perceptor->GetSeenWeapons();
	if (weapons.IsEmpty())
		return false;

	AActor* closestWeapon = nullptr;
	float closestDistance = 9999999.f;
	for (AActor* weapon : weapons)
	{
		if (!weapon) continue;
		
		float distance = FVector::Dist(weapon->GetActorLocation(), MyPawn->GetActorLocation());
		if (distance < closestDistance)
		{
			closestWeapon = weapon;
			closestDistance = distance;
		}
	}
	if (closestWeapon == nullptr)
		return false;
	OwnerComp.GetBlackboardComponent()->SetValueAsObject("ItemTarget", closestWeapon);
	
	return true;
}

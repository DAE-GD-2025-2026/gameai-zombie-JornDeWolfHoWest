#include "BTD_CheckIfWeaponNeededAndAvailable.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_CheckIfWeaponNeededAndAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject("ItemTarget", weapons[0]);
	
	return true;
}

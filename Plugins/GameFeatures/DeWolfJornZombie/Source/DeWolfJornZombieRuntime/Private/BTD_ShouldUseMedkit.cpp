#include "BTD_ShouldUseMedkit.h"

#include "AIController.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_ShouldUseMedkit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
	int damageToHeal = Perceptor->GetHealthComponent()->GetMaxHealth() - Perceptor->GetHealthComponent()->GetHealth();
	return damageToHeal >= Perceptor->GetCurrentMedkitHealingValue();
}

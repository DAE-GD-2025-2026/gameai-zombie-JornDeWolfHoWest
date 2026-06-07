#include "BTD_CheckIfZombieInRange.h"

#include "AIController.h"
#include "GameAI_Zombie/Survivor/SurvivorPawn.h"
#include "StudentPerceptorDeWolfJorn.h"

bool UBTD_CheckIfZombieInRange::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
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

	const FVector MyLocation = MyPawn->GetActorLocation();
	for (AActor* Zombie : Perceptor->GetVisibleZombies())
	{
		if (!Zombie) continue;
		
		const float Dist =
			FVector::Dist(
				MyLocation,
				Zombie->GetActorLocation());

		if (Dist <= Range)
		{
			MyPawn->StartRunning();
			return true;
		}
	}

	MyPawn->StopRunning();
	return false;
}
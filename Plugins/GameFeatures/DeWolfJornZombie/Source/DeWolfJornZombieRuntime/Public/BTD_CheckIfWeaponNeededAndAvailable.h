#pragma once


#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckIfWeaponNeededAndAvailable.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_CheckIfWeaponNeededAndAvailable : public UBTDecorator
{
	GENERATED_BODY()

public:

protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
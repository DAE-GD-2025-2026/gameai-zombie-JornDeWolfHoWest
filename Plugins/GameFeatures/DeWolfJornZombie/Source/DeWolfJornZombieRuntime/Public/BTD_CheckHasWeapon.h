#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckHasWeapon.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_CheckHasWeapon : public UBTDecorator
{
	GENERATED_BODY()

public:

protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
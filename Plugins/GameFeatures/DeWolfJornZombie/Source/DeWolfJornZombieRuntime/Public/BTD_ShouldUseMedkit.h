#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_ShouldUseMedkit.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_ShouldUseMedkit : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
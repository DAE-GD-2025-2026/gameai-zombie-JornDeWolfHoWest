#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_NeedsFood.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_NeedsFood : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
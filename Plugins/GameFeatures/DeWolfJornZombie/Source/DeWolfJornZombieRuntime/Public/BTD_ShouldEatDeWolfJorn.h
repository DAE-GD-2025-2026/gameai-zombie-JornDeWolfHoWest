#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTD_ShouldEatDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_ShouldEatDeWolfJorn : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
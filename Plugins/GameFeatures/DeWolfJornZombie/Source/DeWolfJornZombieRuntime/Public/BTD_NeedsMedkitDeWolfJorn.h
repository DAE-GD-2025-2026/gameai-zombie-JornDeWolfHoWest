#pragma once
#include "BehaviorTree/BTDecorator.h"
#include "BTD_NeedsMedkitDeWolfJorn.generated.h"

UCLASS()
class DEWOLFJORNZOMBIERUNTIME_API UBTD_NeedsMedkitDeWolfJorn : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;
};
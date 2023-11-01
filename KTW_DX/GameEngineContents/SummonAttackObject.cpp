#include "PreCompile.h"
#include "SummonAttackObject.h"

#include "SummonAttacker_Effect.h"

SummonAttackObject::SummonAttackObject()
{
}

SummonAttackObject::~SummonAttackObject()
{
}

void SummonAttackObject::CreateSummonEffect(const float4& _Pos)
{
	std::shared_ptr<SummonAttacker_Effect> Effect = GetLevel()->CreateActor<SummonAttacker_Effect>(EUPDATEORDER::Effect);
	Effect->Transform.SetLocalPosition(_Pos);
}
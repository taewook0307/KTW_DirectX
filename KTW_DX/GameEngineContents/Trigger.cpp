#include "PreCompile.h"
#include "Trigger.h"

Trigger::Trigger()
{
}

Trigger::~Trigger()
{
}

void Trigger::TriggerInit(int _Order, const float4& _Scale /*= float4::ONE*/, const float4& _Position /*= float4::ZERO*/, const float4& _Rotation /*= float4::ZERO*/)
{
	TriggerCollision = CreateComponent<GameEngineCollision>(_Order);

	TriggerCollision->Transform.SetLocalScale(_Scale);
	TriggerCollision->Transform.SetLocalRotation(_Rotation);
	TriggerCollision->Transform.SetLocalPosition(_Position);
}
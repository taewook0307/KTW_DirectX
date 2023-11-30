#include "PreCompile.h"
#include "Trigger.h"

#include "WorldMapLevel.h"
#include "FadeObject.h"

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

void Trigger::Update(float _Delta)
{
	if (nullptr != TriggerCollision)
	{
		if (true == TriggerCollision->Collision(ECOLLISIONORDER::Player) && nullptr == FadeEffect)
		{
			FadeEffect = GetLevel()->CreateActor<FadeObject>(EUPDATEORDER::UI);
			FadeEffect->SetFadeType();
		}
		
		if (nullptr != FadeEffect && true == FadeEffect->GetFadeAnimationEnd())
		{
			WorldMapLevel::LastStageInTrue();
			GameEngineCore::ChangeLevel("3.LastBoss_Stage");
		}
	}
}
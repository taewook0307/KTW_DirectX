#include "PreCompile.h"
#include "CannonBallDust.h"

CannonBallDust::CannonBallDust()
{
}

CannonBallDust::~CannonBallDust()
{
}

void CannonBallDust::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	EffectRenderer->CreateAnimation("CannonBall_Effect", "CannonBall_Effect", 0.05f);
	EffectRenderer->SetEndEvent("CannonBall_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr != EffectRenderer)
			{
				EffectRenderer->Death();
				EffectRenderer = nullptr;
			}

			Death();
		}
	);

	EffectRenderer->ChangeAnimation("CannonBall_Effect");
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetPivotType(PivotType::Left);
}
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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	Renderer->CreateAnimation("CannonBall_Effect", "CannonBall_Effect", 0.05f);
	Renderer->SetEndEvent("CannonBall_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			if (nullptr != Renderer)
			{
				Renderer->Death();
				Renderer = nullptr;
			}

			Death();
		}
	);

	Renderer->ChangeAnimation("CannonBall_Effect");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Left);
}
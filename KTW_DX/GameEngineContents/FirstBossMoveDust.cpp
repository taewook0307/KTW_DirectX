#include "PreCompile.h"
#include "FirstBossMoveDust.h"

FirstBossMoveDust::FirstBossMoveDust()
{
}

FirstBossMoveDust::~FirstBossMoveDust()
{
}

void FirstBossMoveDust::Start()
{
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	EffectRenderer->CreateAnimation("FirstBossDust_1", "FirstBoss_Phase1_Dust", 0.05f);
	EffectRenderer->SetEndEvent("FirstBossDust_1",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetPivotType(PivotType::Center);
	EffectRenderer->SetAutoScaleRatio(0.5f);

	EffectRenderer->ChangeAnimation("FirstBossDust_1");
}

void FirstBossMoveDust::ChangeEffectPhase2()
{
	EffectRenderer->CreateAnimation("FirstBossDust_2", "FirstBoss_Phase2_Dust", 0.05f);
	EffectRenderer->SetEndEvent("FirstBossDust_2",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	EffectRenderer->ChangeAnimation("FirstBossDust_2");

	EffectRenderer->SetAutoScaleRatio(0.8f);
}
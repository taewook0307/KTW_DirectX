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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
	Renderer->CreateAnimation("FirstBossDust_1", "FirstBoss_Phase1_Dust", 0.05f);
	Renderer->SetEndEvent("FirstBossDust_1",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Center);
	Renderer->SetAutoScaleRatio(0.5f);

	Renderer->ChangeAnimation("FirstBossDust_1");
}

void FirstBossMoveDust::ChangeEffectPhase2()
{
	Renderer->CreateAnimation("FirstBossDust_2", "FirstBoss_Phase2_Dust", 0.05f);
	Renderer->SetEndEvent("FirstBossDust_2",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->ChangeAnimation("FirstBossDust_2");

	Renderer->SetAutoScaleRatio(0.8f);
}
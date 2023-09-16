#include "PreCompile.h"
#include "FirstBoss.h"

FirstBoss::FirstBoss()
{
}

FirstBoss::~FirstBoss()
{
}

void FirstBoss::Start()
{
	FirstBossRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Boss);

	FirstBossRenderer->CreateAnimation("Boss_Intro", "FirstBoss_Phase1_Intro");
	FirstBossRenderer->ChangeAnimation("Boss_Intro");

	FirstBossRenderer->SetPivotValue(float4{ 0.0f, 1.0f });
	FirstBossRenderer->AutoSpriteSizeOn();
}

void FirstBoss::Update(float _Delta)
{

}
#include "PreCompile.h"
#include "FirstBossPhase3Effect.h"

FirstBossPhase3Effect::FirstBossPhase3Effect()
{
}

FirstBossPhase3Effect::~FirstBossPhase3Effect()
{
}

void FirstBossPhase3Effect::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayEffect);
}

void FirstBossPhase3Effect::SetType(BossState _State)
{
	EffectType = _State;

	switch (EffectType)
	{
	case BossState::Intro:
	{
		Renderer->CreateAnimation("FirstBoss3IntroDust", "FirstBoss_Phase3_Intro_Dust");
		Renderer->SetEndEvent("FirstBoss3IntroDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		Renderer->ChangeAnimation("FirstBoss3IntroDust");
		break;
	}
	case BossState::Move:
	{
		Renderer->CreateAnimation("FirstBoss3MoveDust", "FirstBoss_Phase3_Move_Dust");
		Renderer->SetEndEvent("FirstBoss3MoveDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		Renderer->ChangeAnimation("FirstBoss3MoveDust");
		break;
	}
	case BossState::Attack:
	{
		Renderer->CreateAnimation("FirstBoss3AttackDust", "FirstBoss_Phase3_Attack_Dust");
		Renderer->SetEndEvent("FirstBoss3AttackDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		Renderer->ChangeAnimation("FirstBoss3AttackDust");
		break;
	}
	/*case BossState::Death:
		break;*/
	default:
		break;
	}

	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetAutoScaleRatio(0.8f);
}

void FirstBossPhase3Effect::Update(float _Delta)
{
	if (ActorDir::None == EffectDir)
	{
		return;
	}
	else if (ActorDir::Left == EffectDir)
	{
		Transform.SetLocalScale({ -1.0f, 1.0f });
	}
	else
	{
		Transform.SetLocalScale({ 1.0f, 1.0f });
	}
}
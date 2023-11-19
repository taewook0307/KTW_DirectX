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
	EffectRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PlayEffect);
}

void FirstBossPhase3Effect::SetType(EBOSSSTATE _State)
{
	EffectType = _State;

	switch (EffectType)
	{
	case EBOSSSTATE::Intro:
	{
		EffectRenderer->CreateAnimation("FirstBoss3IntroDust", "FirstBoss_Phase3_Intro_Dust");
		EffectRenderer->SetEndEvent("FirstBoss3IntroDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		EffectRenderer->ChangeAnimation("FirstBoss3IntroDust");
		break;
	}
	case EBOSSSTATE::Move:
	{
		EffectRenderer->CreateAnimation("FirstBoss3MoveDust", "FirstBoss_Phase3_Move_Dust");
		EffectRenderer->SetEndEvent("FirstBoss3MoveDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		EffectRenderer->ChangeAnimation("FirstBoss3MoveDust");
		break;
	}
	case EBOSSSTATE::Attack:
	{
		EffectRenderer->CreateAnimation("FirstBoss3AttackDust", "FirstBoss_Phase3_Attack_Dust");
		EffectRenderer->SetEndEvent("FirstBoss3AttackDust",
			[=](GameEngineSpriteRenderer* _Renderer)
			{
				Death();
			}
		);
		EffectRenderer->ChangeAnimation("FirstBoss3AttackDust");
		break;
	}
	/*case BossState::Death:
		break;*/
	default:
		break;
	}

	EffectRenderer->SetPivotType(PivotType::Bottom);
	EffectRenderer->AutoSpriteSizeOn();
	EffectRenderer->SetAutoScaleRatio(0.8f);
}

void FirstBossPhase3Effect::Update(float _Delta)
{
	if (EACTORDIR::None == EffectDir)
	{
		return;
	}
	else if (EACTORDIR::Left == EffectDir)
	{
		EffectRenderer->RightFlip();
	}
	else
	{
		EffectRenderer->LeftFlip();
	}
}
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

	FirstBossRenderer->CreateAnimation("Boss_Phase1_Intro", "FirstBoss_Phase1_Intro");
	FirstBossRenderer->CreateAnimation("Boss_Phase2_Intro", "FirstBoss_Phase2_Intro");
	FirstBossRenderer->CreateAnimation("Boss_Phase3_Intro", "FirstBoss_Phase3_Intro");

	FirstBossRenderer->SetPivotValue(float4{ 0.0f, 1.0f });
	FirstBossRenderer->AutoSpriteSizeOn();

	ChangeState(FirstBossState::Intro);
}

void FirstBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('I'))
	{
		PhaseChange();
	}
}

void FirstBoss::DirChange()
{
	if (ActorDir::Left == FirstBossDir)
	{
		FirstBossDir = ActorDir::Right;
	}
	else
	{
		FirstBossDir = ActorDir::Left;
	}
}

void FirstBoss::ChangeState(FirstBossState _State)
{
	if (_State != CurState)
	{
		switch (_State)
		{
		case FirstBossState::Intro:
			IntroStart();
			break;
		default:
			break;
		}
	}
}

void FirstBoss::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case FirstBossState::Intro:
		return IntroUpdate(_Delta);
	default:
		break;
	}
}

void FirstBoss::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Boss_";

	if (BossPhase::Phase1 == CurPhase)
	{
		AnimationName += "Phase1_";
	}
	else if (BossPhase::Phase2 == CurPhase)
	{
		AnimationName += "Phase2_";
	}
	else
	{
		AnimationName += "Phase3_";
	}

	AnimationName += _State;

	State = _State;

	FirstBossRenderer->ChangeAnimation(AnimationName);
}

void FirstBoss::PhaseChange()
{
	if (BossPhase::Phase1 == CurPhase)
	{
		CurPhase = BossPhase::Phase2;
	}
	else if (BossPhase::Phase2 == CurPhase)
	{
		CurPhase = BossPhase::Phase3;
	}

	ChangeState(FirstBossState::Intro);
	return;
}
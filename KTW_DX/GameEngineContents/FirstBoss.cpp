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
	FirstBossRenderer->CreateAnimation("Boss_Phase1_Idle", "FirstBoss_Phase1_Idle");
	FirstBossRenderer->CreateAnimation("Boss_Phase1_Move", "FirstBoss_Phase1_Move", 0.1f, 0, 2, false);
	FirstBossRenderer->CreateAnimation("Boss_Phase1_MoveStay", "FirstBoss_Phase1_Move", 0.1f, 3, 7, false);
	FirstBossRenderer->CreateAnimation("Boss_Phase1_MoveEnd", "FirstBoss_Phase1_Move", 0.1f, 8, 10, false);

	FirstBossRenderer->CreateAnimation("Boss_Phase2_Intro", "FirstBoss_Phase2_Intro");
	FirstBossRenderer->CreateAnimation("Boss_Phase2_Idle", "FirstBoss_Phase2_Idle");
	FirstBossRenderer->CreateAnimation("Boss_Phase2_Move", "FirstBoss_Phase2_Move", 0.1f, 0, 3, false);
	FirstBossRenderer->CreateAnimation("Boss_Phase2_MoveStay", "FirstBoss_Phase2_Move", 0.1f, 4, 8, false);
	FirstBossRenderer->CreateAnimation("Boss_Phase2_MoveEnd", "FirstBoss_Phase2_Move", 0.1f, 9, 13, false);

	/*FirstBossRenderer->CreateAnimation("Boss_Phase3_Intro", "FirstBoss_Phase3_Intro");
	FirstBossRenderer->CreateAnimation("Boss_Phase3_Idle", "FirstBoss_Phase3_Idle");*/

	FirstBossRenderer->SetPivotValue(float4{ 0.0f, 1.0f });
	FirstBossRenderer->AutoSpriteSizeOn();

	FirstBossCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	FirstBossCollision->Transform.SetLocalScale({ 100.0f, 100.0f });

	ChangeState(FirstBossState::Intro);
}

void FirstBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	PhaseChange();

	if (ActorDir::Left == FirstBossDir)
	{
		Transform.SetLocalScale({ 1.0f ,1.0f });
	}
	else
	{
		Transform.SetLocalScale({ -1.0f ,1.0f });
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
		case FirstBossState::Idle:
			IdleStart();
			break;
		case FirstBossState::Move:
			MoveStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void FirstBoss::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case FirstBossState::Intro:
		return IntroUpdate(_Delta);
	case FirstBossState::Idle:
		return IdleUpdate(_Delta);
	case FirstBossState::Move:
		return MoveUpdate(_Delta);
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
	else
	{
		AnimationName += "Phase2_";
	}

	AnimationName += _State;

	State = _State;

	FirstBossRenderer->ChangeAnimation(AnimationName);
}

void FirstBoss::PhaseChange()
{
	if (BossPhase::Phase1 == CurPhase && HitCount > 288)
	{
		CurPhase = BossPhase::Phase2;
		ChangeState(FirstBossState::Intro);
		HitCount = 0;
	}

	return;
}
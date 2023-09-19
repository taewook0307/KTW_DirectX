#include "PreCompile.h"
#include "FirstBossPhase3.h"

#include "Map.h"

FirstBossPhase3::FirstBossPhase3()
{
}

FirstBossPhase3::~FirstBossPhase3()
{
}

void FirstBossPhase3::Start()
{
	FirstBossRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Boss);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Intro", "FirstBoss_Phase3_Intro");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Idle", "FirstBoss_Phase3_Idle");
	
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Move_Left", "FirstBoss_Phase3_Move_Left");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Move_Right", "FirstBoss_Phase3_Move_Right");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Turn_Left", "FirstBoss_Phase3_Turn_Left");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Turn_Right", "FirstBoss_Phase3_Turn_Right");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Attack", "FirstBoss_Phase3_Attack");

	FirstBossRenderer->AutoSpriteSizeOn();
	FirstBossRenderer->SetPivotType(PivotType::Bottom);

	ChangeState(FirstBossState::Intro);
}

void FirstBossPhase3::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void FirstBossPhase3::DirChange()
{

}

void FirstBossPhase3::ChangeState(FirstBossState _State)
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
		case FirstBossState::Turn:
			TurnStart();
			break;
		case FirstBossState::Attack:
			AttackStart();
			break;
		case FirstBossState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _State;
}

void FirstBossPhase3::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case FirstBossState::Intro:
		return IntroUpdate(_Delta);
	case FirstBossState::Idle:
		return IdleUpdate(_Delta);
	case FirstBossState::Move:
		return MoveUpdate(_Delta);
	case FirstBossState::Turn:
		return TurnUpdate(_Delta);
	case FirstBossState::Attack:
		return AttackUpdate(_Delta);
	case FirstBossState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void FirstBossPhase3::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "FirstBoss_Phase3_";

	AnimationName += _State;

	State = _State;

	FirstBossRenderer->ChangeAnimation(AnimationName);
}
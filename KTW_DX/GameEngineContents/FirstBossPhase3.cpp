#include "PreCompile.h"
#include "FirstBossPhase3.h"

#include "Map.h"
#include "FirstBossPhase3Effect.h"

FirstBossPhase3::FirstBossPhase3()
{
	HitCount = 0;
}

FirstBossPhase3::~FirstBossPhase3()
{
}

void FirstBossPhase3::Start()
{
	FirstBossRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Intro", "FirstBoss_Phase3_Intro");
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Intro", 0,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateEffect(CurState);
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Idle", "FirstBoss_Phase3_Idle");
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase3_Idle",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EBOSSSTATE::Move);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Move_Left", "FirstBoss_Phase3_Move_Left");
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Move_Left", 0,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateEffect(CurState);
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Move_Right", "FirstBoss_Phase3_Move_Right");
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Move_Right", 0,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			MoveSoundPlay();
			CreateEffect(CurState);
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Turn_Left", "FirstBoss_Phase3_Turn_Left");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Turn_Right", "FirstBoss_Phase3_Turn_Right");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Attack", "FirstBoss_Phase3_Attack");
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Attack", 8,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_start.wav");
		}
	);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Attack", 9,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			AttackSoundPlay();
			FirstBossAttackCollision->On();
			CreateEffect(CurState);
		}
	);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase3_Attack", 10,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Off();
		}
	);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase3_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossRenderer->SetPivotType(PivotType::Bottom);
			ChangeState(EBOSSSTATE::Move);
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase3_Death", "FirstBoss_Phase3_Death");

	FirstBossRenderer->SetPivotType(PivotType::Bottom);
	FirstBossRenderer->AutoSpriteSizeOn();

	FirstBossCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::UnDamageBoss);
	FirstBossCollision->Transform.SetLocalScale({ 200.0f, 200.0f });
	FirstBossCollision->Transform.SetLocalPosition({ 0.0f, 300.0f });

	FirstBossAttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	FirstBossAttackCollision->Transform.SetLocalScale({ 300.0f, 300.0f });
	FirstBossAttackCollision->Off();

	ChangeState(EBOSSSTATE::Intro);
}

void FirstBossPhase3::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (HitCount > 372)
	{
		FirstBossRenderer->SetPivotType(PivotType::Bottom);
		ChangeState(EBOSSSTATE::Death);
		return;
	}
}

void FirstBossPhase3::DirChange()
{
	if (EACTORDIR::Left == FirstBossDir)
	{
		FirstBossDir = EACTORDIR::Right;
	}
	else
	{
		FirstBossDir = EACTORDIR::Left;
	}

	++DirChangeCount;
}

void FirstBossPhase3::ChangeState(EBOSSSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
		{
		case EBOSSSTATE::Intro:
			IntroStart();
			break;
		case EBOSSSTATE::Idle:
			IdleStart();
			break;
		case EBOSSSTATE::Move:
			MoveStart();
			break;
		case EBOSSSTATE::Turn:
			TurnStart();
			break;
		case EBOSSSTATE::Attack:
			AttackStart();
			break;
		case EBOSSSTATE::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	CurState = _CurState;
}

void FirstBossPhase3::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EBOSSSTATE::Intro:
		return IntroUpdate(_Delta);
	case EBOSSSTATE::Idle:
		return IdleUpdate(_Delta);
	case EBOSSSTATE::Move:
		return MoveUpdate(_Delta);
	case EBOSSSTATE::Turn:
		return TurnUpdate(_Delta);
	case EBOSSSTATE::Attack:
		return AttackUpdate(_Delta);
	case EBOSSSTATE::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void FirstBossPhase3::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "FirstBoss_Phase3_";

	AnimationName += _State;

	if ("Move" == _State || "Turn" == _State)
	{
		if (EACTORDIR::Left == FirstBossDir)
		{
			AnimationName += "_Left";
		}
		else
		{
			AnimationName += "_Right";
		}
	}

	State = _State;

	FirstBossRenderer->ChangeAnimation(AnimationName);
}

void FirstBossPhase3::CreateEffect(EBOSSSTATE _State)
{
	switch (_State)
	{
	case EBOSSSTATE::Intro:
	{
		Effect = GetLevel()->CreateActor<FirstBossPhase3Effect>(EUPDATEORDER::Effect);
		Effect->SetType(EBOSSSTATE::Intro);
		float4 Pos = Transform.GetWorldPosition();
		Effect->Transform.SetLocalPosition(Pos);
		break;
	}
	case EBOSSSTATE::Move:
	{
		Effect = GetLevel()->CreateActor<FirstBossPhase3Effect>(EUPDATEORDER::Effect);
		Effect->SetType(EBOSSSTATE::Move);
		Effect->SetEffectDir(FirstBossDir);
		
		break;
	}
	case EBOSSSTATE::Attack:
	{
		Effect = GetLevel()->CreateActor<FirstBossPhase3Effect>(EUPDATEORDER::Effect);
		Effect->SetType(EBOSSSTATE::Attack);
		float4 Pos = Transform.GetWorldPosition();
		Effect->Transform.SetLocalPosition(Pos);
		break;
	}
	default:
		break;
	}
}
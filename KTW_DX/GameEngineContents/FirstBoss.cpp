#include "PreCompile.h"
#include "FirstBoss.h"

#include "FirstBossMoveDust.h"
#include "FirstMapParryObject.h"

FirstBoss::FirstBoss()
{
}

FirstBoss::~FirstBoss()
{
}

void FirstBoss::Start()
{
	AllParry.resize(3);

	FirstBossRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Intro", "FirstBoss_Phase1_Intro", 0.08f);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Intro",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			IsIntroState = false;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Idle", "FirstBoss_Phase1_Idle");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Move", "FirstBoss_Phase1_Move", 0.1f, 0, 2, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_MoveStay", "FirstBoss_Phase1_Move", 0.1f, 3, 7, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_MoveEnd", "FirstBoss_Phase1_Move", 0.1f, 8, 10, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack", "FirstBoss_Phase1_Attack", 0.1f);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BounceCount = 0;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Intro", "FirstBoss_Phase2_Intro", 0.1f, 0, 28);
	FirstBossRenderer->SetStartEvent("FirstBoss_Phase2_Intro",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossCollision->Off();
			FirstBossUnDamageCollision->On();
		}
	);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_Intro",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateParryObject();
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase2_IntroStay");
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_IntroStay", "FirstBoss_Phase2_Intro", 0.1f, 29, 32);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_IntroEnd", "FirstBoss_Phase2_Intro", 0.1f, 33, 47);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_IntroEnd", 33,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossCollision->On();
			FirstBossUnDamageCollision->Off();
			AllParryDeath();
		}
	);

	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_IntroEnd",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			IsIntroState = false;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Idle", "FirstBoss_Phase2_Idle");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Move", "FirstBoss_Phase2_Move", 0.1f, 0, 3, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_MoveStay", "FirstBoss_Phase2_Move", 0.1f, 4, 8, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_MoveEnd", "FirstBoss_Phase2_Move", 0.1f, 9, 13, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Attack", "FirstBoss_Phase2_Attack");
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BounceCount = 0;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Death", "FirstBoss_Phase2_Death");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Slime", "FirstBoss_Phase2_Slime");
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_Slime",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossRenderer = nullptr;
			FirstBossCollision = nullptr;
			Death();
		}
	);

	FirstBossRenderer->SetPivotType(PivotType::Bottom);
	FirstBossRenderer->AutoSpriteSizeOn();

	FirstBossCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossBody);
	
	float4 CollisionScale = PHASE1BODYCOLLISIONSCALE;
	float4 CollisionPosition = { 0.0f, CollisionScale.Half().Y };

	FirstBossCollision->Transform.SetLocalScale(CollisionScale);
	FirstBossCollision->Transform.SetLocalPosition(CollisionPosition);

	FirstBossUnDamageCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::UnDamageBoss);
	FirstBossUnDamageCollision->Transform.SetLocalScale(CollisionScale);
	FirstBossUnDamageCollision->Transform.SetLocalPosition(CollisionPosition);
	FirstBossUnDamageCollision->Off();

	float4 AttackCollisionScale = PHASE1ATTACKCOLLISIONSCALE;
	FirstBossAttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	FirstBossAttackCollision->Transform.SetLocalScale(AttackCollisionScale);
	FirstBossAttackCollision->Off();

	ChangeState(EBOSSSTATE::Intro);
}

void FirstBoss::Update(float _Delta)
{
	StateUpdate(_Delta);

	PhaseChange();

	if (5 <= BounceCount)
	{
		ChangeState(EBOSSSTATE::Attack);
		return;
	}

	if (EACTORDIR::Left == FirstBossDir)
	{
		FirstBossRenderer->RightFlip();
	}
	else
	{
		FirstBossRenderer->LeftFlip();
	}
}

void FirstBoss::DirChange()
{
	if (EACTORDIR::Left == FirstBossDir)
	{
		FirstBossDir = EACTORDIR::Right;
	}
	else
	{
		FirstBossDir = EACTORDIR::Left;
	}
}

void FirstBoss::ChangeState(EBOSSSTATE _State)
{
	if (_State != CurState)
	{
		switch (_State)
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
		case EBOSSSTATE::Attack:
			AttackStart();
			break;
		case EBOSSSTATE::Death:
			DeathStart();
			break;
		case EBOSSSTATE::Slime:
			SlimeStart();
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
	case EBOSSSTATE::Intro:
		return IntroUpdate(_Delta);
	case EBOSSSTATE::Idle:
		return IdleUpdate(_Delta);
	case EBOSSSTATE::Move:
		return MoveUpdate(_Delta);
	case EBOSSSTATE::Attack:
		return AttackUpdate(_Delta);
	case EBOSSSTATE::Death:
		return DeathUpdate(_Delta);
	case EBOSSSTATE::Slime:
		return SlimeUpdate(_Delta);
	default:
		break;
	}
}

void FirstBoss::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "FirstBoss_";

	if (EBOSSPHASE::Phase1 == CurPhase)
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
	if (EBOSSPHASE::Phase1 == CurPhase && HitCount > PHASE1HP)
	{
		CurPhase = EBOSSPHASE::Phase2;
		ChangeState(EBOSSSTATE::Intro);
		HitCount = 0;
		BounceCount = 0;
	}

	if (EBOSSPHASE::Phase2 == CurPhase && HitCount > PHASE2HP)
	{
		ChangeState(EBOSSSTATE::Death);
		HitCount = 0;
		BounceCount = 0;
	}

	return;
}

void FirstBoss::CreateMoveDust()
{
	std::shared_ptr<FirstBossMoveDust> MoveEffect = GetLevel()->CreateActor<FirstBossMoveDust>(EUPDATEORDER::Effect);
	float4 MonsterPos = Transform.GetWorldPosition();
	MoveEffect->Transform.SetLocalPosition(MonsterPos);

	if (EBOSSPHASE::Phase2 == CurPhase)
	{
		MoveEffect->ChangeEffectPhase2();
	}
}

void FirstBoss::CreateParryObject()
{
	for (size_t i = 0; i < AllParry.size(); i++)
	{
		std::shared_ptr<FirstMapParryObject> ParryObject = GetLevel()->CreateActor<FirstMapParryObject>(EUPDATEORDER::Effect);

		if (nullptr != ParryObject)
		{
			ParryObject->ParryActive();
			AllParry[i] = ParryObject;
		}
	}

	float4 MonsterPos = Transform.GetWorldPosition();
	
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("FirstBoss_Phase2_Intro");
	float4 SpriteScale = Sprite->GetSpriteData(29).GetScale();

	float4 ParryObjectPos = { MonsterPos.X, (MonsterPos.Y + SpriteScale.Y) };

	AllParry[0]->Transform.SetLocalPosition(ParryObjectPos);

	ParryObjectPos = { MonsterPos.X - 50.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[1]->Transform.SetLocalPosition(ParryObjectPos);

	ParryObjectPos = { MonsterPos.X + 50.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[2]->Transform.SetLocalPosition(ParryObjectPos);
}

void FirstBoss::AllParryDeath()
{
	size_t Check = AllParry.size();
	for (size_t i = 0; i < Check; i++)
	{
		AllParry[i]->ParryInactive();
	}
}
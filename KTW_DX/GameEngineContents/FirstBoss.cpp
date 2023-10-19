#include "PreCompile.h"
#include "FirstBoss.h"
#include "FirstBossCollisionData.h"

#include "FirstMapParryObject.h"
#include "BaseCharacter.h"

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
	
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack_Ready", "FirstBoss_Phase1_Attack", 0.1f, 0, 6, false);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 1, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->On();
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE1);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION1);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION1);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 2, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE2);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION2);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION2);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 3, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE3);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION3);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION3);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 4, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE4);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION4);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION4);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 5, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE5);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION5);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION5);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Ready", 6, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE6);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION6);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION6);
			}
		}
	);

	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack_Ready", [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase1_Attack_Start");
		}
	);


	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack_Start", "FirstBoss_Phase1_Attack", 0.1f, 7, 9, false);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Start", 7, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE7);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION7);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION7);
			}
		}
	);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Start", 8, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE8);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION8);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION8);
			}
		}
	);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_Start", 9, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE9);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION9);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION9);
			}
		}
	);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack_Start", [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase1_Attack");
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack", "FirstBoss_Phase1_Attack", 0.1f, 9, 10, true);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 9, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE9);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION9);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION9);
			}
		}
	);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 10, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE10);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION10);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION10);
			}
		}
	);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack", [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase1_Attack_End");
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack_End", "FirstBoss_Phase1_Attack", 0.1f, 11, 15, false);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_End", 11, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE11);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION11);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION11);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_End", 12, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE12);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION12);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION12);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_End", 13, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE13);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION13);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION13);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_End", 14, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE1BOSSATTACKCOLLISIONSCALE14);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONLEFTPOSITION14);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION14);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack_End", 15, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Off();
		}
	);

	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BounceCount = 0;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Intro", "FirstBoss_Phase2_Intro", 0.1f, 0, 28);
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
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Attack", "FirstBoss_Phase2_Attack", 0.1f);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 14, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->On();
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE2BOSSATTACKCOLLISIONSCALE14);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONLEFTPOSITION14);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONRIGHTPOSITION14);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 15, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE2BOSSATTACKCOLLISIONSCALE15);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONLEFTPOSITION15);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONRIGHTPOSITION15);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 16, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE2BOSSATTACKCOLLISIONSCALE16);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONLEFTPOSITION16);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONRIGHTPOSITION16);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 17, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE2BOSSATTACKCOLLISIONSCALE17);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONLEFTPOSITION17);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONRIGHTPOSITION17);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 18, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Transform.SetLocalScale(PHASE2BOSSATTACKCOLLISIONSCALE18);
			if (EACTORDIR::Left == FirstBossDir)
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONLEFTPOSITION18);
			}
			else
			{
				FirstBossAttackCollision->Transform.SetLocalPosition(PHASE2BOSSATTACKCOLLISIONRIGHTPOSITION18);
			}
		}
	);

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 19, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Off();
		}
	);

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

	float4 AttackCollisionScale = PHASE1ATTACKCOLLISIONSCALE;
	FirstBossAttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	FirstBossAttackCollision->Transform.SetLocalScale(AttackCollisionScale);
	FirstBossAttackCollision->Off();

	ChangeState(EBOSSSTATE::Intro);

	// GameEngineInput::AddInputObject(this);
}

void FirstBoss::Update(float _Delta)
{
	if (EACTORDIR::Left == FirstBossDir)
	{
		FirstBossRenderer->RightFlip();
	}
	else
	{
		FirstBossRenderer->LeftFlip();
	}

	StateUpdate(_Delta);

	PhaseChange();

	// if (true == GameEngineInput::IsDown('L', this))
	if (5 <= BounceCount)
	{
		ChangeState(EBOSSSTATE::Attack);
		return;
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

void FirstBoss::DirCheckPrevAttack()
{
	float CharacterPosX = BaseCharacter::MainCharacter->Transform.GetWorldPosition().X;
	float PosX = Transform.GetWorldPosition().X;

	if (PosX < CharacterPosX)
	{
		FirstBossDir = EACTORDIR::Right;
	}
	else
	{
		FirstBossDir = EACTORDIR::Left;
	}
}

void FirstBoss::ChangeState(EBOSSSTATE _CurState)
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

	CurState = _CurState;
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
		FirstBossCollision->On();
		FirstBossAttackCollision->Off();
		CurPhase = EBOSSPHASE::Phase2;
		ChangeState(EBOSSSTATE::Intro);
		HitCount = 0;
		BounceCount = 0;
	}

	if (EBOSSPHASE::Phase2 == CurPhase && HitCount > PHASE2HP)
	{
		FirstBossAttackCollision->Off();
		ChangeState(EBOSSSTATE::Death);
		HitCount = 0;
		BounceCount = 0;
	}

	return;
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

	float4 ParryObjectPos = { MonsterPos.X, (MonsterPos.Y + SpriteScale.Y + 100.0f) };

	AllParry[0]->Transform.SetLocalPosition(ParryObjectPos);

	ParryObjectPos = { MonsterPos.X - 100.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[1]->Transform.SetLocalPosition(ParryObjectPos);
	AllParry[1]->Transform.SetLocalRotation({ 0.0f, 0.0f, -30.0f });

	ParryObjectPos = { MonsterPos.X + 100.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[2]->Transform.SetLocalPosition(ParryObjectPos);
	AllParry[1]->Transform.SetLocalRotation({ 0.0f, 0.0f, 30.0f });
}

void FirstBoss::AllParryDeath()
{
	size_t Check = AllParry.size();
	for (size_t i = 0; i < Check; i++)
	{
		AllParry[i]->ParryInactive();
	}
}
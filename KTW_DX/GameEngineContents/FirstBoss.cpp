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

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Intro", "FirstBoss_Phase1_Intro", 0.08f, -1, -1, false);
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Intro", 9, [=](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineSound::SoundPlay("sfx_slime_small_intro_anim.wav");
		}
	);

	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Intro",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			IsIntroState = false;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Idle", "FirstBoss_Phase1_Idle");

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Move", "FirstBoss_Phase1_Move", FIRSTBOSSANIMATIONINTER, 0, 2, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_MoveStay", "FirstBoss_Phase1_Move", FIRSTBOSSANIMATIONINTER, 3, 7, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_MoveEnd", "FirstBoss_Phase1_Move", FIRSTBOSSANIMATIONINTER, 8, 10, false);
	
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase1_Attack", "FirstBoss_Phase1_Attack", FIRSTBOSSANIMATIONINTER, -1, -1, false);
	std::shared_ptr<GameEngineFrameAnimation> AttackAnimation = FirstBossRenderer->FindAnimation("FirstBoss_Phase1_Attack");
	AttackAnimation->Inter[6] = 0.2f;
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 1, [=](GameEngineSpriteRenderer* _Renderer)
		{
			Phase1AttackSoundPlay();
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 2, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 3, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 4, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 5, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 6, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 7, [=](GameEngineSpriteRenderer* _Renderer)
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
	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 8, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 11, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 12, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 13, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 14, [=](GameEngineSpriteRenderer* _Renderer)
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

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase1_Attack", 15, [=](GameEngineSpriteRenderer* _Renderer)
		{
			FirstBossAttackCollision->Off();
		}
	);

	FirstBossRenderer->SetEndEvent("FirstBoss_Phase1_Attack",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Intro", "FirstBoss_Phase2_Intro", 0.1f, 0, 34, false);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_Intro",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			CreateParryObject();
			FirstBossRenderer->ChangeAnimation("FirstBoss_Phase2_IntroStay");
		}
	);

	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_IntroStay", "FirstBoss_Phase2_Intro", FIRSTBOSSANIMATIONINTER, 35, 36, true);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_IntroEnd", "FirstBoss_Phase2_Intro", FIRSTBOSSANIMATIONINTER, 37, 47, false);
	FirstBossRenderer->SetEndEvent("FirstBoss_Phase2_IntroEnd",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			AllParryDeath();
			IsIntroState = false;
			ChangeState(EBOSSSTATE::Idle);
			return;
		}
	);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Idle", "FirstBoss_Phase2_Idle");
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Move", "FirstBoss_Phase2_Move", FIRSTBOSSANIMATIONINTER, 0, 3, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_MoveStay", "FirstBoss_Phase2_Move", FIRSTBOSSANIMATIONINTER, 4, 8, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_MoveEnd", "FirstBoss_Phase2_Move", FIRSTBOSSANIMATIONINTER, 9, 13, false);
	FirstBossRenderer->CreateAnimation("FirstBoss_Phase2_Attack", "FirstBoss_Phase2_Attack", FIRSTBOSSANIMATIONINTER, 0, 29, true);
	std::shared_ptr<GameEngineFrameAnimation> Attack2Animation = FirstBossRenderer->FindAnimation("FirstBoss_Phase2_Attack");
	Attack2Animation->Inter[10] = 0.3f;

	FirstBossRenderer->SetFrameEvent("FirstBoss_Phase2_Attack", 10, [=](GameEngineSpriteRenderer* _Renderer)
		{
			Phase2AttackSoundPlay();
		}
	);
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
}

void FirstBoss::Update(float _Delta)
{
	std::string BounceCountString = "BounceCount : " + std::to_string(BounceCount);
	OutputDebugStringA(BounceCountString.c_str());
	OutputDebugStringA("\n");

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

	if (0 >= BounceCount)
	{
		ChangeAttackState();
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
		BounceCount = MINBOUNCECOUNT;
	}

	if (EBOSSPHASE::Phase2 == CurPhase && HitCount > PHASE2HP)
	{
		FirstBossAttackCollision->Off();
		ChangeState(EBOSSSTATE::Death);
		HitCount = 0;
		BounceCount = MINBOUNCECOUNT;
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

	ParryObjectPos = { MonsterPos.X - 130.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[1]->Transform.SetLocalPosition(ParryObjectPos);
	AllParry[1]->Transform.SetLocalRotation({ 0.0f, 0.0f, 30.0f });

	ParryObjectPos = { MonsterPos.X + 130.0f, (MonsterPos.Y + SpriteScale.Y) };
	AllParry[2]->Transform.SetLocalPosition(ParryObjectPos);
	AllParry[2]->Transform.SetLocalRotation({ 0.0f, 0.0f, -30.0f });
}

void FirstBoss::AllParryDeath()
{
	size_t Check = AllParry.size();
	for (size_t i = 0; i < Check; i++)
	{
		AllParry[i]->ParryInactive();
	}
}

void FirstBoss::ChangeAttackState()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);
	BounceCount = Random.RandomInt(MINBOUNCECOUNT, MAXBOUNCECOUNT);
	ChangeState(EBOSSSTATE::Attack);
	return;
}
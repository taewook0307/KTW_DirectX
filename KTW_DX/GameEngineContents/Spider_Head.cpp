#include "PreCompile.h"
#include "Spider_Head.h"

#include "Map.h"
#include "BaseCharacter.h"

Spider_Head::Spider_Head()
{
}

Spider_Head::~Spider_Head()
{
}

void Spider_Head::Start()
{
	SpiderRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	SpiderRenderer->AutoSpriteSizeOn();
	SpiderRenderer->SetPivotType(PivotType::Bottom);

	SpiderRenderer->CreateAnimation("SpiderHead_Fall", "SpiderHead_Fall");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				FallSoundPlay();
				SpiderRenderer->ChangeAnimation("SpiderHead_Fall");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::WHITE);

				if (FLOORCOLOR == CheckColor)
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpStart);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Fall, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_JumpStart", "SpiderHead_JumpStart", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SpiderRenderer->ChangeAnimation("SpiderHead_JumpStart");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SpiderRenderer->IsCurAnimationEnd())
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::Jump);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::JumpStart, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_Jump", "SpiderHead_Jump");
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				SetGravityForce(float4::UP * JumpPower);
				SpiderRenderer->ChangeAnimation("SpiderHead_Jump");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				float GravityY = GetGravityForce().Y;

				if (20.0f >= GravityY)
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpToFall);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Jump, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_JumpToFall", "SpiderHead_JumpToFall", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				FallSoundPlay();
				LandCountCheck();
				SpiderRenderer->ChangeAnimation("SpiderHead_JumpToFall");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::WHITE);

				if (FLOORCOLOR == CheckColor)
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::Land);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::JumpToFall, Para);
	}

	SpiderRenderer->CreateAnimation("SpiderHead_Land", "SpiderHead_Land", 0.1f, -1, -1, false);
	{
		CreateStateParameter Para;
		Para.Start = [=](GameEngineState* _Parent)
			{
				++LandCount;
				LandSoundPlay();
				SpiderRenderer->ChangeAnimation("SpiderHead_Land");
			};
		Para.Stay = [=](float _DeltaTime, GameEngineState* _Parent)
			{
				if (true == SpiderRenderer->IsCurAnimationEnd())
				{
					SpiderState.ChangeState(ESPIDERHEADSTATE::JumpStart);
					return;
				}
			};
		SpiderState.CreateState(ESPIDERHEADSTATE::Land, Para);
	}

	SpiderCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	SpiderCollision->Transform.SetLocalScale(SPIDERCOLLISIONSCALE);
	SpiderCollision->Transform.SetLocalPosition(SPIDERCOLLISIONPOSITION);
	SpiderCollision->SetCollisionType(ColType::AABBBOX2D);

	SpiderState.ChangeState(ESPIDERHEADSTATE::Fall);
}

void Spider_Head::Update(float _Delta)
{
	SpiderState.Update(_Delta);

	float GravityForceY = GetGravityForce().Y;

	if (0.0f < GravityForceY)
	{
		float4 Pos = Transform.GetWorldPosition() + float4{ 0.0f, 80.0f };
		ActorGravity(_Delta, Pos, 800.0f, GameEngineColor::WHITE);
	}
	else
	{
		ActorGravity(_Delta, Transform.GetWorldPosition(), 800.0f, GameEngineColor::WHITE);
	}
}

void Spider_Head::LandCountCheck()
{
	if (LandCount >= 3)
	{
		Death();
	}
	else
	{
		float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
		float4 Pos = Transform.GetWorldPosition();

		Transform.SetWorldPosition({ CharacterPos.X, Pos.Y });
	}
}

void Spider_Head::FallSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 5);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("devil_spider_fall_001.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("devil_spider_fall_002.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("devil_spider_fall_003.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("devil_spider_fall_004.wav");
		break;
	case 4:
		GameEngineSound::SoundPlay("devil_spider_fall_005.wav");
		break;
	default:
		GameEngineSound::SoundPlay("devil_spider_fall_006.wav");
		break;
	}
}

void Spider_Head::LandSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 5);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_001.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_002.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_003.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_004.wav");
		break;
	case 4:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_005.wav");
		break;
	default:
		GameEngineSound::SoundPlay("devil_spiderhead_hitfloor_006.wav");
		break;
	}
}

#include "PreCompile.h"
#include "Bullet.h"

#include "BaseBoss.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	BulletRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Bullet);
	BulletRenderer->CreateAnimation("Bullet_Spawn", "BulletSpawn", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("Bullet_Move", "BulletMove", BULLETANIMATIONINTER);
	BulletRenderer->CreateAnimation("Bullet_Death", "BulletDeath", BULLETANIMATIONINTER);
	BulletRenderer->AutoSpriteSizeOn();
	BulletRenderer->SetAutoScaleRatio(BULLETRATIO);

	BulletCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Bullet);
	BulletCollision->Transform.SetLocalScale({ 27.0f, 18.0f });

	ChangeBulletState(BulletState::Spawn);
}

void Bullet::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (Direction8::Left == BulletDir)
	{
		Transform.SetLocalScale({ -1.0f, 1.0f });
	}

	else if (Direction8::Right == BulletDir)
	{
		Transform.SetLocalScale({ 1.0f, 1.0f });
	}

	else if (Direction8::Up == BulletDir)
	{
		Transform.SetLocalRotation({0.0f, 0.0f, 90.0f});
	}

	else if (Direction8::Down == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	}

	else if (Direction8::LeftUp == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 135.0f });
	}

	else if (Direction8::LeftDown == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -135.0f });
	}

	else if (Direction8::RightUp == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, 45.0f });
	}

	else if (Direction8::RightDown == BulletDir)
	{
		Transform.SetLocalRotation({ 0.0f, 0.0f, -45.0f });
	}

	BulletCollision->Collision(CollisionOrder::Monster,
		[=](std::vector<std::shared_ptr<GameEngineCollision>> _Col)
		{
			if (BulletState::Move == CurState)
			{
				std::shared_ptr<GameEngineCollision> CurCollision = _Col[_Col.size() - 1];
				GameEngineActor* ColMaster = CurCollision->GetActor();
				BaseBoss* ColBoss = dynamic_cast<BaseBoss*>(ColMaster);
				
				if (nullptr != ColBoss)
				{
					for (int i = 0; i < Att; ++i)
					{
						ColBoss->PlusHitCount();
					}
				}

				ChangeBulletState(BulletState::Death);
				return;
			}
		}
	);
}

void Bullet::ChangeBulletState(BulletState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case BulletState::Spawn:
			SpawnStart();
			break;
		case BulletState::Move:
			MoveStart();
			break;
		case BulletState::Death:
			DeathStart();
			break;
		default:
			break;
		}

		CurState = _State;
	}
}

void Bullet::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BulletState::Spawn:
		return SpawnUpdate(_Delta);
	case BulletState::Move:
		return MoveUpdate(_Delta);
	case BulletState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void Bullet::ChangeBulletAnimation(std::string_view _State)
{
	std::string AnimationName = "Bullet_";

	AnimationName += _State;

	State = _State;

	BulletRenderer->ChangeAnimation(AnimationName);
}
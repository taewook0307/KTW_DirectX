#include "PreCompile.h"
#include "BaseCharacter.h"

#include "Map.h"
#include "ParryObject.h"
#include "StageFailUI.h"
#include "StageLevel.h"

void BaseCharacter::CharacterMove(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_LEFT, this))
	{
		MovePos = float4::LEFT * _Delta * Speed;
		CheckPos = LEFTCHECKPOS;
	}

	if (GameEngineInput::IsPress(VK_RIGHT, this))
	{
		MovePos = float4::RIGHT * _Delta * Speed;
		CheckPos = RIGHTCHECKPOS;
	}

	float4 AfterMovePos = Transform.GetWorldPosition() + CheckPos;

	GameEngineColor MoveCheckColor = Map::MainMap->GetColor(AfterMovePos, FLOORCOLOR);

	if (FLOORCOLOR != MoveCheckColor && false == PlayerCollision->Collision(ECOLLISIONORDER::Obstacle, CheckPos))
	{
		Transform.AddLocalPosition(MovePos);
	}
}

void BaseCharacter::ActorGravity(float _Delta, float4 _CheckPos)
{
	GameEngineColor CheckColor = Map::MainMap->GetColor(_CheckPos, FLOORCOLOR);

	if (false == StoolPass)
	{
		if (FLOORCOLOR != CheckColor && STOOLCOLOR != CheckColor)
		{
			GravityOn(_Delta);
		}
		else
		{
			float4 CheckPos = Transform.GetWorldPosition() + float4::UP;
			GameEngineColor UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);

			while (UpColor == FLOORCOLOR)
			{
				CheckPos = Transform.GetWorldPosition() + float4::UP;
				UpColor = Map::MainMap->GetColor(CheckPos, FLOORCOLOR);
				Transform.AddLocalPosition(float4::UP);
			}

			GravityReset();
		}
	}
	else
	{
		if (FLOORCOLOR != CheckColor)
		{
			GravityOn(_Delta);
		}
		else
		{
			GravityReset();
			StoolPass = false;
		}
	}
}

void BaseCharacter::IntroStart()
{
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));

	int IntroType = Random.RandomInt(0, 1);

	if (0 == IntroType)
	{
		ChangeAnimation("Intro");
	}
	else
	{
		ChangeAnimation("Intro_Flex");
	}
}

void BaseCharacter::IntroUpdate(float _Delta)
{
	// Gravity
	ActorGravity(_Delta, Transform.GetWorldPosition());

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}
}

void BaseCharacter::IdleStart()
{
	ChangeAnimation("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	DirChange();

	// Gravity
	ActorGravity(_Delta, Transform.GetWorldPosition());

	// Change State
	if (true == GameEngineInput::IsPress(VK_LEFT, this) && true == GameEngineInput::IsPress('X', this)
		|| true == GameEngineInput::IsPress(VK_RIGHT, this) && true == GameEngineInput::IsPress('X', this))
	{
		ChangeState(ECHARACTERSTATE::RunShoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LEFT, this)
		|| true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		ChangeState(ECHARACTERSTATE::Run);
		return;
	}

	if (true == GameEngineInput::IsPress('Z', this))
	{
		ChangeState(ECHARACTERSTATE::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress('C', this))
	{
		ChangeState(ECHARACTERSTATE::Aim);
		return;
	}

	if (true == GameEngineInput::IsPress('X', this))
	{
		ChangeState(ECHARACTERSTATE::Shoot);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN, this))
	{
		ChangeState(ECHARACTERSTATE::Duck);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(ECHARACTERSTATE::Dash);
		return;
	}
}

void BaseCharacter::RunStart()
{
	ChangeAnimation("Run");
}

void BaseCharacter::RunUpdate(float _Delta)
{
	DirChange();

	// Gravity
	ActorGravity(_Delta, Transform.GetWorldPosition());
	
	// Move
	CharacterMove(_Delta);

	// Change State
	if (true == GameEngineInput::IsFree(VK_LEFT, this)
		&& true == GameEngineInput::IsFree(VK_RIGHT, this))
	{
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(ECHARACTERSTATE::Dash);
		return;
	}

	if (true == GameEngineInput::IsDown('X', this))
	{
		ChangeState(ECHARACTERSTATE::RunShoot);
		return;
	}

	if (true == GameEngineInput::IsDown('Z', this))
	{
		ChangeState(ECHARACTERSTATE::Jump);
		return;
	}
}

void BaseCharacter::JumpStart()
{
	SetGravityForce(float4::UP * JUMPPOWER);
	ChangeAnimation("Jump");
}

void BaseCharacter::JumpUpdate(float _Delta)
{
	DirChange();
	ShootAimState();

	// Gravity
	if (GetGravityForce().Y > 0)
	{
		StoolPass = true;
		ActorGravity(_Delta, Transform.GetWorldPosition() + float4{ 0.0f, 80.0f });
	}
	else
	{
		StoolPass = false;
		ActorGravity(_Delta, Transform.GetWorldPosition());
	}

	//Move
	CharacterMove(_Delta);

	// Change State
	GameEngineColor Color = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (FLOORCOLOR == Color || (STOOLCOLOR == Color && false == StoolPass))
	{
		CreateJumpDust();

		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('Z', this))
	{
		ChangeState(ECHARACTERSTATE::Parry);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT, this))
	{
		ChangeState(ECHARACTERSTATE::Dash);
		return;
	}
}

void BaseCharacter::DashStart()
{
	GravityReset();
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		ChangeAnimation("Dash_Air");
	}
	else
	{
		ChangeAnimation("Dash");
	}
}

void BaseCharacter::DashUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (EACTORDIR::Right == Dir)
	{
		MovePos = float4::RIGHT * DashSpeed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}
	else if (EACTORDIR::Left == Dir)
	{
		MovePos = float4::LEFT * DashSpeed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}

	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition() + CheckPos, FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		Transform.AddLocalPosition(MovePos);
	}


	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		ChangeState(ECHARACTERSTATE::Fall);
		return;
	}
}

void BaseCharacter::FallStart()
{
	ChangeAnimation("Fall");
}

void BaseCharacter::FallUpdate(float _Delta)
{
	DirChange();

	// Gravity
	ActorGravity(_Delta, Transform.GetWorldPosition());

	if (0 == GetGravityForce().Y)
	{
		CreateJumpDust();
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}

	// Move
	CharacterMove(_Delta);

	if (true == GameEngineInput::IsDown('Z', this))
	{
		ChangeState(ECHARACTERSTATE::Parry);
		return;
	}
}

void BaseCharacter::DuckStart()
{
	PlayerCollision->Transform.SetLocalScale(CHARACTERDUCKCOLLISIONSCALE);
	PlayerCollision->Transform.SetLocalPosition(CHARACTERDUCKCOLLISIONPOS);
	ChangeAnimation("Duck");
}

void BaseCharacter::DuckUpdate(float _Delta)
{
	DirChange();
	ActorGravity(_Delta, Transform.GetWorldPosition());
	
	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (STOOLCOLOR == CheckColor)
	{
		if (true == GameEngineInput::IsPress(VK_DOWN, this) && true == GameEngineInput::IsDown('Z', this))
		{
			ChangeAnimation("Fall");
			StoolPass = true;
		}
	}

	if (true == GameEngineInput::IsPress('X', this))
	{
		ChangeState(ECHARACTERSTATE::DuckShoot);
		return;
	}

	if (true == GameEngineInput::IsFree(VK_DOWN, this))
	{
		PlayerCollision->Transform.SetLocalScale(CHARACTERCOLLISIONSCALE);
		PlayerCollision->Transform.SetLocalPosition(CHARACTERCOLLISIONPOS);
		ChangeState(ECHARACTERSTATE::Idle);
		return;
	}
}

void BaseCharacter::ParryStart()
{
	ChangeAnimation("Parry");
}

void BaseCharacter::ParryUpdate(float _Delta)
{
	DirChange();

	// Gravity
	if (GetGravityForce().Y > 0)
	{
		ActorGravity(_Delta, Transform.GetWorldPosition() + float4{ 0.0f, 80.0f });
	}
	else
	{
		ActorGravity(_Delta, Transform.GetWorldPosition());
	}

	//Move
	CharacterMove(_Delta);

	
	PlayerCollision->Collision(ECOLLISIONORDER::ParryObject,
		[=](std::vector<std::shared_ptr<GameEngineCollision>> _Col)
		{
			std::shared_ptr<GameEngineCollision> CurCollision = _Col[_Col.size() - 1];
			GameEngineActor* ColMaster = CurCollision->GetActor();
			ParryObject* ColParryOB = dynamic_cast<ParryObject*>(ColMaster);

			bool ParryActive = ColParryOB->GetParryActivation();
			if (true == ParryActive)
			{
				ColParryOB->ParryInactive();
				ColParryOB->IsParry();

				ParrySuccess = true;
				float4 ParryPos = float4::UP * JUMPPOWER * 0.7f;
				SetGravityForce(ParryPos);

				CreateParryEffect();

				ChangeState(ECHARACTERSTATE::Fall);
				return;
			}
		}
	);
}

void BaseCharacter::HitStart()
{
	NoDamage = true;

	GameEngineColor CheckColor = Map::MainMap->GetColor(Transform.GetWorldPosition(), FLOORCOLOR);

	if (CheckColor != FLOORCOLOR)
	{
		ChangeAnimation("Hit_Air");
	}
	else
	{
		ChangeAnimation("Hit");
	}

	--Hp;
}

void BaseCharacter::HitUpdate(float _Delta)
{
	if (Hp <= 0)
	{
		ChangeState(ECHARACTERSTATE::Death);
		return;
	}
}

void BaseCharacter::DeathStart()
{
	ChangeAnimation("Death");
	PlayerCollision->Off();
	StageLevel::StageFail();
}

void BaseCharacter::DeathUpdate(float _Delta)
{
	float4 MovePos = float4::UP * Speed * 0.5f * _Delta;

	Transform.AddLocalPosition(MovePos);

	if (true == PlayerRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}
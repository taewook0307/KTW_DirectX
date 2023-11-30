#include "PreCompile.h"
#include "PirateBullet.h"

#include "BaseCharacter.h"

PirateBullet::PirateBullet()
{
}

PirateBullet::~PirateBullet()
{
}

void PirateBullet::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::PrevBoss5);
	Renderer->CreateAnimation("Pirate_Bullet_Yellow_Move", "Pirate_Bullet_Yellow_Move");
	Renderer->CreateAnimation("Pirate_Bullet_Yellow_Death", "Pirate_Bullet_Yellow_Death");

	{
		CreateStateParameter Para;

		Para.Start =
			[=](GameEngineState* _State)
			{
				Renderer->ChangeAnimation("Pirate_Bullet_Yellow_Move");
			};

		Para.Stay =
			[=](float _Delta, GameEngineState* _State)
			{
				HitCheck();
				PirateMove(_Delta);
				CameraOutCheck();
			};

		PirateBulletState.CreateState(EPIRATEBULLETSTATE::Move, Para);
	}

	{
		CreateStateParameter Para;

		Para.Start =
			[=](GameEngineState* _State)
			{
				BulletCollision->Off();
				BulletPopSoundPlay();
				Renderer->ChangeAnimation("Pirate_Bullet_Yellow_Death");
			};

		Para.Stay =
			[=](float _Delta, GameEngineState* _State)
			{
				if (true == Renderer->IsCurAnimationEnd())
				{
					Death();
				}
			};

		PirateBulletState.CreateState(EPIRATEBULLETSTATE::Death, Para);
	}

	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Left);

	BulletCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	BulletCollision->Transform.SetLocalScale(PIRATEBULLETCOLLISIONSCALE);
	BulletCollision->Transform.SetLocalPosition(PIRATEBULLETCOLLISIONPOSITION);

	float4 CharacterPos = BaseCharacter::MainCharacter->Transform.GetWorldPosition();
	PlayerPos = { CharacterPos.X, CharacterPos.Y + ADJUSTVALUE };
	PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Move);
}

void PirateBullet::Update(float _Delta)
{
	PirateBulletState.Update(_Delta);
}

void PirateBullet::PirateMove(float _Delta)
{
	if (false == DirVectorSet)
	{
		DirVector = PlayerPos - Transform.GetWorldPosition();
		DirVectorSet = true;
	}

	float4 MovePos = DirVector.NormalizeReturn() * _Delta * Speed;
	Transform.AddLocalPosition(MovePos);

	CameraOutCheck();
}

void PirateBullet::CameraOutCheck()
{
	float4 BulletPos = Transform.GetWorldPosition();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	if (-200.0f > BulletPos.X
		|| WinScale.X + 200.0f < BulletPos.X
		|| 200.0f < BulletPos.Y
		|| -WinScale.Y - 200.0f > BulletPos.Y)
	{
		PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
}

void PirateBullet::HitCheck()
{
	if (true == BulletCollision->Collision(ECOLLISIONORDER::Player))
	{
		PirateBulletState.ChangeState(EPIRATEBULLETSTATE::Death);
		return;
	}
}

void PirateBullet::BulletPopSoundPlay()
{
	GameEngineSound::SoundPlay("sfx_pirate_squid_attack_pop.wav");
}
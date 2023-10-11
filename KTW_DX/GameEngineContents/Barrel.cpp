#include "PreCompile.h"
#include "Barrel.h"

#include "Map.h"

Barrel::Barrel()
{
}

Barrel::~Barrel()
{
}

void Barrel::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	Renderer->CreateAnimation("Barrel_Idle", "Barrel_Idle");
	Renderer->CreateAnimation("Barrel_SmashReady", "Barrel_SmashReady");
	Renderer->CreateAnimation("Barrel_Drop", "Barrel_Drop", 0.2f, -1, -1, false);
	Renderer->CreateAnimation("Barrel_Smash", "Barrel_Smash", 0.1f, -1, -1, false);
	Renderer->CreateAnimation("Barrel_SmashEnd", "Barrel_SmashEnd", 0.1f, -1, -1, false);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);
 
	AttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::MonsterBody);
	AttackCollision->Transform.SetLocalScale(ATTACKCOLLISIONSCALE);
	AttackCollision->Transform.SetLocalPosition(ATTACKCOLLISIONPOSITION);

	ChangeState(EBARRELSTATE::Idle);
}

void Barrel::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Barrel::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case EBARRELSTATE::Idle:
		return IdleUpdate(_Delta);
	case EBARRELSTATE::SmashReady:
		return SmashReadyUpdate(_Delta);
	case EBARRELSTATE::Drop:
		return DropUpdate(_Delta);
	case EBARRELSTATE::Smash:
		return SmashUpdate(_Delta);
	case EBARRELSTATE::SmashEnd:
		return SmashEndUpdate(_Delta);
	default:
		break;
	}
}

void Barrel::ChangeState(EBARRELSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
		{
		case EBARRELSTATE::Idle:
			IdleStart();
			break;
		case EBARRELSTATE::SmashReady:
			SmashReadyStart();
			break;
		case EBARRELSTATE::Drop:
			DropStart();
			break;
		case EBARRELSTATE::Smash:
			SmashStart();
			break;
		case EBARRELSTATE::SmashEnd:
			SmashEndStart();
			break;
		default:
			break;
		}
		CurState = _CurState;
	}
}

void Barrel::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Barrel_";
	
	AnimationName += _State;

	State = _State;

	Renderer->ChangeAnimation(AnimationName);
}

void Barrel::BarrelMove(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (EACTORDIR::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTMOVECHECKPOS;
	}
	else
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTMOVECHECKPOS;
	}

	CheckPos += Transform.GetWorldPosition();

	if (CheckPos.X > RIGHTMOVEMAX)
	{
		Dir = EACTORDIR::Left;
		return;
	}
	else if (CheckPos.X < LEFTMOVEMIN)
	{
		Dir = EACTORDIR::Right;
		return;
	}
	
	Transform.AddLocalPosition(MovePos);
}
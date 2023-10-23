#include "PreCompile.h"
#include "ShipBeam.h"

ShipBeam::ShipBeam()
{
}

ShipBeam::~ShipBeam()
{
}

void ShipBeam::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	Renderer->CreateAnimation("Ship_Beam_Appear", "Ship_Beam", 0.05f, 0, 4, false);
	Renderer->SetEndEvent("Ship_Beam_Appear",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer->ChangeAnimation("Ship_Beam_Stay");
			return;
		}
	);
	Renderer->CreateAnimation("Ship_Beam_Stay", "Ship_Beam", 0.05f, 5, 6, true);
	Renderer->CreateAnimation("Ship_Beam_End", "Ship_Beam", 0.05f, 7, 10, false);
	Renderer->SetEndEvent("Ship_Beam_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	Renderer->SetAutoScaleRatio(2.0f);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Right);
	ChangeState(ESHIPBEAMSTATE::Appear);

	AttackCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::BossAttack);
	AttackCollision->Transform.SetLocalScale({ 1280.0f, 260.0f });
	AttackCollision->Transform.SetLocalPosition({ -640.0f, 0.0f });
	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
}

void ShipBeam::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void ShipBeam::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case ESHIPBEAMSTATE::Appear:
		return AppearUpdate(_Delta);
	default:
		break;
	}
}

void ShipBeam::ChangeState(ESHIPBEAMSTATE _CurState)
{
	if (_CurState != CurState)
	{
		switch (_CurState)
		{
		case ESHIPBEAMSTATE::Appear:
			AppearStart();
			break;
		case ESHIPBEAMSTATE::End:
			EndStart();
			break;
		default:
			break;
		}
		CurState = _CurState;
	}
}

void ShipBeam::ChangeAnimation(std::string_view _State)
{
	std::string AnimationName = "Ship_Beam_";
	AnimationName += _State;
	State = _State;
	Renderer->ChangeAnimation(AnimationName);
}

void ShipBeam::AppearStart()
{
	ChangeAnimation("Appear");
}

void ShipBeam::AppearUpdate(float _Delta)
{
	if (0.0f > AppearTimer)
	{
		AppearTimer = BEAMAPPEARTIMER;
		ChangeState(ESHIPBEAMSTATE::End);
		return;
	}

	AppearTimer -= _Delta;
}

void ShipBeam::EndStart()
{
	AttackCollision->Off();
	ChangeAnimation("End");
}
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
	BeamRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BossEffect);
	BeamRenderer->CreateAnimation("Ship_Beam_Appear", "Ship_Beam", 0.05f, 0, 4, false);
	BeamRenderer->SetEndEvent("Ship_Beam_Appear",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			BeamRenderer->ChangeAnimation("Ship_Beam_Stay");
			return;
		}
	);
	BeamRenderer->CreateAnimation("Ship_Beam_Stay", "Ship_Beam", 0.05f, 5, 6, true);
	BeamRenderer->CreateAnimation("Ship_Beam_End", "Ship_Beam", 0.05f, 7, 10, false);
	BeamRenderer->SetEndEvent("Ship_Beam_End",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	BeamRenderer->SetAutoScaleRatio(2.0f);
	BeamRenderer->AutoSpriteSizeOn();
	BeamRenderer->SetPivotType(PivotType::Right);
	ChangeState(ESHIPBEAMSTATE::Appear);
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
	BeamRenderer->ChangeAnimation(AnimationName);
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
	ChangeAnimation("End");
}
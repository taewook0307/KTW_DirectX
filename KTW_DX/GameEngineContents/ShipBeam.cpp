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
			BeamRenderer->ChangeAnimation("Ship_Beam");
			return;
		}
	);
	BeamRenderer->CreateAnimation("Ship_Beam", "Ship_Beam", 0.05f, 5, 6);

	BeamRenderer->AutoSpriteSizeOn();
	BeamRenderer->SetPivotType(PivotType::Right);
	BeamRenderer->ChangeAnimation("Ship_Beam_Appear");
}

void ShipBeam::Update(float _Delta)
{

}
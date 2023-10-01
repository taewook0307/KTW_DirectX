#include "PreCompile.h"
#include "ShipBoss.h"

ShipBoss::ShipBoss()
{
}

ShipBoss::~ShipBoss()
{
}

void ShipBoss::Start()
{
	ShipRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Boss);
	ShipRenderer->CreateAnimation("ShipIdle", "Ship_Idle");

	ShipRenderer->ChangeAnimation("ShipIdle");
	ShipRenderer->AutoSpriteSizeOn();
	ShipRenderer->SetPivotType(PivotType::RightBottom);
}
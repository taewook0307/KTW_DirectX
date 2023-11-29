#include "PreCompile.h"
#include "Lava.h"

Lava::Lava()
{
}

Lava::~Lava()
{
}

void Lava::Start()
{
	LavaRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBackGround);
	LavaRenderer->CreateAnimation("Lava_A", "Lava_A");
	LavaRenderer->CreateAnimation("Lava_B", "Lava_B");
	LavaRenderer->AutoSpriteSizeOn();
	LavaRenderer->SetPivotType(PivotType::Top);

	SmokeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBackGround);
	SmokeRenderer->CreateAnimation("Smoke_A", "Smoke_A");
	SmokeRenderer->CreateAnimation("Smoke_B", "Smoke_B");
	SmokeRenderer->AutoSpriteSizeOn();
	SmokeRenderer->SetPivotType(PivotType::Bottom);

	LavaRenderer->ChangeAnimation("Lava_A");
	SmokeRenderer->ChangeAnimation("Smoke_A");
	SmokeRenderer->Transform.SetLocalPosition({ 15.0f, 0.0f });
}

void Lava::ChagneLavaType()
{
	LavaRenderer->ChangeAnimation("Lava_B");
	SmokeRenderer->ChangeAnimation("Smoke_B");
	SmokeRenderer->Transform.SetLocalPosition({ 5.0f, -10.0f });
}
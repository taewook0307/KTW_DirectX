#include "PreCompile.h"
#include "Smoke.h"

Smoke::Smoke()
{
}

Smoke::~Smoke()
{
}

void Smoke::Start()
{
	SmokeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);
	SmokeRenderer->CreateAnimation("Smoke_A", "Smoke_A");
	SmokeRenderer->CreateAnimation("Smoke_B", "Smoke_B");
	SmokeRenderer->AutoSpriteSizeOn();
	SmokeRenderer->SetPivotType(PivotType::Bottom);

	SmokeRenderer->ChangeAnimation("Smoke_A");
}
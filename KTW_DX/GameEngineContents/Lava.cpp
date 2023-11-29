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
	LavaRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);
	LavaRenderer->CreateAnimation("Lava_A", "Lava_A");
	LavaRenderer->CreateAnimation("Lava_B", "Lava_B");
	LavaRenderer->AutoSpriteSizeOn();
	LavaRenderer->SetPivotType(PivotType::Top);

	LavaRenderer->ChangeAnimation("Lava_B");
}
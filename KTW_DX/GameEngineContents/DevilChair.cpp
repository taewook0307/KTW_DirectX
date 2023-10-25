#include "PreCompile.h"
#include "DevilChair.h"

DevilChair::DevilChair()
{
}

DevilChair::~DevilChair()
{
}

void DevilChair::Start()
{
	ChairRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperMap1);
	ChairRenderer->SetSprite("LastStageChair.png");
	ChairRenderer->AutoSpriteSizeOn();
	ChairRenderer->SetPivotType(PivotType::Bottom);
}
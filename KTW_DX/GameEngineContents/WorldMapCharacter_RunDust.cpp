#include "PreCompile.h"
#include "WorldMapCharacter_RunDust.h"

WorldMapCharacter_RunDust::WorldMapCharacter_RunDust()
{
}

WorldMapCharacter_RunDust::~WorldMapCharacter_RunDust()
{
}

void WorldMapCharacter_RunDust::Start()
{
	DustRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackEffect);
	DustRenderer->CreateAnimation("RunDust", "WorldMapCharacter_Run_Dust", 0.05f);
	DustRenderer->SetEndEvent("RunDust",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);
	DustRenderer->AutoSpriteSizeOn();
	DustRenderer->SetAutoScaleRatio(0.8f);

	DustRenderer->ChangeAnimation("RunDust");
}
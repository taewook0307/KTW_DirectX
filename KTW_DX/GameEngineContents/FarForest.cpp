#include "PreCompile.h"
#include "FarForest.h"

FarForest::FarForest()
{
}

FarForest::~FarForest()
{
}

void FarForest::Start()
{
	FarForestRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);
	FarForestRenderer->SetSprite("FirstBossBackGround_1.png");
	FarForestRenderer->SetPivotType(PivotType::Top);
	FarForestRenderer->AutoSpriteSizeOn();
}
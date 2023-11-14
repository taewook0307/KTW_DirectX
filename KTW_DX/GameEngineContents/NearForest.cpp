#include "PreCompile.h"
#include "NearForest.h"

NearForest::NearForest()
{
}

NearForest::~NearForest()
{
}

void NearForest::Start()
{
	NearForestRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::BackGround);
	NearForestRenderer->SetSprite("FirstBossBackGround_2.png");
	NearForestRenderer->AutoSpriteSizeOn();
	NearForestRenderer->SetPivotType(PivotType::Bottom);
}
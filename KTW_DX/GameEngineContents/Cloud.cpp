#include "PreCompile.h"
#include "Cloud.h"

Cloud::Cloud()
{
}

Cloud::~Cloud()
{
}

void Cloud::SetCloud(int _Order, std::string_view _ImageName)
{
	CloudRenderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
	CloudRenderer->SetSampler("EngineBaseWRAPSampler");
	CloudRenderer->SetSprite(_ImageName);
	CloudRenderer->AutoSpriteSizeOn();
	CloudRenderer->SetAutoScaleRatio(1.25f);
	CloudRenderer->SetPivotType(PivotType::LeftBottom);
}

void Cloud::Update(float _Delta)
{
	CloudRenderer->RenderBaseInfoValue.VertexUVPlus.X += CloudSpeed * _Delta;
}
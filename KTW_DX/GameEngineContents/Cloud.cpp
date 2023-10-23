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
	CloudRenderer->SetSprite(_ImageName);
	CloudRenderer->AutoSpriteSizeOn();
	CloudRenderer->SetAutoScaleRatio(1.25f);
	CloudRenderer->SetPivotType(PivotType::Bottom);
}

void Cloud::Update(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition();
	float4 ScaleHalf = CloudRenderer->GetImageTransform().GetWorldScale().Half();
	
	if (Pos.X <= -ScaleHalf.X)
	{
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Transform.SetWorldPosition({ WinScale.X + ScaleHalf.X, Pos.Y });
	}

	float4 MovePos = float4::LEFT * CloudSpeed * _Delta;
	Transform.AddLocalPosition(MovePos);
}
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
	CloudRenderer->SetPivotType(PivotType::LeftBottom);
}

void Cloud::Update(float _Delta)
{
	float4 Pos = Transform.GetWorldPosition();
	float4 Scale = CloudRenderer->GetImageTransform().GetWorldScale();
	
	if (Pos.X <= -Scale.X)
	{
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Transform.SetWorldPosition({ WinScale.X, Pos.Y });
	}

	float4 MovePos = float4::LEFT * CloudSpeed * _Delta;
	Transform.AddLocalPosition(MovePos);
}
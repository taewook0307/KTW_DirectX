#include "PreCompile.h"
#include "Ocean.h"

Ocean::Ocean()
{
}

Ocean::~Ocean()
{
}

void Ocean::SetOceanAnimation(int _Order, std::string_view _AniMationName, std::string_view _SpriteName, float _Inter, int _Start, int _End, bool _Loop)
{
	OceanRenderer = CreateComponent<GameEngineSpriteRenderer>(_Order);

	OceanRenderer->CreateAnimation(_AniMationName, _SpriteName, _Inter, _Start, _End, _Loop);

	OceanRenderer->SetPivotType(PivotType::Bottom);
	OceanRenderer->AutoSpriteSizeOn();
	OceanRenderer->SetAutoScaleRatio(1.3f);

	OceanRenderer->ChangeAnimation(_AniMationName);
}
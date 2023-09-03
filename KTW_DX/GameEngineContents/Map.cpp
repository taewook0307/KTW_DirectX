#include "PreCompile.h"
#include "Map.h"

Map* Map::MainMap = nullptr;

Map::Map()
{
	MainMap = this;
}

Map::~Map()
{
}

void Map::Start()
{
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Map);
}

void Map::MapInit(std::string_view _SpriteName)
{
	MapRenderer->SetSprite(_SpriteName);
	MapRenderer->AutoSpriteSizeOn();
}

GameEngineColor Map::GetColor(float4 _Pos, std::string_view _MapFileName, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(_MapFileName);

	return Tex->GetColor(_Pos, _DefaultColor);
}
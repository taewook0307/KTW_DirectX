#include "PreCompile.h"
#include "Map.h"

Map::Map()
{
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
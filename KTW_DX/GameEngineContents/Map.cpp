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
	MapRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
}

void Map::MapInit(std::string_view _SpriteName)
{
	MapRenderer->SetSprite(_SpriteName);
	MapRenderer->AutoSpriteSizeOn();
}
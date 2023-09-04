#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Map : public GameEngineActor
{
public:
	static Map* MainMap;

	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void MapInit(std::string_view _SpriteName);
	void BitMapInit(std::string_view _SpriteName);

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor);

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BitMapRenderer = nullptr;

	std::string BitMapFileName = "";

	void Start() override;
};
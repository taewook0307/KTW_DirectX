#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void MapInit(std::string_view _SpriteName);

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BitMapRenderer = nullptr;

	void Start() override;
};
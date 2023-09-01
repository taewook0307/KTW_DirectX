#pragma once

#include <GameEngineCore/GameEngineLevel.h>

class MiniMapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MiniMapLevel();
	~MiniMapLevel();

	// delete Function
	MiniMapLevel(const MiniMapLevel& _Other) = delete;
	MiniMapLevel(MiniMapLevel&& _Other) noexcept = delete;
	MiniMapLevel& operator=(const MiniMapLevel& _Other) = delete;
	MiniMapLevel& operator=(MiniMapLevel&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class Map> MiniMap;
	std::shared_ptr<class MiniMapCharacter> Character;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void Update(float _Delta) override;
};
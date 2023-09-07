#pragma once

#include <GameEngineCore/GameEngineLevel.h>

#define TUTORIALENTERPOS { 823.0f, -2100.0f }
#define FIRSTBOSSENTERPOS { 2205.0f, -2070.0f }

#define CHARACTERSTARTPOS { 885.0f, -2208.0f }

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
	std::shared_ptr<class Map> MiniMap = nullptr;
	std::shared_ptr<class MiniMapCharacter> Character = nullptr;

	std::shared_ptr<class MiniMapEnter> TutorialEnter = nullptr;
	std::shared_ptr<class MiniMapEnter> FirstEnter = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Update(float _Delta) override;

	static float4 CharacterPos;
};
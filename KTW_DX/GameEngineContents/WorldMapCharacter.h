#pragma once

#include "BaseActor.h"

#include "ContentsSoundPlayer.h"

#define MINIMAPCHARACTERCOLLISIONSCALE { 60.0f, 90.0f }

#define CLEARLOOPCOUNT 2

class WorldMapCharacter : public BaseActor
{
public:
	// constrcuter destructer
	WorldMapCharacter();
	~WorldMapCharacter();

	// delete Function
	WorldMapCharacter(const WorldMapCharacter& _Other) = delete;
	WorldMapCharacter(WorldMapCharacter&& _Other) noexcept = delete;
	WorldMapCharacter& operator=(const WorldMapCharacter& _Other) = delete;
	WorldMapCharacter& operator=(WorldMapCharacter&& _Other) noexcept = delete;

	void ChangeClearState();

	bool GetAnimationEnd(std::string_view _AnimationName)
	{
		return WorldCharacterRenderer->IsCurAnimation(_AnimationName) && WorldCharacterRenderer->IsCurAnimationEnd();
	}

protected:
	void DirChange();
	void ChangeAnimation(std::string_view _State);

	void IdleStart(GameEngineState* _State);
	void IdleUpdate(float _Delta, GameEngineState* _State);

	void RunStart(GameEngineState* _State);
	void RunUpdate(float _Delta, GameEngineState* _State);

	int ClearLoopCount = CLEARLOOPCOUNT;
	void ClearStart(GameEngineState* _State);
	void ClearUpdate(float _Delta, GameEngineState* _State);

protected:
	EACTORDIR Dir = EACTORDIR::None;
	ECHARACTERAIMDIR MoveDir = ECHARACTERAIMDIR::Down;
	EWORLDMAPCHARACTERSTATE CurState = EWORLDMAPCHARACTERSTATE::None;
	std::string State = "";

	class WorldMapPortal* PrevPortal = nullptr;
	class WorldMapPortal* CurPortal = nullptr;
	EventParameter PortalPara;

private:
	std::shared_ptr<GameEngineSpriteRenderer> WorldCharacterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> WorldCharacterCollision = nullptr;

	GameEngineState WorldMapCharacterState;
	float Speed = 200.0f;
	bool SpeedUp = false;

	void Start() override;
	void Update(float _Delta) override;

	void PortalEventParaSetting();

	ContentsSoundPlayer RunSoundPlayer;

	void CreateRunDust();
	void RunSoundSetting();
};
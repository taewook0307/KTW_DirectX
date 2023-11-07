#pragma once

#include "BaseActor.h"

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

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	int ClearLoopCount = CLEARLOOPCOUNT;
	void ClearStart();
	void ClearUpdate(float _Delta);

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

	void Start() override;
	void Update(float _Delta) override;

	void PortalEventParaSetting();
};
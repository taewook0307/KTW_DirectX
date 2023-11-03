#pragma once

#include "BaseActor.h"

#define MINIMAPCHARACTERCOLLISIONSCALE { 60.0f, 90.0f }

#define CLEARLOOPCOUNT 2

class MiniMapCharacter : public BaseActor
{
public:
	// constrcuter destructer
	MiniMapCharacter();
	~MiniMapCharacter();

	// delete Function
	MiniMapCharacter(const MiniMapCharacter& _Other) = delete;
	MiniMapCharacter(MiniMapCharacter&& _Other) noexcept = delete;
	MiniMapCharacter& operator=(const MiniMapCharacter& _Other) = delete;
	MiniMapCharacter& operator=(MiniMapCharacter&& _Other) noexcept = delete;

	void ChangeClearState();

	bool GetAnimationEnd(std::string_view _AnimationName)
	{
		return MiniCharacterRenderer->IsCurAnimation(_AnimationName) && MiniCharacterRenderer->IsCurAnimationEnd();
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
	EMINIMAPCHARACTERSTATE CurState = EMINIMAPCHARACTERSTATE::None;
	std::string State = "";

	class MiniMapPortal* PrevPortal = nullptr;
	class MiniMapPortal* CurPortal = nullptr;
	EventParameter PortalPara;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MiniCharacterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MiniCharacterCollision = nullptr;

	GameEngineState MiniMapCharacterState;

	void Start() override;
	void Update(float _Delta) override;

	void PortalEventParaSetting();
};
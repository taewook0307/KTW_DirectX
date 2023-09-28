#pragma once

#include "BaseActor.h"

#define MINIMAPCHARACTERCOLLISIONSCALE { 60.0f, 90.0f }

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

protected:
	void DirChange();
	void ChangeState(EMINIMAPCHARACTERSTATE _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

protected:
	EACTORDIR Dir = EACTORDIR::None;
	ECHARACTERAIMDIR MoveDir = ECHARACTERAIMDIR::Down;
	EMINIMAPCHARACTERSTATE CurState = EMINIMAPCHARACTERSTATE::None;
	std::string State = "";

private:
	std::shared_ptr<GameEngineSpriteRenderer> MiniCharacterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MiniCharacterCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
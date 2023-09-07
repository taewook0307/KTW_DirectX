#pragma once

#include "BaseActor.h"

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
	void ChangeState(MiniMapCharacterState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

protected:
	CharacterDir Dir = CharacterDir::None;
	CharacterAimDir MoveDir = CharacterAimDir::Down;
	MiniMapCharacterState CurState = MiniMapCharacterState::None;
	std::string State = "";

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSprite = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
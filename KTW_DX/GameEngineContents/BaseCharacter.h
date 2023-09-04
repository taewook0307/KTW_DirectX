#pragma once
#include "BaseActor.h"

class BaseCharacter : public BaseActor
{
public:
	// constrcuter destructer
	BaseCharacter();
	~BaseCharacter();

	// delete Function
	BaseCharacter(const BaseCharacter& _Other) = delete;
	BaseCharacter(BaseCharacter&& _Other) noexcept = delete;
	BaseCharacter& operator=(const BaseCharacter& _Other) = delete;
	BaseCharacter& operator=(BaseCharacter&& _Other) noexcept = delete;

protected:
	void ChangeState(CharacterState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	CharacterDir Dir = CharacterDir::None;
	CharacterState CurState = CharacterState::Idle;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
};
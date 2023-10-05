#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Shark : public GameEngineActor
{
public:
	// constrcuter destructer
	Shark();
	~Shark();

	// delete Function
	Shark(const Shark& _Other) = delete;
	Shark(Shark&& _Other) noexcept = delete;
	Shark& operator=(const Shark& _Other) = delete;
	Shark& operator=(Shark&& _Other) noexcept = delete;

protected:

private:
	void FinStart();
	void FinUpdate(float _Delta);

	void EntryStart();
	void EntryUpdate(float _Delta);

	void BiteStart();

	void LeaveStart();
	void LeaveUpdate(float _Delta);

private:
	float Speed = 400.0f;
	ESHARKSTATE CurState = ESHARKSTATE::None;
	std::string State = "";

	void StateUpdate(float _Delta);
	void ChangeState(ESHARKSTATE _State);
	void ChangeAnimation(std::string_view _State);

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
};
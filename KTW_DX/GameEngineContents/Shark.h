#pragma once

#include <GameEngineCore/GameEngineActor.h>

#define SHARKANMATIONINTER 0.05f
#define SHARKBITEANIMATIONINTER 0.03f

#define SHARKCOLLISIONSCALE { 750.0f, 260.0f }
#define SHARKCOLLISIONPOSITION { 325.0f, 130.0f }

#define FINSPEED 500.0f
#define SHARKSPEED 800.0f
#define LEAVESPEED 400.0f

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
	float FinSpeed = FINSPEED;
	float Speed = SHARKSPEED;
	float LeaveSpeed = LEAVESPEED;
	ESHARKSTATE CurState = ESHARKSTATE::None;
	std::string State = "";

	void StateUpdate(float _Delta);
	void ChangeState(ESHARKSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> SharkRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
};
#pragma once

#include "BaseActor.h"

#define IDLETIMER 3.0f
#define RIGHTMOVEMAX 900.0f
#define LEFTMOVEMIN 200.0f
#define RIGHTMOVECHECKPOS { 40.0f, 0.0f }
#define LEFTMOVECHECKPOS { -40.0f, 0.0f }
#define ATTACKCOLLISIONSCALE { 160.0f, 110.0f }
#define ATTACKCOLLISIONPOSITION { 0.0f, 90.0f }

class Barrel : public BaseActor
{
public:
	// constrcuter destructer
	Barrel();
	~Barrel();

	// delete Function
	Barrel(const Barrel& _Other) = delete;
	Barrel(Barrel&& _Other) noexcept = delete;
	Barrel& operator=(const Barrel& _Other) = delete;
	Barrel& operator=(Barrel&& _Other) noexcept = delete;

protected:

private:
	float IdleTimer = IDLETIMER;
	void IdleStart();
	void IdleUpdate(float _Delta);

	void SmashReadyStart();
	void SmashReadyUpdate(float _Delta);

	void DropStart();
	void DropUpdate(float _Delta);

	void SmashStart();
	void SmashUpdate(float _Delta);

	void SmashEndStart();
	void SmashEndUpdate(float _Delta);

private:
	float Speed = 100.0f;
	EBARRELSTATE CurState = EBARRELSTATE::None;
	std::string State = "";
	EACTORDIR Dir = EACTORDIR::Left;

	void StateUpdate(float _Delta);
	void ChangeState(EBARRELSTATE _State);
	void ChangeAnimation(std::string_view _State);
	void BarrelMove(float _Delta);

	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
};
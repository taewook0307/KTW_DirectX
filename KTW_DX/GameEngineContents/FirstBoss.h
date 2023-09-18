#pragma once

#include "BaseBoss.h"

class FirstBoss : public BaseBoss
{
	friend class Bullet;
public:
	// constrcuter destructer
	FirstBoss();
	~FirstBoss();

	// delete Function
	FirstBoss(const FirstBoss& _Other) = delete;
	FirstBoss(FirstBoss&& _Other) noexcept = delete;
	FirstBoss& operator=(const FirstBoss& _Other) = delete;
	FirstBoss& operator=(FirstBoss&& _Other) noexcept = delete;

protected:

private:
	void IntroStart();
	void IntroUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	std::string State = "";

private:
	float JumpPower = 1500.0f;
	float Speed = 600.0f;
	int BounceCount = 0;

	std::shared_ptr<GameEngineSpriteRenderer> FirstBossRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossCollision = nullptr;

	ActorDir FirstBossDir = ActorDir::Left;
	FirstBossState CurState = FirstBossState::None;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	void PhaseChange();
	void ChangeState(FirstBossState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void FirstBossMove(float4 _Delta);
};
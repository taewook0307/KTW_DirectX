#pragma once

#include "BaseActor.h"

class FirstBoss : public BaseActor
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

	void PlusHitCount()
	{
		++HitCount;
	}

	std::string State = "";

	BossPhase CurPhase = BossPhase::Phase1;
	int HitCount = 0;

private:
	float JumpPower = 1500.0f;

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

	void FirstBossGravity(float4 _CheckPos, float _Delta);
};
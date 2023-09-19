#pragma once

#include "BaseBoss.h"

class FirstBossPhase3 : public BaseBoss
{
public:
	// constrcuter destructer
	FirstBossPhase3();
	~FirstBossPhase3();

	// delete Function
	FirstBossPhase3(const FirstBossPhase3& _Other) = delete;
	FirstBossPhase3(FirstBossPhase3&& _Other) noexcept = delete;
	FirstBossPhase3& operator=(const FirstBossPhase3& _Other) = delete;
	FirstBossPhase3& operator=(FirstBossPhase3&& _Other) noexcept = delete;

protected:

private:
	float IntroTimer = 3.0f;

	void IntroStart();
	void IntroUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void TurnStart();
	void TurnUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

private:
	float Speed = 400.0f;
	std::string State = "";
	ActorDir FirstBossDir = ActorDir::Left;
	FirstBossState CurState = FirstBossState::None;

	std::shared_ptr<GameEngineSpriteRenderer> FirstBossRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	void ChangeState(FirstBossState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);
};
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

	bool LandSoundOn = false;

	void FallStart();
	void FallUpdate(float _Delta);

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

	void CreateEffect(EBOSSSTATE _State);

	void IdleSoundPlay();
	void MoveSoundPlay();
	void MoveVoiceSoundPlay();
	void AttackSoundPlay();

	GameEngineSoundPlayer MoveSound;

private:
	int DirChangeCount = 0;

	float Speed = 800.0f;
	std::string State = "";
	EBOSSSTATE CurState = EBOSSSTATE::None;
	EACTORDIR FirstBossDir = EACTORDIR::Left;

	std::shared_ptr<GameEngineSpriteRenderer> FirstBossRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossCollision = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossAttackCollision = nullptr;
	std::shared_ptr<class FirstBossPhase3Effect> Effect = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	void StateUpdate(float _Delta);
	void ChangeState(EBOSSSTATE _CurState);
	void ChangeAnimation(std::string_view _State);
};
#pragma once

#include "BaseBoss.h"

#define PHASE1HP 288
#define PHASE2HP 540

#define PHASE2INTROTIMER 3.0f

#define PHASE1BODYCOLLISIONSCALE { 180.0f, 180.0f }
#define PHASE2BODYCOLLISIONSCALE { 335.0f, 335.0f }
#define PHASE1ATTACKCOLLISIONSCALE { 330.0f, 330.0f }
#define PHASE2ATTACKCOLLISIONSCALE { 220.0f, 220.0f }

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

	bool GetPhase2End() const
	{
		return Phase2End;
	}

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

	void DeathStart();
	void DeathUpdate(float _Delta);

	void SlimeStart();
	void SlimeUpdate(float _Delta);

	std::string State = "";
	EBOSSSTATE CurState = EBOSSSTATE::None;

private:
	float JumpPower = 1500.0f;
	float Speed = 400.0f;
	int BounceCount = 0;

	bool Phase2End = false;

	std::shared_ptr<GameEngineSpriteRenderer> FirstBossRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossCollision = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossUnDamageCollision = nullptr;
	std::shared_ptr<GameEngineCollision> FirstBossAttackCollision = nullptr;

	EACTORDIR FirstBossDir = EACTORDIR::Left;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	void PhaseChange();
	void ChangeState(EBOSSSTATE _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	void FirstBossMove(float4 _Delta);
	void CreateMoveDust();

	float Phase2IntroTimer = PHASE2INTROTIMER;
	std::vector<std::shared_ptr<class FirstMapParryObject>> AllParry;
	void CreateParryObject();
	void AllParryDeath();
};
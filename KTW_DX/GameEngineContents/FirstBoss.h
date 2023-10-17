#pragma once

#include "BaseBoss.h"

#define PHASE1HP 288
#define PHASE2HP 540

#define PHASE2INTROTIMER 3.0f

#define PHASE1BODYCOLLISIONSCALE { 180.0f, 180.0f }
#define PHASE2BODYCOLLISIONSCALE { 335.0f, 335.0f }
#define PHASE1ATTACKCOLLISIONSCALE { 330.0f, 330.0f }
#define PHASE2ATTACKCOLLISIONSCALE { 220.0f, 220.0f }

#define PHASE1BOSSATTACKCOLLISIONSCALE1 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE2 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE3 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE4 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE5 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE6 { 150.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE7 { 230.0f, 230.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE8 { 270.0f, 270.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE9 { 340.0f, 340.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE10 { 360.0f, 360.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE11 { 300.0f, 300.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE12 { 250.0f, 250.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE13 { 190.0f, 190.0f }
#define PHASE1BOSSATTACKCOLLISIONSCALE14 { 190.0f, 190.0f }

#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION1 { 40.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION2 { 80.0f, 160.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION3 { 120.0f, 130.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION4 { 140.0f, 120.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION5 { 150.0f, 115.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION6 { 160.0f, 100.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION7 { 80.0f, 210.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION8 { -40.0f, 250.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION9 { -420.0f, 230.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION10 { -415.0f, 240.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION11 { -160.0f, 230.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION12 { -90.0f, 190.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION13 { -55.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONLEFTPOSITION14 { -5.0f, 120.0f }

#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION1 { -40.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION2 { -80.0f, 160.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION3 { -120.0f, 130.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION4 { -140.0f, 120.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION5 { -150.0f, 115.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION6 { -160.0f, 100.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION7 { -80.0f, 210.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION8 { 40.0f, 250.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION9 { 420.0f, 230.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION10 { 415.0f, 240.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION11 { 160.0f, 230.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION12 { 90.0f, 190.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION13 { 55.0f, 150.0f }
#define PHASE1BOSSATTACKCOLLISIONRIGHTPOSITION14 { 5.0f, 120.0f }

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
	void StateUpdate(float _Delta);
	void ChangeState(EBOSSSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	void FirstBossMove(float4 _Delta);
	void CreateMoveDust();

	float Phase2IntroTimer = PHASE2INTROTIMER;
	std::vector<std::shared_ptr<class FirstMapParryObject>> AllParry;
	void CreateParryObject();
	void AllParryDeath();
};
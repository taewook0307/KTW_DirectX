#pragma once

#include "BaseBoss.h"

#define PHASE1HP 400
#define PHASE2HP 952

#define MINSHOOTCOUNT 3
#define MAXSHOOTCOUNT 5

#define PIRATEBOSSANIMATIONINTER 0.05f

#define PIRATECOLLISIONSCALE { 390.0f, 250.0f }
#define PIRATECOLLISIONPOSITION { 0.0f, 250.0f }

#define IDLETIMER 3.0f
#define INTROTIMER 3.0f
#define PIRATEDEATHTIMER 3.0f

#define SUMMONSHARKPOS { 1000.0f, -500.0f }
#define SUMMONSCOPEPOS { 1050.0f, -720.0f }

class PirateBoss : public BaseBoss
{
public:
	static PirateBoss* MainPirateBoss;

	// constrcuter destructer
	PirateBoss();
	~PirateBoss();

	// delete Function
	PirateBoss(const PirateBoss& _Other) = delete;
	PirateBoss(PirateBoss&& _Other) noexcept = delete;
	PirateBoss& operator=(const PirateBoss& _Other) = delete;
	PirateBoss& operator=(PirateBoss&& _Other) noexcept = delete;

	void ChangePhase3();

protected:

private:
	float IntroTimer = INTROTIMER;
	void IntroStart();
	void IntroUpdate(float _Delta);
	
	float IdleTimer = IDLETIMER;
	void IdleStart();
	void IdleUpdate(float _Delta);

	void ShootStart();

	void KnockoutStart();

	bool WhistleTime = true;
	void WhistleStart();
	void WhistleUpdate(float _Delta);

	float PirateDeathTimer = PIRATEDEATHTIMER;
	void DeathStart();
	void DeathUpdate(float _Delta);

private:
	void StateUpdate(float _Delta);
	void ChangeState(EPIRATEBOSSSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	EPIRATEBOSSSTATE CurState = EPIRATEBOSSSTATE::None;
	std::string State = "";

	std::shared_ptr<GameEngineSpriteRenderer> PirateRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> PirateUpperRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PirateCollision = nullptr;

	void Start() override;
	void Update(float _Delta);
	void CreatePirateBullet();
	void PhaseChange();

	bool SummonScope = false;
	void SummonEnemy();

	int ShootCount = 3;

	void IntroSoundPlay();
	void ShootSoundPlay();
};
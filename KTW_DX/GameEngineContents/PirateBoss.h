#pragma once

#include "BaseBoss.h"
#define PIRATEBOSSANIMATIONINTER 0.05f
#define IDLETIMER 2.0f

class PirateBoss : public BaseBoss
{
public:
	// constrcuter destructer
	PirateBoss();
	~PirateBoss();

	// delete Function
	PirateBoss(const PirateBoss& _Other) = delete;
	PirateBoss(PirateBoss&& _Other) noexcept = delete;
	PirateBoss& operator=(const PirateBoss& _Other) = delete;
	PirateBoss& operator=(PirateBoss&& _Other) noexcept = delete;

protected:

private:
	float IdleTimer = IDLETIMER;
	void IdleStart();
	void IdleUpdate(float _Delta);

	void ShootStart();
	void ShootUpdate(float _Delta);

	void LaughStart();
	void LaughUpdate(float _Delta);

	void KnockoutStart();
	void KnockoutUpdate(float _Delta);

	void WhistleStart();
	void WhistleUpdate(float _Delta);

private:
	void ChangeState(EPIRATEBOSSSTATE _State);
	void StateUpdate(float _Delta);
	void ChangeAnimation(std::string_view _State);

	EPIRATEBOSSSTATE CurState = EPIRATEBOSSSTATE::None;
	std::string State = "";

	std::shared_ptr<GameEngineSpriteRenderer> PirateRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> PirateUpperRenderer = nullptr;

	void Start() override;
	void Update(float _Delta);
	void CreatePirateBullet();

	int ShootCount = 0;
};
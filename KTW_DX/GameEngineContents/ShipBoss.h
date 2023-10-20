#pragma once

#include "BaseBoss.h"

#define PHASE3HP 448

#define SHIPANIMATIONINTER 0.05f
#define PHASE1SHIPIDLETIMER 7.0f
#define PHASE2SHIPIDLETIMER 2.0f
#define PHASE3SHIPIDLETIMER 1.4f
#define SHIPCHARGETIMER 2.0f
#define SHIPBEAMTIMER 3.0f
#define ATTACKCOUNT 3

#define SHIPRAILPOS { -100.0f, 390.0f }
#define SHIPSAILPOS { -50.0f, 500.0f }
#define SHIPMASTPOS { -100.0f, 400.0f }

class ShipBoss : public BaseBoss
{
	friend class PirateBoss;
public:
	static ShipBoss* MainShip;

	// constrcuter destructer
	ShipBoss();
	~ShipBoss();

	// delete Function
	ShipBoss(const ShipBoss& _Other) = delete;
	ShipBoss(ShipBoss&& _Other) noexcept = delete;
	ShipBoss& operator=(const ShipBoss& _Other) = delete;
	ShipBoss& operator=(ShipBoss&& _Other) noexcept = delete;

protected:
	float IdleTimer = SHIPIDLETIMER;
	void IdleStart();
	void IdleUpdate(float _Delta);

	int AttackCount = ATTACKCOUNT;
	void AttackStart();
	void AttackUpdate(float _Delta);

	void WinceStart();

	void TransformStart();

	float ChargeTimer = SHIPCHARGETIMER;
	void ChargeStart();
	void ChargeUpdate(float _Delta);

	float BeamTimer = SHIPBEAMTIMER;
	void BeamStart();
	void BeamUpdate(float _Delta);

	void DeathStart();

protected:
	void StateUpdate(float _Delta);
	void ChangeState(ESHIPBOSSSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	ESHIPBOSSSTATE CurState = ESHIPBOSSSTATE::None;
	std::string State = "";

	bool ChangeShip = false;
private:
	std::shared_ptr<GameEngineSpriteRenderer> ShipRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShipRailRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShipSailRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> ShipMastRenderer = nullptr;

	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void CreateCannonBall();
	void CreateBubble();
	void CreateBeam();
};
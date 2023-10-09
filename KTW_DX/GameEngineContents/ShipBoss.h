#pragma once

#include "BaseBoss.h"

#define SHIPANIMATIONINTER 0.05f
#define SHIPIDLETIMER 7.0f
#define CANNONATTACKCOUNT 3

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

	int CannonAttackCount = CANNONATTACKCOUNT;
	void AttackStart();
	void AttackUpdate(float _Delta);

	void TransformStart();
	void TransformUpdate(float _Delta);

protected:
	void StateUpdate(float _Delta);
	void ChangeState(ESHIPBOSSSTATE _State);
	void ChangeAnimation(std::string_view _State);

	ESHIPBOSSSTATE CurState = ESHIPBOSSSTATE::None;
	std::string State = "";

	bool ChangeShip = false;

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShipRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void CreateCannonBall();
};
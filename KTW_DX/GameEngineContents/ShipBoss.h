#pragma once

#include "BaseBoss.h"

class ShipBoss : public BaseBoss
{
public:
	// constrcuter destructer
	ShipBoss();
	~ShipBoss();

	// delete Function
	ShipBoss(const ShipBoss& _Other) = delete;
	ShipBoss(ShipBoss&& _Other) noexcept = delete;
	ShipBoss& operator=(const ShipBoss& _Other) = delete;
	ShipBoss& operator=(ShipBoss&& _Other) noexcept = delete;

protected:
	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

protected:
	void StateUpdate(float _Delta);
	void ChangeState(ESHIPBOSSSTATE _State);
	void ChangeAnimation(std::string_view _State);

	ESHIPBOSSSTATE CurState = ESHIPBOSSSTATE::None;
	std::string State = "";

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShipRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void CreateCannonBall();
};
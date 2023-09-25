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

private:
	std::shared_ptr<GameEngineSpriteRenderer> ShipRenderer = nullptr;

	void Start() override;
};
#pragma once

#include "ParryObject.h"

class ShipBeam : public ParryObject
{
public:
	// constrcuter destructer
	ShipBeam();
	~ShipBeam();

	// delete Function
	ShipBeam(const ShipBeam& _Other) = delete;
	ShipBeam(ShipBeam&& _Other) noexcept = delete;
	ShipBeam& operator=(const ShipBeam& _Other) = delete;
	ShipBeam& operator=(ShipBeam&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> BeamRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
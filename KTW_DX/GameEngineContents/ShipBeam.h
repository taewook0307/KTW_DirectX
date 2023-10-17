#pragma once

#include "ParryObject.h"

#define BEAMAPPEARTIMER 3.0f

class ShipBeam : public ParryObject
{
	friend class ShipBoss;
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
	float AppearTimer = BEAMAPPEARTIMER;
	void AppearStart();
	void AppearUpdate(float _Delta);
	void EndStart();

private:
	std::string State = "";
	ESHIPBEAMSTATE CurState = ESHIPBEAMSTATE::None;

	void StateUpdate(float _Delta);
	void ChangeState(ESHIPBEAMSTATE _CurState);
	void ChangeAnimation(std::string_view _State);

	std::shared_ptr<GameEngineSpriteRenderer> BeamRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
	std::shared_ptr<GameEngineCollision> ParryCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
#pragma once

#define SPECIALATTACKEFFECTANIMATIONINTER 0.05f

#include <GameEngineCore/GameEngineActor.h>

class SpecialAttackDust : public GameEngineActor
{
public:
	// constrcuter destructer
	SpecialAttackDust();
	~SpecialAttackDust();

	// delete Function
	SpecialAttackDust(const SpecialAttackDust& _Other) = delete;
	SpecialAttackDust(SpecialAttackDust&& _Other) noexcept = delete;
	SpecialAttackDust& operator=(const SpecialAttackDust& _Other) = delete;
	SpecialAttackDust& operator=(SpecialAttackDust&& _Other) noexcept = delete;

	void SetSpecialAttackDustDirection(EDIRECTION8 _DustDirection)
	{
		SpecialAttackDustDirection = _DustDirection;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	EDIRECTION8 SpecialAttackDustDirection = EDIRECTION8::None;

	void Start() override;
	void Update(float _Delta) override;
};
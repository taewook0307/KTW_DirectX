#pragma once

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

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	Direction8 DustDirection = Direction8::None;

	void Start() override;
	void Update(float _Delta) override;
};
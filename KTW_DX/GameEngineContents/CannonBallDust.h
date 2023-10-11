#pragma once

#include <GameEngineCore/GameEngineActor.h>

class CannonBallDust : public GameEngineActor
{
public:
	// constrcuter destructer
	CannonBallDust();
	~CannonBallDust();

	// delete Function
	CannonBallDust(const CannonBallDust& _Other) = delete;
	CannonBallDust(CannonBallDust&& _Other) noexcept = delete;
	CannonBallDust& operator=(const CannonBallDust& _Other) = delete;
	CannonBallDust& operator=(CannonBallDust&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;
};
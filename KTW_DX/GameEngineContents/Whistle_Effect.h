#pragma once

#include <GameEngineCore/GameEngineActor.h>

class Whistle_Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	Whistle_Effect();
	~Whistle_Effect();

	// delete Function
	Whistle_Effect(const Whistle_Effect& _Other) = delete;
	Whistle_Effect(Whistle_Effect&& _Other) noexcept = delete;
	Whistle_Effect& operator=(const Whistle_Effect& _Other) = delete;
	Whistle_Effect& operator=(Whistle_Effect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;
};
#pragma once

class SummonAttacker_Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	SummonAttacker_Effect();
	~SummonAttacker_Effect();

	// delete Function
	SummonAttacker_Effect(const SummonAttacker_Effect& _Other) = delete;
	SummonAttacker_Effect(SummonAttacker_Effect&& _Other) noexcept = delete;
	SummonAttacker_Effect& operator=(const SummonAttacker_Effect& _Other) = delete;
	SummonAttacker_Effect& operator=(SummonAttacker_Effect&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;

	void Start() override;
};
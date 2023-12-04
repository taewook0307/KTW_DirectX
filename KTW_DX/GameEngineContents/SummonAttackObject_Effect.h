#pragma once

class SummonAttackObject_Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	SummonAttackObject_Effect();
	~SummonAttackObject_Effect();

	// delete Function
	SummonAttackObject_Effect(const SummonAttackObject_Effect& _Other) = delete;
	SummonAttackObject_Effect(SummonAttackObject_Effect&& _Other) noexcept = delete;
	SummonAttackObject_Effect& operator=(const SummonAttackObject_Effect& _Other) = delete;
	SummonAttackObject_Effect& operator=(SummonAttackObject_Effect&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;

private:
	void Start() override;
};
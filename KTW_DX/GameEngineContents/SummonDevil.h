#pragma once

class SummonDevil : public GameEngineActor
{
public:
	// constrcuter destructer
	SummonDevil();
	~SummonDevil();

	// delete Function
	SummonDevil(const SummonDevil& _Other) = delete;
	SummonDevil(SummonDevil&& _Other) noexcept = delete;
	SummonDevil& operator=(const SummonDevil& _Other) = delete;
	SummonDevil& operator=(SummonDevil&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> SummonDevilRenderer = nullptr;
	GameEngineState SummonDevilState;

	void Start() override;
	void Update(float _Delta) override;
};
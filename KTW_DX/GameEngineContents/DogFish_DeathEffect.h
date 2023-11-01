#pragma once

class DogFish_DeathEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	DogFish_DeathEffect();
	~DogFish_DeathEffect();

	// delete Function
	DogFish_DeathEffect(const DogFish_DeathEffect& _Other) = delete;
	DogFish_DeathEffect(DogFish_DeathEffect&& _Other) noexcept = delete;
	DogFish_DeathEffect& operator=(const DogFish_DeathEffect& _Other) = delete;
	DogFish_DeathEffect& operator=(DogFish_DeathEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;
};
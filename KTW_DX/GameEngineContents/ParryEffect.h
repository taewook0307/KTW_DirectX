#pragma once

#define PARRYEFFECTANIMATIONINTER 0.05f

class ParryEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ParryEffect();
	~ParryEffect();

	// delete Function
	ParryEffect(const ParryEffect& _Other) = delete;
	ParryEffect(ParryEffect&& _Other) noexcept = delete;
	ParryEffect& operator=(const ParryEffect& _Other) = delete;
	ParryEffect& operator=(ParryEffect&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	void Start() override;
};
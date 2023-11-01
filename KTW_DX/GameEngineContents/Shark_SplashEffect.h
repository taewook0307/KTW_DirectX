#pragma once

class Shark_SplashEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	Shark_SplashEffect();
	~Shark_SplashEffect();

	// delete Function
	Shark_SplashEffect(const Shark_SplashEffect& _Other) = delete;
	Shark_SplashEffect(Shark_SplashEffect&& _Other) noexcept = delete;
	Shark_SplashEffect& operator=(const Shark_SplashEffect& _Other) = delete;
	Shark_SplashEffect& operator=(Shark_SplashEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;
};
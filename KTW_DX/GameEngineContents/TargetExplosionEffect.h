#pragma once

class TargetExplosionEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	TargetExplosionEffect();
	~TargetExplosionEffect();

	// delete Function
	TargetExplosionEffect(const TargetExplosionEffect& _Other) = delete;
	TargetExplosionEffect(TargetExplosionEffect&& _Other) noexcept = delete;
	TargetExplosionEffect& operator=(const TargetExplosionEffect& _Other) = delete;
	TargetExplosionEffect& operator=(TargetExplosionEffect&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};
#pragma once

class FirstBossPhase3Effect : public GameEngineActor
{
public:
	// constrcuter destructer
	FirstBossPhase3Effect();
	~FirstBossPhase3Effect();

	// delete Function
	FirstBossPhase3Effect(const FirstBossPhase3Effect& _Other) = delete;
	FirstBossPhase3Effect(FirstBossPhase3Effect&& _Other) noexcept = delete;
	FirstBossPhase3Effect& operator=(const FirstBossPhase3Effect& _Other) = delete;
	FirstBossPhase3Effect& operator=(FirstBossPhase3Effect&& _Other) noexcept = delete;

	void SetType(EBOSSSTATE _State);

	void SetEffectDir(EACTORDIR _Dir)
	{
		EffectDir = _Dir;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;
	EBOSSSTATE EffectType = EBOSSSTATE::None;
	EACTORDIR EffectDir = EACTORDIR::None;

	void Start() override;
	void Update(float _Delta) override;
};
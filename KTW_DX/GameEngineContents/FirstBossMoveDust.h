#pragma once

class FirstBossMoveDust : public GameEngineActor
{
public:
	// constrcuter destructer
	FirstBossMoveDust();
	~FirstBossMoveDust();

	// delete Function
	FirstBossMoveDust(const FirstBossMoveDust& _Other) = delete;
	FirstBossMoveDust(FirstBossMoveDust&& _Other) noexcept = delete;
	FirstBossMoveDust& operator=(const FirstBossMoveDust& _Other) = delete;
	FirstBossMoveDust& operator=(FirstBossMoveDust&& _Other) noexcept = delete;

	void ChangeEffectPhase2();
protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> EffectRenderer = nullptr;

	void Start() override;
};
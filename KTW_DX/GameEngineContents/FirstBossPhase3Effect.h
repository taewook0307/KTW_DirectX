#pragma once

#include <GameEngineCore/GameEngineActor.h>

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

	void SetType(BossState _State);

	void SetEffectDir(ActorDir _Dir)
	{
		EffectDir = _Dir;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	BossState EffectType = BossState::None;
	ActorDir EffectDir = ActorDir::None;

	void Start() override;
	void Update(float _Delta) override;
};
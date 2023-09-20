#pragma once

#include <GameEngineCore/GameEngineActor.h>

class DashDust : public GameEngineActor
{
public:
	// constrcuter destructer
	DashDust();
	~DashDust();

	// delete Function
	DashDust(const DashDust& _Other) = delete;
	DashDust(DashDust&& _Other) noexcept = delete;
	DashDust& operator=(const DashDust& _Other) = delete;
	DashDust& operator=(DashDust&& _Other) noexcept = delete;

	void SetDashDustDir(ActorDir _DustDir)
	{
		DashDustDir = _DustDir;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	ActorDir DashDustDir = ActorDir::None;

	void Start() override;
	void Update(float _Delta) override;
};
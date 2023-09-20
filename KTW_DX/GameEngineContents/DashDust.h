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

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	void Start() override;
};
#pragma once

#include <GameEngineCore/GameEngineActor.h>

class StageFailUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StageFailUI();
	~StageFailUI();

	// delete Function
	StageFailUI(const StageFailUI& _Other) = delete;
	StageFailUI(StageFailUI&& _Other) noexcept = delete;
	StageFailUI& operator=(const StageFailUI& _Other) = delete;
	StageFailUI& operator=(StageFailUI&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> Renderer = nullptr;

	void Start() override;
};
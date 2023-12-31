#pragma once

class StageClearUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StageClearUI();
	~StageClearUI();

	// delete Function
	StageClearUI(const StageClearUI& _Other) = delete;
	StageClearUI(StageClearUI&& _Other) noexcept = delete;
	StageClearUI& operator=(const StageClearUI& _Other) = delete;
	StageClearUI& operator=(StageClearUI&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> EffectRenderer = nullptr;

	void Start() override;
};
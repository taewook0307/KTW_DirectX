#pragma once

class StageStartUI : public GameEngineActor
{
public:
	// constrcuter destructer
	StageStartUI();
	~StageStartUI();

	// delete Function
	StageStartUI(const StageStartUI& _Other) = delete;
	StageStartUI(StageStartUI&& _Other) noexcept = delete;
	StageStartUI& operator=(const StageStartUI& _Other) = delete;
	StageStartUI& operator=(StageStartUI&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> EffectRenderer = nullptr;

	void Start() override;

	int SoundANum = 0;
	void StartSoundAPlay();
	void StartSoundBPlay();
};
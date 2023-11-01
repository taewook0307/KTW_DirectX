#pragma once

#define RUNEFFECTANIMATIONINTER 0.05f

class RunDust : public GameEngineActor
{
public:
	// constrcuter destructer
	RunDust();
	~RunDust();

	// delete Function
	RunDust(const RunDust& _Other) = delete;
	RunDust(RunDust&& _Other) noexcept = delete;
	RunDust& operator=(const RunDust& _Other) = delete;
	RunDust& operator=(RunDust&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	void Start() override;
};
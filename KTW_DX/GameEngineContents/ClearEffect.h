#pragma once

class ClearEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ClearEffect();
	~ClearEffect();

	// delete Function
	ClearEffect(const ClearEffect& _Other) = delete;
	ClearEffect(ClearEffect&& _Other) noexcept = delete;
	ClearEffect& operator=(const ClearEffect& _Other) = delete;
	ClearEffect& operator=(ClearEffect&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineUIRenderer> ClearRenderer = nullptr;

	void Start() override;
};
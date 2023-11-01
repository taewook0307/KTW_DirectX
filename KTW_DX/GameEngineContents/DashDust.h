#pragma once

#define DASHEFFECTANIMATIONINTER 0.05f

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

	void SetDashDustDir(EACTORDIR _DustDir)
	{
		DashDustDir = _DustDir;
	}

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	EACTORDIR DashDustDir = EACTORDIR::None;

	void Start() override;
	void Update(float _Delta) override;
};
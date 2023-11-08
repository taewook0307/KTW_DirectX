#pragma once

class SummonDevil : public GameEngineActor
{
public:
	// constrcuter destructer
	SummonDevil();
	~SummonDevil();

	// delete Function
	SummonDevil(const SummonDevil& _Other) = delete;
	SummonDevil(SummonDevil&& _Other) noexcept = delete;
	SummonDevil& operator=(const SummonDevil& _Other) = delete;
	SummonDevil& operator=(SummonDevil&& _Other) noexcept = delete;

	void SetStartDirRight();

protected:

private:
	float Speed = 300.0f;
	EACTORDIR Dir = EACTORDIR::Left;

	std::shared_ptr<GameEngineSpriteRenderer> SummonDevilRenderer = nullptr;
	GameEngineState SummonDevilState;

	void Start() override;
	void Update(float _Delta) override;

	void DirChange();
	bool CameraOutCheck();

	void SummonDevilMove(float _Delta);
};
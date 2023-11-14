#pragma once

class FarForest : public GameEngineActor
{
public:
	// constrcuter destructer
	FarForest();
	~FarForest();

	// delete Function
	FarForest(const FarForest& _Other) = delete;
	FarForest(FarForest&& _Other) noexcept = delete;
	FarForest& operator=(const FarForest& _Other) = delete;
	FarForest& operator=(FarForest&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> FarForestRenderer = nullptr;

	void Start() override;
	void Update(float _Delta);
};
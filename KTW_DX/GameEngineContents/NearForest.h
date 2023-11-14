#pragma once

class NearForest : public GameEngineActor
{
public:
	// constrcuter destructer
	NearForest();
	~NearForest();

	// delete Function
	NearForest(const NearForest& _Other) = delete;
	NearForest(NearForest&& _Other) noexcept = delete;
	NearForest& operator=(const NearForest& _Other) = delete;
	NearForest& operator=(NearForest&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> NearForestRenderer = nullptr;

	void Start() override;
};
#pragma once

class Smoke : public GameEngineActor
{
public:
	// constrcuter destructer
	Smoke();
	~Smoke();

	// delete Function
	Smoke(const Smoke& _Other) = delete;
	Smoke(Smoke&& _Other) noexcept = delete;
	Smoke& operator=(const Smoke& _Other) = delete;
	Smoke& operator=(Smoke&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> SmokeRenderer = nullptr;
};
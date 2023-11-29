#pragma once

class Lava : public GameEngineActor
{
public:
	// constrcuter destructer
	Lava();
	~Lava();

	// delete Function
	Lava(const Lava& _Other) = delete;
	Lava(Lava&& _Other) noexcept = delete;
	Lava& operator=(const Lava& _Other) = delete;
	Lava& operator=(Lava&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> LavaRenderer = nullptr;

	void Start() override;
};
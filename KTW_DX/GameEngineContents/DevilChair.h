#pragma once

class DevilChair : public GameEngineActor
{
public:
	// constrcuter destructer
	DevilChair();
	~DevilChair();

	// delete Function
	DevilChair(const DevilChair& _Other) = delete;
	DevilChair(DevilChair&& _Other) noexcept = delete;
	DevilChair& operator=(const DevilChair& _Other) = delete;
	DevilChair& operator=(DevilChair&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> ChairRenderer = nullptr;

	void Start() override;
};
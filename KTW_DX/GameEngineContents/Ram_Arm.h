#pragma once

#define RAMARMANIMATIONINTER 0.1f

class Ram_Arm : public GameEngineActor
{
public:
	// constrcuter destructer
	Ram_Arm();
	~Ram_Arm();

	// delete Function
	Ram_Arm(const Ram_Arm& _Other) = delete;
	Ram_Arm(Ram_Arm&& _Other) noexcept = delete;
	Ram_Arm& operator=(const Ram_Arm& _Other) = delete;
	Ram_Arm& operator=(Ram_Arm&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> ArmRenderer = nullptr;
	GameEngineState ArmState;

	float Speed = 1000.0f;

private:
};
#pragma once

#define RAMARMANIMATIONINTER 0.1f
#define MOVEENDPOINTERROR 0.05f

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

	void ChangeLeftDir();

protected:

private:
	EACTORDIR ArmDir = EACTORDIR::Right;
	float Speed = 1000.0f;
	float MoveEndPoint = 0.0f;

	GameEngineState ArmState;
	std::shared_ptr<GameEngineSpriteRenderer> ArmRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void ArmMove(float _Delta, bool _Back = false);
	bool MoveEndCheck();
	bool DeathPosCheck();
};
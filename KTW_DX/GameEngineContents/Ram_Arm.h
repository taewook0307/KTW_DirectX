#pragma once

#include "DevilSummonActor.h"

#define RAMARMANIMATIONINTER 0.1f
#define MOVEENDPOINTERROR 0.05f

#define RAMARMCOLLISIONSCALE { 950.0f, 80.0f }
#define RAMARMCOLLISIONPOSITIONRIGHT { -475.0f, 0.0f }
#define RAMARMCOLLISIONPOSITIONLEFT { 475.0f, 0.0f }

class Ram_Arm : public DevilSummonActor
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

private:
	EACTORDIR ArmDir = EACTORDIR::Right;
	float Speed = 2000.0f;
	float MoveEndPoint = 0.0f;

	GameEngineState ArmState;
	std::shared_ptr<GameEngineSpriteRenderer> ArmRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ArmCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void ArmMove(float _Delta, bool _Back = false);
	bool MoveEndCheck();
	bool DeathPosCheck();
	void ChangeLeftDir() override;

	void ClapSoundPlay();
};
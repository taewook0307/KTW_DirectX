#pragma once

#include "Ram_Arm.h"

class Ram_Arm_Right : public Ram_Arm
{
public:
	// constrcuter destructer
	Ram_Arm_Right();
	~Ram_Arm_Right();

	// delete Function
	Ram_Arm_Right(const Ram_Arm_Right& _Other) = delete;
	Ram_Arm_Right(Ram_Arm_Right&& _Other) noexcept = delete;
	Ram_Arm_Right& operator=(const Ram_Arm_Right& _Other) = delete;
	Ram_Arm_Right& operator=(Ram_Arm_Right&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};
#pragma once

#include "Ram_Arm.h"

class Ram_Arm_Left : public Ram_Arm
{
public:
	// constrcuter destructer
	Ram_Arm_Left();
	~Ram_Arm_Left();

	// delete Function
	Ram_Arm_Left(const Ram_Arm_Left& _Other) = delete;
	Ram_Arm_Left(Ram_Arm_Left&& _Other) noexcept = delete;
	Ram_Arm_Left& operator=(const Ram_Arm_Left& _Other) = delete;
	Ram_Arm_Left& operator=(Ram_Arm_Left&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};
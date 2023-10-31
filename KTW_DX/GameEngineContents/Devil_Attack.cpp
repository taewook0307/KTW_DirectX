#include "PreCompile.h"
#include "Devil.h"

#include "Ram_Arm_Left.h"
#include "Ram_Arm_Right.h"
#include "Spider_Head.h"

void Devil::CreateRamArm()
{
	SummonAttacker = true;

	std::shared_ptr<Ram_Arm_Right> RightCheck = GetLevel()->CreateActor<Ram_Arm_Right>(EUPDATEORDER::Monster);
	RightCheck->Transform.SetLocalPosition({ 0.0f, -500.0f });

	std::shared_ptr<Ram_Arm_Left> LeftCheck = GetLevel()->CreateActor<Ram_Arm_Left>(EUPDATEORDER::Monster);
	LeftCheck->Transform.SetLocalPosition({ 1280.0f, -500.0f });
}

void Devil::CreateSpiderHead()
{
	SummonAttacker = true;
}

void Devil::CreateSerpentHead()
{
	SummonAttacker = true;
}

void Devil::CreateFireBall()
{
	SummonAttacker = true;
}
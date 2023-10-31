#include "PreCompile.h"
#include "Devil.h"

#include "Ram_Arm.h"
#include "Spider_Head.h"
#include "Serpent_Head.h"

void Devil::CreateRamArm()
{
	SummonAttacker = true;

	std::shared_ptr<Ram_Arm> RightCheck = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	RightCheck->Transform.SetLocalPosition({ 0.0f, -500.0f });

	std::shared_ptr<Ram_Arm> LeftCheck = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	LeftCheck->ChangeLeftDir();
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
#include "PreCompile.h"
#include "Devil.h"

#include "Ram_Arm.h"
#include "Spider_Head.h"
#include "Serpent_Head.h"

void Devil::CreateRamArm()
{
	SummonAttacker = true;
	Arms.resize(2);

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	Arms[0] = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	Arms[0]->Transform.SetLocalPosition({ CameraPos.X - WinHalfScale.X, -600.0f });

	Arms[1] = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	Arms[1]->ChangeLeftDir();
	Arms[1]->Transform.SetLocalPosition({ CameraPos.X + WinHalfScale.X, -600.0f });
}

bool Devil::ArmDeathCheck()
{
	for (size_t i = 0; i < Arms.size(); i++)
	{
		bool Check = Arms[i]->IsDeath();

		if (false == Check)
		{
			return false;
		}
	}
	return true;
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
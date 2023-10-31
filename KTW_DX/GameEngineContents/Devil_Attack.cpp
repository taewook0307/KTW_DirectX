#include "PreCompile.h"
#include "Devil.h"

#include "Ram_Arm.h"
#include "Spider_Head.h"
#include "Serpent_Head.h"

void Devil::CreateRamArm()
{
	SummonActors.resize(2);

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	SummonActors[0] = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	SummonActors[0]->Transform.SetLocalPosition({ CameraPos.X - WinHalfScale.X, CameraPos.Y - WinHalfScale.Y + 70.0f });

	SummonActors[1] = GetLevel()->CreateActor<Ram_Arm>(EUPDATEORDER::Monster);
	SummonActors[1]->ChangeLeftDir();
	SummonActors[1]->Transform.SetLocalPosition({ CameraPos.X + WinHalfScale.X, CameraPos.Y - WinHalfScale.Y + 70.0f });
}

void Devil::CreateSpiderHead()
{
	SummonActors.resize(1);

	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	SummonActors[0] = GetLevel()->CreateActor<Spider_Head>(EUPDATEORDER::Monster);
	SummonActors[0]->Transform.SetLocalPosition({ WinHalfScale.X, 0.0f });
}

void Devil::CreateSerpentHead()
{
	SummonActors.resize(1);

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	SummonActors[0] = GetLevel()->CreateActor<Serpent_Head>(EUPDATEORDER::Monster);
	SummonActors[0]->Transform.SetLocalPosition({ CameraPos.X - WinHalfScale.X, CameraPos.Y - WinHalfScale.Y });
}

void Devil::CreateFireBall()
{
	
}

bool Devil::SummonDeathCheck()
{
	for (size_t i = 0; i < SummonActors.size(); i++)
	{
		bool Check = SummonActors[i]->IsDeath();

		if (false == Check)
		{
			return false;
		}
	}
	return true;
}
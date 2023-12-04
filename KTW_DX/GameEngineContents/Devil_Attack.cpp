#include "PreCompile.h"
#include "Devil.h"

#include "Ram_Arm.h"
#include "Spider_Head.h"
#include "Serpent_Head.h"
#include "Summon_Fire.h"
#include "Summon_Ball.h"

void Devil::CreateRamArm()
{
	AllSummonDeath();

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
	AllSummonDeath();

	SummonActors.resize(1);

	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	SummonActors[0] = GetLevel()->CreateActor<Spider_Head>(EUPDATEORDER::Monster);
	SummonActors[0]->Transform.SetLocalPosition({ WinHalfScale.X, 0.0f });
}

void Devil::CreateSerpentHead()
{
	AllSummonDeath();

	SummonActors.resize(1);

	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WinHalfScale = GameEngineCore::MainWindow.GetScale().Half();

	SummonActors[0] = GetLevel()->CreateActor<Serpent_Head>(EUPDATEORDER::Monster);
	SummonActors[0]->Transform.SetLocalPosition({ CameraPos.X - WinHalfScale.X, CameraPos.Y - WinHalfScale.Y - 50.0f });

	if (EACTORDIR::Right == SerpentDir)
	{
		SummonActors[0]->ChangeLeftDir();
		SummonActors[0]->Transform.SetLocalPosition({ CameraPos.X + WinHalfScale.X, CameraPos.Y - WinHalfScale.Y - 50.0f });
	}
}

void Devil::CreateFire()
{
	AllSummonDeath();

	AllChangeMove = false;
	FireMoveTimer = 1.0f;
	FireIndex = 0;

	SummonActors.resize(6);
	
	float4 DevilPos = Transform.GetWorldPosition();

	SummonActors[0] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[0]->Transform.SetLocalPosition(DevilPos + float4{ 0.0f, 480.0f });

	SummonActors[1] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[1]->Transform.SetLocalPosition(DevilPos + float4{ -150.0f, 400.0f });

	SummonActors[2] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[2]->Transform.SetLocalPosition(DevilPos + float4{ -150.0f, 200.0f });

	SummonActors[3] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[3]->Transform.SetLocalPosition(DevilPos + float4{ 0.0f, 120.0f });

	SummonActors[4] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[4]->Transform.SetLocalPosition(DevilPos + float4{ 150.0f, 200.0f });

	SummonActors[5] = GetLevel()->CreateActor<Summon_Fire>(EUPDATEORDER::Bullet);
	SummonActors[5]->Transform.SetLocalPosition(DevilPos + float4{ 150.0f, 400.0f });
}

void Devil::CreateBall()
{
	AllSummonDeath();

	AllChangeMove = false;
	SummonActors.resize(4);

	float4 DevilPos = Transform.GetWorldPosition();

	SummonActors[0] = GetLevel()->CreateActor<Summon_Ball>(EUPDATEORDER::Bullet);
	SummonActors[0]->Transform.SetLocalPosition(DevilPos + float4{ 0.0f, 480.0f });

	SummonActors[1] = GetLevel()->CreateActor<Summon_Ball>(EUPDATEORDER::Bullet);
	SummonActors[1]->Transform.SetLocalPosition(DevilPos + float4{ -200.0f, 300.0f });

	SummonActors[2] = GetLevel()->CreateActor<Summon_Ball>(EUPDATEORDER::Bullet);
	SummonActors[2]->Transform.SetLocalPosition(DevilPos + float4{ 200.0f, 300.0f });

	SummonActors[3] = GetLevel()->CreateActor<Summon_Ball>(EUPDATEORDER::Bullet);
	SummonActors[3]->Transform.SetLocalPosition(DevilPos + float4{ 0.0f, 120.0f });
}

void Devil::FireMoveReq(float _Delta)
{
	if (true == AllChangeMove)
	{
		return;
	}

	if (FireIndex >= SummonActors.size())
	{
		AllChangeMove = true;
		return;
	}

	FireMoveTimer -= _Delta;

	if (0.0f > FireMoveTimer)
	{
		SummonActors[FireIndex]->ChangeStateReq();
		FireMoveTimer = 1.0f;
		++FireIndex;
	}
}

void Devil::BallMoveReq(float _Delta)
{
	if (true == AllChangeMove)
	{
		return;
	}

	if (0.0f > BallMoveTimer)
	{
		BallMoveTimer = 1.0f;
		for (size_t i = 0; i < SummonActors.size(); i++)
		{
			SummonActors[i]->ChangeStateReq();
		}
		AllChangeMove = true;
	}

	BallMoveTimer -= _Delta;
}
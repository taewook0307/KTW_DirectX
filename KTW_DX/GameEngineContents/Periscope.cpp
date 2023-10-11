#include "PreCompile.h"
#include "Periscope.h"

#include "DogFish.h"
#include "DogFish_Splash.h"
#include "PirateBoss.h"

Periscope::Periscope()
{
}

Periscope::~Periscope()
{
}

void Periscope::Start()
{
	PeriscopeRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	PeriscopeRenderer->CreateAnimation("Periscope", "Periscope", 0.05f, -1, -1, false);
	PeriscopeRenderer->SetEndEvent("Periscope",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SummonStart = true;
			PeriscopeRenderer->Off();
		}
	);
	PeriscopeRenderer->AutoSpriteSizeOn();
	PeriscopeRenderer->SetPivotType(PivotType::Bottom);
	PeriscopeRenderer->ChangeAnimation("Periscope");
}

void Periscope::Update(float _Delta)
{
	if (0.0f > SummonTimer)
	{
		std::shared_ptr<DogFish> NewDogFish = GetLevel()->CreateActor<DogFish>(EUPDATEORDER::Monster);
		NewDogFish->Transform.SetLocalPosition(SUMMONPOS);

		std::shared_ptr<DogFish_Splash> Effect = GetLevel()->CreateActor<DogFish_Splash>(EUPDATEORDER::Monster);
		Effect->Transform.SetLocalPosition(SUMMONPOS);

		SummonTimer = SUMMONTIMER;
		--SummonCount;
	}
	
	if (true == SummonStart)
	{
		SummonTimer -= _Delta;
	}

	if (0 == SummonCount)
	{
		PirateBoss::MainPirateBoss->SummonDeath();
		Death();
	}
}
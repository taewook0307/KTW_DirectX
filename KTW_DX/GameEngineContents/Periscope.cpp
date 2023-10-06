#include "PreCompile.h"
#include "Periscope.h"

#include "DogFish.h"

Periscope::Periscope()
{
}

Periscope::~Periscope()
{
}

void Periscope::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::UpperBoss);
	Renderer->CreateAnimation("Periscope", "Periscope", 0.05f, -1, -1, false);
	Renderer->SetEndEvent("Periscope",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			SummonStart = true;
		}
	);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->ChangeAnimation("Periscope");
}

void Periscope::Update(float _Delta)
{
	if (0.0f > SummonTimer)
	{
		std::shared_ptr<DogFish> NewDogFish = GetLevel()->CreateActor<DogFish>(EUPDATEORDER::Monster);
		NewDogFish->Transform.SetLocalPosition(SUMMONPOS);

		SummonTimer = SUMMONTIMER;
		--SummonCount;
	}
	
	if (true == SummonStart)
	{
		SummonTimer -= _Delta;
	}

	if (0 == SummonCount)
	{
		Death();
	}
}
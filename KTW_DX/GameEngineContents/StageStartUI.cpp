#include "PreCompile.h"
#include "StageStartUI.h"

StageStartUI::StageStartUI()
{
}

StageStartUI::~StageStartUI()
{
}

void StageStartUI::Start()
{
	EffectRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	EffectRenderer->CreateAnimation("Start_Effect", "StageStart_Effect", 0.08f, -1, -1, false);

	EffectRenderer->SetStartEvent("Start_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			StartSoundAPlay();
		}
	);

	EffectRenderer->SetFrameEvent("Start_Effect", 25,
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			StartSoundBPlay();
		}
	);

	EffectRenderer->SetEndEvent("Start_Effect",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		}
	);

	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	EffectRenderer->SetImageScale(WinScale);

	EffectRenderer->ChangeAnimation("Start_Effect");
}

void StageStartUI::StartSoundAPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 4);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_level_announcer_0001_a.wav");
		SoundANum = 1;
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_level_announcer_0001_b.wav");
		SoundANum = 2;
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_level_announcer_0001_c.wav");
		SoundANum = 3;
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_level_announcer_0001_d.wav");
		SoundANum = 4;
		break;
	default:
		GameEngineSound::SoundPlay("sfx_level_announcer_0001_e.wav");
		SoundANum = 5;
		break;
	}
}

void StageStartUI::StartSoundBPlay()
{
	switch (SoundANum)
	{
	case 1:
		GameEngineSound::SoundPlay("sfx_level_announcer_0002_a.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_level_announcer_0002_b.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_level_announcer_0002_c.wav");
		break;
	case 4:
		GameEngineSound::SoundPlay("sfx_level_announcer_0002_d.wav");
		break;
	case 5:
		GameEngineSound::SoundPlay("sfx_level_announcer_0002_e.wav");
		break;
	default:
		MsgBoxAssert("SoundA가 제대로 세팅되지 않았습니다.");
		break;
	}
}

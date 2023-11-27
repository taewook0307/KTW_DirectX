#include "PreCompile.h"
#include "FirstBossPhase3.h"

void FirstBossPhase3::IdleSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_taunts_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_taunts_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_taunts_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_taunts_04.wav");
		break;
	}
}

void FirstBossPhase3::MoveSoundPlay()
{
	MoveSound.Stop();

	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 4);

	switch (SoundNum)
	{
	case 0:
		MoveSound = GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_01.wav");
		break;
	case 1:
		MoveSound = GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_02.wav");
		break;
	case 2:
		MoveSound = GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_03.wav");
		break;
	case 3:
		MoveSound = GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_04.wav");
		break;
	default:
		MoveSound = GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_05.wav");
		break;
	}
}

void FirstBossPhase3::MoveVoiceSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 3);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_vo_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_vo_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_vo_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_slide_vo_04.wav");
		break;
	}
}

void FirstBossPhase3::AttackSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 4);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_03.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_04.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_tombstone_splat_05.wav");
		break;
	}
}
#include "PreCompile.h"
#include "FirstBoss.h"

void FirstBoss::Phase2MoveSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 4);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_big_jump_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_big_jump_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_big_jump_03.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_slime_big_jump_04.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_big_jump_05.wav");
		break;
	}
}

void FirstBoss::Phase2LandSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 5);

	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_big_land_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_big_land_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_big_land_03.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_slime_big_land_04.wav");
		break;
	case 4:
		GameEngineSound::SoundPlay("sfx_slime_big_land_05.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_big_land_06.wav");
		break;
	}
}

void FirstBoss::DeathSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 1);

	if (0 == SoundNum)
	{
		GameEngineSound::SoundPlay("sfx_slime_big_death_voice_01.wav");
	}
	else
	{
		GameEngineSound::SoundPlay("sfx_slime_big_death_voice_02.wav");
	}
}

void FirstBoss::Phase2AttackSoundPlay()
{
	GameEngineRandom Random;
	long long Time = static_cast<long long>(time(NULL));
	Random.SetSeed(Time);

	int SoundNum = Random.RandomInt(0, 5);
	int AttackNum = Random.RandomInt(0, 3);
	
	switch (SoundNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_03.wav");
		break;
	case 3:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_04.wav");
		break;
	case 4:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_05.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_voice_06.wav");
		break;
	}

	switch (AttackNum)
	{
	case 0:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_01.wav");
		break;
	case 1:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_02.wav");
		break;
	case 2:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_03.wav");
		break;
	default:
		GameEngineSound::SoundPlay("sfx_slime_big_punch_04.wav");
		break;
	}
}
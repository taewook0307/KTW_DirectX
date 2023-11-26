#include "PreCompile.h"
#include "ContentsSoundPlayer.h"

ContentsSoundPlayer::ContentsSoundPlayer()
{
}

ContentsSoundPlayer::~ContentsSoundPlayer()
{
}

void ContentsSoundPlayer::AddSoundList(std::string_view _SoundFileName)
{
	SoundList.push_back(_SoundFileName.data());
}

void ContentsSoundPlayer::RandomSoundPlay()
{
	int SoundListSize = static_cast<int>(SoundList.size());

	GameEngineRandom Random;
	unsigned int Time = static_cast<unsigned int>(time(NULL));
	Random.SetSeed(static_cast<long long>(Time));

	int SoundNum = Random.RandomInt(0, SoundListSize - 1);

	if (SoundNum >= SoundListSize)
	{
		MsgBoxAssert("재생할 수 사운드 범위를 넘었습니다");
		return;
	}

	std::string SoundName = SoundList[SoundNum];

	GameEngineSound::SoundPlay(SoundName);
}
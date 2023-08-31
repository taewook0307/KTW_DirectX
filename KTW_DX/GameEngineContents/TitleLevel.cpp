﻿#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "BackGround.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Level\\Title");

	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		size_t FileSize = Files.size();

		for (size_t i = 0; i < FileSize; i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Title_BackGround.Png");
	}

	{
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		size_t DirSize = Directorys.size();

		for (size_t i = 0; i < DirSize; i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	TitleBackGround = CreateActor<BackGround>(UpdateOrder::BackGround);
	TitleBackGround->BackGroundInit("Title_BackGround.Png");

	TitleAnimation = CreateActor<BackGround>(UpdateOrder::BackGround);
	TitleAnimation->AnimationInit("Title_Animation", "TitleAnimation", 0.1f, false);
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}
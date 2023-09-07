#include "PreCompile.h"
#include "TitleLevel.h"

#include "BackGround.h"
//#include "FadeObject.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
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

	/*{
		GameEngineDirectory FadeDir;
		FadeDir.MoveParentToExistsChild("Resources");
		FadeDir.MoveChild("Resources\\Texture\\Fade");

		std::vector<GameEngineDirectory> Directorys = FadeDir.GetAllDirectory();

		size_t DirSize = Directorys.size();

		for (size_t i = 0; i < DirSize; i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}*/

	TitleBackGround = CreateActor<BackGround>(UpdateOrder::BackGround);
	TitleBackGround->BackGroundInit("Title_BackGround.Png");

	TitleAnimation = CreateActor<BackGround>(UpdateOrder::BackGround);
	TitleAnimation->AnimationInit("Title_Animation", "TitleAnimation", 0.04f, true, false);
	TitleAnimation->Transform.SetLocalPosition({ 0.0f, -75.0f });
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("MenuLevel");
	}

	/*if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		FadeEffect = CreateActor<FadeObject>(UpdateOrder::UI);
		FadeEffect->SetFadeType();
	}

	if (nullptr != FadeEffect && true == FadeEffect->GetFadeAnimationEnd())
	{
		GameEngineCore::ChangeLevel("MenuLevel");
	}*/
}
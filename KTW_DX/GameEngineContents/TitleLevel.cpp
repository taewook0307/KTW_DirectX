#include "PreCompile.h"
#include "TitleLevel.h"

#include "BackGround.h"
#include "FadeObject.h"


TitleLevel::TitleLevel()
{
	GameEngineInput::AddInputObject(this);
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\Title\\TitleAnimation");
	ContentsSpriteManager::CreateSingleSpriteImage("Resources\\Texture\\Title\\Title_BackGround.Png");
	ContentsSpriteManager::CreateFolderSpriteAllDir("Resources\\Texture\\Global\\Fade");

	TitleBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleBackGround->BackGroundInit("Title_BackGround.Png");

	TitleAnimation = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleAnimation->AnimationInit("Title_Animation", "TitleAnimation", 0.04f, true, false);
	TitleAnimation->Transform.SetLocalPosition({ 0.0f, -GameEngineCore::MainWindow.GetScale().Half().Y });
	TitleAnimation->SetBackGroundRendererPivotType(PivotType::Bottom);
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		FadeEffect = CreateActor<FadeObject>(EUPDATEORDER::UI);
		FadeEffect->SetFadeType();
	}

	if (nullptr != FadeEffect && true == FadeEffect->GetFadeAnimationEnd())
	{
		TitleBackGround->BackGroundDeath();
		TitleAnimation->BackGroundDeath();
		GameEngineCore::ChangeLevel("MenuLevel");
	}
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != TitleBackGround)
	{
		TitleBackGround->Death();
		TitleBackGround = nullptr;
	}

	if (nullptr != TitleAnimation)
	{
		TitleAnimation->Death();
		TitleAnimation = nullptr;
	}

	{
		GameEngineTexture::Release("Title_BackGround.Png");
		GameEngineSprite::Release("Title_BackGround.Png");
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Title");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		size_t DirSize = Directorys.size();

		for (size_t i = 0; i < DirSize; i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::Release(Dir.GetFileName());

			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile File = Files[i];

				GameEngineTexture::Release(File.GetFileName());
			}
		}
	}
}
#include "PreCompile.h"
#include "TitleLevel.h"

#include "BackGround.h"
#include "FadeObject.h"


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\Texture\\Title");

		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		size_t DirSize = Directorys.size();

		for (size_t i = 0; i < DirSize; i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	{
		GameEnginePath Path;
		Path.MoveParentToExistsChild("Resources");
		Path.MoveChild("Resources\\Texture\\Title\\Title_BackGround.Png");
		GameEngineTexture::Load(Path.GetStringPath());

		GameEngineSprite::CreateSingle("Title_BackGround.Png");
	}

	{
		GameEngineDirectory FadeDir;
		FadeDir.MoveParentToExistsChild("Resources");
		FadeDir.MoveChild("Resources\\Texture\\Global\\Fade");

		std::vector<GameEngineDirectory> Directorys = FadeDir.GetAllDirectory();

		size_t DirSize = Directorys.size();

		for (size_t i = 0; i < DirSize; i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}
	}

	TitleBackGround = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleBackGround->BackGroundInit("Title_BackGround.Png");

	TitleAnimation = CreateActor<BackGround>(EUPDATEORDER::BackGround);
	TitleAnimation->AnimationInit("Title_Animation", "TitleAnimation", 0.04f, true, false);
	TitleAnimation->Transform.SetLocalPosition({ 0.0f, -GameEngineCore::MainWindow.GetScale().Half().Y });
	TitleAnimation->SetBackGroundRendererPivotType(PivotType::Bottom);
}

void TitleLevel::Update(float _Delta)
{
	/*if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("MenuLevel");
	}*/

	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		FadeEffect = CreateActor<FadeObject>(EUPDATEORDER::UI);
		FadeEffect->SetFadeType();
	}

	if (nullptr != FadeEffect && true == FadeEffect->GetFadeAnimationEnd())
	{
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
}
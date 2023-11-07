#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "MenuLevel.h"
#include "IntroLevel.h"
#include "WorldMapLevel.h"
#include "TutorialStage.h"
#include "FirstBossStage.h"
#include "SecondBossStage.h"
#include "LastBossStage.h"
#include "OutroLevel.h"
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

#include "TestStage.h"

#include "LevelChangeWindow.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::ContentsResourcesInit()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineContentsShader");
		Dir.MoveChild("GameEngineContentsShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("OldFilm");
		Mat->SetVertexShader("OldFilm_VS");
		Mat->SetPixelShader("OldFilm_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	ContentsSpriteManager::CreateFolderSpriteDir("Resources\\Texture\\Global\\OldFilm");

	//{
	//	D3D11_BLEND_DESC Desc = {};
	//	Desc.IndependentBlendEnable = false;
	//	Desc.RenderTarget[0].BlendEnable = true;
	//	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	//	// 
	//	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	//	std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("OverLay", Desc);
	//}

	//{
	//	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureOver");
	//	Mat->SetVertexShader("TextureShader_VS");
	//	Mat->SetPixelShader("TextureShader_PS");
	//	Mat->SetBlendState("OverRay");
	//}
}

void ContentsCore::Start()
{	
	ContentsResourcesInit();

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });

	GameEngineRenderTarget::IsDepth = false;

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");
	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<WorldMapLevel>("WorldMapLevel");
	GameEngineCore::CreateLevel<TutorialStage>("0.Tutorial_Stage");
	GameEngineCore::CreateLevel<FirstBossStage>("1.FirstBoss_Stage");
	GameEngineCore::CreateLevel<SecondBossStage>("2.SecondBoss_Stage");
	GameEngineCore::CreateLevel<LastBossStage>("3.LastBoss_Stage");
	GameEngineCore::CreateLevel<OutroLevel>("OutroLevel");
	GameEngineCore::CreateLevel<TestStage>("Test_Stage");
	GameEngineCore::ChangeLevel("Test_Stage");

	GameEngineLevel::OffDebug();

	//GameEngineGUI::CreateGUIWindow<LevelChangeWindow>("Level Change Tool");

	GameEngineInput::AddInputObject(this);
}

void ContentsCore::Update(float _Delta)
{
	/*OutputDebugStringA(std::to_string(1.0f / _Delta).c_str());
	OutputDebugStringA("\n");*/

	if (true == GameEngineInput::IsDown('K', this))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	/*if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
	if (true == GameEngineInput::IsDown(VK_F2, this))
	{
		GameEngineCore::ChangeLevel("0.Tutorial_Stage");
	}
	if (true == GameEngineInput::IsDown(VK_F3, this))
	{
		GameEngineCore::ChangeLevel("1.FirstBoss_Stage");
	}
	if (true == GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineCore::ChangeLevel("2.SecondBoss_Stage");
	}
	if (true == GameEngineInput::IsDown(VK_F5, this))
	{
		GameEngineCore::ChangeLevel("3.LastBoss_Stage");
	}
	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineCore::ChangeLevel("Test_Stage");
	}*/
}

void ContentsCore::Release()
{

}
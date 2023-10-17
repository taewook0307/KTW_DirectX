#include "PreCompile.h"
#include "ContentsCore.h"

#include "LogoLevel.h"
#include "TitleLevel.h"
#include "MenuLevel.h"
#include "IntroLevel.h"
#include "MiniMapLevel.h"
#include "TutorialStage.h"
#include "FirstBossStage.h"
#include "SecondBossStage.h"
#include "OutroLevel.h"
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

#include "TestStage.h"
#include "LevelChangeWindow.h"
#include <GameEngineCore/GameEngineGUI.h>

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	// GameEngineGUI::CreateGUIWindow<LevelChangeWindow>("LevelChangeTool");
	
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

	GameEngineRenderTarget::IsDepth = false;

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");
	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<MiniMapLevel>("MiniMapLevel");
	GameEngineCore::CreateLevel<TutorialStage>("TutorialStage");
	GameEngineCore::CreateLevel<FirstBossStage>("FirstBossStage");
	GameEngineCore::CreateLevel<SecondBossStage>("SecondBossStage");
	GameEngineCore::CreateLevel<OutroLevel>("OutroLevel");
	GameEngineCore::CreateLevel<TestStage>("TestStage");
	GameEngineCore::ChangeLevel("FirstBossStage");

	GameEngineLevel::OffDebug();

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

	if (true == GameEngineInput::IsDown(VK_F1, this))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
	if (true == GameEngineInput::IsDown(VK_F2, this))
	{
		GameEngineCore::ChangeLevel("TutorialStage");
	}
	if (true == GameEngineInput::IsDown(VK_F3, this))
	{
		GameEngineCore::ChangeLevel("FirstBossStage");
	}
	if (true == GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineCore::ChangeLevel("SecondBossStage");
	}
	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineCore::ChangeLevel("TestStage");
	}
}

void ContentsCore::Release()
{

}
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

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
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

	GameEngineCore::CreateLevel<LogoLevel>("LogoLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MenuLevel>("MenuLevel");
	GameEngineCore::CreateLevel<IntroLevel>("IntroLevel");
	GameEngineCore::CreateLevel<MiniMapLevel>("MiniMapLevel");
	GameEngineCore::CreateLevel<TutorialStage>("TutorialStage");
	GameEngineCore::CreateLevel<FirstBossStage>("FirstBossStage");
	GameEngineCore::CreateLevel<SecondBossStage>("SecondBossStage");
	GameEngineCore::CreateLevel<OutroLevel>("OutroLevel");
	GameEngineCore::ChangeLevel("SecondBossStage");

	GameEngineLevel::OffDebug();
}

void ContentsCore::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('K'))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		GameEngineCore::ChangeLevel("MiniMapLevel");
	}
	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("TutorialStage");
	}
	if (true == GameEngineInput::IsDown(VK_F3))
	{
		GameEngineCore::ChangeLevel("FirstBossStage");
	}
	if (true == GameEngineInput::IsDown(VK_F4))
	{
		GameEngineCore::ChangeLevel("SecondBossStage");
	}
}

void ContentsCore::Release()
{

}
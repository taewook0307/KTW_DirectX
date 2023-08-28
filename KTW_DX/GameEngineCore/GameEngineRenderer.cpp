﻿#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVertex.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	// 메인카메라에 들어갔다.
	SetViewCameraSelect(0);

	// 카메라를 찾아서 들어가야 합니다.
	// 카메를 찾으려면? GameEngineLevel
	// Level부터 찾아야해.
	// Level누가 들고 있죠? 나를 들고 있는 Actor가 들고 있어.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();
	Draw();
}

void GameEngineRenderer::ResSetting()
{

	{
		float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();

		// 인풋어셈블러1 버텍스 버퍼 세팅
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}


		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("TextureShader_VS");

		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();
			LayOut->ResCreate(VertexBuffer, VertexShader);
		}

		std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");

		if (nullptr != Buffer)
		{
			const TransformData& Data = Transform.GetConstTransformDataRef();
			Buffer->ChangeData(Data);
			Buffer->Setting();
		}



		if (nullptr != LayOut)
		{
			LayOut->Setting();
		}

		// 버텍스 쉐이더 세팅
		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}


		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}

		// 인덱스버퍼를 어떻게 사용할 것이냐에 대한 옵션이다.
		// 삼각형의 배열로 보고 그려라.
		// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		// 선의 배열로 보고 그려라.
		// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// 나중에 아웃풋 머저 때문에 그렇습니다.
		D3D11_VIEWPORT ViewPort = {};

		// 좀더 식이 있어야 하는데 그건 다이렉트가 알아서 해준다.
		// 우리 viewport들어가 
		ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
		ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;

		GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);


		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (nullptr != Rasterizer)
		{
			Rasterizer->Setting();
		}

		std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("TextureShader_PS");
		if (nullptr != PixelShader)
		{
			PixelShader->Setting();
		}




		std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
		if (nullptr != BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}



		// 세팅된 버텍스 버퍼로 그려라.
		// 그린다라는 버튼을 누르지는 않은것.
		// 이게 찍는 버튼이다.

		// 그걸 다시 옵션을 줄수 있는데.
		// 인덱스버퍼를 사용하는 경우 홏룰하는 DRAW함수이다.
	}
}


void GameEngineRenderer::Draw()
{
	std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
	if (nullptr == IndexBuffer)
	{
		return;
	}
	GameEngineCore::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}
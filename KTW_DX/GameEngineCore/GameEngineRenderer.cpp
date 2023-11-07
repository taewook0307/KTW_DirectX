#include "PreCompile.h"
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
#include "GameEngineBlend.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

// ī�޶� ���ο����� ���� ����
void GameEngineRenderer::SetRenderOrder(int _Order)
{

	if (nullptr == Camera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴ� ������ �Դϴ�. ī�޶���� �������ּ���.");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());

}

// �� �ٶ󺸴� ī�޶� ����
void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{
	SetCameraOrder(ECAMERAORDER::Main);
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴµ� �������� �������� �߽��ϴ�.");
		return;
	}

	if (nullptr != Camera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	// ViewInfo[Camera.get()] = _Order;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	RenderBaseInfoValue.RendererScreenPos = GetScreenPosition();

	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->ResSetting();
		Units[i]->Draw();
	}
}

void GameEngineRenderer::Update(float _Delta)
{
	RenderBaseInfoValue.DeltaTime = _Delta;
	RenderBaseInfoValue.AccDeltaTime += _Delta;
}

std::shared_ptr<GameEngineRenderUnit> GameEngineRenderer::CreateAndFindRenderUnit(int _Index)
{
	Units.resize(_Index + 1);

	// ������
	if (nullptr != Units[_Index])
	{
		//����
		return Units[_Index];
	}

	// ������ �����.
	Units[_Index] = std::make_shared<GameEngineRenderUnit>();
	Units[_Index]->SetParentRenderer(this);
	return Units[_Index];
}


void GameEngineRenderer::SetMesh(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMesh(_Name);
}

void GameEngineRenderer::SetMaterial(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMaterial(_Name);

	if (Unit->ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Transform.GetConstTransformDataRef());
	}

	if (Unit->ShaderResHelper.IsConstantBuffer("RenderBaseInfo"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	}

	SetMaterialEvent(_Name, _Index);
}

GameEngineShaderResHelper& GameEngineRenderer::GetShaderResHelper(int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	return Unit->ShaderResHelper;
}

void GameEngineRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{

}

float4 GameEngineRenderer::GetScreenPosition()
{
	float4x4 ViewPort;
	float4 ScreenPos = Transform.GetWorldPosition();
	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);
	ScreenPos *= ViewPort.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();
	return ScreenPos;
}
#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() 
{
}

GameEngineRasterizer::~GameEngineRasterizer() 
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::GetDevice()->CreateRasterizerState(&_Desc, &State))
	{
		MsgBoxAssert("�����Ͷ����� ������ ����µ� �����߽��ϴ�.");
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("������ ������ ������ �������� �۴µ� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineCore::GetContext()->RSSetState(State);
}
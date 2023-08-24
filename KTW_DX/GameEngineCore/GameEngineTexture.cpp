﻿#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

GameEngineTexture::GameEngineTexture()
{
}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}


void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이미지를 수정할수 있는 권한을 '만든다'

	HRESULT Result = GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟뷰 생성에 실패했습니다.");
		return;
	}

}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	// 팩토리니 어뎁터니 

	// png 및 다수의 이미지를 로드 가능한 함수 

	DirectX::LoadFromWICFile(L"안될거 뻔함", DirectX::WIC_FLAGS_NONE, &Data, Image);

	int a = 0;
}
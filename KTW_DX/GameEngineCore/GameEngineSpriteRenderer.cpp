﻿#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"


GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	// 랜더러는 뭐든지 그릴수 있어 니가 세팅만 잘해주면
	// 

	// 부모쪽에서 대부분의 일은 해주고
	GameEngineRenderer::ResSetting();

	// 용도에 의해서
// 여기에서 세팅되는것이 순서상 여기가 맞아.
	//std::shared_ptr<GameEngineTexture> TestTexture = GameEngineTexture::Find("nset.png");
	//if (nullptr == TestTexture)
	//{
	//	MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	//}
	//TestTexture->PSSetting(0);

	CurSprite.Texture->PSSetting(0);


	std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	if (nullptr == Sampler)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	}
	Sampler->PSSetting(0);


	// 내꺼 쪼금더 넣고 

	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(index);
	Transform.SetLocalScale(CurSprite.GetScale());
}
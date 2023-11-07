#include "PreCompile.h"
#include "OldFilm.h"
#include <GameEngineCore/GAMEENGINECORE.H>

OldFilm::OldFilm()
{
}

OldFilm::~OldFilm()
{
}

void OldFilm::Start()
{
	std::shared_ptr<GameEngineLevel> CurLevel = GameEngineCore::GetCurLevel();

	std::shared_ptr<GameEngineCamera> CurCamera = GameEngineCore::GetCurLevel()->GetMainCamera();

	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("OldFilm");
	FilmSprite = GameEngineSprite::Find("OldFilm");
	EffectUnit.ShaderResHelper.SetSampler("FilmTexSampler", "POINT");
}

void OldFilm::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();

	EffectUnit.ShaderResHelper.SetTexture("FilmTex", FilmSprite->GetSpriteData(CurIndex).Texture);

	++CurIndex;

	if (CurIndex >= FilmSprite->GetSpriteCount())
	{
		CurIndex = 0;
	}

	EffectUnit.Render();

	GameEngineRenderTarget::RenderTargetReset();
}
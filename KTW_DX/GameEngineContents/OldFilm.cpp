#include "PreCompile.h"
#include "OldFilm.h"
#include <GameEngineCore/GameEngineCore.h>

OldFilm::OldFilm()
{
}

OldFilm::~OldFilm()
{
}

void OldFilm::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("OldFilm");

	FilmSprite = GameEngineSprite::Find("OldFilm");

	EffectUnit.ShaderResHelper.SetSampler("FilmTexSampler", "POINT");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("OldFilmData", OldFilmDataValue);
}

void OldFilm::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.ShaderResHelper.SetTexture("FilmTex", FilmSprite->GetSpriteData(CurIndex).Texture);

	if (0.0f > Frame)
	{
		++CurIndex;
		Frame = 0.05f;
	}
	else
	{
		Frame -= _DeltaTime;
	}

	if (CurIndex >= FilmSprite->GetSpriteCount())
	{
		CurIndex = 0;
	}

	EffectUnit.Render();

	GameEngineRenderTarget::RenderTargetReset();
}
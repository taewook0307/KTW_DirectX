#pragma once

#include <GameEngineCore/GameEngineRenderTarget.h>

struct OldFilmData
{
	float MulValue = 5.0f;
	float Temp;
	float Temp1;
	float Temp2;
};

// Ό³Έν :
class OldFilm : public Effect
{
public:
	// constrcuter destructer
	OldFilm();
	~OldFilm();

	// delete Function
	OldFilm(const OldFilm& _Other) = delete;
	OldFilm(OldFilm&& _Other) noexcept = delete;
	OldFilm& operator=(const OldFilm& _Other) = delete;
	OldFilm& operator=(OldFilm&& _Other) noexcept = delete;

	void SetOldFilmDataMul(float _Value)
	{
		OldFilmDataValue.MulValue = _Value;

		EffectUnit.ShaderResHelper.SetConstantBufferLink("OldFilmData", OldFilmDataValue);
	}

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	float Frame = 0.05f;

	unsigned int CurIndex = 0;

	std::shared_ptr<GameEngineSprite> FilmSprite;

	OldFilmData OldFilmDataValue;
};
struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut OldFilm_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    
    Result.TEXCOORD.x = Result.TEXCOORD.x / 2.0f + 0.25f;
    Result.TEXCOORD.y = Result.TEXCOORD.y / 2.0f + 0.25f;

    return Result;
}

cbuffer OldFilmData : register(b1)
{
    float MulValue;
    float Temp;
    float Temp1;
    float Temp2;
};

Texture2D FilmTex : register(t0);
SamplerState FilmTexSampler : register(s0);

float4 OldFilm_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = FilmTex.Sample(FilmTexSampler, _Input.TEXCOORD.xy);
    
    Color.x = (1.0f - Color.x) * MulValue;
    Color.yzw = Color.x;
    
    return Color;
}
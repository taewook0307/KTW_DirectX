#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};


// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���Դϴ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
PixelOutPut TextureShader_VS(GameEngineVertex2D _Input) 
{
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ°�
    PixelOutPut Result = (PixelOutPut)0;
    
    // ���� ���ϴ� ���� �̾ȿ� �־��ټ� �־�� �Ѵ�.
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    // Result.TEXCOORD = _Input.TEXCOORD;
    
    // 6�� ���ؽ��� ���ð��̴�.
    Result.TEXCOORD.x = (_Input.TEXCOORD.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (_Input.TEXCOORD.y * Scale2DY) + Pos2DY;
    
    // ���ؽ� ���� ��� �Ǿ��ֳ�?
    
    
    
    return Result;
}

// b���� 14
// t�ؽ�ó 
// s���÷� 
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.
Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
   
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCOORD.xy);
    // ������ �۾��� ����� �Ѵ�.
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    return Color;
}
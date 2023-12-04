#include "Transform.fx"
#include "ParticleHeader.fx"

struct GameEngineParticleVSIn
{
    float4 POSITION : POSITION;
    // �ν��Ͻ����� �׸��� ����� �������� �˷��ش�.
    // �츮�� �� �Ű澵�ʿ䰡 ����.
    uint iInstance : SV_InstanceID;
};


struct GameEngineParticleVSOut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : POSITION;
    uint iInstance : SV_InstanceID; // �ν��Ͻ����� ������ �ؾ߸� ����� ���� ä������.
};

GameEngineParticleVSOut ParticleRender_VS(GameEngineParticleVSIn _Input)
{
    GameEngineParticleVSOut Out = (GameEngineParticleVSOut) 0.0f;
    Out.POSITION = _Input.POSITION;
    Out.iInstance = _Input.iInstance;
    return Out;
}

// inout�� (c++ int&) == (hlsl inout int)
//void Test(inout int Value)
//void Test(int& Value)
//{
//    Value = 200;
//}

struct GameEngineParticleGSOut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_Position;
    float4 UV : TEXCOORD;
    uint iInstance : SV_InstanceID;
};

// ���Ӱ� ���� ��� ���ؽ� ������ ������ִ°����� �����մϴ�.
[maxvertexcount(6)]
void ParticleRender_GS(point GameEngineParticleVSOut _In[1], inout TriangleStream<GameEngineParticleGSOut> _OutStream)
{
    if (0 == ParticleInfoRenderBuffer[_In[0].iInstance].iActive)
    {
        return;
    }
    
    GameEngineParticleGSOut outPut[4] = { (GameEngineParticleGSOut) 0.0f, (GameEngineParticleGSOut) 0.0f, (GameEngineParticleGSOut) 0.0f, (GameEngineParticleGSOut) 0.0f };

    float3 WorldPos = _In[0].POSITION.xyz + ParticleInfoRenderBuffer[_In[0].iInstance].RelativePos.xyz;
    
    float3 ViewPos = mul(float4(WorldPos, 1.0f), ViewMatrix).xyz;
    
    // ���� ���� ���� ��ġ�� ũ�⸦ ���ϱ� ���� ������ �����
    float Ratio = ParticleInfoRenderBuffer[_In[0].iInstance].CurTime / ParticleInfoRenderBuffer[_In[0].iInstance].MaxTime;
    float3 Scale = lerp(StartScale, EndScale, Ratio);
    
    float3 NewPos[4] =
    {
        ViewPos - (float3(-0.5f, 0.5f, 0.0f) * Scale),
        ViewPos - (float3(0.5f, 0.5f, 0.0f) * Scale),
        ViewPos - (float3(0.5f, -0.5f, 0.0f) * Scale),
        ViewPos - (float3(-0.5f, -0.5f, 0.0f) * Scale)
    };

    for (int i = 0; i < 4; ++i)
    {
        outPut[i].POSITION = mul(float4(NewPos[i], 1.0f), ProjectionMatrix);
        outPut[i].iInstance = _In[0].iInstance;
    }
    
    // WVP�� �� ��������.

    outPut[0].UV.xy = float2(1.0f, 1.0f);
    outPut[1].UV.xy = float2(0.0f, 1.0f);
    outPut[2].UV.xy = float2(0.0f, 0.0f);
    outPut[3].UV.xy = float2(1.0f, 0.0f);

    _OutStream.Append(outPut[0]);
    _OutStream.Append(outPut[1]);
    _OutStream.Append(outPut[2]);
    _OutStream.RestartStrip();
    
    _OutStream.Append(outPut[0]);
    _OutStream.Append(outPut[2]);
    _OutStream.Append(outPut[3]);
    _OutStream.RestartStrip();
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
    float4 Color4 : SV_Target4;
    float4 Color5 : SV_Target5;
    float4 Color6 : SV_Target6;
    float4 Color7 : SV_Target7;
};

// SV_Target0
// SV_Target1
// SV_Target2
// SV_Target3
// SV_Target4

PixelOut ParticleRender_PS(GameEngineParticleGSOut _Input)
{
    PixelOut Result = (PixelOut) 0.0f;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.UV.xy);
    
    //if (0.0f >= Color.a)
    //{
    //    clip(-1);
    //}
    
    //if (BaseColorOnly != 0)
    //{
    //    Color = BaseColor;
    //    Color.a = 1;
    //}
    
    Result.Color0 = Color;
    
    if (0 < Target1)
    {
        Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        Result.Color3 = Color;
    }
    
    return Result;
}
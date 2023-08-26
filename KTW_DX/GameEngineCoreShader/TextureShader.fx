#include "Transform.fx"


// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���Դϴ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
float4 TextureShader_VS(float4 pos : POSITION) : SV_POSITION
{
    return mul(pos, WorldViewPorjectionMatrix);
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

float4 TextureShader_PS(float4 pos : SV_Position) : SV_Target0
{
    // �̷� ������� ����ϸ� ���� ���� �������� ������ �Ѵ�.
    // DiffuseTex.Load(int3)

    // ���÷��� ������ ���ؼ� dx�� �˾Ƽ� ������ִ� ������� ó���ϴ°�.
    float4 Color = DiffuseTex.Sample(Sampler, float2(0, 0));

    // �ȿ��� ������� ������ �ƿ� �������� �ʴ´�.
    return Color;
}
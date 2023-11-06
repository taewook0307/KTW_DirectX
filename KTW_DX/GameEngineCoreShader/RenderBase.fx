// ���ؽ� ���̴� �Դϴ�.

// �ܺο��� �־��ִ� ���� ���� �����͵��� ������۶�� �θ���.
// dx11 ���̴������� ������ ���� �����ؾ� �Ѵ�.
// �ܺο��� �������ִ� �����ʹ�
// ������۰� ���԰��信 �ش��մϴ�.
// 16���� ������ �ְ� �Ⱦ��ִ� �����̴�.
// � ���̴��� �����Ҷ� �����͸� 16������ ����ϰ� �ִ�.
// �־��ִ°� ��Ե� �ȴٰ� �ص�. 
// b�� buffer�� ����
// 0 ������ index ������Ѻ��� 14 ���� ����Ѵ�.
cbuffer RenderBaseInfo : register(b11)
{
    float4 BaseColor;
    int IsMask;
    int BaseColorOnly;
    int MaskMode;
    int BaseTemp2;
    float4 RendererScreenPos;
    float4 RenderScreenScale;
    float4 MaskScreenScale;
    float4 MaskPivot;
    float4 VertexUVPlus;
    float4 VertexUVMul;
    float DeltaTime;
    float AccDeltaTime;
    int Target0;
    int Target1;
    int Target2;
    int Target3;
    int Target4;
    int Target5;
    int Target6;
    int Target7;
};
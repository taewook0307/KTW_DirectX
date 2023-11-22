#include "RenderBase.fx"
#include "Function.fx"


struct ParticleShareData
{
    uint iAliveCount;
    uint iPadding0;
    uint iPadding1;
    uint iPadding2;
};

struct ParticleInfoData
{
    // ������ġ
    float4 RelativePos;
    
    // ���ư��� ����
    float4 Dir;
    
    // �״½ð�
    float MaxTime;
    
    // ������� ����� �ð�
    float CurTime;
    
    // �̵��Ҷ��� ���ǵ�
    float Speed;
    
    // �� �׾��� ��Ҵ�.
    uint iActive;
};

cbuffer ParticleUpdateInfo : register(b7)
{
	// ��ƼŬ�� �ִ� ����� ���� ���ϰų�?
    int ParticleMaxCount;
	// ��ƼŬ�� ���� �������� �����ǳ�
	// 1�̸� �ڱ� ��ġ�� �����°ɷ� ���ϴ�
    int IsWorldSpawn;
	// ������ ����
	// ��ƼŬ�� ��������� ����
    float SpawnRange;
    float MinSpeed;
    float MaxSpeed;
    float MaxLife;
    float Temp;
    float4 ObjectWorldPos; // ���ͳ� �������� ���� ������
};

// �׷���
RWStructuredBuffer<ParticleShareData> ParticleShareBuffer : register(u0);

// �Ʒ� �޸𸮴� 100�� �� �����忡�� 100���� �迭�� �ڱⲬ �˾Ƽ� �а�ġ�� �����̱� ������ ������ 
// ������ ����.
RWStructuredBuffer<ParticleInfoData> ParticleInfoBuffer : register(u1);

[numthreads(128, 1, 1)]
void ParticleUpdate_CS(uint3 _id : SV_DispatchThreadID)
{
    
    if (ParticleMaxCount <= _id.x)
    {
        return;
    }
    
    // ���� ��Ȱ��ȭ�� ��ƼŬ�̹Ƿ� �� ��ƼŬ�� ������ ������ �����ؾ� �Ѵ�.
    if (0 == ParticleInfoBuffer[_id.x].iActive)
    {
        // ũ�ٸ� �ڱ� �ڽ��� ������ϴ� �༮������ Ȯ���Ѵ�.
        while (0 < ParticleShareBuffer[0].iAliveCount)
        {
            int iOriginValue = ParticleShareBuffer[0].iAliveCount;
            // ���� �׾������ϱ�.
            int iExchange = iOriginValue - 1;
            
            // ������ �ݴϴ�.
            InterlockedCompareExchange(ParticleShareBuffer[0].iAliveCount, iOriginValue, iExchange, iExchange);
            
            // ����ȭ�� ���� ������� �ʾҴٸ�
            if (iOriginValue == iExchange)
            {
                ParticleInfoBuffer[_id.x].iActive = 1;
                break;
            }
        }
        
        // �̳༮�� Ȱ��ȭ �˴ϴ�.
        if (0 != ParticleInfoBuffer[_id.x].iActive)
        {
            
        }

    }
    // �����̴� ���ؾ��մϴ�
    else
    {
        
    }
        
    
    // �����带 ���� 
    // SV_DispatchThreadID
    
    
    // ���� ���⼭ ��ƼŬ�� ����ؾ� ����.
    
    ParticleShareBuffer[0].iAliveCount = 1;
}
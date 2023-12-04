#include "Random.fx"

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
    float iActive;
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
    float Temp0;
    float Temp1;
    float4 ObjectWorldPos; // ���ͳ� �������� ���� ������
    float4 StartScale; // ���ͳ� �������� ���� ������
    float4 EndScale; // ���ͳ� �������� ���� ������
};

// UAV
// �׷���
RWStructuredBuffer<ParticleShareData> ParticleShareBuffer : register(u0);
// �Ʒ� �޸𸮴� 100�� �� �����忡�� 100���� �迭�� �ڱⲬ �˾Ƽ� �а�ġ�� �����̱� ������ ������ 
// ������ ����.
RWStructuredBuffer<ParticleInfoData> ParticleInfoBuffer : register(u1);

// SRV
// �׷���
StructuredBuffer<ParticleShareData> ParticleShareRenderBuffer : register(t11);
// �Ʒ� �޸𸮴� 100�� �� �����忡�� 100���� �迭�� �ڱⲬ �˾Ƽ� �а�ġ�� �����̱� ������ ������ 
// ������ ����.
StructuredBuffer<ParticleInfoData> ParticleInfoRenderBuffer : register(t12);

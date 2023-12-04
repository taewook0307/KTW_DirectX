#include "ParticleHeader.fx"

[numthreads(128, 1, 1)]
void ParticleUpdate_CS(uint3 _id : SV_DispatchThreadID)
{
    
    if ((uint) ParticleMaxCount <= _id.x)
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
            float4 RandomVector = RandomFloat4(_id.x, ParticleMaxCount);
            
            float Random = RandomVector.x * 3.141592f * 2.0f;

            // ������ xy��ġ�� �̰�
            ParticleInfoBuffer[_id.x].RelativePos.xy = float2(cos(Random), sin(Random)) * RandomVector.y * SpawnRange;
            ParticleInfoBuffer[_id.x].RelativePos.z = 0.0f;
            
            ParticleInfoBuffer[_id.x].Dir.xy = normalize(ParticleInfoBuffer[_id.x].RelativePos.xy);

            if (0 != IsWorldSpawn)
            {
                ParticleInfoBuffer[_id.x].RelativePos += ObjectWorldPos;
            }
            
            // ������ �ӷ�
            ParticleInfoBuffer[_id.x].Speed = RandomVector.z * (MaxSpeed - MinSpeed) + MinSpeed;
            
            ParticleInfoBuffer[_id.x].CurTime = 0.0f;
            ParticleInfoBuffer[_id.x].MaxTime = MaxLife;
        }
    }
    // �����̴� ���ؾ��մϴ�
    else
    {
        ParticleInfoBuffer[_id.x].CurTime += DeltaTime;

        if (ParticleInfoBuffer[_id.x].MaxTime < ParticleInfoBuffer[_id.x].CurTime)
        {
            // �ٽ� �״°̴ϴ�.
            ParticleInfoBuffer[_id.x].iActive = 0;
        }
        else
        {
            ParticleInfoBuffer[_id.x].RelativePos += ParticleInfoBuffer[_id.x].Dir * ParticleInfoBuffer[_id.x].Speed * DeltaTime;
        }
    }
    
    
    // ������Ʈ �Ϸ�
}


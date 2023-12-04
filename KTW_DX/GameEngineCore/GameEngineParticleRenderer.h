#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineComputeUnit.h"

struct ParticleUpdateInfo
{
	// ��ƼŬ�� �ִ� ����� ���� ���ϰų�?
	int ParticleMaxCount = 100;
	// ��ƼŬ�� ���� �������� �����ǳ�
	// 1�̸� �ڱ� ��ġ�� �����°ɷ� ���ϴ�
	int IsWorldSpawn = 1;
	// ������ ����
	// ��ƼŬ�� ��������� ����
	float SpawnRange = 100.0f;
	float MinSpeed = 100.0f;
	float MaxSpeed = 100.0f;
	float MaxLife = 100.0f;
	float Temp0;
	float Temp1;
	float4 ObjectWorldPos; // ���ͳ� �������� ���� ������
	float4 StartScale = float4::ONE * 100.0f; // ���ͳ� �������� ���� ������
	float4 EndScale = float4::ONE * 100.0f; // ���ͳ� �������� ���� ������
};

struct ParticleShareData
{
	// ���� ��� ����ֳ�?
	unsigned int iAliveCount;
	unsigned int iPadding0;
	unsigned int iPadding1;
	unsigned int iPadding2;
};

struct ParticleInfoData
{
	float4 RelativePos;
	float4 Dir;
	float MaxTime;
	float CurTime;
	float Speed;
	float iActive;
};


// ���� :
class GameEngineParticleRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineParticleRenderer();
	~GameEngineParticleRenderer();

	// delete Function
	GameEngineParticleRenderer(const GameEngineParticleRenderer& _Other) = delete;
	GameEngineParticleRenderer(GameEngineParticleRenderer&& _Other) noexcept = delete;
	GameEngineParticleRenderer& operator=(const GameEngineParticleRenderer& _Other) = delete;
	GameEngineParticleRenderer& operator=(GameEngineParticleRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	ParticleUpdateInfo ParticleUpdateInfoValue;
	GameEngineComputeUnit UpdateUnit;
	std::shared_ptr<GameEngineStructuredBuffer> ParticleShareBuffer;
	float Frequency = 5.0f;
};


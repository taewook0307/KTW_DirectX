#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

class GameEngineShaderResources
{
public:
	std::string Name; // Transformdata <= ���̴����� ����ϴ� ���ҽ��� �̸�
	class GameEngineShader* ParentShader; // <= �� ����ϴ� ���̴�
	int BindPoint = -1; // <= b0 t0 s0 ... s1 s2 s3, b1 b2 b3 ��� ������۳�

public:
	virtual void Setting() = 0;
	virtual void Reset() = 0;
};

// �� ���̴��� ������۸� � ����ϳ�
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:

	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:

	void Setting() override;
	void Reset() override;
};

// ���� : ���̴� ���ҽ� ���۴� 2���� ������ �մϴ�.
//       1. Ư�� ���̴��� � ���ҽ����� ������ �ִ��ĸ� ���縦 ���ִ� ������
//       2. Ư�� �������� � ���ҽ����� �����ؾ��ϴ����� ���� ���� <= ��Ƽ������ �ؾ��Ѵ�.

// �̰� ����Ե� ������ <= �׷� ������ ���ҽ��� ������ �̸����� �����ϱ� ���ؼ� 
// SetConstBuffer(0, TransData);
// SetConstBuffer("TransformData", TransData);

class GameEngineShaderResHelper
{
public:
	// constrcuter destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	// delete Function
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _Other) noexcept = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper& operator=(GameEngineShaderResHelper&& _Other) noexcept = delete;

	// ���̴��� �����ϵ� �ڵ� �����
	void ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode);

protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};


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
// ������۰� �ƴ϶�.
// ������۸� �̿��ϴ� Ŭ����
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;

	const void* CPUDataPtr = nullptr;
	UINT DataSize = -1;

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineSampler> Res;

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
	void ShaderResCheck(std::string _FunctionName, class GameEngineShader* _Shader, ID3DBlob* _CompileCode);

	void ShaderResCopy(class GameEngineShader* _Shader);

	void AllShaderResourcesSetting();

	bool IsConstantBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return ConstantBufferSetters.contains(UpperString);
	}

	bool IsTexture(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return TextureSetters.contains(UpperString);
	}

	bool IsSampler(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return SamplerSetters.contains(UpperString);
	}

	// ���⿡ ������ ���ϴ�.
	template<typename DataType>
	void SetConstantBufferLink(std::string_view _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, &_Data, sizeof(_Data));
	}

	void SetConstantBufferLink(std::string_view _Name, const void* _Data, size_t _Size);

	void SetTexture(std::string_view _Name, std::string_view _TextureName);

	void SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture);

	void SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler);

	void ResClear();

protected:

private:
	// std::shared_ptr�� ����� 
	// �װ� ����� �س����ϱ� ������.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};


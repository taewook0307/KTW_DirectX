#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineStructuredBuffer.h"

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
	int DataSize = -1;

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

class GameEngineStructedBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineStructuredBuffer> Res;

	const void* CPUDataPtr = nullptr;
	int DataSize = -1;
	int DataCount = -1;

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

	// ���̴��� �����ϵ� �ڵ� �����
	void ShaderResCheck(std::string _FunctionName, class GameEngineShader* _Shader, ID3DBlob* _CompileCode);

	void ShaderResCopy(class GameEngineShader* _Shader);

	void AllShaderResourcesReset();
	void AllShaderResourcesSetting();

	bool IsConstantBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return ConstantBufferSetters.contains(UpperString);
	}

	bool IsStructedBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return StructedBufferSetters.contains(UpperString);
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

	void SetConstantBufferLink(std::string_view _Name, const void* _Data, int _Size);

	void SetTexture(std::string_view _Name, std::string_view _TextureName, bool _SamplerCheck = true);

	void SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture, bool _SamplerCheck = true);

	void SetSampler(std::string_view _Name, std::string_view _SamplerName);

	void SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler);

	void ResClear();

	template<typename DataType>
	void SetStructedBufferLink(std::string_view _Name, const std::vector<DataType>& _ArrData)
	{
		if (true == _ArrData.empty())
		{
			MsgBoxAssert(std::string(_Name) + "������ 0���� �����͸� ��Ʈ��ó�� ���ۿ� �����Ϸ��� �߽��ϴ�.");
		}

		SetStructedBufferLink(_Name, &_ArrData[0], sizeof(DataType), static_cast<int>(_ArrData.size()));
	}

	void SetStructedBufferLink(std::string_view _Name, const void* _Data, int _Size, int _Count);


protected:

private:
	// std::shared_ptr�� ����� 
	// �װ� ����� �س����ϱ� ������.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
	std::multimap<std::string, GameEngineStructedBufferSetter> StructedBufferSetters;

};


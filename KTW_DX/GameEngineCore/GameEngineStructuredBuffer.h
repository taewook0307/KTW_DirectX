#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

enum class StructuredBufferType
{
	NONE,
	SRV_ONLY, // => ���̴� ���ҽ��θ� ����ϰڴ�.
	UAV_INC, // => ��ǻƮ ���̴��� �־ ����ϰ� ������� ���� �ްڴ�.
};


// ��Ʈ��ó�� ���۴� �������� �������� ũ�⵵ �����Ҽ� �־��.
// �޸𸮸� �Ʋ��� �Ѵ�.
// �̳༮�� ������۶� ����ϰ� �⺻ ���谡 �޶����� �մϴ�.

// ���� :
class GameEngineStructuredBuffer : public GameEngineResources<GameEngineStructuredBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();

	// delete Function
	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _Other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer& operator=(GameEngineStructuredBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineStructuredBuffer> Find(int _Byte)
	{
		if (false == StructuredBufferRes.contains(_Byte))
		{
			return nullptr;
		}

		return StructuredBufferRes[_Byte];
	}

	static std::shared_ptr<GameEngineStructuredBuffer> CreateAndFind(int _Byte, std::string_view _Name, D3D11_SHADER_BUFFER_DESC _BufferDesc, void* _StartData = nullptr)
	{
		std::shared_ptr<GameEngineStructuredBuffer> FindBuffer = Find(_Byte);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr<GameEngineStructuredBuffer> NewBuffer = CreateRes();
		NewBuffer->DataSize = _Byte;
		return NewBuffer;
	}

	void CreateResize(int _Byte, int _Count, StructuredBufferType _Type, const void* _StartData = nullptr);

	void Release();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	void VSReset(UINT _Slot);
	void PSReset(UINT _Slot);

	void ChangeData(const void* _Data, size_t _Size);

protected:


private:
	ID3D11ShaderResourceView* SRV = nullptr; // ���̴��� �������ټ� �ִ� ����.
	ID3D11UnorderedAccessView* UAV = nullptr; // ��ǻƮ���̴����� ����� �޾ƿ��� �뵵�� ����.
	D3D11_MAPPED_SUBRESOURCE SettingResources;
	int DataSize = 0;
	int DataCount = 0;
	StructuredBufferType Type = StructuredBufferType::NONE;

	// 
	//                         ��üũ�Ⱑ x
	//                        40����Ʈũ���� 10�� ����
	//                        40����Ʈ�� �ǹ��Ѵ�.
	static std::map<int, std::shared_ptr < GameEngineStructuredBuffer>> StructuredBufferRes;
};


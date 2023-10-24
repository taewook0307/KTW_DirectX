#pragma once
#include <vector>
#include "GameEngineDebug.h"
#include "GameEngineMath.h"

// ���������� ��ǻ���� ��� �����ʹ� ����Ʈ ������ �Ҽ� �ִ�.
// �� ����Ʈ ����� ���� ���ϴ� ��ŭ ���� ���ϴ� ������ 
// �о���̰ų� ��Ʈ���Ҽ� �ְ� ������ִ� Ŭ���� �̴�.

// ���� :
class GameEngineSerializer
{
public:
	// constrcuter destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	void Write(const void* Data, unsigned int _Size);
	void operator<<(std::string_view _Value);
	void operator<<(const std::string& _Value);
	void operator<<(const int& _Value);
	void operator<<(const unsigned int& _Value);
	void operator<<(const uint64_t& _Value);
	void operator<<(const float& _Value);
	void operator<<(const bool& _Value);
	void operator<<(const float4& _Value);
	void operator<<(const float4x4& _Value);

	void Read(void* Data, unsigned int _Size);
	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(uint64_t& _Value);
	void operator>>(float& _Value);
	void operator>>(bool& _Value);
	void operator>>(float4& _Value);
	void operator>>(float4x4& _Value);

	std::string_view GetStringView();

	//// delete Function
	//GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	//GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	//GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	//GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	void BufferResize(size_t _BufferSize)
	{
		Data.resize(_BufferSize);
	}

	size_t GetBufferSize()
	{
		return Data.size();
	}

	size_t GetWriteOffset()
	{
		return WriteOffset;
	}


	template<typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}

protected:

private:
	// �ϰ� ���� ���� �ٸ��� �����̰�.
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;

	// �̷� Ŭ������ �ִٸ�
	// ���� ���ų� ���ϼ��� �ִ�.
	std::vector<char> Data;
};


// �̷� Ŭ������ �׳� �����ص� �ǿ�.
//struct PlayData
//{
//	int A;
//	int B;
//	int C;
//};

// 
//struct PlayData
//{
//	int A;
//	int B;
//	int C;
// std::string Name;
//};

class GameEngineSerializerObject
{
public:
	// ��ü => File(byte ���)
	virtual void Serializer(GameEngineSerializer& _Data) = 0;

	// File(byte ���) => ��ü
	virtual void DeSerializer(GameEngineSerializer& _Data) = 0;
};
#pragma once
#include <vector>

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

	template<typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}

protected:

private:
	// �̷� Ŭ������ �ִٸ�
	// ���� ���ų� ���ϼ��� �ִ�.
	std::vector<char> Data;
};


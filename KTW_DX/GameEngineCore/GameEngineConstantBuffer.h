#pragma once
#include "GameEngineDirectBuffer.h"
// #include "GameEngineShader.h"

// ���� :
class GameEngineConstantBuffer :
	public GameEngineResources<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, std::string_view _Name, D3D11_SHADER_BUFFER_DESC _BufferDesc)
	{
		if (ConstantBuffers.end() == ConstantBuffers.find(_Byte))
		{
			// �� ũ���� ������۰� �������� �ʴ´�.
			ConstantBuffers[_Byte];
		}

		std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>& Buffers = ConstantBuffers[_Byte];

		std::string UpperName = GameEngineString::ToUpperReturn(_Name.data());

		if (Buffers.end() != Buffers.find(UpperName))
		{
			return ConstantBuffers[_Byte][UpperName];
		}

		std::shared_ptr<GameEngineConstantBuffer> Res = GameEngineResources::CreateRes();
		Res->SetName(UpperName);
		Res->BufferDesc = _BufferDesc;
		ConstantBuffers[_Byte][UpperName] = Res;
		Res->ResCreate(_Byte);
		return Res;
	}

	template<typename DataType>
	void ChangeData(const DataType& _Data)
	{
		ChangeData(&_Data, sizeof(DataType));
	}

	// 1����Ʈ �ڷ���
	void ChangeData(const void* _Data, UINT _Size);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

protected:

private:
	D3D11_SHADER_BUFFER_DESC BufferDesc;

	// ShaderType Type = ShaderType::None;
	// int Slot = 0;

	// �ڷᱸ���� Resources�� �ٸ��� �ٸ��� ������ �־�� �Ѵ�.
	//            500byte         transformdata
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBuffers;

	void ResCreate(int _ByteSize);
};


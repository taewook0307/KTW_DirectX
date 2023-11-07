#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBuffers;

GameEngineConstantBuffer::GameEngineConstantBuffer() 
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer() 
{
}

void GameEngineConstantBuffer::ResCreate(int _ByteSize)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.ByteWidth = _ByteSize;

	// �ȹٲ�
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	//                                                                 �ʱ�ȭ
	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "��������� ���� ������۸� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineCore::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "��������� ���� ������۸� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineCore::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgBoxAssert(Name + "nullptr�� �����͸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ũ�Ⱑ �ٸ�
	if (_Size != BufferInfo.ByteWidth)
	{
		std::string Name = GetName().data();
		MsgBoxAssert(Name + "ũ�Ⱑ �ٸ� �����ͷ� ������۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// �׷���ī��� �ʰ������ ������ ������ 
	// ���������� �����Ѵ�.
	// �׷��Ƿ� �����͸� CPU���� �����͸� �����Ѵٴ� ����
	// �׷���ī�忡�� �����ϴ� ���°� �˴ϴ�.
	// �׸��� �׷� ���� ��κ��� �׷���ī�带 ������ ����ϴ�.
	// ��� �׸��°� ����� �׸��µ� �ʿ��� �����͸� ���� �����Ծ�
	// �ִ��� 1���� �����ϴ� ������ �ְ��.
	// map�� ȣ���ϴ� Ƚ���� ������.
	// ���Ͱ� ��� �ڷᱸ���߿��� ���� ���� ������ ���⿡ �ֽ��ϴ�.
	// ������ �׷������� ¥�� ���Ǽ��� ������ ����� ������ �׳� ���� �Ұ̴ϴ�.
	
	// �� ���۸� ��� ������ ��� ������ �����Ұž�.
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// �׷���ī�忡 ���� �����ִ� �ּҰ��� ����ݴϴ�.
	// Data

	if (Data.pData == nullptr)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "���� ���� ������ ���� ���߽��ϴ�.");
		return;
	}

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);
	


	// �ٽ��.
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}
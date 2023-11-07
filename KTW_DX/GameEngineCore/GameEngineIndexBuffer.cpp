#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer() 
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer() 
{
}


void GameEngineIndexBuffer::ResCreate(const void* _Data, size_t _IndexCount)
{
	IndexCount = static_cast<UINT>(_IndexCount);

	// ���۴� ������� ���ߵ��� 
	// ���� �뵵�� ���ž�?
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(IndexSize * IndexCount);

	// �ȹٲ�
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	// ID3D11Buffer* Arr[1];

	if (nullptr == Buffer)
	{
		MsgBoxAssert("����������� ���� ���ؽ� ���۸� ������ ���� �����ϴ�.");
	}


	// ���ؽ����۸� ������ �־��ټ� �ִ�.
	GameEngineCore::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
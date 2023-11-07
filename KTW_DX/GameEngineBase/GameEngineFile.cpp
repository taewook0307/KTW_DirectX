#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include <filesystem>

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

GameEngineFile::GameEngineFile(const std::string& _path)
	: GameEnginePath(_path)
{

}


void GameEngineFile::Open(FileOpenType _OpenType, FileDataType _DataType)
{

	// C�������� �������� �Ҿƹ��� �Լ��� ����� �̴ϴ�.
	// �ٲ����� �����.

	std::string Path = GameEngineFile::GetStringPath();

	std::string Mode = "";

	switch (_OpenType)
	{
	case FileOpenType::Write:
		Mode += "w";
		break;
	case FileOpenType::Read:
		Mode += "r";
		break;
	default:
		break;
	}

	switch (_DataType)
	{
	case FileDataType::Binary:
		Mode += "b";
		break;
	case FileDataType::Text:
		Mode += "t";
		break;
	default:
		break;
	}

	// "rb" �аڴ� ���̳ʸ���
	// "rt" �аڴ� Text��
	
	// "wb" �аڴ� ���̳ʸ���
	// "wt" �аڴ� Text��

	fopen_s(&FilePtr, Path.c_str(), Mode.c_str());

	OpenType = _OpenType;
	DataType = _DataType;


	if (false == IsExits() && OpenType == FileOpenType::Read)
	{
		MsgBoxAssert("�������� �ʴ� ������ ��� �������� �ؽ��ϴ�.");
	}
}

void GameEngineFile::DataAllRead(class GameEngineSerializer& _Data)
{
	_Data.BufferResize(GetFileSize<size_t>());
	Read(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

void GameEngineFile::Read(void* _Data, size_t _Size)
{
	//void* _Buffer, �о�帰 �����͸� �� ������ ��ġ
	//size_t _BufferSize, // ������ ũ��
	//size_t _ElementSize, // ���� �� 50
	//size_t _ElementCount, // ���� Ƚ�� 2
	//FILE* _Stream 


	if (nullptr == FilePtr)
	{
		MsgBoxAssert("������ ���� ������ �������� �߽��ϴ�. Open�� ���� �������ּ���.");
	}

	if (OpenType != FileOpenType::Read)
	{
		MsgBoxAssert("�б� ���� ������ ���� �����Դϴ�.");
	}

	fread_s(_Data, _Size, _Size, 1, FilePtr);
}

uintmax_t GameEngineFile::GetFileSize()
{
	// c �Լ��� ����ߴµ� 
	return std::filesystem::file_size(Path);
}

void GameEngineFile::Write(class GameEngineSerializer& _Data)
{
	Write(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

// ���Ͽ��� �����͸� ����.
void GameEngineFile::Write(void* _Data, size_t _Size)
{
	if (nullptr == FilePtr)
	{
		MsgBoxAssert("������ ���� ������ �������� �߽��ϴ�. Open�� ���� �������ּ���.");
	}

	if (OpenType != FileOpenType::Write)
	{
		MsgBoxAssert("���� ���� ������ ���� �����Դϴ�.");
	}

	fwrite(_Data, _Size, 1, FilePtr);

}
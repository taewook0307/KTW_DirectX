#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"
#include <string>

// Ostream Istream
// �װ� ���ο��� ���� ���� �Լ��� ���� �־��.

enum class FileOpenType
{
	Write,
	Read,
};

enum class FileDataType
{
	Binary,
	Text,
};

// ���� :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _path);
	~GameEngineFile();

	//// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	// �ü������ ����� �þƼ� �� ������ �������� �����ϰų� �аڽ��ϴ�.
	void Open(FileOpenType _OpenType, FileDataType _DataType, bool _IsStartAllData = true);

	// ���Ͽ��� �����͸� �о�帰��.
	void Read(void* _Data, size_t _Size);

	// ���Ͽ��� �����͸� ����.
	void Write(void* _Data, size_t _Size);

	// 8����Ʈ ������
	template<typename ReturnType>
	ReturnType GetFileSize()
	{
		return static_cast<ReturnType>(GetFileSize());
	}

	uintmax_t GetFileSize();

	std::string_view GetStringView();

protected:

private:
	FILE* FilePtr = nullptr;
	FileOpenType OpenType;
	FileDataType DataType;
	GameEngineSerializer Serializer;
};

